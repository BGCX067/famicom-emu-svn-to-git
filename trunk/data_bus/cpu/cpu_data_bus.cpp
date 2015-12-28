#include "cpu_data_bus.h"
#include "data_bus/memory_bank.h"
#include "ppu/ppu_port_interface.h"
#include "apu/apu_port_interface.h"
#include <iostream>

CPU_Data_Bus::CPU_Data_Bus() : Data_Bus(65536)
{
    ram_bank = new Memory_Bank(0x800, false);
    sram_bank = new Memory_Bank(0x2000, false);
}

CPU_Data_Bus::~CPU_Data_Bus()
{
    delete ram_bank;
    delete sram_bank;
}

void
CPU_Data_Bus::connect_ppu_ports(PPU_Port_Interface* _ppu_ports)
{
    ppu_ports = _ppu_ports;
}

void
CPU_Data_Bus::connect_apu_ports(APU_Port_Interface* _apu_ports)
{
    apu_ports = _apu_ports;
}


unsigned
CPU_Data_Bus::read_ram_bank(unsigned address)
{
    return (ram_bank->read(address));
}

unsigned
CPU_Data_Bus::read_ppu_ports(unsigned address)
{
    return (ppu_ports->read(address));
}

unsigned
CPU_Data_Bus::read_apu_ports(unsigned address)
{
    return (apu_ports->read(address));
}

unsigned
CPU_Data_Bus::read_sram_bank(unsigned address)
{
    return (sram_bank->read(address));
}

void
CPU_Data_Bus::write_ram_bank(unsigned address, unsigned value)
{
    ram_bank->write(address, value);
}

void
CPU_Data_Bus::write_ppu_ports(unsigned address, unsigned value)
{
    ppu_ports->write(address, value);
}

void
CPU_Data_Bus::write_apu_ports(unsigned address, unsigned value)
{
    apu_ports->write(address, value);
}

void
CPU_Data_Bus::write_sram_bank(unsigned address, unsigned value)
{
    sram_bank->write(address, value);
}

