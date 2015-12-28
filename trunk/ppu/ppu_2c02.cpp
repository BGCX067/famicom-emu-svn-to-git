#include "ppu_2c02.h"
#include "data_bus/ppu/ppu_data_bus.h"
#include "data_bus/memory_bank.h"
#include "ppu_control_register_1.h"
#include "ppu_control_register_2.h"
#include "ppu_status_register.h"
#include "ppu_port_interface.h"
#include "flip_flop.h"
#include "register/register_16bit.h"
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <iostream>
#include "SDL.h"



PPU_2C02::PPU_2C02()
{
    spr_ram                         = new Memory_Bank(spr_ram_size, false);//FIXME! - Cambiar booleano a enumerado
    shared_flip_flop                = new Flip_Flop;
    control_register_1              = new PPU_Control_Register_1;
    control_register_2              = new PPU_Control_Register_2;
    status_register                 = new PPU_Status_Register;
    spr_ram_address_register        = new Register_8bit;
    spr_ram_data_register           = new Register_8bit;
    spr_dma_register                = new Register_8bit;
    bkg_scroll_register             = new Register_16bit;
    vram_data_register              = new Register_8bit;
    vram_addr_register              = new Register_16bit;

    init_frame_buffer();
    init_internal_variables();
}

PPU_2C02::~PPU_2C02()
{
    delete spr_ram;
    delete shared_flip_flop;
    delete control_register_1;
    delete control_register_2;
    delete status_register;
    delete spr_ram_address_register;
    delete spr_ram_data_register;
    delete spr_dma_register;
    delete bkg_scroll_register;
    delete vram_data_register;
    delete vram_addr_register;
    delete port_interface;
    SDL_FreeSurface(screen);
}


void
PPU_2C02::init_internal_variables()
{
    this->frame_counter = 0;
    this->tick_counter = 0;

    this->spr_buf_mem_count = 0;
    this->spr_temp_mem_count = 0;
    for (unsigned sprite_num = 0; sprite_num < 8; sprite_num++)
        {
        spr_horiz_position[sprite_num] = 0;
        spr_attribute[sprite_num] = 0;
        spr_shift_register[sprite_num][0] = 0;
        spr_shift_register[sprite_num][1] = 0;
        }

    for (unsigned i = 0; i < 32; i++)
        spr_temp_mem[i] = 0;
    this->sprite_0_in_range = false;

    this->bkg_attribute_preload_1 = 0;
    this->bkg_attribute_preload_2 = 0;
    this->bkg_attribute_selector = 0;
    this->bkg_pattern_0_preload_1 = 0;
    this->bkg_pattern_0_preload_2 = 0;
    this->bkg_pattern_0_selector = 0;
    this->bkg_pattern_1_preload_1 = 0;
    this->bkg_pattern_1_preload_2 = 0;
    this->bkg_pattern_1_selector = 0;
    this->sprite_debug = false;
    this->buf_debug = false;
}

void
PPU_2C02::init_frame_buffer()
{
unsigned screen_width = 512;
unsigned screen_height = 480;
//asdfasd
/*int bpp = SDL_VideoModeOK(screen_width, screen_height, 8, SDL_SWSURFACE);
if (bpp == 0)
{
    std::cout << "Video mode not supported";
    exit(1);
}
else
    std::cout << "Closest video mode in bpp = " << bpp << std::endl;
    exit(1);*/

screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_SWSURFACE);
if (!screen)
    {
    std::cout << "Could not set screen " << std::endl;
    exit(-1);
    }
this->frame_height = screen_height;
this->frame_width = screen_width;
//screen = SDL_SetVideoMode(256, 240, 8, SDL_SWSURFACE);

this->load_SDL_palette();
//SDL_SetColors(this->screen, this->sdl_colors, 0, 64); //8bpp only
this->build_32bpp_palette();
this->clear_frame_buffer();
}

void
PPU_2C02::clear_frame_buffer()
{
 SDL_LockSurface(screen);
 SDL_FillRect(screen, NULL, 0);
 SDL_UnlockSurface(screen);
}

