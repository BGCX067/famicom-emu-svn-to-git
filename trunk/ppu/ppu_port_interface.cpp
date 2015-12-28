#include "ppu_port_interface.h"
#include "data_bus/ppu/ppu_data_bus.h"
#include "ppu_status_port.h"
#include "ppu_vram_address_port.h"
#include "ppu_vram_data_port.h"
#include "ppu_spr_ram_address_port.h"
#include "ppu_spr_ram_data_port.h"
#include "ppu_bkg_scroll_port.h"
#include "data_bus/memory_bank.h"
#include "port/port_passthru_8bit.h"
#include <iostream>

PPU_Port_Interface::PPU_Port_Interface()
{
}

PPU_Port_Interface::~PPU_Port_Interface()
{
    delete status_port;
    delete vram_data_port;
    delete vram_addr_port;
    delete spr_ram_data_port;
    delete spr_ram_addr_port;
    delete control_1_port;
    delete control_2_port;
    delete spr_dma_port;
    delete bkg_scroll_port;
}

void
PPU_Port_Interface::connect_ppu_side(
        PPU_Data_Bus* ppu_bus,
        Memory_Bank* spr_ram_bank,
        Flip_Flop* flip_flop,
        PPU_Control_Register_1* control_1,
        PPU_Control_Register_2* control_2,
        PPU_Status_Register* status,
        Register_8bit* spr_ram_addr,
        Register_8bit* spr_ram_data,
        Register_8bit* spr_dma,
        Register_16bit* bkg_scroll,
        Register_8bit* vram_data,
        Register_16bit* vram_addr
        )
{
    status_port = new PPU_Status_Port(status, flip_flop);
    vram_data_port = new PPU_VRAM_Data_Port(control_1, vram_addr, ppu_bus);
    vram_addr_port = new PPU_VRAM_Address_Port(vram_addr, flip_flop);
    spr_ram_data_port = new PPU_SPR_RAM_Data_Port(spr_ram_data, spr_ram_bank);
    spr_ram_addr_port = new PPU_SPR_RAM_Address_Port(spr_ram_addr);
    bkg_scroll_port = new PPU_BKG_Scroll_Port(bkg_scroll, flip_flop);
    control_1_port = new Port_Passthru_8bit((Register_8bit*) control_1);
    control_2_port = new Port_Passthru_8bit((Register_8bit*) control_2);
    spr_dma_port = new Port_Passthru_8bit(spr_dma);//FIXME! - No usado aca, va en CPU directamente
}


unsigned
PPU_Port_Interface::read(unsigned address)
{
 switch(address)
 {
 case 0x2:
     return (status_port->read());
     break;
 case 0x4:
     return (spr_ram_data_port->read());
     break;
 case 0x7:
     return (vram_data_port->read());
     break;
 default:
     return 0;
     break;
 }
}

void
PPU_Port_Interface::write(unsigned address, unsigned value)
{
//    std::cout << "PPU Port Interface Write - Addr: " << address << " - Value: " << value << std::endl;
    switch(address)
    {
    case 0x0:
        control_1_port->write(value);
        break;
    case 0x1:
        control_2_port->write(value);
        break;
    case 0x3:
        spr_ram_addr_port->write(value);
        break;
    case 0x4:
        spr_ram_data_port->write(value);
        break;
    case 0x5:
        bkg_scroll_port->write(value);
        break;
    case 0x6:
        vram_addr_port->write(value);
        break;
    case 0x7:
        vram_data_port->write(value);
        break;
    default:
        break;
    }
}
