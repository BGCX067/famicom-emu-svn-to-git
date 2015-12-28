#include "ppu_vram_data_port.h"
#include "ppu_control_register_1.h"
#include "data_bus/ppu/ppu_data_bus.h"
#include <iostream>

PPU_VRAM_Data_Port::PPU_VRAM_Data_Port(
        PPU_Control_Register_1* _control_reg,
        Register_16bit* _addr_reg,
        PPU_Data_Bus* _bus) :
        control_register(_control_reg), addr_register(_addr_reg), bus(_bus)
{
}

unsigned
PPU_VRAM_Data_Port::read()
{
    unsigned read_address = addr_register->read_value();
    adjust_address_after_rw();

    //Addresses below 0x3F00 are latched first.
    // On every read operation, the latch value is returned
    // and a new latch value will be written to the latch after the read
    if (read_address < 0x3F00)
    {
        unsigned ret_val = data_latch.read_value();
        data_latch.set_value(bus->read(read_address));
        return ret_val;
    }
    else
    //Addresses equal and above are read immediately (Palette RAM)
    {
        return (bus->read(read_address));
    }
}

void
PPU_VRAM_Data_Port::write(unsigned value)
{
    unsigned write_address = addr_register->read_value();
//    std::cout << "PPU Port Interface Write - Addr: " << write_address << " - Value: " << value << std::endl;
    bus->write(write_address, value);
    adjust_address_after_rw();
//    std::cout << "Finish Write" << std::endl;
}

void
PPU_VRAM_Data_Port::adjust_address_after_rw()
{
//    std::cout << "Adjust address after RW" << std::endl;
    unsigned address = addr_register->read_value();
//    std::cout << "Original address " << address << std::endl;
    if (control_register->read_vram_addr_increment())
        address += 32;
    else
        address++;
    address &= 0xFFFF;
//    std::cout << "Adjusted address " << address << std::endl;
    addr_register->set_value(address);
}