//8bpp only
void
PPU_2C02::load_SDL_palette()
{
 const unsigned char *c = ppu_raw_colors;
 for (unsigned color = 0; color < 64; color++)
        {
        sdl_colors[color].r = *c++;
        sdl_colors[color].g = *c++;
        sdl_colors[color].b = *c++;
        }
}

//Warning - requires "load_SDL_palette" executed previously
void
PPU_2C02::build_32bpp_palette()
{
 for (unsigned color = 0; color < 64; color++)
        {
        ppu_32bpp_colors[color] = SDL_MapRGB(this->screen->format, sdl_colors[color].r, sdl_colors[color].g, sdl_colors[color].b);
        }
}


void
PPU_2C02::connect_data_bus(PPU_Data_Bus* db)
{
    data_bus = db;
    port_interface = new PPU_Port_Interface;
    port_interface->connect_ppu_side
            (
            db,
            spr_ram,
            shared_flip_flop,
            control_register_1,
            control_register_2,
            status_register,
            spr_ram_address_register,
            spr_ram_data_register,
            spr_dma_register,
            bkg_scroll_register,
            vram_data_register,
            vram_addr_register
            );
}

void
PPU_2C02::connect_cpu_nmi(bool* _cpu_nmi)
{
    cpu_nmi = _cpu_nmi;
}


const unsigned char*
PPU_2C02::get_palette()
{
 return ppu_raw_colors;
}

const unsigned
PPU_2C02::get_palette_size()
{
 return total_colors;
}


void
PPU_2C02::execute()
{
    unsigned start_tick = SDL_GetTicks();
    SDL_LockSurface(screen);

/*    if (sprite_debug)
        {
        std::cout << std::endl << "Sprite Temp Mem DUMP" << std::endl;
        std::cout << "Spr. Num  |  Hor. Pos.  | Scanline |  Diff  |  Tile  |  Attr " << std::endl;
        }*/

    if (control_register_2->read_bkg_visibility())
    {
        //LLenar con el bkg color
/*        unsigned fill_color = data_bus->read(0x3F00);
        frame_buffer->fill(fill_color);//FIXME! - Verificar que esto esta bien*/
        for (unsigned scanline = 0; scanline < scanlines_per_frame; scanline++)
        {
            render_scanline(scanline);
/*            if (sprite_debug)
                dump_sprite_temporary_memory(scanline);*/

            this->load_sprite_buffer_memory();
/*            if (buf_debug)
                dump_sprite_buf_mem(scanline);*/
        }
/*    if (sprite_debug)
        sprite_debug = false;
    if (buf_debug)
        buf_debug = false;*/
    }
    status_register->set_vblank();
    if (control_register_1->read_nmi_on_vblank())
        *cpu_nmi = true;

    //Frame buffer updates and statistics
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_UnlockSurface(screen);
    this->frame_counter++;
    unsigned stop_tick = SDL_GetTicks();
    this->tick_counter += (stop_tick - start_tick);
}


void
PPU_2C02::render_scanline(unsigned scanline_num)
{
    const unsigned tiles_per_scanline = 32;
    const unsigned preload_tiles_per_scanline = 2;

    if (scanline_num < 20)//VINT PERIOD
        return;
    else if (scanline_num == 20)
    {
        scanline_num = 0;
        scan_sprites_in_range(scanline_num);

        //Preload tiles 0-1 of next scanline
        for (unsigned tile_col = 0; tile_col < preload_tiles_per_scanline; tile_col++)
            clock_bkg_pipeline(tile_col, scanline_num);
    }
    else if (scanline_num < 251)
    {
        scanline_num -= 21;
        scan_sprites_in_range(scanline_num);

        unsigned tile_col = preload_tiles_per_scanline;
        while (tile_col < tiles_per_scanline) //Tiles 2 - 31
        {
            run_multiplexer(tile_col - 2, scanline_num);
            clock_bkg_pipeline(tile_col, scanline_num);
            tile_col++;
        }

        //Preload first two tiles of next scanline, render tiles 32-33 of current scanline
        while (tile_col < 34)
        {
            run_multiplexer(tile_col - 2, scanline_num);
            clock_bkg_pipeline(tile_col - 32, scanline_num + 1); //Tiles 0-1 of the NEXT scanline
            tile_col++;
        }
    }
    else
         return;
}


