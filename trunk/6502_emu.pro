# -------------------------------------------------
# Project created by QtCreator 2010-04-02T18:14:24
# -------------------------------------------------
TARGET = 6502_emu
TEMPLATE = app
CONFIG += console
SOURCES += main.cpp \
    famicom_emu.cpp \
    flip_flop.cpp \
    dma_cpu_spr_ram_port.cpp \
    register/register_16bit.cpp \
    register/register_8bit.cpp \
    register/register.cpp \
    cpu/program_counter.cpp \
    cpu/flags_register.cpp \
    cpu/cpu_2a03.cpp \
    cpu/alu.cpp \
    ppu/ppu_vram_data_port.cpp \
    ppu/ppu_vram_address_port.cpp \
    ppu/ppu_status_register.cpp \
    ppu/ppu_status_port.cpp \
    ppu/ppu_spr_ram_data_port.cpp \
    ppu/ppu_spr_ram_address_port.cpp \
    ppu/ppu_port_interface.cpp \
    ppu/ppu_control_register_2.cpp \
    ppu/ppu_control_register_1.cpp \
    ppu/ppu_2c02.cpp \
    port/port_passthru_8bit.cpp \
    port/port_8bit.cpp \
    inspectors/tile_inspector.cpp \
    inspectors/palette_inspector.cpp \
    inspectors/data_bus_inspector.cpp \
    inspectors/cpu_2a03_inspector.cpp \
    ines/ines_loader.cpp \
    ines/ines_header.cpp \
    data_bus/memory_bank.cpp \
    data_bus/data_bus.cpp \
    data_bus/cpu/cpu_data_bus_m0.cpp \
    data_bus/cpu/cpu_data_bus.cpp \
    data_bus/ppu/ppu_data_bus_m0.cpp \
    data_bus/ppu/ppu_data_bus.cpp \
    apu/apu_port_interface.cpp \
    apu/apu.cpp \
    emulator.cpp \
    data_bus/name_table_mirroring.cpp \
    disassembler.cpp \
    famicom_emu_builder.cpp \
    cartridge_data.cpp \
    memory_bank_model.cpp \
    disassembler_model.cpp \
    controller_port.cpp \
    controller_inputs.cpp \
    ppu/ppu_bkg_scroll_port.cpp \
    tv_set/tv_set.cpp \
    win32_resolver.cpp
HEADERS += famicom_emu.h \
    flip_flop.h \
    dma_cpu_spr_ram_port.h \
    register/register_8bit.h \
    register/register.h \
    register/register_16bit.h \
    cpu/flags_register.h \
    cpu/cpu_2a03.h \
    cpu/alu.h \
    cpu/program_counter.h \
    ppu/ppu_vram_address_port.h \
    ppu/ppu_status_register.h \
    ppu/ppu_status_port.h \
    ppu/ppu_spr_ram_data_port.h \
    ppu/ppu_spr_ram_address_port.h \
    ppu/ppu_port_interface.h \
    ppu/ppu_control_register_2.h \
    ppu/ppu_control_register_1.h \
    ppu/ppu_2c02.h \
    ppu/ppu_vram_data_port.h \
    port/port_8bit.h \
    port/port_passthru_8bit.h \
    inspectors/palette_inspector.h \
    inspectors/data_bus_inspector.h \
    inspectors/cpu_2a03_inspector.h \
    inspectors/tile_inspector.h \
    ines/ines_header.h \
    ines/ines_loader.h \
    data_bus/data_bus.h \
    data_bus/memory_bank.h \
    data_bus/cpu/cpu_data_bus.h \
    data_bus/cpu/cpu_data_bus_m0.h \
    data_bus/ppu/ppu_data_bus.h \
    data_bus/ppu/ppu_data_bus_m0.h \
    apu/apu_port_interface.h \
    apu/apu.h \
    emulator.h \
    data_bus/name_table_mirroring.h \
    disassembler.h \
    famicom_emu_builder.h \
    cartridge_data.h \
    memory_bank_model.h \
    disassembler_model.h \
    controller_port.h \
    controller_inputs.h \
    6502_common.h \
    ppu/ppu_bkg_scroll_port.h \
    tv_set/tv_set.h \
    win32_resolver.h \
    random_generator.h
FORMS += cpu_2a03_inspector.ui \
    data_bus_inspector.ui \
    tile_inspector.ui \
    emulator.ui
RESOURCES = resources.qrc

# #WIN32
LIBS += -lSDL
INCLUDEPATH += C:/SDL/SDL-1.2.14/include/SDL
LIBPATH = C:/SDL/SDL-1.2.14/lib
