#include "famicom_emu.h"
#include "cpu/cpu_2a03.h"
#include "ppu/ppu_2c02.h"
#include "data_bus/cpu/cpu_data_bus.h"
#include "data_bus/ppu/ppu_data_bus.h"
#include "apu/apu.h"
#include "controller_inputs.h"

Famicom_Emu::Famicom_Emu()
{

}

Famicom_Emu::~Famicom_Emu()
{
    delete cpu;
    delete apu;
    delete ppu;
    delete cpu_data_bus;
    delete ppu_data_bus;
    delete gamepad_a_inputs;
}

