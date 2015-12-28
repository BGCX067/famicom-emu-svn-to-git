#ifndef EMULATOR_H
#define EMULATOR_H

#include <QWidget>

namespace Ui {
    class Emulator;
}

class Famicom_Emu;
class Data_Bus_Inspector;
class Cartridge_Data;
class SDL_Thread;

class Emulator : public QWidget {
    Q_OBJECT
public:
    Emulator(QWidget *parent = 0);
    ~Emulator();
    void            start_tv_set();
    void            stop_tv_set();
    void            stop_emulation();


public slots:
    void            execute_loop();
    void            update_cpu_bus_inspector();
    void            update_ppu_bus_inspector();
    void            load_rom();

protected:
    void            changeEvent(QEvent *e);

private:
    void            poll_sdl_events();
    unsigned        compute_average_frame_delay();
    std::string     select_rom_file();
    bool            file_exists(const std::string& filename);
    Cartridge_Data* load_cartridge();
    void            build_machine_with_cartridge(Cartridge_Data* d);


private:
    Ui::Emulator *ui;
    Famicom_Emu* emu;
    Data_Bus_Inspector* ppu_bus_inspector;
    Data_Bus_Inspector* cpu_bus_inspector;

    bool        run_emulator;
    unsigned    frame_delay_ticks;
    SDL_Thread* tv_thread;
};

#endif // EMULATOR_H
