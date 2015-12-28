#ifndef CARTRIDGE_DATA_H
#define CARTRIDGE_DATA_H
#include <iosfwd>
#include <vector>

class INES_Header;
class Memory_Bank;

class Cartridge_Data
{
friend std::ostream& operator<<(std::ostream& o, const Cartridge_Data& d);
friend class INES_Loader;

public:
    Cartridge_Data();
    ~Cartridge_Data();
    virtual bool        can_be_executed() { return true; };
    INES_Header* get_header() {return header;};
    std::vector<Memory_Bank*> get_prg_rom_banks() {return prg_rom_banks;};
    std::vector<Memory_Bank*> get_chr_rom_banks() {return chr_rom_banks;};

private:
    INES_Header*    header;
    std::vector<Memory_Bank*>   prg_rom_banks;
    std::vector<Memory_Bank*>   chr_rom_banks;
};

class Empty_Cartridge_Data : public Cartridge_Data
{
public:
    bool        can_be_executed() { return false; };
};

#endif // CARTRIDGE_DATA_H
