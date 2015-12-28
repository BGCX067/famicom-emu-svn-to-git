#include "tv_set.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "win32_resolver.h"
#include "random_generator.h"

void audio_callback(void *userdata, Uint8 *stream, int len);

TV_Set::TV_Set(unsigned screen_width, unsigned screen_height) : screen(0), frame_height(screen_height), frame_width(screen_width)
{    
}

TV_Set::~TV_Set()
{
}

void
TV_Set::initialize()
{
this->init_random_generator();
this->init_win32_functions();
this->init_video();
this->init_audio();
}

void
TV_Set::finalize()
{
this->shutdown_video();
this->shutdown_audio();
}

//========================================================================
// Initializers
//========================================================================
void
TV_Set::init_random_generator()
{
srand(time(NULL));
}

void
TV_Set::init_video()
{
SDL_WM_SetCaption("TV", "Famicom TV");
screen = SDL_SetVideoMode(this->frame_width, this->frame_height, 32, SDL_SWSURFACE);
if (!screen)
    {
    std::cout << "Could not set screen " << std::endl;
    exit(-1);
    }
this->sdl_window_handle = this->get_sdl_window_handle();
this->move_tv_window_to_the_right_of_gui_window();

this->load_SDL_palette();
this->build_32bpp_palette();
this->clear_frame_buffer();
}

void
TV_Set::init_audio()
{
 SDL_AudioSpec* desired_audio_spec = new SDL_AudioSpec;
 SDL_AudioSpec* obtained_audio_spec = new SDL_AudioSpec;
 desired_audio_spec->freq = 44100;
 desired_audio_spec->format = AUDIO_S16;
 desired_audio_spec->channels = 1;
 desired_audio_spec->samples = 512;
 desired_audio_spec->callback = audio_callback;
 desired_audio_spec->userdata = NULL;

 if ( SDL_OpenAudio(desired_audio_spec, obtained_audio_spec) < 0 )
    {
     std::cout << "Could not open audio " << std::endl;
     exit(-1);
    }
 delete desired_audio_spec;
 delete obtained_audio_spec;
 SDL_PauseAudio(0);
}



//========================================================================
// Finalizers
//========================================================================
void
TV_Set::shutdown_audio()
{
SDL_PauseAudio(1);
SDL_CloseAudio();
}

void
TV_Set::shutdown_video()
{
SDL_FreeSurface(this->screen);
this->screen = 0;
}


//========================================================================
// Win32 Helpers
//========================================================================
void
TV_Set::init_win32_functions()
{
Win_Resolver* resolver = new Win_Resolver();
this->get_window_rect = resolver->resolve_get_window_rect();
this->move_window = resolver->resolve_move_window();
delete resolver;
}

void
TV_Set::set_parent_window_id(HWND parent_window_id)
{
this->parent_window_id = parent_window_id;
}


HWND
TV_Set::get_sdl_window_handle()
{
struct SDL_SysWMinfo wmInfo;
SDL_VERSION(&wmInfo.version);

int ret = SDL_GetWMInfo(&wmInfo);
if (ret != 1)
{
    std::cout << "SDL_GetWMInfo failed!" << std::endl;
    exit(1);
}

return wmInfo.window;
}


void
TV_Set::move_tv_window_to_the_right_of_gui_window()
{
LPRECT parent_window_rectangle = new RECT;
this->get_window_rect(this->parent_window_id, parent_window_rectangle);
int new_x = parent_window_rectangle->right;
int new_y = parent_window_rectangle->top;
delete parent_window_rectangle;

bool must_repaint_window = true;
this->move_window(this->sdl_window_handle, new_x, new_y, this->frame_width, this->frame_height, must_repaint_window);
}


//========================================================================
// Common Video Helpers
//========================================================================
void
TV_Set::clear_frame_buffer()
{
 SDL_LockSurface(screen);
 SDL_FillRect(screen, NULL, 0);
 SDL_UnlockSurface(screen);
}


//8bpp only
void
TV_Set::load_SDL_palette()
{
 unsigned brightness = 0;
 unsigned brightness_step = FULL_BRIGHTNESS / TOTAL_GRAYSCALE_COLORS;

 for (unsigned color = 0; color < TOTAL_GRAYSCALE_COLORS; color++)
        {
        sdl_colors[color].r = brightness;
        sdl_colors[color].g = brightness;
        sdl_colors[color].b = brightness;
        brightness += brightness_step;
        }
}

