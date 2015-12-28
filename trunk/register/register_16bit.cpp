#include "register_16bit.h"

Register_16bit::Register_16bit()
{
    value = 0;
}

void
Register_16bit::set_bit(unsigned bit_position)
{
    value |= (1 << bit_position);
}

void
Register_16bit::clear_bit(unsigned bit_position)
{
    unsigned mask = ((0xFFFF) ^ (1 << bit_position)) & 0xFFFF;
    value &= mask;
}

unsigned
Register_16bit::read_bit(unsigned bit_position)
{
    return (value >> bit_position) & 0x1;
}

void
Register_16bit::set_value(unsigned v)
{
 value = v;
}

unsigned
Register_16bit::read_value()
{
 return value;
}
