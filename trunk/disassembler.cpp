#include "disassembler.h"
#include "data_bus/memory_bank.h"
#include "6502_common.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Disassembler::Disassembler()
{
}

/*std::string
Disassembler::disassemble_bank(Memory_Bank* _bank, unsigned _bank_address)
{
    this->bank = _bank;
    this->bank_address = _bank_address;
    this->disasm_location = 0;

    std::ostringstream disassembly;
    disassembly << std::hex << std::uppercase;
    do
    {
        this->disassemble_instruction(disassembly);
    } while (this->disasm_location < _bank->get_size());

    return disassembly.str();
}*/

std::map<unsigned, std::string>
Disassembler::debugger_disassemble_bank(Memory_Bank* _bank, unsigned _bank_address)
{
    this->bank = _bank;
    this->bank_address = _bank_address;
    this->disasm_location = 0;

    std::map<unsigned, std::string> disassembly;
    do
    {
        disassembly[this->disasm_location + this->bank_address] = this->disassemble_instruction();
    } while (this->disasm_location < _bank->get_size());

    return disassembly;
}


std::string
Disassembler::disassemble_instruction()
{
 std::ostringstream d;
 d << std::hex << std::uppercase;

 //Write disassembly location
 d << std::setfill('0');
 d.width(4);
 d << std::right << this->disasm_location + this->bank_address << " ";

 //Write instruction raw bytes
 unsigned opcode = this->bank->read(this->disasm_location);
 d.width(2);
 d << std::right << opcode << " ";

 if (instr_bytes[opcode] != 0)
 {
    for (unsigned i = 1; i < instr_bytes[opcode]; i++)
     {
         d.width(2);
         d << std::right << this->bank->read(this->disasm_location + i) << " ";
     }

    //Write instruction disassembly
    unsigned spaces = 0;
    switch (instr_bytes[opcode])
    {
        case 1:
            spaces = 8;
            break;
        case 2:
            spaces = 5;
            break;
        case 3:
            spaces = 2;
            break;
    }
    for (unsigned i = 0; i < spaces; i++)
        d << " ";

    d << mnemonics[opcode] << " ";

    //Write operand
    switch (modes[opcode])
    {
    unsigned relative_address;

        case ZZZ:
        case IMP:
            break;
        case ABS:
            d << "$";
            this->output_16bit(d);
            break;
        case IMM:
            d << "#";
            this->output_8bit(d);
            break;
        case ZPA:
            d << "$";
            this->output_8bit(d);
            break;
        case ACC:
            d << "ACC";
            break;
        case REL:
            relative_address = this->calculate_relative_address();
            d << "$";
            d.width(4);
            d << relative_address;
            break;
        case IDX:
            d << "$";
            this->output_16bit(d);
            d << ",X";
            break;
        case IDY:
            d << "$";
            this->output_16bit(d);
            d << ",Y";
            break;
        case ZPX:
            d << "$";
            this->output_8bit(d);
            d << ",X";
            break;
        case ZPY:
            d << "$";
            this->output_8bit(d);
            d << ",Y";
            break;
        case IND:
            d << "($";
            this->output_16bit(d);
            d << ")";
            break;
        case PRE:
            d << "($";
            this->output_8bit(d);
            d << ",X)";
            break;
        case PST:
            d << "($";
            this->output_8bit(d);
            d << "),Y";
            break;
    }

    //Move disassembly location
    this->disasm_location += instr_bytes[opcode];
 }
 else
    this->disasm_location++;

// d << std::endl;
 return d.str();
}

void
Disassembler::output_16bit(std::ostringstream& d)
{
 d.width(2);
 d << std::right << this->bank->read(this->disasm_location + 2);
 d.width(2);
 d << std::right << this->bank->read(this->disasm_location + 1);
}

void
Disassembler::output_8bit(std::ostringstream& d)
{
 d.width(2);
 d << std::right << this->bank->read(this->disasm_location + 1);
}

unsigned
Disassembler::calculate_relative_address()
{
    unsigned operand = this->bank->read(this->disasm_location + 1);
    unsigned value = this->disasm_location + 2;

    if (operand & 0x80)
    {
        value += (operand ^ 0x80) - 0x80;
        value &= 0xFFFF;
    }
    else
        value += operand;

    return (value + this->bank_address);
}
