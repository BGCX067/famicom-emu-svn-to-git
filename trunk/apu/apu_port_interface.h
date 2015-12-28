#ifndef APU_PORT_INTERFACE_H
#define APU_PORT_INTERFACE_H

class Port_Passthru_8bit;
class Register_8bit;
class CPU_Data_Bus;
class PPU_SPR_RAM_Data_Port;
class DMA_CPU_SPR_RAM_Port;
class Controller_Port;
class Controller_Inputs;

class APU_Port_Interface
{
public:
    APU_Port_Interface();
    ~APU_Port_Interface();

    void connect_dma_spr_ram(CPU_Data_Bus* cpu_bus, PPU_SPR_RAM_Data_Port* data_port);
    void connect_gamepad_a_inputs(Controller_Inputs* gamepad_a_inputs);

 /*void connect_ppu_side(
                Register_8bit*,
                Register_8bit*,
                Register_8bit*,
                Register_8bit*,
                Register_8bit*,
                Register_8bit*
                );*/

        unsigned read(unsigned address);
        void write(unsigned address, unsigned value);

public:
        //Specialized ports, with collateral effects
        Port_Passthru_8bit*         ch1_vol_decay_port;
        Port_Passthru_8bit*         ch1_sweep_port;
        Port_Passthru_8bit*         ch1_freq_port;
        Port_Passthru_8bit*         ch1_length_port;
        Port_Passthru_8bit*         ch2_vol_decay_port;
        Port_Passthru_8bit*         ch2_sweep_port;
        Port_Passthru_8bit*         ch2_freq_port;
        Port_Passthru_8bit*         ch2_length_port;
        Port_Passthru_8bit*         ch3_linear_counter_port;
        Port_Passthru_8bit*         ch3_freq_port;
        Port_Passthru_8bit*         ch3_length_port;
        Port_Passthru_8bit*         ch4_vol_decay_port;
        Port_Passthru_8bit*         ch4_freq_port;
        Port_Passthru_8bit*         ch4_length_port;
        Port_Passthru_8bit*         ch5_play_mode_dma_port;
        Port_Passthru_8bit*         ch5_delta_counter_port;
        Port_Passthru_8bit*         ch5_addr_load_port;
        Port_Passthru_8bit*         ch5_length_port;
        DMA_CPU_SPR_RAM_Port*       spr_ram_dma_port;
        Port_Passthru_8bit*         channel_status_port;
        Controller_Port*            joypad_1_port;
        Port_Passthru_8bit*         joypad_2_port;
};

#endif // APU_PORT_INTERFACE_H
