#include "emulator.h"
#include "ui_emulator.h"
#include "famicom_emu.h"
#include "famicom_emu_builder.h"
#include "ppu/ppu_2c02.h"
#include "cpu/cpu_2a03.h"
#include "inspectors/data_bus_inspector.h"
#include "controller_inputs.h"
#include "cartridge_data.h"
#include "ines/ines_loader.h"
#include "tv_set/tv_set.h"
#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QTimer>
#include "SDL.h"

bool run_tv_set = false;

int run_tv_thread(void* data)
{
    unsigned screen_width = 512;
    unsigned screen_height = 480;
    TV_Set* tv_set = new TV_Set(screen_width, screen_height);

    HWND* parent_window_id = (HWND*) data;
    tv_set->set_parent_window_id(*parent_window_id);
    delete parent_window_id;

    tv_set->initialize();

    run_tv_set = true;
    while (run_tv_set)
    {
        tv_set->run();
        SDL_Delay(5);
    };

    tv_set->finalize();

    delete tv_set;
    return 0;
}

void
Emulator::start_tv_set()
{
    HWND* parent_id = new HWND;
    *parent_id = this->window()->winId();


    this->tv_thread = SDL_CreateThread(run_tv_thread, (void *) parent_id);
}

void
Emulator::stop_tv_set()
{
int status;
if (run_tv_set)
    {
    run_tv_set = false;
    SDL_WaitThread(this->tv_thread, &status);
    }
}

//===========================================================================================

Emulator::Emulator(QWidget *parent) :
        QWidget(parent),
    ui(new Ui::Emulator)
{
    this->ui->setupUi(this);
    this->ppu_bus_inspector = 0;
    this->cpu_bus_inspector = 0;
    this->emu = 0;

    this->frame_delay_ticks = compute_average_frame_delay();
}



Emulator::~Emulator()
{
    delete this->emu;
    delete this->ui;
    delete this->ppu_bus_inspector;
    delete this->cpu_bus_inspector;
}

std::string
Emulator::select_rom_file()
{
//Select a ROM file
QFileDialog dialog(NULL);
dialog.setFileMode(QFileDialog::ExistingFile);
dialog.setNameFilter("NES Files (*.nes)");

QStringList filenames;
if (dialog.exec())
    filenames = dialog.selectedFiles();

if (filenames.empty())
    return std::string("");

//Load the file and obtain cartridge data
return filenames.at(0).toStdString();
}


void
Emulator::load_rom()
{
Cartridge_Data* cart_data = this->load_cartridge();
if (not cart_data->can_be_executed())
    {
    delete cart_data;
    this->ui->run_push_button->setEnabled(false);
    return;
    }

if (run_tv_set)
    this->stop_tv_set();

this->build_machine_with_cartridge(cart_data);
this->ui->run_push_button->setEnabled(true);
this->execute_loop();
}

Cartridge_Data*
Emulator::load_cartridge()
{
    //Prompt the user to select a ROM file
    std::string rom_filename = select_rom_file();

    if (rom_filename.empty())
        return new Empty_Cartridge_Data();

    if (not this->file_exists(rom_filename))
        return new Empty_Cartridge_Data();

    //Load the file and obtain cartridge data
    Cartridge_Data* d = INES_Loader::load_file(rom_filename);
    std::cout << *d << std::endl;
    return d;
}


void
Emulator::build_machine_with_cartridge(Cartridge_Data* d)
{
    //Build an emulated machine
    delete this->emu;
    this->emu = Famicom_Emu_Builder::build_emu(d);
    delete d;
}

