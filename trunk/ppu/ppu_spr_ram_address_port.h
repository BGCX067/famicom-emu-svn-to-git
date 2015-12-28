#ifndef PPU_SPR_RAM_ADDRESS_PORT_H
#define PPU_SPR_RAM_ADDRESS_PORT_H

#include "port/port_8bit.h"

class Register_8bit;

class PPU_SPR_RAM_Address_Port : public Port_8bit
{
public:
    PPU_SPR_RAM_Address_Port(Register_8bit* addr_reg);
    unsigned read();
    void write(unsigned value);
private:
    Register_8bit*  addr_register;
};

#endif // PPU_SPR_RAM_ADDRESS_PORT_H
