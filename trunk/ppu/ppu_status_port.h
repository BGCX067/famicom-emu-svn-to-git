#ifndef PPU_STATUS_PORT_H
#define PPU_STATUS_PORT_H

#include "port/port_8bit.h"

class PPU_Status_Register;
class Flip_Flop;

class PPU_Status_Port : public Port_8bit
{
public:
    PPU_Status_Port(PPU_Status_Register* r, Flip_Flop* f);
    unsigned read();
    void write(unsigned value);

private:
    PPU_Status_Register*    status_register;
    Flip_Flop*              flip_flop;
};

#endif // PPU_STATUS_PORT_H
