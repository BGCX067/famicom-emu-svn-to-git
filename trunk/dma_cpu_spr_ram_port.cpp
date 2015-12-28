#include "dma_cpu_spr_ram_port.h"
#include "data_bus/cpu/cpu_data_bus.h"
#include "register/register_8bit.h"
#include "ppu/ppu_spr_ram_data_port.h"

DMA_CPU_SPR_RAM_Port::DMA_CPU_SPR_RAM_Port(
        CPU_Data_Bus* _cpu_data_bus,
        PPU_SPR_RAM_Data_Port* _data_port) :
        cpu_data_bus(_cpu_data_bus),
        spr_data_port(_data_port)
{
}

void
DMA_CPU_SPR_RAM_Port::write(unsigned value)
{
    unsigned addr_hi = value;

    for (unsigned addr_lo = 0; addr_lo < 256; addr_lo++)
    {
        unsigned full_read_address = addr_lo | (addr_hi << 8);
        unsigned data = cpu_data_bus->read(full_read_address);
        spr_data_port->write(data);
    }
}
