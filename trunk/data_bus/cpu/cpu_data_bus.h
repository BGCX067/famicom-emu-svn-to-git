#ifndef CPU_DATA_BUS_H
#define CPU_DATA_BUS_H

#include "data_bus/data_bus.h"

class PPU_Port_Interface;
class APU_Port_Interface;
class Memory_Bank;

class CPU_Data_Bus : public Data_Bus
{
public:
    CPU_Data_Bus();
    virtual ~CPU_Data_Bus();
    void connect_ppu_ports(PPU_Port_Interface* ppu_ports);
    void connect_apu_ports(APU_Port_Interface* apu_ports);

    virtual unsigned read(unsigned address) = 0;
    virtual void write(unsigned address, unsigned value) = 0;

    unsigned read_ram_bank(unsigned address);
    unsigned read_ppu_ports(unsigned address);
    unsigned read_apu_ports(unsigned address);
    unsigned read_sram_bank(unsigned address);
    void write_ram_bank(unsigned address, unsigned value);
    void write_ppu_ports(unsigned address, unsigned value);
    void write_apu_ports(unsigned address, unsigned value);
    void write_sram_bank(unsigned address, unsigned value);

private:
    Memory_Bank*    ram_bank;
    Memory_Bank*    sram_bank;
    PPU_Port_Interface* ppu_ports;
    APU_Port_Interface* apu_ports;
};

#endif // CPU_DATA_BUS_H
