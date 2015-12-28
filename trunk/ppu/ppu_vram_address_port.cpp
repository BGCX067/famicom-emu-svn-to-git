#include "ppu_vram_address_port.h"
#include "flip_flop.h"
#include <iostream>

PPU_VRAM_Address_Port::PPU_VRAM_Address_Port(Register_16bit* _address_full, Flip_Flop* _flip_flop)
    : address_full(_address_full), flip_flop(_flip_flop)
{
}

void
PPU_VRAM_Address_Port::write(unsigned value)
{
//    std::cout << "PPU VRAM Addres Port Write - Value: " << value << std:: endl;
    //FIXME! - Revisar esto
    if (flip_flop->output())
    {
//        std::cout << "Flip Flop is SET" << std:: endl;
//        std::cout << "Setting Addr Lo to " << value << std:: endl;
        address_low.set_value(value);
    }
    else
    {
//        std::cout << "Flip Flop is CLEAR" << std:: endl;
//        std::cout << "Setting Addr Hi to " << value << std:: endl;
        address_high.set_value(value);
    }
    address_full->set_value(address_low.read_value() | (address_high.read_value() << 8));
//    std::cout << "Addr FULL is " << address_full->read_value() << std:: endl;
    flip_flop->invert();
}


unsigned
PPU_VRAM_Address_Port::read()
{
    return (0); //READ ONLY REGISTER
}
