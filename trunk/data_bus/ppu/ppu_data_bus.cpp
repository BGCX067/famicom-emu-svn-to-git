#include "ppu_data_bus.h"
#include "data_bus/memory_bank.h"
#include <iostream>

PPU_Data_Bus::PPU_Data_Bus() : Data_Bus(16384)
{
    ram_bank_0 = new Memory_Bank(1024, false);
    ram_bank_1 = new Memory_Bank(1024, false);
    palette_ram = new Memory_Bank(256, false);
}

PPU_Data_Bus::~PPU_Data_Bus()
{
    delete ram_bank_0;
    delete ram_bank_1;
    delete palette_ram;
}

unsigned
PPU_Data_Bus::read_palette(unsigned address)
{
    return (palette_ram->read(address));
}

unsigned
PPU_Data_Bus::read_ram_bank(unsigned ram_bank_number, unsigned address)
{
    if (ram_bank_number == 0)
        return (ram_bank_0->read(address));
    else
        return (ram_bank_1->read(address));
}

void
PPU_Data_Bus::write_palette(unsigned address, unsigned value)
{
    palette_ram->write(address, value);
}

void
PPU_Data_Bus::write_ram_bank(unsigned ram_bank_number, unsigned address, unsigned value)
{
    if (ram_bank_number == 0)
        ram_bank_0->write(address, value);
    else
        ram_bank_1->write(address, value);
}

