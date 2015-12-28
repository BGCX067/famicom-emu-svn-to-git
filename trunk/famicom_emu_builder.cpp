#include "famicom_emu_builder.h"
#include "famicom_emu.h"
#include "data_bus/memory_bank.h"
#include "cpu/cpu_2a03.h"
#include "ppu/ppu_2c02.h"
#include "ppu/ppu_port_interface.h"
#include "apu/apu.h"
#include "apu/apu_port_interface.h"
#include "data_bus/cpu/cpu_data_bus_m0.h"
#include "data_bus/ppu/ppu_data_bus.h"
#include "data_bus/ppu/ppu_data_bus_m0.h"
#include "cartridge_data.h"
#include "ines/ines_header.h"
#include "controller_inputs.h"

Famicom_Emu_Builder::Famicom_Emu_Builder()
{
}

Famicom_Emu*
Famicom_Emu_Builder::build_emu(Cartridge_Data* d)
{
    //Build Emulator, CPU, PPU and APU objects
    Famicom_Emu* emu = new Famicom_Emu;
    emu->cpu = new CPU_2A03;
    emu->apu = new APU;
    emu->ppu = new PPU_2C02;

    //Build CPU Data Bus and PPU Data Bus
    CPU_Data_Bus_M0* cpu_m0 = new CPU_Data_Bus_M0;
    PPU_Data_Bus_M0* ppu_m0 = new PPU_Data_Bus_M0(d->get_header()->get_mirroring());

    //Connect PRG-ROM and CHR-ROM banks to the respective data buses
    std::vector<Memory_Bank*> v = d->get_prg_rom_banks();
    for (unsigned i = 0; i < v.size(); i++)
        cpu_m0->connect_rom_bank(i, v[i]->copy());

    v = d->get_chr_rom_banks();
    for (unsigned i = 0; i < v.size(); i++)
        ppu_m0->connect_chr_rom(v[i]->copy());

    //Connect CPU to CPU Data Bus, PPU to PPU Data Bus
    emu->cpu_data_bus = cpu_m0;
    emu->ppu_data_bus = ppu_m0;
    emu->cpu->connect_data_bus(emu->cpu_data_bus);
    emu->ppu->connect_data_bus(emu->ppu_data_bus);

    //Connect PPU NMI line to CPU
    emu->ppu->connect_cpu_nmi(emu->cpu->nmi);

    //Connect CPU to PPU and APU ports
    PPU_Port_Interface* ppu_ports = emu->ppu->get_port_interface();
    APU_Port_Interface* apu_ports = emu->apu->get_port_interface();
    emu->cpu_data_bus->connect_apu_ports(apu_ports);
    emu->cpu_data_bus->connect_ppu_ports(ppu_ports);

    //Connect DMA SPR-RAM port in APU to PPU
    apu_ports->connect_dma_spr_ram(emu->cpu_data_bus, ppu_ports->spr_ram_data_port);

    //Connect Controller 1 APU port to Controller 1 inputs
    emu->gamepad_a_inputs = new Controller_Inputs;
    apu_ports->connect_gamepad_a_inputs(emu->gamepad_a_inputs);

    //Init CPU
    emu->cpu->init_cpu();

    return (emu);
}

