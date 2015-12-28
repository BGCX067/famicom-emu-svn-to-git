#ifndef _6502_COMMON_H
#define _6502_COMMON_H

enum addr_mode { ZZZ, IMM, ABS, ZPA, ZPX, ZPY, IMP, ACC, IDX, IDY, IND, PRE, PST, REL };

/*
ZZZ = Nada (opcode invalido)
IMM = Inmediato (8 bits)
ABS = Absoluto (16 bits)
ZPA = Zero Page (8 bits) (un caso especial de ABS)
IMP = Implicito (0 bits de operando)
ACC = Acumulador (un caso especial de IMP)
REL = Relativo (offset de 8 bits, signed char)
IDX = Indexado X (16 bits + registro indice)
IDY = Indexado Y (16 bits + registro indice)
ZPX = Indexado zero-page (8 bits + registro indice) (un caso especial de IDX)
ZPY = Indexado zero-page (8 bits + registro indice) (un caso especial de IDY)
IND = Indirecto (direccion absoluta de 16 bits, de la que se lee una nueva direccion)
PRE = Pre-indexado indirecto (X)
PST = Post-indexado indirecto (Y)
*/

enum opcode_operation
    {
    ADC, AHX, ALR, ANC, AND, ARR, ASL, ASL_A, AXS,
    BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS,
    CLC, CLD, CLI, CLV, CMP, CPX, CPY,
    DCP, DEC, DEX, DEY,
    EOR,
    HLT,
    INC, INX, INY, ISB,
    JMP, JSR,
    LAS, LAX, LDA, LDX, LDY, LSR, LSR_A, LXA,
    NOP,
    ORA,
    PHA, PHP, PLA, PLP,
    RLA, ROL, ROL_A, ROR, ROR_A, RRA, RTI, RTS,
    SAX, SBC, SBN, SEC, SED, SEI, SHX, SHY, SKB, SKW, SLO, SRE, STA, STX, STY,
    TAS, TAX, TAY, TSX, TXA, TXS, TYA,
    XAA
    };

const unsigned total_opcodes = 256;

const addr_mode modes[total_opcodes] =
{
/*
 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F*/
IMP, PRE, IMP, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, ACC, IMM, ABS, ABS, ABS, ABS, //00-0F
REL, PST, IMP, PST, ZPX, ZPX, ZPX, ZPX, IMP, IDY, IMP, IDY, IDX, IDX, IDX, IDX, //10-1F
ABS, PRE, IMP, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, ACC, IMM, ABS, ABS, ABS, ABS, //20-2F
REL, PST, IMP, PST, ZPX, ZPX, ZPX, ZPX, IMP, IDY, IMP, IDY, IDX, IDX, IDX, IDX, //30-3F
IMP, PRE, IMP, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, ACC, IMM, ABS, ABS, ABS, ABS, //40-4F
REL, PST, IMP, PST, ZPX, ZPX, ZPX, ZPX, IMP, IDY, IMP, IDY, IDX, IDX, IDX, IDX, //50-5F
IMP, PRE, IMP, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, ACC, IMM, IND, ABS, ABS, ABS, //60-6F
REL, PST, IMP, PST, ZPX, ZPX, ZPX, ZPX, IMP, IDY, IMP, IDY, IDX, IDX, IDX, IDX, //70-7F
IMM, PRE, IMM, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, //80-8F
REL, PST, IMP, PST, ZPX, ZPX, ZPY, ZPY, IMP, IDY, IMP, IDY, IDX, IDX, IDY, IDX, //90-9F
IMM, PRE, IMM, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, //A0-AF
REL, PST, IMP, PST, ZPX, ZPX, ZPY, ZPY, IMP, IDY, IMP, IDY, IDX, IDX, IDY, IDX, //B0-BF
IMM, PRE, IMM, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, //C0-CF
REL, PST, IMP, PST, ZPX, ZPX, ZPX, ZPX, IMP, IDY, IMP, IDY, IDX, IDX, IDX, IDX, //D0-DF
IMM, PRE, IMM, PRE, ZPA, ZPA, ZPA, ZPA, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, //E0-EF
REL, PST, IMP, PST, ZPX, ZPX, ZPX, ZPX, IMP, IDY, IMP, IDY, IDX, IDX, IDX, IDX, //F0-FF
};

