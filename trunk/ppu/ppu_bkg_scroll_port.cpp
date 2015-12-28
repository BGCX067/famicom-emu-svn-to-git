#include "ppu_bkg_scroll_port.h"
#include "flip_flop.h"
#include <iostream>

PPU_BKG_Scroll_Port::PPU_BKG_Scroll_Port(Register_16bit* scroll_register, Flip_Flop* _flip_flop) : offset_full(scroll_register), flip_flop(_flip_flop)
{
}

void
PPU_BKG_Scroll_Port::write(unsigned value)
{
        if (flip_flop->output())
            offset_high.set_value(value);
        else
            offset_low.set_value(value);

        offset_full->set_value(offset_low.read_value() | (offset_high.read_value() << 8));
        flip_flop->invert();
}

