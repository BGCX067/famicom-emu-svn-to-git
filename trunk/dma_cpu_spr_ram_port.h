#ifndef DMA_CPU_SPR_RAM_PORT_H
#define DMA_CPU_SPR_RAM_PORT_H

#include "port/port_8bit.h"

class CPU_Data_Bus;
class Memory_Bank;
class Register_8bit;
class PPU_SPR_RAM_Data_Port;


class DMA_CPU_SPR_RAM_Port : Port_8bit
{
public:
    DMA_CPU_SPR_RAM_Port(CPU_Data_Bus*, PPU_SPR_RAM_Data_Port*);
    void write(unsigned value);
    unsigned read() { return 0; };

private:
    CPU_Data_Bus*   cpu_data_bus;
    PPU_SPR_RAM_Data_Port*  spr_data_port;
};

#endif // DMA_CPU_SPR_RAM_PORT_H