const opcode_operation opcode_operations[total_opcodes] =
{
/*
 0    1    2    3    4    5    6    7    8    9    A      B    C    D    E    F*/
BRK, ORA, HLT, SLO, SKB, ORA, ASL, SLO, PHP, ORA, ASL_A, ANC, SKW, ORA, ASL, SLO, //00-0F
BPL, ORA, HLT, SLO, SKB, ORA, ASL, SLO, CLC, ORA, NOP,   SLO, SKW, ORA, ASL, SLO, //10-1F
JSR, AND, HLT, RLA, BIT, AND, ROL, RLA, PLP, AND, ROL_A, ANC, BIT, AND, ROL, RLA, //20-2F
BMI, AND, HLT, RLA, SKB, AND, ROL, RLA, SEC, AND, NOP,   RLA, SKW, AND, ROL, RLA, //30-3F
RTI, EOR, HLT, SRE, SKB, EOR, LSR, SRE, PHA, EOR, LSR_A, ALR, JMP, EOR, LSR, SRE, //40-4F
BVC, EOR, HLT, SRE, SKB, EOR, LSR, SRE, CLI, EOR, NOP,   SRE, SKW, EOR, LSR, SRE, //50-5F
RTS, ADC, HLT, RRA, SKB, ADC, ROR, RRA, PLA, ADC, ROR_A, ARR, JMP, ADC, ROR, RRA, //60-6F
BVS, ADC, HLT, RRA, SKB, ADC, ROR, RRA, SEI, ADC, NOP,   RRA, SKW, ADC, ROR, RRA, //70-7F
SKB, STA, SKB, SAX, STY, STA, STX, SAX, DEY, SKB, TXA,   XAA, STY, STA, STX, SAX, //80-8F
BCC, STA, HLT, AHX, STY, STA, STX, SAX, TYA, STA, TXS,   TAS, SHY, STA, SHX, AHX, //90-9F
LDY, LDA, LDX, LAX, LDY, LDA, LDX, LAX, TAY, LDA, TAX,   LXA, LDY, LDA, LDX, LAX, //A0-AF
BCS, LDA, HLT, LAX, LDY, LDA, LDX, LAX, CLV, LDA, TSX,   LAS, LDY, LDA, LDX, LAX, //B0-BF
CPY, CMP, SKB, DCP, CPY, CMP, DEC, DCP, INY, CMP, DEX,   AXS, CPY, CMP, DEC, DCP, //C0-CF
BNE, CMP, HLT, DCP, SKB, CMP, DEC, DCP, CLD, CMP, NOP,   DCP, SKW, CMP, DEC, DCP, //D0-DF
CPX, SBC, SKB, ISB, CPX, SBC, INC, ISB, INX, SBC, NOP,   SBC, CPX, SBC, INC, ISB, //E0-EF
BEQ, SBC, HLT, ISB, SKB, SBC, INC, ISB, SED, SBC, NOP,   ISB, SKW, SBC, INC, ISB  //F0-FF
};

const unsigned instr_bytes[total_opcodes] =
{
/*
0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F*/
1, 2, 1, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //00-0F
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //10-1F
3, 2, 1, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //20-2F
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //30-3F
1, 2, 1, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //40-4F
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //50-5F
1, 2, 1, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //60-6F
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //70-7F
2, 2, 2, 2, 2, 2, 2, 2,  1, 1, 1, 2, 3, 3, 3, 3, //80-8F
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //90-9F
2, 2, 2, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //A0-AF
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //B0-BF
2, 2, 2, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //C0-CF
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3, //D0-DF
2, 2, 2, 2, 2, 2, 2, 2,  1, 2, 1, 2, 3, 3, 3, 3, //E0-EF
2, 2, 1, 2, 2, 2, 2, 2,  1, 3, 1, 3, 3, 3, 3, 3  //F0-FF
};

