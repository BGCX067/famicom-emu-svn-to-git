#ifndef REGISTER_16BIT_H
#define REGISTER_16BIT_H

#include "register.h"

class Register_16bit : public Register
{
public:
    Register_16bit();

    void        set_bit(unsigned bit_position);
    void        clear_bit(unsigned bit_position);
    unsigned    read_bit(unsigned bit_position);
    virtual void        set_value(unsigned value);
    virtual unsigned    read_value();

private:
    unsigned    value;
};

#endif // REGISTER_16BIT_H
