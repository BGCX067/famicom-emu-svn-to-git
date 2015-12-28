#ifndef PPU_SPR_RAM_DATA_PORT_H
#define PPU_SPR_RAM_DATA_PORT_H

#include "port/port_8bit.h"

class Register_8bit;
class Memory_Bank;

class PPU_SPR_RAM_Data_Port : public Port_8bit
{
public:
    PPU_SPR_RAM_Data_Port(Register_8bit* addr_register, Memory_Bank* bank);
    unsigned read();
    void write(unsigned value);

private:
    Register_8bit*  addr_register;
    Memory_Bank*    bank;
};

#endif // PPU_SPR_RAM_DATA_PORT_H
