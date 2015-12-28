#include "alu.h"
#include <iostream>

ALU::ALU()
{
}

unsigned ALU::add(unsigned v1, unsigned v2)
{
    unsigned sum = v1 + v2 + read_carry();
    if (sum & 0x100)
        set_carry();
    else
        clear_carry();
    unsigned r1 = (v1 ^ v2) & 0x80;
    unsigned r2 = (v1 ^ sum) & 0x80;
    if (!r1 && r2)
        set_overflow();
    else
        clear_overflow();

    return (sum & 0xFF);
}

unsigned ALU::subtract(unsigned v1, unsigned v2)
{
/*    std::cout << "Subtract" << std::endl;
    std::cout << "V1: " << v1 << std::endl;
    std::cout << "V2: " << v2 << std::endl;
    std::cout << "Input carry: " << read_carry() << std::endl;*/
    unsigned sum = v1 - v2 - (!read_carry());
//    std::cout << "Result: " << (sum & 0xFF) << std::endl;

    if (sum < 0x100)
    {
        set_carry();
//        std::cout << "Carry set" << std::endl;
    }
    else
    {
        clear_carry();
//        std::cout << "Carry clear" << std::endl;
    }
    unsigned r1 = (v1 ^ v2) & 0x80;
    unsigned r2 = (v1 ^ sum) & 0x80;
    if (r1 && r2)
    {
        set_overflow();
//        std::cout << "Overflow set" << std::endl;
    }
    else
    {
        clear_overflow();
//        std::cout << "Overflow clear" << std::endl;
    }

    return (sum & 0xFF);
}

unsigned ALU::compare(unsigned v1, unsigned v2)
{
    int sum = (int) v1 - (int) v2;

    if (v1 >= v2)
        set_carry();
    else
        clear_carry();

    return (sum & 0xFF);
}


unsigned ALU::increment(unsigned v)
{
    v++;
    return (v & 0xFF);
}

unsigned ALU::decrement(unsigned v)
{
    v--;
    return (v & 0xFF);
}


unsigned ALU::_or(unsigned v1, unsigned v2)
{
    return (v1 | v2);
}

unsigned ALU::_and(unsigned v1, unsigned v2)
{
    return (v1 & v2);
}

unsigned ALU::_xor(unsigned v1, unsigned v2)
{
    return (v1 ^ v2);
}

unsigned ALU::shift_left(unsigned value)
{
    if (value & 0x80)
        set_carry();
    else
        clear_carry();

    return ((value << 1) & 0xFF);
}

unsigned ALU::shift_right(unsigned value)
{
    if (value & 0x01)
        set_carry();
    else
        clear_carry();

    return ((value >> 1) & 0xFF);
}

unsigned ALU::rotate_left(unsigned value)
{
    unsigned new_carry = value & 0x80;
    value = (value << 1) & 0xFF;

    if (read_carry())
        value |= 0x01;

    if (new_carry)
        set_carry();
    else
        clear_carry();

    return (value);
}

unsigned ALU::rotate_right(unsigned value)
{
    unsigned new_carry = value & 0x01;

    value >>= 1;

    if (read_carry())
        value |= 0x80;

    if (new_carry)
        set_carry();
    else
        clear_carry();

    return (value);
}

void ALU::set_carry()
{
    carry = 1;
}

void ALU::clear_carry()
{
    carry = 0;
}

unsigned ALU::read_carry()
{
    return carry;
}

void ALU::set_overflow()
{
    overflow = 1;
}

void ALU::clear_overflow()
{
    overflow = 0;
}

unsigned ALU::read_overflow()
{
    return overflow;
}

void ALU::set_negative()
{
    negative = 1;
}

void ALU::clear_negative()
{
    negative = 0;
}

unsigned ALU::read_negative()
{
    return negative;
}

void ALU::set_zero()
{
    zero = 1;
}

void ALU::clear_zero()
{
    zero = 0;
}

unsigned ALU::read_zero()
{
    return zero;
}
