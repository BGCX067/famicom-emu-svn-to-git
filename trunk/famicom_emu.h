#ifndef FAMICOM_EMU_H
#define FAMICOM_EMU_H

class CPU_2A03;
class APU;
class PPU_2C02;
class CPU_Data_Bus;
class PPU_Data_Bus;
class Controller_Inputs;

class Famicom_Emu
{
friend class INES_Loader;

public:
        Famicom_Emu();
        ~Famicom_Emu();

public:
    CPU_2A03*           cpu;
    APU*                apu;
    PPU_2C02*           ppu;
    CPU_Data_Bus*       cpu_data_bus;
    PPU_Data_Bus*       ppu_data_bus;
    Controller_Inputs*  gamepad_a_inputs;
};

#endif // FAMICOM_EMU_H
