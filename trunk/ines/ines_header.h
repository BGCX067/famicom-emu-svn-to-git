#ifndef INES_HEADER_H
#define INES_HEADER_H
#include <iosfwd>

#include "data_bus/name_table_mirroring.h"
class INES_Loader;

class INES_Header
{
friend class INES_Loader;
friend std::ostream& operator<<(std::ostream& o, const INES_Header& header);

public:
    INES_Header();
    unsigned get_total_prg_banks() {return total_prg_banks;};
    unsigned get_total_chr_banks() {return total_chr_banks;};
    unsigned get_total_ram_banks() {return total_ram_banks;};
    unsigned get_mapper() {return mapper;};
    bool get_has_sram() {return has_sram;};
    bool get_has_trainer() {return has_trainer;};
    Name_Table_Mirroring::Type get_mirroring() {return mirroring;};

private:
    unsigned	total_prg_banks;
    unsigned	total_chr_banks;
    unsigned	total_ram_banks;
    unsigned	mapper;
    bool	has_sram;
    bool	has_trainer;
    Name_Table_Mirroring::Type	mirroring;
};

#endif // INES_HEADER_H
