#include "ines_loader.h"
#include <fstream>
#include <iostream>
#include "ines_header.h"
#include "cartridge_data.h"
#include "data_bus/memory_bank.h"

INES_Loader::INES_Loader()
{
}

Cartridge_Data*
INES_Loader::load_file(std::string rom_fname)
{
    //Open file
    std::ifstream iNES_file(rom_fname.c_str(), std::ios_base::binary);
    if (iNES_file.fail())
        throw new INES_Loader_Exception("Could not open file");

    //Read header
    Cartridge_Data* cart_data = new Cartridge_Data;
    const char* const raw_header = INES_Loader::read_raw_header(iNES_file);
    cart_data->header = INES_Loader::read_header(raw_header);
    delete[] raw_header;

    //Read memory banks
    INES_Loader::load_banks(cart_data, iNES_file);

    //Cleanup and return emu environment
    iNES_file.close();
    return (cart_data);
}

void
INES_Loader::load_banks(Cartridge_Data* d, std::ifstream& iNES_file)
{
    static const unsigned prg_bank_size = 0x4000;
    static const unsigned chr_bank_size = 0x2000;

    //Load ROM banks
    for (unsigned bank_num = 0; bank_num < d->header->total_prg_banks; bank_num++)
    {
        d->prg_rom_banks.push_back(INES_Loader::read_rom_bank(iNES_file, prg_bank_size));
    }
    for (unsigned bank_num = 0; bank_num < d->header->total_chr_banks; bank_num++)
    {
        d->chr_rom_banks.push_back(INES_Loader::read_rom_bank(iNES_file, chr_bank_size));
    }
}

Memory_Bank*
INES_Loader::read_rom_bank(std::ifstream& iNES_file, unsigned bank_size)
{
    char* bank = INES_Loader::read_buffer(iNES_file, bank_size);
    Memory_Bank* mem_bank = new Memory_Bank(bank_size, Memory_Bank::Read_Only);
    unsigned load_address = 0;
    mem_bank->load_buffer_to_memory(bank, load_address, bank_size);
    delete[] bank;
    return (mem_bank);
}

char*
INES_Loader::init_buffer(unsigned size)
{
    char* buf = new char [size];
    for (unsigned i = 0; i < size; i++)
        buf[i] = 0;
    return buf;
}

char*
INES_Loader::read_buffer(std::ifstream& i, unsigned size)
{
    char* buf = INES_Loader::init_buffer(size);
    i.read(buf, size);
    //FIXME! - Chequear excepciones
    return(buf);
}


/*
==============================================================================================================
HEADER HELPERS
==============================================================================================================
*/
char*
INES_Loader::read_raw_header(std::ifstream& i)
{
    char* raw_header = new char [header_size];
    i.read(raw_header, header_size);
    return (raw_header);
}

INES_Header*
INES_Loader::read_header(const char* const raw_header)
{
  if (!INES_Loader::validate_magic_number(raw_header))
      throw new INES_Loader_Exception("Magic header invalid");

  INES_Header *header = new INES_Header;

  header->total_prg_banks = (unsigned) raw_header[4];
  header->total_chr_banks = (unsigned) raw_header[5];
  header->total_ram_banks = (unsigned) raw_header[8];
  header->mapper = (unsigned) ((raw_header[6] >> 4) || (raw_header[7] >> 4) << 4);
  header->has_sram = (bool) (raw_header[6] & 0x02);
  header->has_trainer = (bool) (raw_header[6] & 0x04);

  if (raw_header[6] & 0x08)
    header->mirroring = Name_Table_Mirroring::Four_Screen;
  else if (raw_header[6] & 0x01)
      header->mirroring = Name_Table_Mirroring::Vertical;
  else
      header->mirroring = Name_Table_Mirroring::Horizontal;

  if (header->total_ram_banks == 0)
         header->total_ram_banks = 1;

  return header;
}

bool
INES_Loader::validate_magic_number(const char* const raw_header)
{
 bool success = true;

 success &= (raw_header[0] == 'N');
 success &= (raw_header[1] == 'E');
 success &= (raw_header[2] == 'S');
 success &= (raw_header[3] == 0x1A);

 return (success);
}