const unsigned cycles[256] =
{
/*0x00*/ 7,6,2,8,3,3,5,5,3,2,2,2,4,4,6,6,
/*0x10*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x20*/ 6,6,2,8,3,3,5,5,4,2,2,2,4,4,6,6,
/*0x30*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x40*/ 6,6,2,8,3,3,5,5,3,2,2,2,3,4,6,6,
/*0x50*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x60*/ 6,6,2,8,3,3,5,5,4,2,2,2,5,4,6,6,
/*0x70*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0x80*/ 2,6,2,6,3,3,3,3,2,2,2,2,4,4,4,4,
/*0x90*/ 2,6,2,6,4,4,4,4,2,5,2,5,5,5,5,5,
/*0xA0*/ 2,6,2,6,3,3,3,3,2,2,2,2,4,4,4,4,
/*0xB0*/ 2,5,2,5,4,4,4,4,2,4,2,4,4,4,4,4,
/*0xC0*/ 2,6,2,8,3,3,5,5,2,2,2,2,4,4,6,6,
/*0xD0*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
/*0xE0*/ 2,6,3,8,3,3,5,5,2,2,2,2,4,4,6,6,
/*0xF0*/ 2,5,2,8,4,4,6,6,2,4,2,7,4,4,7,7,
};

const std::string mnemonics[total_opcodes] =
 {
/*           0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F */
 /*00-0F*/ "BRK", "ORA", "HLT", "SLO", "SKB", "ORA", "ASL", "SLO", "PHP", "ORA", "ASL", "ANC", "SKW", "ORA", "ASL", "SLO",
 /*10-1F*/ "BPL", "ORA", "HLT", "SLO", "SKB", "ORA", "ASL", "SLO", "CLC", "ORA", "NOP", "SLO", "SKW", "ORA", "ASL", "SLO",
 /*20-2F*/ "JSR", "AND", "HLT", "RLA", "BIT", "AND", "ROL", "RLA", "PLP", "AND", "ROL", "ANC", "BIT", "AND", "ROL", "RLA",
 /*30-3F*/ "BMI", "AND", "HLT", "RLA", "SKB", "AND", "ROL", "RLA", "SEC", "AND", "NOP", "RLA", "SKW", "AND", "ROL", "RLA",
 /*40-4F*/ "RTI", "EOR", "HLT", "SRE", "SKB", "EOR", "LSR", "SRE", "PHA", "EOR", "LSR", "ALR", "JMP", "EOR", "LSR", "SRE",
 /*50-5F*/ "BVC", "EOR", "HLT", "SRE", "SKB", "EOR", "LSR", "SRE", "CLI", "EOR", "NOP", "SRE", "SKW", "EOR", "LSR", "SRE",
 /*60-6F*/ "RTS", "ADC", "HLT", "RRA", "SKB", "ADC", "ROR", "RRA", "PLA", "ADC", "ROR", "ARR", "JMP", "ADC", "ROR", "RRA",
 /*70-7F*/ "BVS", "ADC", "HLT", "RRA", "SKB", "ADC", "ROR", "RRA", "SEI", "ADC", "NOP", "RRA", "SKW", "ADC", "ROR", "RRA",
 /*80-8F*/ "SKB", "STA", "SKB", "SAX", "STY", "STA", "STX", "SAX", "DEY", "SKB", "TXA", "XAA", "STY", "STA", "STX", "SAX",
 /*90-9F*/ "BCC", "STA", "HLT", "AHX", "STY", "STA", "STX", "SAX", "TYA", "STA", "TXS", "TAS", "SHY", "STA", "SHX", "AHX",
 /*A0-AF*/ "LDY", "LDA", "LDX", "LAX", "LDY", "LDA", "LDX", "LAX", "TAY", "LDA", "TAX", "LXA", "LDY", "LDA", "LDX", "LAX",
 /*B0-BF*/ "BCS", "LDA", "HLT", "LAX", "LDY", "LDA", "LDX", "LAX", "CLV", "LDA", "TXS", "LAS", "LDY", "LDA", "LDX", "LAX",
 /*C0-CF*/ "CPY", "CMP", "SKB", "DCP", "CPY", "CMP", "DEC", "DCP", "INY", "CMP", "DEX", "AXS", "CPY", "CMP", "DEC", "DCP",
 /*D0-DF*/ "BNE", "CMP", "HLT", "DCP", "SKB", "CMP", "DEC", "DCP", "CLD", "CMP", "NOP", "DCP", "SKW", "CMP", "DEC", "DCP",
 /*E0-EF*/ "CPX", "SBC", "SKB", "ISB", "CPX", "SBC", "INC", "ISB", "INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "ISB",
 /*F0-FF*/ "BEQ", "SBC", "HLT", "ISB", "SKB", "SBC", "INC", "ISB", "SED", "SBC", "NOP", "ISB", "SKW", "SBC", "INC", "ISB"
 };



#endif // 6502_COMMON_H