void
PPU_2C02::clock_bkg_pipeline(unsigned tile_col, unsigned scanline_num)
{
// std::cout << "Clock BKG - Tile column: " << tile_col << "  Scanline: " << scanline_num << std::endl;
 //Load selectors with preload_1 values
 bkg_pattern_0_selector = bkg_pattern_0_preload_1;
 bkg_pattern_1_selector = bkg_pattern_1_preload_1;
 bkg_attribute_selector = bkg_attribute_preload_1;

 //Preload Stage 1 registers
 unsigned tile_index = fetch_name_table_byte(tile_col, scanline_num);
 bkg_attribute_preload_1 = fetch_attr_table_byte(tile_col, scanline_num);
 bkg_pattern_0_preload_1 = fetch_bkg_pattern_0(tile_index, scanline_num);
 bkg_pattern_1_preload_1 = fetch_bkg_pattern_1(tile_index, scanline_num);
}


void
PPU_2C02::run_multiplexer(unsigned tile_column, unsigned scanline_num)
{
//    std::cout << "Multiplexer - Tile column: " << tile_column << "  Scanline: " << scanline_num << std::endl;
    for (unsigned pixel = 0; pixel < 8; pixel++)
    {
        unsigned horizontal_position = (tile_column * 8 + pixel);
        unsigned sprite_palette = 0, sprite_color_index = 0, sprite_priority = 0;
        int sprite_number = 0;
        unsigned bkg_palette = 0, bkg_color_index = 0;

        fetch_sprite_pixel(horizontal_position, &sprite_palette, &sprite_color_index, &sprite_priority, &sprite_number);
        bkg_palette = fetch_bkg_palette(bkg_attribute_selector, tile_column, scanline_num);
        bkg_color_index = fetch_bkg_pixel(horizontal_position);

        //If both sprite and bkg color indexes are non-transparent
        // and the sprite has slot number 0, and it is the sprite 0 itself (as specified by "sprite_0_in_range", because slot numbers are independent
        // from sprite numbers), then we have a BKG collision
        if ((sprite_number == 0) and this->sprite_0_in_range and (sprite_color_index != 0) and (bkg_color_index != 0))
            this->status_register->set_bkg_collision();

        if ((sprite_number != -1) and (sprite_priority == 0) and (sprite_color_index != 0))
            {
            pixel_out(horizontal_position, scanline_num, sprite_palette + 4, sprite_color_index);//Sprite palettes start after BKG palettes (there are 4 bkg palettes)
            }
        else
            pixel_out(horizontal_position, scanline_num, bkg_palette, bkg_color_index);
    }
}

void
PPU_2C02::fetch_sprite_pixel(unsigned hor_pos, unsigned* sprite_palette, unsigned* sprite_pixel, unsigned* sprite_priority, int* sprite_number)
{
    if (this->spr_buf_mem_count == 0)
    {
        *sprite_number = -1;
        return;
    }

    for (unsigned spr_num = 0; spr_num < 8 and spr_num < spr_buf_mem_count; spr_num++)
    {
        unsigned spr_hor_pos = spr_horiz_position[spr_num];
        if (hor_pos >= spr_hor_pos and hor_pos <= spr_hor_pos + 7)
        {
            unsigned sprite_pixel_col = hor_pos - spr_hor_pos;
            unsigned pixel_0 = (spr_shift_register[spr_num][0] >> (7 - sprite_pixel_col)) & 1;
            unsigned pixel_1 = (spr_shift_register[spr_num][1] >> (7 - sprite_pixel_col)) & 1;
            *sprite_pixel = pixel_0 | (pixel_1 << 1);
            if (*sprite_pixel == 0)
                continue;
            *sprite_palette = spr_attribute[spr_num] & 3;
            *sprite_priority = (spr_attribute[spr_num] >> 5) & 0x1;
            *sprite_number = spr_num;
            return;
        }
    }
    //No sprites have pixels in this horizontal position
    *sprite_number = -1;
    return;
}