//Warning - requires "load_SDL_palette" executed previously
void
TV_Set::build_32bpp_palette()
{
 for (unsigned color = 0; color < TOTAL_GRAYSCALE_COLORS; color++)
        {
        ppu_32bpp_colors[color] = SDL_MapRGB(this->screen->format, sdl_colors[color].r, sdl_colors[color].g, sdl_colors[color].b);
        }
} 

void
TV_Set::run()
{
    SDL_LockSurface(screen);
    unsigned* p = (unsigned *) this->screen->pixels;

    for (unsigned y = 0; y < this->frame_height; y++)
        for (unsigned x = 0; x < this->frame_width; x++)
        {
            unsigned color_index = (unsigned) RANDOM(D_TOTAL_GRAYSCALE_COLORS);
            *p = ppu_32bpp_colors[color_index];
            p++;
        }

    SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_UnlockSurface(screen);
}

//========================================================================
// Common Audio Helpers
//========================================================================
void
TV_Set::mute_audio()
{
    SDL_PauseAudio(1);
}

void
TV_Set::unmute_audio()
{
    SDL_PauseAudio(0);
}

unsigned char* generate_white_noise(int len);
unsigned char* generate_square_wave(int len);
unsigned char* generate_triangle_wave(int len);
typedef unsigned char* (*audio_generator) (int);

audio_generator ag = generate_white_noise;
//audio_generator ag = generate_square_wave;
//audio_generator ag = generate_triangle_wave;

void
audio_callback(void *userdata, Uint8 *stream, int len)
{
 unsigned char* next_audio_samples = ag(len);
 memcpy((void*) stream, (void*) next_audio_samples, len * sizeof(unsigned char));
 delete next_audio_samples;
}

unsigned char*
generate_white_noise(int len)
{
 unsigned char* samples = new unsigned char[len];
 unsigned char* s = samples;
 const Uint16 loudness = 32;

 for (int i = 0; i < len / 2; i++)
     {
     Uint16 sample = (unsigned char) RANDOM(loudness);
     *s = (sample & 0xFF00) >> 8;
     s++;
     *s = sample & 0xFF;
     s++;
     }

 return samples;
}

unsigned char*
generate_square_wave(int len)
{
    const double frequency_in_hertz = 220;
    const unsigned sampling_rate = 44100;
    const unsigned frequency_in_samples = (unsigned) (double) sampling_rate / frequency_in_hertz;
    const unsigned half_cycle_in_samples = frequency_in_samples / 2;

    static int pulse_state = 0;
    static unsigned cycle_pos = 0;

    unsigned char* samples = new unsigned char[len];
    unsigned char* s = samples;
    const Uint16 loudness = 10;

    for (int i = 0; i < len / 2; i++)
    {
        Uint16 sample = 0;

        if (pulse_state == 0)
        {
            sample = loudness;
        }
        else
        {
            sample = -loudness;
        }

        *s = (sample & 0xFF00) >> 8;
        s++;
        *s = sample & 0xFF;
        s++;

        cycle_pos++;
        if (cycle_pos == half_cycle_in_samples)
        {
            if (pulse_state == 0)
                pulse_state = 1;
            else
                pulse_state = 0;
            cycle_pos = 0;
        }

    }


   return samples;
}


unsigned char*
generate_triangle_wave(int len)
{
    const double frequency_in_hertz = 220;
    const unsigned sampling_rate = 44100;
    const unsigned frequency_in_samples = (unsigned) (double) sampling_rate / frequency_in_hertz;
    const unsigned half_cycle_in_samples = frequency_in_samples / 2;


    unsigned char* samples = new unsigned char[len];
    unsigned char* s = samples;
    const Uint16 loudness = 40;

    const double triangle_step = (double) loudness * 2.0 / (double) half_cycle_in_samples;
    static int pulse_state = 0;
    static unsigned cycle_pos = 0;
    static double accumulated_step = 0.0;

    for (int i = 0; i < len / 2; i++)
    {
        Uint16 sample = 0;

        if (pulse_state == 0)
        {
            sample = - loudness + (Uint16) accumulated_step;
            accumulated_step += triangle_step;
        }
        else
        {
            sample = loudness + (Uint16) accumulated_step;
            accumulated_step -= triangle_step;
        }

        *s = (sample & 0xFF00) >> 8;
        s++;
        *s = sample & 0xFF;
        s++;

        cycle_pos++;
        if (cycle_pos == half_cycle_in_samples)
        {
            if (pulse_state == 0)
                pulse_state = 1;
            else
                pulse_state = 0;

            cycle_pos = 0;
            accumulated_step = 0.0;
        }

    }


   return samples;
}


