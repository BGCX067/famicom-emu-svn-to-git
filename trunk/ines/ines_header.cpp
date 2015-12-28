#include "ines_header.h"
#include <iostream>

INES_Header::INES_Header()
{
}

std::ostream&
operator<<(std::ostream& o, const INES_Header& header)
{
 o << "Total PRG: " << header.total_prg_banks << std::endl;
 o << "Total CHR: " << header.total_chr_banks << std::endl;
 o << "Total RAM: " << header.total_ram_banks << std::endl;
 o << "Mapper: " << header.mapper << std::endl;
 o << "Has SRAM: " << header.has_sram << std::endl;
 o << "Has Trainer: " << header.has_trainer << std::endl;
 o << "Mirroring: ";
 switch (header.mirroring)
 {
     case Name_Table_Mirroring::Horizontal:
        o << "Horizontal";
        break;
     case Name_Table_Mirroring::Vertical:
        o << "Vertical";
        break;
     case Name_Table_Mirroring::Four_Screen:
        o << "Four screen";
        break;
 }
 o << std::endl;
 return o;
}
