#ifndef FLAGS_REGISTER_H
#define FLAGS_REGISTER_H

#include "register/register_8bit.h"

class Flags_Register : public Register_8bit
{
public:
    Flags_Register();
    void clear_carry()      {clear_bit(0);};
    void set_carry()        {set_bit(0);};
    void clear_zero()       {clear_bit(1);};
    void set_zero()         {set_bit(1);};
    void clear_interrupt()  {clear_bit(2);};
    void set_interrupt()    {set_bit(2);};
    void clear_decimal()    {clear_bit(3);};
    void set_decimal()      {set_bit(3);};
    void clear_break()      {clear_bit(4);};
    void set_break()        {set_bit(4);};
    void clear_unused()     {clear_bit(5);};
    void set_unused()       {set_bit(5);};
    void clear_overflow()   {clear_bit(6);};
    void set_overflow()     {set_bit(6);};
    void clear_negative()   {clear_bit(7);};
    void set_negative()     {set_bit(7);};

    unsigned read_carry()   {return read_bit(0);};
    unsigned read_zero()    {return read_bit(1);};
    unsigned read_interrupt()   {return read_bit(2);};
    unsigned read_decimal() {return read_bit(3);};
    unsigned read_break()   {return read_bit(4);};
    unsigned read_unused()  {return read_bit(5);};
    unsigned read_overflow(){return read_bit(6);};
    unsigned read_negative(){return read_bit(7);};
};

#endif // FLAGS_REGISTER_H
