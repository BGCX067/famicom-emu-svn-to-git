#include "apu.h"
#include "apu_port_interface.h"

APU::APU()
{
    port_interface = new APU_Port_Interface;
}

APU::~APU()
{
    delete port_interface;
}


