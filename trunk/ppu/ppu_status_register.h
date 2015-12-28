#ifndef PPU_STATUS_REGISTER_H
#define PPU_STATUS_REGISTER_H

#include "register/register_8bit.h"

class PPU_Status_Register : public Register_8bit
{
public:
    PPU_Status_Register();

public:
    void clear_vblank()             {clear_bit(7);};
    void set_vblank()               {set_bit(7);};
    void clear_bkg_collision()      {clear_bit(6);};
    void set_bkg_collision()        {set_bit(6);};
    void clear_sprite_overflow()    {clear_bit(5);};
    void set_sprite_overflow()      {set_bit(5);};

    unsigned read_vblank()          {return read_bit(7);};
    unsigned read_bkg_collision()   {return read_bit(6);};
    unsigned read_sprite_overflow() {return read_bit(5);};
};

#endif // PPU_STATUS_REGISTER_H
