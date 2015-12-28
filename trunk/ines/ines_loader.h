#ifndef ROM_LOADER_H
#define ROM_LOADER_H

#include <stdexcept>
#include <string>
//#include "famicom_emu.h"

class Cartridge_Data;

class INES_Loader_Exception : public std::runtime_error
{
public:
    INES_Loader_Exception(std::string s) : std::runtime_error(s) {};
};


class INES_Header;
class Memory_Bank;

class INES_Loader
{
public:
    INES_Loader();
    static Cartridge_Data*     load_file(std::string rom_fname);

private:
    static  char*               read_raw_header(std::ifstream& i);
    static  INES_Header*        read_header(const char* const raw_header);
    static  bool                validate_magic_number(const char* const raw_header);

    static  char*               init_buffer(unsigned size);
    static  char*               read_buffer(std::ifstream& i, unsigned size);
    static  Memory_Bank*        read_rom_bank(std::ifstream& iNES_file, unsigned bank_size);

    static  void                load_banks(Cartridge_Data* d, std::ifstream& iNES_file);

    static const unsigned header_size = 16;

};

#endif // ROM_LOADER_H
