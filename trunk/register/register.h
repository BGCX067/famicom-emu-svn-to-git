#ifndef REGISTER_H
#define REGISTER_H

class Register
{
public:
    Register();
    virtual ~Register();

    virtual void        set_bit(unsigned bit_position) = 0;
    virtual void        clear_bit(unsigned bit_position) = 0;
    virtual unsigned    read_bit(unsigned bit_position) = 0;
    virtual void        set_value(unsigned value) = 0;
    virtual unsigned    read_value() = 0;
};

#endif // REGISTER_H