unsigned
PPU_2C02::fetch_bkg_pixel(unsigned hor_pos)
{
    unsigned pixel_col = hor_pos % 8;
    unsigned bit_0 = bkg_pattern_0_selector >> (7 - pixel_col) & 0x1;
    unsigned bit_1 = bkg_pattern_1_selector >> (7 - pixel_col) & 0x1;
    return (bit_0 | (bit_1 << 1));
}

void
PPU_2C02::pixel_out(unsigned x, unsigned y, unsigned palette_select, unsigned palette_index)
{
 unsigned palette_base = 0x3F00 + 4 * palette_select;
 unsigned color_index = data_bus->read(palette_base + palette_index);
 if (color_index == 0)
        color_index = data_bus->read(0x3F00);

 unsigned* p = (unsigned *) screen->pixels;
 unsigned scaled_x = x * 2;
 unsigned scaled_y = y * 2;
 p[(scaled_y * this->frame_width) + scaled_x] = ppu_32bpp_colors[color_index];
 p[(scaled_y * this->frame_width) + scaled_x + 1] = ppu_32bpp_colors[color_index];
 p[((scaled_y + 1) * this->frame_width) + scaled_x] = ppu_32bpp_colors[color_index];
 p[((scaled_y + 1) * this->frame_width) + scaled_x + 1] = ppu_32bpp_colors[color_index];
}

unsigned
PPU_2C02::fetch_name_table_byte(unsigned tile_column, unsigned scanline_num)
{
unsigned name_table_base = 0x2000;
if (control_register_1->read_name_table_vert_scroll())
    name_table_base += 0x400;
if (control_register_1->read_name_table_hor_scroll())
    name_table_base += 0x800;

scanline_num += (this->bkg_scroll_register->read_value() & 0xFF00) >> 8;
unsigned tile_row = (scanline_num / 8);
unsigned tiles_per_row = 32;
tile_column += (this->bkg_scroll_register->read_value() & 0xFF) >> 3;
unsigned tile_offset = tiles_per_row * tile_row + tile_column;
return (data_bus->read(name_table_base + tile_offset));
}

unsigned
PPU_2C02::fetch_attr_table_byte(unsigned tile_col, unsigned scanline_num)
{
scanline_num += (this->bkg_scroll_register->read_value() & 0xFF00) >> 8;
tile_col += (this->bkg_scroll_register->read_value() & 0xFF) >> 3;
unsigned name_table_base = 0x2000;
if (control_register_1->read_name_table_vert_scroll())
    name_table_base += 0x400;
if (control_register_1->read_name_table_hor_scroll())
    name_table_base += 0x800;

 unsigned tile_row = (scanline_num / 8);
 unsigned attr_row = tile_row / 4;
 unsigned attr_col = tile_col / 4;
 const unsigned attr_cols_per_attr_row = 8;
 unsigned attr_offset = 0x3C0 + attr_row * attr_cols_per_attr_row + attr_col;
 return (data_bus->read(name_table_base + attr_offset));
}

unsigned
PPU_2C02::fetch_bkg_pattern_0(unsigned tile_index, unsigned scanline_num)
{
scanline_num += (this->bkg_scroll_register->read_value() & 0xFF00) >> 8;
unsigned pattern_base;
if (control_register_1->read_pattern_table_addr_bkg())
    pattern_base = 0x1000;
else
    pattern_base = 0x0000;

const unsigned pattern_size = 16;
pattern_base += pattern_size * tile_index;

unsigned vertical_offset = scanline_num % 8;
pattern_base += vertical_offset;

return(data_bus->read(pattern_base));
}

