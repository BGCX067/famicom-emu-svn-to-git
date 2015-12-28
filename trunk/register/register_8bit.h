#ifndef REGISTER_8BIT_H
#define REGISTER_8BIT_H

#include "register.h"

class Register_8bit : public Register
{
public:
    Register_8bit();

            void        set_bit(unsigned bit_position);
            void        clear_bit(unsigned bit_position);
            unsigned    read_bit(unsigned bit_position);
    virtual void        set_value(unsigned value);
    virtual unsigned    read_value();

private:
    unsigned    value;
};

#endif // REGISTER_8BIT_H
