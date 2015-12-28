#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <string>
#include <vector>
#include <map>
#include "data_bus/memory_bank.h"

class Disassembler
{
public:
    Disassembler();
    ~Disassembler() {};
//    std::string   disassemble_bank(Memory_Bank* bank, unsigned bank_address);
    std::map<unsigned, std::string>   debugger_disassemble_bank(Memory_Bank* bank, unsigned bank_address);

private:
    std::string   disassemble_instruction();
    void   output_16bit(std::ostringstream& d);
    void   output_8bit(std::ostringstream& d);
    unsigned calculate_relative_address();


private:
    unsigned disasm_location;
    unsigned bank_address;
    Memory_Bank*    bank;
};

#endif // DISASSEMBLER_H