bool
Emulator::file_exists(const std::string& filename)
{
if (FILE *file = fopen(filename.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
else
    return false;
}

unsigned
Emulator::compute_average_frame_delay()
{
const double fps = 60.0;
const double frame_delay_in_seconds = 1.0 / fps;
const unsigned frame_delay_in_milliseconds = (unsigned) (frame_delay_in_seconds * 1000.0);
const unsigned total_samples = 100;

std::vector<unsigned> differences;


for (unsigned i = 0; i < total_samples; i++)
    {
    unsigned start_tick = SDL_GetTicks();
    SDL_Delay(frame_delay_in_milliseconds);
    unsigned stop_tick = SDL_GetTicks();
    unsigned tick_difference = stop_tick - start_tick;
    differences.push_back(tick_difference);
    }

std::vector<unsigned>::iterator it = differences.begin();
unsigned total_differences = 0;
for (; it != differences.end(); it++)
    total_differences += *it;

return total_differences / total_samples;
}

void
Emulator::execute_loop()
{
const unsigned ppu_cycles_per_scanline = 341; //NTSC
const unsigned ppu_scanlines_per_frame = 262; //NTSC
const unsigned ppu_cycles_per_frame = ppu_scanlines_per_frame * ppu_cycles_per_scanline;
const unsigned cpu_cycles_per_frame = ppu_cycles_per_frame / 3;

if (this->emu == 0)
    return;


run_emulator = true;
while (run_emulator)
    {
    unsigned start_tick = SDL_GetTicks();

    this->emu->cpu->execute_clocks(cpu_cycles_per_frame);
    this->emu->ppu->execute();
    this->poll_sdl_events();

    //Inter-frame delay
    //FIXME - Implement proper frame throttling
    unsigned stop_tick = SDL_GetTicks();
    unsigned passed_ticks = stop_tick - start_tick;
    unsigned remaining_ticks = this->frame_delay_ticks - passed_ticks;
    if (remaining_ticks > this->frame_delay_ticks)
        remaining_ticks = 0;
    SDL_Delay(remaining_ticks);
    }
}

void
Emulator::stop_emulation()
{
    this->run_emulator = false;
}

void
Emulator::update_ppu_bus_inspector()
{
    if (this->ppu_bus_inspector)
        delete this->ppu_bus_inspector;

    this->ppu_bus_inspector = new Data_Bus_Inspector ((Data_Bus*) emu->ppu_data_bus, "PPU Data Bus");
    this->ppu_bus_inspector->show();
}

void
Emulator::update_cpu_bus_inspector()
{
    if (this->cpu_bus_inspector)
        delete this->cpu_bus_inspector;

    this->cpu_bus_inspector = new Data_Bus_Inspector ((Data_Bus*) emu->cpu_data_bus, "CPU Data Bus");
    this->cpu_bus_inspector->show();
}


void Emulator::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Emulator::poll_sdl_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        run_emulator = false;
                        break;
                    case SDLK_UP:
                        this->emu->gamepad_a_inputs->set_up();
                        break;
                    case SDLK_DOWN:
                        this->emu->gamepad_a_inputs->set_down();
                        break;
                    case SDLK_LEFT:
                        this->emu->gamepad_a_inputs->set_left();
                        break;
                    case SDLK_RIGHT:
                        this->emu->gamepad_a_inputs->set_right();
                        break;
                    case SDLK_RETURN:
                        this->emu->gamepad_a_inputs->set_start();
                        break;
                    case SDLK_RSHIFT:
                        this->emu->gamepad_a_inputs->set_select();
                        break;
                    case SDLK_z:
                        this->emu->gamepad_a_inputs->set_a_button();
                        break;
                    case SDLK_x:
                        this->emu->gamepad_a_inputs->set_b_button();
                        break;
                    case SDLK_d:
                        this->emu->ppu->sprite_debug = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        this->emu->gamepad_a_inputs->clear_up();
                        break;
                    case SDLK_DOWN:
                        this->emu->gamepad_a_inputs->clear_down();
                        break;
                    case SDLK_LEFT:
                        this->emu->gamepad_a_inputs->clear_left();
                        break;
                    case SDLK_RIGHT:
                        this->emu->gamepad_a_inputs->clear_right();
                        break;
                    case SDLK_RETURN:
                        this->emu->gamepad_a_inputs->clear_start();
                        break;
                    case SDLK_RSHIFT:
                        this->emu->gamepad_a_inputs->clear_select();
                        break;
                    case SDLK_z:
                        this->emu->gamepad_a_inputs->clear_a_button();
                        break;
                    case SDLK_x:
                        this->emu->gamepad_a_inputs->clear_b_button();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                run_emulator = false;
                run_tv_set = false;
                break;
            default:
                break;
        }
    }
}

