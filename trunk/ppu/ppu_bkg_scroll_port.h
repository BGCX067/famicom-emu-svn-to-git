#ifndef PPU_BKG_SCROLL_REGISTER_H
#define PPU_BKG_SCROLL_REGISTER_H

#include "port/port_8bit.h"
#include "register/register_8bit.h"
#include "register/register_16bit.h"

class Flip_Flop;

class PPU_BKG_Scroll_Port : public Port_8bit
{
public:
    PPU_BKG_Scroll_Port(Register_16bit* scroll_register, Flip_Flop* flip_flop);
    unsigned read() { return 0; };
    void write(unsigned value);

private:
    Register_8bit   offset_low;
    Register_8bit   offset_high;
    Register_16bit*  offset_full;
    Flip_Flop*  flip_flop;
};

#endif // PPU_BKG_SCROLL_REGISTER_H
