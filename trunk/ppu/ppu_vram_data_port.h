#ifndef PPU_VRAM_DATA_PORT_H
#define PPU_VRAM_DATA_PORT_H

#include "port/port_8bit.h"
#include "register/register_8bit.h"
#include "register/register_16bit.h"

class PPU_Data_Bus;
class PPU_Control_Register_1;

class PPU_VRAM_Data_Port : Port_8bit
{
public:
    PPU_VRAM_Data_Port(PPU_Control_Register_1* control_reg, Register_16bit* addr_reg, PPU_Data_Bus* bus);
    unsigned read();
    void write(unsigned value);

private:
    void adjust_address_after_rw();

private:
    PPU_Control_Register_1* control_register;
    Register_16bit*          addr_register;
    Register_8bit           data_latch;
    PPU_Data_Bus*           bus;
};

#endif // PPU_VRAM_DATA_PORT_H
