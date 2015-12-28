#include "register_8bit.h"

Register_8bit::Register_8bit()
{
    value = 0;
}

void
Register_8bit::set_bit(unsigned bit_position)
{
    value |= (1 << bit_position);
}

void
Register_8bit::clear_bit(unsigned bit_position)
{
    unsigned mask = ((0xFF) ^ (1 << bit_position)) & 0xFF;
    value &= mask;
}

unsigned
Register_8bit::read_bit(unsigned bit_position)
{
    return (value >> bit_position) & 0x1;
}

void
Register_8bit::set_value(unsigned v)
{
 value = v;
}

unsigned
Register_8bit::read_value()
{
 return value;
}
