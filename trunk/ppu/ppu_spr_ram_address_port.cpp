#include "ppu_spr_ram_address_port.h"
#include "register/register_8bit.h"

PPU_SPR_RAM_Address_Port::PPU_SPR_RAM_Address_Port(Register_8bit* addr_reg) : addr_register(addr_reg)
{
}

void
PPU_SPR_RAM_Address_Port::write(unsigned value)
{
 addr_register->set_value(value);
}


unsigned
PPU_SPR_RAM_Address_Port::read()
{
    return (0); // Read only port
}
