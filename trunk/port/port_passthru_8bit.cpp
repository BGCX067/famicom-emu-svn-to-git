#include "port_passthru_8bit.h"
#include "register/register_8bit.h"
#include <iostream>

Port_Passthru_8bit::Port_Passthru_8bit(Register_8bit* r) : _register(r)
{
}

void
Port_Passthru_8bit::write(unsigned value)
{
    //std::cout << "Passthru Port Write  - Value: " << value << std::endl;
    _register->set_value(value);
}

unsigned
Port_Passthru_8bit::read()
{
    return (_register->read_value());
}
