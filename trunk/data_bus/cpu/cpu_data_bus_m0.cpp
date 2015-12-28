#include "cpu_data_bus_m0.h"
#include "data_bus/memory_bank.h"

CPU_Data_Bus_M0::CPU_Data_Bus_M0() : rom_size(0)
{
}

CPU_Data_Bus_M0::~CPU_Data_Bus_M0()
{
    for(unsigned i = 0; i < this->rom_banks.size(); i++)
        delete this->rom_banks[i];
}

void
CPU_Data_Bus_M0::connect_rom_bank(unsigned bank_num, Memory_Bank* _rom_bank)
{
    this->rom_banks.push_back(_rom_bank);
    this->rom_size += _rom_bank->get_size();
}

unsigned
CPU_Data_Bus_M0::read(unsigned address)
{
    if (address <= 0x1FFF) //WRAM 0000-1FFF
    {
        address &= 0x07FF; //Mirroring 0800-1FFF -> 0000-07FF
        return (CPU_Data_Bus::read_ram_bank(address));
    }
    else if (address >= 0x2000 and address <= 0x3FFF) //PPU Ports
    {
        address &= 0x0007; //Mirroring 0x2000-2007 -> 0x2000-3FFF
        return (CPU_Data_Bus::read_ppu_ports(address));
    }
    else if (address >= 0x4000 and address <= 0x4017) // APU Ports
    {
        address &= 0x001F; // Relevant addresses: 00-17
        return (CPU_Data_Bus::read_apu_ports(address));
    }
    else if (address >= 0x4018 and address <= 0x5FFF) // Expansion RAM - NOT PRESENT IN THIS MAPPER
    {
        return (0);
    }
    else if (address >= 0x6000 and address <= 0x7FFF) // SRAM
    {
        address &= 0x1FFF; //Relevant adresses: 0000-1FFF (8K)
        return (CPU_Data_Bus::read_sram_bank(address));
    }
    else // ROM bank
    {
        if (this->rom_size == 0x4000) //16K ROM
        {
            address &= 0x3FFF; //Relevant addresses - 0000-3FFF
            return this->rom_banks[0]->read(address);
        }
        else //32K ROM - No mirroring, two banks
        {
            unsigned bank_number = 0;
            if (address >= 0xC000 and address <= 0xFFFF)
                bank_number = 1;

            address &= 0x3FFF; //Relevant addresses - 0000-3FFF
            return this->rom_banks[bank_number]->read(address);
        }
    }
}

void
CPU_Data_Bus_M0::write(unsigned address, unsigned value)
{
    if (address <= 0x1FFF) //WRAM 0000-1FFF
    {
        address &= 0x07FF; //Mirroring 0800-1FFF -> 0000-07FF
        CPU_Data_Bus::write_ram_bank(address, value);
    }
    else if (address >= 0x2000 and address <= 0x3FFF) //PPU Ports
    {
        address &= 0x0007; //Mirroring 0x2000-2007 -> 0x2000-3FFF
        CPU_Data_Bus::write_ppu_ports(address, value);
    }
    else if (address >= 0x4000 and address <= 0x4017) // APU Ports
    {
        address &= 0x001F; // Relevant addresses: 00-17
        CPU_Data_Bus::write_apu_ports(address, value);
    }
    else if (address >= 0x4018 and address <= 0x5FFF) // Expansion RAM - NOT PRESENT IN THIS MAPPER
    {
        ;
    }
    else if (address >= 0x6000 and address <= 0x7FFF) // SRAM
    {
        address &= 0x1FFF; //Relevant adresses: 0000-1FFF (8K)
        CPU_Data_Bus::write_sram_bank(address, value);
    }
    else // ROM bank - CANNOT WRITE
    {
        ;
    }
}


