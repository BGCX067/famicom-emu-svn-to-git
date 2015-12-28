#ifndef EMU_PPU_2C02_H
#define EMU_PPU_2C02_H

//#include "ppu_status_register.h"
//#include "ppu_control_register_1.h"
//#include "ppu_control_register_2.h"
//#include "ppu_bkg_scroll_register.h"
//#include "ppu_vram_address_register.h"
//#include "flip_flop_8bit.h"
#include "register/register_8bit.h"
#include "SDL.h"


class PPU_Data_Bus;
class Register_8bit;
class Register_16bit;
class Flip_Flop;
class PPU_Control_Register_1;
class PPU_Control_Register_2;
class PPU_Status_Register;
class PPU_BKG_Scroll_Port;
class PPU_VRAM_Address_Port;
class PPU_VRAM_Data_Register;
class PPU_Port_Interface;
class Memory_Bank;
class Emulator;
class SDL_Surface;

class PPU_2C02
{
    friend class Emulator;
public:
    PPU_2C02();
    ~PPU_2C02();
    void                        connect_data_bus(PPU_Data_Bus* db);
    void                        connect_cpu_nmi(bool* cpu_nmi);
    const unsigned char*        get_palette();
    const unsigned              get_palette_size();
    PPU_Port_Interface*         get_port_interface() {return port_interface;};
    void                        execute();

private:
    void    init_frame_buffer();
    void    load_SDL_palette();
    void    build_32bpp_palette();

    void    init_internal_variables();
    void    clear_frame_buffer();
    void    dump_sprite_temporary_memory(unsigned scanline);
    void    dump_sprite_buf_mem();

    void    render_scanline(unsigned scanline_number);
    void    fetch_pattern_scanline(unsigned scanline_num, unsigned pattern_number, unsigned* pattern_1, unsigned* pattern_2);
//    void    fetch_attr_bits(unsigned attr_byte, unsigned tile_col, unsigned scanline_num, unsigned* color_bits);
    void    render_pattern_row(unsigned start_col, unsigned row, unsigned color_bits, unsigned pattern_1, unsigned pattern_2);

    void    scan_sprites_in_range(unsigned scanline_number);
    unsigned logical_invert(unsigned i);
    int     invert_difference(int d);

    void    load_sprite_buffer_memory();
    void    clock_bkg_pipeline(unsigned tile_col, unsigned scanline_num);
    void    run_multiplexer(unsigned, unsigned);

    unsigned    fetch_name_table_byte(unsigned, unsigned);
    unsigned    fetch_bkg_pattern_0(unsigned, unsigned);
    unsigned    fetch_bkg_pattern_1(unsigned, unsigned);    
    unsigned    fetch_attr_table_byte(unsigned, unsigned);

    void        fetch_sprite_pixel(unsigned hor_pos, unsigned* sprite_palette, unsigned* sprite_pixel, unsigned* sprite_priority, int* sprite_number);
    unsigned    fetch_bkg_pixel(unsigned hor_pos);
    unsigned    fetch_bkg_palette(unsigned attr_byte, unsigned tile_col, unsigned scanline_num);
    void        pixel_out(unsigned x, unsigned y, unsigned palette_select, unsigned palette_index);


private:
    //PPU Data Bus
    PPU_Data_Bus*           data_bus;

    //SPR-RAM Memory Bank
    Memory_Bank*            spr_ram;

    //CPU NMI line
    bool*                   cpu_nmi;

    //Registers (used by the different ports and the PPU itself)
    PPU_Control_Register_1*     control_register_1;
    PPU_Control_Register_2*     control_register_2;
    PPU_Status_Register*        status_register;
    Register_8bit*              spr_ram_address_register;
    Register_8bit*              spr_ram_data_register;
    Register_8bit*              spr_dma_register;
    Register_16bit*             bkg_scroll_register;
    Register_8bit*              vram_data_register;
    Register_16bit*             vram_addr_register;
    Flip_Flop*                  shared_flip_flop;
    PPU_Port_Interface*         port_interface;

