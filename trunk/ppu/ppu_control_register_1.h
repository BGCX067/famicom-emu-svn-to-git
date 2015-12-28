#ifndef PPU_CONTROL_REGISTER_1_H
#define PPU_CONTROL_REGISTER_1_H

#include "register/register_8bit.h"

class PPU_Control_Register_1 : Register_8bit
{
public:
    PPU_Control_Register_1();

    void clear_nmi_on_vblank()              {clear_bit(7);};
    void set_nmi_on_vblank()                {set_bit(7);};
    void clear_ppu_master_slave()           {clear_bit(6);};
    void set_ppu_master_slave()             {set_bit(6);};
    void clear_sprite_size()                {clear_bit(5);};
    void set_sprite_size()                  {set_bit(5);};
    void clear_pattern_table_addr_bkg()     {clear_bit(4);};
    void set_pattern_table_addr_bkg()       {set_bit(4);};
    void clear_pattern_table_addr_spr()     {clear_bit(3);};
    void set_pattern_table_addr_spr()       {set_bit(3);};
    void clear_vram_addr_increment()        {clear_bit(2);};
    void set_vram_addr_increment()          {set_bit(2);};
    void clear_name_table_hor_scroll()      {clear_bit(1);};
    void set_name_table_hor_scroll()        {set_bit(1);};
    void clear_name_table_vert_scroll()     {clear_bit(0);};
    void set_name_table_vert_scroll()       {set_bit(0);};

    unsigned read_nmi_on_vblank()                {return read_bit(7);};
    unsigned read_ppu_master_slave()             {return read_bit(6);};
    unsigned read_sprite_size()                  {return read_bit(5);};
    unsigned read_pattern_table_addr_bkg()       {return read_bit(4);};
    unsigned read_pattern_table_addr_spr()       {return read_bit(3);};
    unsigned read_vram_addr_increment()          {return read_bit(2);};
    unsigned read_name_table_hor_scroll()        {return read_bit(1);};
    unsigned read_name_table_vert_scroll()       {return read_bit(0);};

};

#endif // PPU_CONTROL_REGISTER_1_H
