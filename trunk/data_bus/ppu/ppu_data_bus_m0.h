#ifndef PPU_DATA_BUS_M0_H
#define PPU_DATA_BUS_M0_H

#include "ppu_data_bus.h"
#include "data_bus/name_table_mirroring.h"

class Memory_Bank;

class PPU_Data_Bus_M0 : public PPU_Data_Bus
{
public:
    PPU_Data_Bus_M0(Name_Table_Mirroring::Type mirroring);
    ~PPU_Data_Bus_M0();

    void        connect_chr_rom(Memory_Bank* _chr_rom);

    unsigned    read(unsigned address);
    void        write(unsigned address, unsigned value);

private:
    unsigned    map_nametable_to_ram_bank(unsigned nametable_number);

private:
    Memory_Bank* chr_rom;
    Name_Table_Mirroring::Type    mirroring;
};

#endif // PPU_DATA_BUS_M0_H
