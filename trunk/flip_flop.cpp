#include "flip_flop.h"

Flip_Flop::Flip_Flop()
{
}

void
Flip_Flop::set()
{
    flip_flop = true;
}

void
Flip_Flop::reset()
{
    flip_flop = false;
}

void
Flip_Flop::invert()
{
    flip_flop = !flip_flop;
}

bool
Flip_Flop::output()
{
    return flip_flop;
}
