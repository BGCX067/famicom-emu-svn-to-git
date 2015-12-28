#include <QtGui/QApplication>
#include "emulator.h"
//#include "SDL.h"
//#include <SDL.h>

/*#include "inspectors/cpu_2a03_inspector.h"
#include "inspectors/data_bus_inspector.h"
#include "inspectors/palette_inspector.h"
#include "inspectors/tile_inspector.h"
#include "disassembler.h"
#include "data_bus/data_bus.h"
#include "data_bus/cpu/cpu_data_bus.h"
#include "data_bus/cpu/cpu_data_bus_m0.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QRgb>
#include <iostream>

#include "memory_bank_model.h"
#include <QTableView>

#include "disassembler_model.h"
#include "disassembler.h"
#include <QListView>

#include <sstream>
#include <string>
#include <vector>
#include <map>*/


#include "SDL.h"
#undef main
void
init_SDL()
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ))
        exit(-1);
    SDL_EnableKeyRepeat(0, 0);
}

void
finalize_SDL()
{
    SDL_Quit();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init_SDL();

    //Run emulator GUI
    Emulator* e = new Emulator;
    e->show();
    e->start_tv_set();

    a.exec();

    //Cleanup
    e->stop_emulation();
    e->stop_tv_set();
    delete e;

    finalize_SDL();
    return 0;
}


    /*QAbstractTableModel* m = new Memory_Bank_Model(d->get_prg_rom_banks()[0]);
    QTableView* v = new QTableView;
    v->setModel(m);
    v->resizeColumnsToContents();
    v->show();*/

    /*CPU_2A03_Inspector cpu_insp(emu->cpu, d->get_prg_rom_banks()[1]);
    cpu_insp.show();*/

    //Data_Bus_Inspector cpu_db_insp((Data_Bus*) emu->cpu_data_bus, "CPU Data Bus");
    //cpu_db_insp.show();

    //Data_Bus_Inspector ppu_db_insp((Data_Bus*) emu->ppu_data_bus, "PPU Data Bus");
    //ppu_db_insp.show();

    /*Disassembler dis;
    unsigned bank_address = 0x8000;
    if (d->get_prg_rom_banks().size() == 1)
        bank_address = 0xC000;

    for (unsigned bank_num = 0; bank_num < d->get_prg_rom_banks().size(); bank_num++)
    {
        std::string disassembly = dis.disassemble_bank(d->get_prg_rom_banks()[bank_num], bank_address);
        bank_address += 0x4000;
        std::cout << disassembly << std::endl;
    }*/

    /*const unsigned char* colors = emu->ppu->get_palette();
    const unsigned total_colors = emu->ppu->get_palette_size();
    QVector<QRgb> palette;
    for (unsigned color = 0; color < total_colors; color++)
    {
        QRgb r = qRgb(colors[color * 3], colors[color * 3 + 1], colors[color * 3 + 2]);
        palette.push_back(r);
    }*/

    /*Palette_Inspector palette_insp;
    QGraphicsView* palette_view = palette_insp.display_palette(palette);
    palette_view->show();*/

    /*Tile_Inspector tile_insp(emu->ppu_data_bus);
    QGraphicsView* tile_view = tile_insp.display_tiles(palette);
    tile_view->show();*/
