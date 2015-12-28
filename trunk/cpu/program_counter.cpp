#include "program_counter.h"

Program_Counter::Program_Counter()
{
    set_value(0x0000);
}

unsigned
Program_Counter::read()
{
    return (value & 0xFFFF);
}

void
Program_Counter::set_value(unsigned v)
{
    value = v;
}

void
Program_Counter::increment()
{
    if (value == 0xFFFF)
        value = 0x0000;
    else
        value++;
}

void
Program_Counter::decrement()
{
    if (value == 0x0000)
        value = 0xFFFF;
    else
        value--;
}

bool
Program_Counter::add_relative(unsigned operand)
{
    //Store current PC page (high byte) for comparison
    unsigned pc_page = value & 0xFF00;

    if (operand & 0x80)
    {
        value += (operand ^ 0x80) - 0x80;
        value &= 0xFFFF;
    }
    else
        value += operand;

    //Return whether the page changed or not
    unsigned dest_page = value & 0xFF00;
    return (pc_page == dest_page);
}
