#ifndef PPU_DATA_BUS_H
#define PPU_DATA_BUS_H

#include "data_bus/data_bus.h"

class Memory_Bank;

class PPU_Data_Bus : public Data_Bus
{
public:
    PPU_Data_Bus();
    virtual ~PPU_Data_Bus();
    virtual unsigned read(unsigned address) = 0;
    virtual void write(unsigned address, unsigned value) = 0;

    unsigned    read_palette(unsigned address);
    unsigned    read_ram_bank(unsigned ram_bank_number, unsigned address);
    void        write_palette(unsigned address, unsigned value);
    void        write_ram_bank(unsigned ram_bank_number, unsigned address, unsigned value);

private:
    Memory_Bank* ram_bank_0;
    Memory_Bank* ram_bank_1;
    Memory_Bank* palette_ram;
};

#endif // PPU_DATA_BUS_H
