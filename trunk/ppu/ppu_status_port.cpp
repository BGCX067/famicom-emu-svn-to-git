#include "ppu_status_port.h"
#include "ppu_status_register.h"
#include "flip_flop.h"

PPU_Status_Port::PPU_Status_Port(PPU_Status_Register* r, Flip_Flop* f): status_register(r), flip_flop(f)
{
}

unsigned
PPU_Status_Port::read()
{
 unsigned ret_value = status_register->read_value();
 status_register->clear_vblank();
 flip_flop->reset();
 return ret_value;
}

void
PPU_Status_Port::write(unsigned value)
{
 status_register->set_value(value);
}
