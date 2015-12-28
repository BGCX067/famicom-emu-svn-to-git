#include "ppu_spr_ram_data_port.h"
#include "register/register_8bit.h"
#include "data_bus/memory_bank.h"

PPU_SPR_RAM_Data_Port::PPU_SPR_RAM_Data_Port(Register_8bit* _addr_register, Memory_Bank* _bank)
    : addr_register(_addr_register), bank(_bank)
{
}

unsigned
PPU_SPR_RAM_Data_Port::read()
{
    unsigned read_address = addr_register->read_value();
    return (bank->read(read_address));
}

void
PPU_SPR_RAM_Data_Port::write(unsigned value)

{
    unsigned write_address = addr_register->read_value();
    bank->write(write_address, value);
    write_address++;
    write_address &= 0xFF;
    addr_register->set_value(write_address);
}
