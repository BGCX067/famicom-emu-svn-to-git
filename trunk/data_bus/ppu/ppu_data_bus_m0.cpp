#include "ppu_data_bus_m0.h"
#include "data_bus/memory_bank.h"
#include <iostream>

PPU_Data_Bus_M0::PPU_Data_Bus_M0(Name_Table_Mirroring::Type _mirroring) :
        mirroring(_mirroring)
{
}

PPU_Data_Bus_M0::~PPU_Data_Bus_M0()
{
    delete chr_rom;
}

void
PPU_Data_Bus_M0::connect_chr_rom(Memory_Bank* _chr_rom)
{
    chr_rom = _chr_rom;
}

unsigned
PPU_Data_Bus_M0::read(unsigned address)
{
    /*if (address > 0x3FFF)
    {
        QString s("PPU Data Bus M0 address > 0x3FFF");
        std::cout << s.toStdString() << std::endl;
        throw new std::string(s.toStdString());//EXCEPTION
    }*/

    //Global bus mirroring: 4000-FFFF -> 0000-3FFF
    address &= 0x3FFF;

    if (address <= 0x1FFF) //ROM Bank
        return (chr_rom->read(address));
    else if (address >= 0x2000 and address <= 0x3EFF) //Nametables
    {
       unsigned name_table_number = (address & 0x0C00) >> 18;
       unsigned ram_bank_internal_address = address & 0x03FF;
       unsigned ram_bank_number = this->map_nametable_to_ram_bank(name_table_number);
       return (PPU_Data_Bus::read_ram_bank(ram_bank_number, ram_bank_internal_address));
    }
    else //Palette (3F00-3FFF)
    {
        //Palette mirroring: 3F20-3FFF -> 3F00-3F1F
        //Relevant addresses: 00-1F
        address &= 0x001F;
        return (PPU_Data_Bus::read_palette(address));
    }
}

void
PPU_Data_Bus_M0::write(unsigned address, unsigned value)
{
    /*if (address > 0x3FFF)
    {
        QString s("PPU Data Bus M0 address > 0x3FFF");
        std::cout << s.toStdString() << std::endl;
        throw new std::string(s.toStdString());//EXCEPTION
    }*/

    //Global bus mirroring: 4000-FFFF -> 0000-3FFF
    address &= 0x3FFF;

    if (address <= 0x1FFF) //ROM Bank
        ; //Cannot write to ROM
    else if (address >= 0x2000 and address <= 0x3EFF) //Nametables
    {
       unsigned name_table_number = (address & 0x0C00) >> 18;
       unsigned ram_bank_internal_address = address & 0x03FF;
       unsigned ram_bank_number = this->map_nametable_to_ram_bank(name_table_number);
       return (PPU_Data_Bus::write_ram_bank(ram_bank_number, ram_bank_internal_address, value));
    }
    else //Palette (3F00-3FFF)
    {
        //Palette mirroring: 3F20-3FFF -> 3F00-3F1F
        //Relevant addresses: 00-1F
        address &= 0x001F;
        return (PPU_Data_Bus::write_palette(address, value));
    }
}

unsigned
PPU_Data_Bus_M0::map_nametable_to_ram_bank(unsigned nametable_number)
{
 if (mirroring == Name_Table_Mirroring::Horizontal)
 {
     //NT0, NT1 ->   BANK0
     //NT2, NT3 ->   BANK1
    if (nametable_number == 0 or nametable_number == 1)
        return (0);
    else
        return (1);

 }
 else if (mirroring == Name_Table_Mirroring::Vertical)
 {
     //NT0, NT2 ->   BANK0
     //NT1, NT3 ->   BANK1
    if (nametable_number == 0 or nametable_number == 2)
        return (0);
    else
        return (1);
 }
 else if (mirroring == Name_Table_Mirroring::Four_Screen)
 {
    return 0;//FIXME!
 }
 else
    return 0;
}