unsigned
PPU_2C02::fetch_bkg_pattern_1(unsigned tile_index, unsigned scanline_num)
{
scanline_num += (this->bkg_scroll_register->read_value() & 0xFF00) >> 8;

unsigned pattern_base;
if (control_register_1->read_pattern_table_addr_bkg())
    pattern_base = 0x1000;
else
    pattern_base = 0x0000;

const unsigned pattern_size = 16;
pattern_base += pattern_size * tile_index;

unsigned vertical_offset = scanline_num % 8;
pattern_base += vertical_offset;

return(data_bus->read(pattern_base + 8));
}

unsigned
PPU_2C02::fetch_bkg_palette(unsigned attr_byte, unsigned tile_col, unsigned scanline_num)
{
    scanline_num += (this->bkg_scroll_register->read_value() & 0xFF00) >> 8;

    unsigned tile_row = scanline_num / 8;
    unsigned tile_col_mod_4 = tile_col % 4;
    unsigned tile_row_mod_4 = tile_row % 4;

    if((tile_col_mod_4 == 0) or (tile_col_mod_4 == 1))
        ;
    else
        attr_byte >>= 2;

    if((tile_row_mod_4 == 0) or (tile_row_mod_4 == 1))
        ;
    else
        attr_byte >>= 4;

    return (attr_byte & 0x3);
}

void PPU_2C02::load_sprite_buffer_memory()
{
    unsigned sprite_num = 0;
    while (sprite_num < this->spr_temp_mem_count)
    {
        unsigned tile_index = spr_temp_mem[sprite_num*4];
        unsigned spr_attributes = spr_temp_mem[sprite_num*4+1];
        unsigned difference = spr_temp_mem[sprite_num*4+3];
        unsigned pattern_base = 0;

        if (this->control_register_1->read_sprite_size()) //8x16 Sprites
        {
            if (tile_index & 0x01)
                pattern_base = 0x1000;

            tile_index &= 0xFE;
            tile_index |= ((difference & 0x8) >> 3);
        }
        else // 8x8 Sprites
        {
            if (this->control_register_1->read_pattern_table_addr_spr())
                pattern_base = 0x1000;
        }
        //Pattern byte address calculation
        const unsigned pattern_size = 16;
        pattern_base += pattern_size * tile_index;
        unsigned vertical_offset = difference & 0x07;
        pattern_base += vertical_offset;

        //Pattern "scanline" fetches
        unsigned pattern_1 = data_bus->read(pattern_base);
        unsigned pattern_2 = data_bus->read(pattern_base + 8);

        //Perform horizontal inversion, if needed
        if (spr_attributes & 0x40)
        {
            pattern_1 = this->logical_invert(pattern_1);
            pattern_2 = this->logical_invert(pattern_2);
        }

        //Load data into sprite buffer memory
        spr_horiz_position[sprite_num] = spr_temp_mem[sprite_num*4+2];
        spr_attribute[sprite_num] = spr_attributes;
        spr_shift_register[sprite_num][0] = pattern_1;
        spr_shift_register[sprite_num][1] = pattern_2;

        sprite_num++;
    }
    while (sprite_num < 8)
        {
        spr_horiz_position[sprite_num] = 0;
        spr_attribute[sprite_num] = 0;
        spr_shift_register[sprite_num][0] = 0;
        spr_shift_register[sprite_num][1] = 0;
        sprite_num++;
        }
    this->spr_buf_mem_count = this->spr_temp_mem_count;
}

