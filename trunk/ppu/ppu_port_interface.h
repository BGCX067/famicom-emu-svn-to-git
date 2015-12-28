#ifndef PPU_PORT_INTERFACE_H
#define PPU_PORT_INTERFACE_H

class PPU_Data_Bus;
class Memory_Bank;
class Flip_Flop;
class PPU_Control_Register_1;
class PPU_Control_Register_2;
class PPU_Status_Register;
class Register_8bit;
class Register_16bit;
class PPU_BKG_Scroll_Port;
class PPU_Status_Port;
class PPU_VRAM_Data_Port;
class PPU_VRAM_Address_Port;
class PPU_SPR_RAM_Data_Port;
class PPU_SPR_RAM_Address_Port;
class Port_Passthru_8bit;


class PPU_Port_Interface
{
public:
    PPU_Port_Interface();
    ~PPU_Port_Interface();

    void connect_ppu_side(
            PPU_Data_Bus*,
            Memory_Bank*,
            Flip_Flop*,
            PPU_Control_Register_1*,
            PPU_Control_Register_2*,
            PPU_Status_Register*,
            Register_8bit*,
            Register_8bit*,
            Register_8bit*,
            Register_16bit*,
            Register_8bit*,
            Register_16bit*
            );
//    PPU_SPR_RAM_Data_Port* get_spr_ram_data_port() {return spr_dma_port;};

    unsigned read(unsigned address);
    void write(unsigned address, unsigned value);

public:
    //Specialized ports, with collateral effects
    PPU_Status_Port*            status_port;
    PPU_VRAM_Data_Port*         vram_data_port;
    PPU_VRAM_Address_Port*      vram_addr_port;
    PPU_SPR_RAM_Data_Port*      spr_ram_data_port;
    PPU_SPR_RAM_Address_Port*   spr_ram_addr_port;
    PPU_BKG_Scroll_Port*        bkg_scroll_port;

    //Pass-thru ports
    Port_Passthru_8bit*         control_1_port;
    Port_Passthru_8bit*         control_2_port;
    Port_Passthru_8bit*         spr_dma_port;
};

#endif // PPU_PORT_INTERFACE_H
