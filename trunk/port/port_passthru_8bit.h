#ifndef PORT_PASSTHRU_8BIT_H
#define PORT_PASSTHRU_8BIT_H

#include "port_8bit.h"

class Register_8bit;

class Port_Passthru_8bit : public Port_8bit
{
public:
    Port_Passthru_8bit(Register_8bit* r);
    void write(unsigned value);
    unsigned read();

private:
    Register_8bit*  _register;
};

#endif // PORT_PASSTHRU_8BIT_H