    //Sprite temporary memory
    unsigned                    spr_temp_mem[32];
    bool                        sprite_0_in_range;
    unsigned                    spr_temp_mem_count;

    //Sprite buffer memory
    unsigned                    spr_buf_mem_count;
    unsigned                    spr_horiz_position[8];
    unsigned                    spr_attribute[8];
    unsigned                    spr_shift_register[8][2];

    //BKG buffer memory
    unsigned                    bkg_pattern_0_preload_1;
    unsigned                    bkg_pattern_0_preload_2;
    unsigned                    bkg_pattern_0_selector;
    unsigned                    bkg_pattern_1_preload_1;
    unsigned                    bkg_pattern_1_preload_2;
    unsigned                    bkg_pattern_1_selector;
    unsigned                    bkg_attribute_preload_1;
    unsigned                    bkg_attribute_preload_2;
    unsigned                    bkg_attribute_selector;

    //Debugging
    bool                        sprite_debug;
    bool                        buf_debug;

    //Frame Buffer
    SDL_Surface*    screen;
    unsigned        frame_width;
    unsigned        frame_height;

    SDL_Color       sdl_colors[64];
    unsigned        ppu_32bpp_colors[64];
    unsigned        frame_counter;
    unsigned        tick_counter;

    static const unsigned spr_ram_size = 256;
    static const unsigned scanlines_per_frame = 262;//FIXME! - NTSC ONLY
};

static const unsigned total_colors = 64;
static const unsigned char ppu_raw_colors [total_colors * 3] =
    {
    0x75, 0x75, 0x75,
    0x27, 0x1B, 0x8F,
    0x00, 0x00, 0xAB,
    0x47, 0x00, 0x9F,
    0x8F, 0x00, 0x77,
    0xAB, 0x00, 0x13,
    0xA7, 0x00, 0x00,
    0x7F, 0x0B, 0x00,
    0x43, 0x2F, 0x00,
    0x00, 0x47, 0x00,
    0x00, 0x51, 0x00,
    0x00, 0x3F, 0x17,
    0x1B, 0x3F, 0x5F,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0xBC, 0xBC, 0xBC,
    0x00, 0x73, 0xEF,
    0x23, 0x3B, 0xEF,
    0x83, 0x00, 0xF3,
    0xBF, 0x00, 0xBF,
    0xE7, 0x00, 0x5B,
    0xDB, 0x2B, 0x00,
    0xCB, 0x4F, 0x0F,
    0x8B, 0x73, 0x00,
    0x00, 0x97, 0x00,
    0x00, 0xAB, 0x00,
    0x00, 0x93, 0x3B,
    0x00, 0x83, 0x8B,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF,
    0x3F, 0xBF, 0xFF,
    0x5F, 0x97, 0xFF,
    0xA7, 0x8B, 0xFD,
    0xF7, 0x7B, 0xFF,
    0xFF, 0x77, 0xB7,
    0xFF, 0x77, 0x63,
    0xFF, 0x9B, 0x3B,
    0xF3, 0xBF, 0x3F,
    0x83, 0xD3, 0x13,
    0x4F, 0xDF, 0x4B,
    0x58, 0xF8, 0x98,
    0x00, 0xEB, 0xDB,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF,
    0xAB, 0xE7, 0xFF,
    0xC7, 0xD7, 0xFF,
    0xD7, 0xCB, 0xFF,
    0xFF, 0xC7, 0xFF,
    0xFF, 0xC7, 0xDB,
    0xFF, 0xBF, 0xB3,
    0xFF, 0xDB, 0xAB,
    0xFF, 0xE7, 0xA3,
    0xE3, 0xFF, 0xA3,
    0xAB, 0xF3, 0xBF,
    0xB3, 0xFF, 0xCF,
    0x9F, 0xFF, 0xF3,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
    };


#endif // EMU_PPU_2C02_H
