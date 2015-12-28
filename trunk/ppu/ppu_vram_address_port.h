#ifndef PPU_VRAM_ADDRESS_PORT_H
#define PPU_VRAM_ADDRESS_PORT_H

#include "register/register_8bit.h"
#include "register/register_16bit.h"
#include "port/port_8bit.h"

class Flip_Flop;

class PPU_VRAM_Address_Port : public Port_8bit
{
public:
    PPU_VRAM_Address_Port(Register_16bit* address_full, Flip_Flop* flip_flop);
    unsigned read();
    void write(unsigned value);

private:
    Register_8bit   address_low;
    Register_8bit   address_high;
    Register_16bit* address_full;
    Flip_Flop*      flip_flop;
};

#endif // PPU_VRAM_ADDRESS_PORT_H
