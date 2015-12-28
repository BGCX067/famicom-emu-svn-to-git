#include "cartridge_data.h"
#include "ines/ines_header.h"
#include "data_bus/memory_bank.h"
#include <iostream>

Cartridge_Data::Cartridge_Data()
{
}

Cartridge_Data::~Cartridge_Data()
{
    delete this->header;
    for (unsigned i = 0; i < this->prg_rom_banks.size(); i++)
        delete this->prg_rom_banks[i];
    for (unsigned i = 0; i < this->chr_rom_banks.size(); i++)
        delete this->chr_rom_banks[i];
}

std::ostream&
operator<<(std::ostream& o, const Cartridge_Data& d)
{
 o << "CARTRIDGE DATA" << std::endl;
 o << "Total PRG banks: " << d.prg_rom_banks.size() << std::endl;
 o << "Total CHR banks: " << d.chr_rom_banks.size() << std::endl;
 o << "HEADER..." << std::endl;
 o << *(d.header);

 return o;
}
