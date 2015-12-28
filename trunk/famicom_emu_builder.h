#ifndef FAMICOM_EMU_BUILDER_H
#define FAMICOM_EMU_BUILDER_H

class Famicom_Emu;
class Cartridge_Data;

class Famicom_Emu_Builder
{
public:
    Famicom_Emu_Builder();
    static Famicom_Emu* build_emu(Cartridge_Data* d);
};

#endif // FAMICOM_EMU_BUILDER_H
