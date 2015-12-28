#include "apu_port_interface.h"
#include "dma_cpu_spr_ram_port.h"
#include "data_bus/cpu/cpu_data_bus.h"
#include "controller_port.h"
#include "controller_inputs.h"

APU_Port_Interface::APU_Port_Interface()
{
}

APU_Port_Interface::~APU_Port_Interface()
{
    delete spr_ram_dma_port;
    delete joypad_1_port;
}

void
APU_Port_Interface::connect_dma_spr_ram(CPU_Data_Bus* cpu_bus, PPU_SPR_RAM_Data_Port* data_port)
{
    spr_ram_dma_port = new DMA_CPU_SPR_RAM_Port(cpu_bus, data_port);
}

void
APU_Port_Interface::connect_gamepad_a_inputs(Controller_Inputs* gamepad_a_inputs)
{
    joypad_1_port = new Controller_Port(gamepad_a_inputs);
}


unsigned
APU_Port_Interface::read(unsigned address)
{
 switch(address)
 {
 case 0x16:
    return joypad_1_port->read();
    break;
 default:
     return 0;
     break;
 }
}

void
APU_Port_Interface::write(unsigned address, unsigned value)
{
    switch(address)
    {
    case 0x14:
        spr_ram_dma_port->write(value);
        break;
    case 0x16:
        joypad_1_port->write(value);
    default:
        break;
    }
}