void PPU_2C02::scan_sprites_in_range(unsigned scanline_number)
{
    unsigned temp_mem_index = 0;
    unsigned spr_ram_address = 0;
    bool sprite_in_range = false;

    this->sprite_0_in_range = false;

    //Init Sprite temporary memory with 0xFF as the real Famicom
    for (unsigned i = 0; i < 32; i++)
        spr_temp_mem[i] = 0xFF;

    for (spr_ram_address = 0; spr_ram_address < 256; spr_ram_address += 4)
        {
        //The SPR-RAM addr. register value must always match this loop "spr_ram_address" value
        this->spr_ram_address_register->set_value(spr_ram_address);

        unsigned vertical_position = this->spr_ram->read(spr_ram_address);
        int difference = (int) scanline_number - (int) vertical_position;

        if (this->control_register_1->read_sprite_size()) //8x16 sprites
            {
            if (difference < 16 and difference >= 0)
                sprite_in_range = true;
            else
                sprite_in_range = false;
            }
        else //8x8 sprites
            {
            if (difference < 8 and difference >= 0)
                sprite_in_range = true;
            else
                sprite_in_range = false;
            }

        if (sprite_in_range)
            {
            if (temp_mem_index < 8)//If no sprite overflow has occurred (8 sprites can fit before overflow occurs)
                {
                unsigned tile_index = this->spr_ram->read(spr_ram_address + 1);
                unsigned sprite_attributes = this->spr_ram->read(spr_ram_address + 2);
                unsigned horiz_position = this->spr_ram->read(spr_ram_address + 3);
/*                if (sprite_debug)
                    {
                    std::cout << "Spr Ram Addr: " << spr_ram_address << std::endl;
                    std::cout << "Scanline: " << scanline_number << std::endl;
                    std::cout << "Vertical position " << vertical_position << std::endl;
                    std::cout << "Difference " << difference << std::endl;
                    if (sprite_attributes & 0x80)
                        std::cout << "Inverted difference: " << this->invert_difference(difference);
                    std::cout << "Tile Index: " << tile_index << std::endl;
                    std::cout << "Spr Attrib: " << sprite_attributes << std::endl;
                    std::cout << "Horiz Pos: " << horiz_position << std::endl;
                    std::cout << "Total sprites buffered: " << temp_mem_index + 1 << std::endl;
                    }*/

                //Apply vertical inversion to the difference, if needed
                if (sprite_attributes & 0x80)
                    difference = this->invert_difference(difference);

                //Copy Sprite information to Sprite temporary memory
                spr_temp_mem[temp_mem_index*4] = tile_index;
                spr_temp_mem[temp_mem_index*4 + 1] = sprite_attributes;
                spr_temp_mem[temp_mem_index*4 + 2] = horiz_position;
                spr_temp_mem[temp_mem_index*4 + 3] = (unsigned) difference;
                temp_mem_index++;

                //Sprite 0 found in range?
                if (spr_ram_address == 0)
                    this->sprite_0_in_range = true;
                }
            else //Sprite overflow has occurred
                this->status_register->set_sprite_overflow();
            }//end if (sprite_in_range)
        }//end for

    this->spr_temp_mem_count = temp_mem_index;
}

unsigned PPU_2C02::logical_invert(unsigned i)
{
    unsigned o = 0;

    for (unsigned bit = 0; bit < 8; bit++)
        if (i & (1 << bit))
            o |= (1 << (7 - bit));

    return o;
}

int PPU_2C02::invert_difference(int d)
{
    if (this->control_register_1->read_sprite_size())
    {
        return 15 - d;
    }
    else
        return 7 - d;
}

void
PPU_2C02::dump_sprite_temporary_memory(unsigned scanline)
{
    for (unsigned i = 0; i < this->spr_temp_mem_count; i++)
        {
        std::cout << "   " << i << "             " << spr_temp_mem[i*4+2];
        std::cout << "      " << scanline;
        std::cout << "         " << spr_temp_mem[i*4 + 3] << "       " << spr_temp_mem[i*4];
        std::cout << "      " << spr_temp_mem[i*4 + 1] << std::endl;
        }
}

void
PPU_2C02::dump_sprite_buf_mem()
{
    if (this->spr_buf_mem_count == 0)
        return;

    std::cout << "Slot | Hor. Pos. | Attr. | Shift 1 | Shift 2" << std::endl;
    for (unsigned i = 0; i < this->spr_buf_mem_count; i++)
        {
        std::cout << "  " << i << "    " << spr_horiz_position[i];
        std::cout << "    " << spr_attribute[i];
        std::cout << "    " << spr_shift_register[i][0];
        std::cout << "    " << spr_shift_register[i][1];
        }
}

