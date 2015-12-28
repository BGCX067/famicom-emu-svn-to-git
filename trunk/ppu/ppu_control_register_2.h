#ifndef PPU_CONTROL_REGISTER_2_H
#define PPU_CONTROL_REGISTER_2_H

#include "register/register_8bit.h"

class PPU_Control_Register_2 : Register_8bit
{
public:
    PPU_Control_Register_2();

public:
    void set_color_emphasis(unsigned value)       { Register_8bit::set_value(Register_8bit::read_value() | (value << 5));};
    void clear_spr_visibility()     {clear_bit(4);};
    void set_spr_visibility()       {set_bit(4);};
    void clear_bkg_visibility()     {clear_bit(3);};
    void set_bkg_visibility()       {set_bit(3);};
    void clear_spr_no_clipping()    {clear_bit(2);};
    void set_spr_no_clipping()      {set_bit(2);};
    void clear_bkg_no_clipping()    {clear_bit(1);};
    void set_bkg_no_clipping()      {set_bit(1);};
    void clear_monochrome_mode()    {clear_bit(0);};
    void set_monochrome_mode()      {set_bit(0);};

    unsigned read_color_emphasis()       {return Register_8bit::read_value() >> 5;};
    unsigned read_spr_visibility()       {return read_bit(4);};
    unsigned read_bkg_visibility()       {return read_bit(3);};
    unsigned read_spr_no_clipping()      {return read_bit(2);};
    unsigned read_bkg_no_clipping()      {return read_bit(1);};
    unsigned read_monochrome_mode()      {return read_bit(0);};

};

#endif // PPU_CONTROL_REGISTER_2_H
