#ifndef TV_SET_H
#define TV_SET_H

#include "SDL.h"
#include "win32_resolver.h"


#define TOTAL_GRAYSCALE_COLORS 64
#define D_TOTAL_GRAYSCALE_COLORS 64.0 //Expressed as a double
#define FULL_BRIGHTNESS 256

class SDL_Surface;

class TV_Set
{
public:
    TV_Set(unsigned screen_width, unsigned screen_height);
    ~TV_Set();    
    void initialize();
    void finalize();
    void run();
    void mute_audio();
    void unmute_audio();

    void set_parent_window_id(HWND parent_window_id);
    void move_tv_window_to_the_right_of_gui_window();

private:
    void init_video();
    void init_audio();
    void init_random_generator();
    void shutdown_audio();
    void shutdown_video();

    void clear_frame_buffer();
    void load_SDL_palette();
    void build_32bpp_palette();
    void pixel_out(unsigned x, unsigned y, unsigned color_index);

    void init_win32_functions();
    HWND get_sdl_window_handle();

private:
    SDL_Surface*    screen;
    unsigned        frame_height;
    unsigned        frame_width;
    SDL_Color       sdl_colors[TOTAL_GRAYSCALE_COLORS];
    unsigned        ppu_32bpp_colors[TOTAL_GRAYSCALE_COLORS];

    HWND                sdl_window_handle;
    HWND                parent_window_id;
    get_window_rect_fn  get_window_rect;
    move_window_fn      move_window;
};


#endif