//=====================================================================================
// OLD ROUTINES
//=====================================================================================
void
PPU_2C02::fetch_pattern_scanline(unsigned scanline_num, unsigned pattern_number, unsigned* pattern_1, unsigned* pattern_2)
{
unsigned pattern_base;
if (control_register_1->read_pattern_table_addr_bkg())
    pattern_base = 0x1000;
else
    pattern_base = 0x0000;

const unsigned pattern_size = 16;
pattern_base += pattern_size * pattern_number;

unsigned vertical_offset = scanline_num % 8;
pattern_base += vertical_offset;

*pattern_1 = data_bus->read(pattern_base);
*pattern_2 = data_bus->read(pattern_base + 8);
}

/* Original version
void
PPU_2C02::fetch_attr_bits(unsigned attr_byte, unsigned tile_col, unsigned scanline_num, unsigned* color_bits)
{
    unsigned tile_row = scanline_num / 8;
    unsigned tile_col_mod_4 = tile_col % 4;
    unsigned tile_row_mod_4 = tile_row % 4;

    if((tile_col_mod_4 == 0) or (tile_col_mod_4 == 1))
        ;
    else
        attr_byte >>= 2;

    if((tile_row_mod_4 == 0) or (tile_row_mod_4 == 1))
        ;
    else
        attr_byte >>= 4;

    *color_bits = attr_byte & 0x3;
}
*/

void
PPU_2C02::render_pattern_row(unsigned start_col, unsigned row, unsigned palette_select, unsigned pattern_1, unsigned pattern_2)
{
 unsigned palette_base = 0x3F00 + 4 * palette_select;

 char* p = (char *) screen->pixels;

 for (unsigned pixel_col = 0; pixel_col < 8; pixel_col++)
    {
    unsigned pattern_1_bit = (pattern_1 >> (7 - pixel_col)) & 0x1;
    unsigned pattern_2_bit = (pattern_2 >> (7 - pixel_col)) & 0x1;
    unsigned palette_index = pattern_1_bit | (pattern_2_bit << 1);
    unsigned color_index = data_bus->read(palette_base + palette_index);

    //FIXME! - Cuando haya sprites, esto cambia
    if (palette_index == 0)
        color_index = data_bus->read(0x3F00);

    //frame_buffer->setPixel(start_col + pixel_col, row, color_index);
    p[row*256 + start_col + pixel_col] = color_index;
    }

}

/* LEGACY RENDERER
        unsigned name_table_base = 0x2000;
        if (control_register_1->read_name_table_vert_scroll())
            name_table_base += 0x400;
        if (control_register_1->read_name_table_hor_scroll())
            name_table_base += 0x800;

        unsigned tile_row = (scanline_num / 8);
        unsigned tiles_per_row = 32;
        unsigned tile_offset = tiles_per_row * tile_row;

        unsigned attr_offset = 0x3C0;
        for (unsigned tile_col = 0; tile_col < 32; tile_col++)//32 tiles per scanline
        {
            unsigned pattern_number = data_bus->read(name_table_base + tile_offset);

            unsigned attr_row = tile_row / 4;
            unsigned attr_col = tile_col / 4;
            const unsigned attr_cols_per_attr_row = 8;
            attr_offset = 0x3C0 + attr_row * attr_cols_per_attr_row + attr_col;
            unsigned attr_byte = data_bus->read(name_table_base + attr_offset);
            tile_offset++;

            unsigned pattern_1, pattern_2;
            fetch_pattern_scanline(scanline_num, pattern_number, &pattern_1, &pattern_2);
            unsigned attr_color_bits;
            fetch_attr_bits(attr_byte, tile_col, scanline_num, &attr_color_bits);
            render_pattern_row(tile_col * 8, scanline_num, attr_color_bits, pattern_1, pattern_2);
        }
*/
