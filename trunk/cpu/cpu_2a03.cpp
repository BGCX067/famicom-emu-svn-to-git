#include "cpu_2a03.h"
#include "6502_common.h"

#include <iostream>
#include <QObject>

/*
============================================================================================================================================
Construction, destruction and interconnection
============================================================================================================================================
*/
CPU_2A03::CPU_2A03()
{
    this->nmi = new bool;
    *(this->nmi) = false;
    this->clocks = 0;
    this->has_breakpoints = false;
}

CPU_2A03::~CPU_2A03()
{
    delete this->nmi;
}

void CPU_2A03::connect_data_bus(CPU_Data_Bus* db)
{
    this->data_bus = db;
}


/*
============================================================================================================================================
Execution control
============================================================================================================================================
*/
//WARNING! - Do not init CPU until the CPU Data bus is connected
// as the reset_vector must point to valid memory
void CPU_2A03::init_cpu()
{
    sp.set_value(0xFF);
    ac.set_value(0);
    x.set_value(0);
    y.set_value(0);
    *(this->nmi) = false;
    jump_to_vector(reset_vector);
    this->clocks = 0;
}

void
CPU_2A03::execute_clocks(unsigned exec_clocks)
{
 unsigned stop_clock = clocks + exec_clocks;
 while (clocks < stop_clock)
    {
    //Breakpoint detection
    unsigned address = pc.read();
    if (this->has_breakpoints)
        {
        if (this->breakpoints.find(address) != this->breakpoints.end())
            return;
        }
    execute();
    }
}

//DEBUGGING ONLY
void
CPU_2A03::debug_run()
{
 while (true)
    {
    //Breakpoint detection
    unsigned address = pc.read();
    if (this->has_breakpoints)
        {
        if (this->breakpoints.find(address) != this->breakpoints.end())
            return;
        }
    execute();
    }
}


void
CPU_2A03::toggle_breakpoint(unsigned address)
{
    if (this->breakpoints.find(address) == this->breakpoints.end())
    {
        this->breakpoints.insert(address);
        this->has_breakpoints = true;
    }
    else
    {
        this->breakpoints.erase(address);
        if (this->breakpoints.size() == 0)
            this->has_breakpoints = false;
    }
}

/*
============================================================================================================================================
Instruction execution
============================================================================================================================================
*/
void CPU_2A03::execute()
{
    unsigned operand_address = 0, address = 0;
    unsigned operand = 0;
    unsigned temp_result = 0;

    if (*nmi)
        handle_nmi();

    //Instruction opcode fetch
    address = pc.read();

    //Breakpoint detection
    if (this->has_breakpoints)
    {
        if (this->breakpoints.find(address) != this->breakpoints.end())
                emit breakpoint_occurred();
    }
    unsigned operation = data_bus->read(address);
    pc.increment();


    //Operand fetch
    switch (modes[operation])
    {
    case ZZZ:
    case IMP:
        break;
    case ACC:   //Accumulator
        operand = ac.read_value();
        break;
    case IMM:   //Immediate
    case REL:   //Relative
        operand = this->read_8bit_address();
        break;
    case ABS:   //Absolute 16-bit
        operand_address = this->generate_absolute_address();
        break;
    case IDX:   //Absolute 16-bit + X
        operand_address = this->generate_absolute_x_address();
        break;
    case IDY:   //Absolute 16-bit + Y
        operand_address = this->generate_absolute_y_address();
        break;
    case ZPA:   //Zero page
        operand_address = this->generate_zero_page_address();
        break;
    case ZPX:   //Zero page + X
        operand_address = this->generate_zero_page_x_address();
        break;
    case ZPY:   //Zero page + Y
        operand_address = this->generate_zero_page_y_address();
        break;
    case IND:   //Indirect
        operand_address = this->generate_indirect_address();
        break;
    case PRE:   //Pre-indexed indirect
        operand_address = this->generate_indirect_pre_indexed();
        break;
    case PST:   //Post-indexed indirect
        operand_address = this->generate_indirect_post_indexed();
        break;
    }

    //STA, STX and STY opcodes do not perform a Read operation on the data bus
    // for the addressing modes of the second case group. All other opcodes do perform a read operation for thos
    // addressing modes.
    if (opcode_operations[operation] != STA and
        opcode_operations[operation] != STX and
        opcode_operations[operation] != STY)
    {
        switch (modes[operation])
        {
        case ZZZ:
        case IMP:
        case ACC:
        case IND:
        case IMM:
        case REL:
            break;
        case ABS:
        case IDX:
        case IDY:            
        case PST:
        case ZPA:
        case ZPX:
        case ZPY:
        case PRE:
            operand = data_bus->read(operand_address);
            break;
        }
    }
    // RMW operations perform a dummy write with the same value read
    if (opcode_operations[operation] == INC or
        opcode_operations[operation] == DEC or
        opcode_operations[operation] == ROL or
        opcode_operations[operation] == ROR or
        opcode_operations[operation] == ASL or
        opcode_operations[operation] == LSR)
    {
        data_bus->write(operand_address, operand);
    }

    //Instruction decoding and execution
    switch(opcode_operations[operation])
    {
    //Register load/store operations
    case LDA:
        ac.set_value(operand);
        adjust_n(operand);
        adjust_z(operand);
        break;
    case LDX:
        x.set_value(operand);
        adjust_n(operand);
        adjust_z(operand);
        break;
    case LDY:
        y.set_value(operand);
        adjust_n(operand);
        adjust_z(operand);
        break;
    case STA:
        data_bus->write(operand_address, ac.read_value());
        break;
    case STX:
        data_bus->write(operand_address, x.read_value());
        break;
    case STY:
        data_bus->write(operand_address, y.read_value());
        break;
    //Arithmetic operations
    case ADC:
        adjust_alu_carry();
        ac.set_value(alu.add(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        overflow_in(alu.read_overflow());
        break;
    case SBC:
        adjust_alu_carry();
        ac.set_value(alu.subtract(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        overflow_in(alu.read_overflow());
        break;
    case CMP:
        temp_result = alu.compare(ac.read_value(), operand);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case CPX:
        temp_result = alu.compare(x.read_value(), operand);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case CPY:
        temp_result = alu.compare(y.read_value(), operand);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case DEX:
        x.set_value(alu.decrement(x.read_value()));
        adjust_n(x.read_value());
        adjust_z(x.read_value());
        break;
    case DEY:
        y.set_value(alu.decrement(y.read_value()));
        adjust_n(y.read_value());
        adjust_z(y.read_value());
        break;
    case DEC:
        temp_result = (alu.decrement(operand));
        adjust_n(temp_result);
        adjust_z(temp_result);
        data_bus->write(operand_address, temp_result);
        break;
    case INC:
        temp_result = (alu.increment(operand));
        adjust_n(temp_result);
        adjust_z(temp_result);
        data_bus->write(operand_address, temp_result);
        break;
    case INX:
        x.set_value(alu.increment(x.read_value()));
        adjust_n(x.read_value());
        adjust_z(x.read_value());
        break;
    case INY:
        y.set_value(alu.increment(y.read_value()));
        adjust_n(y.read_value());
        adjust_z(y.read_value());
        break;
    //Logical and bit operations
    case BIT:
        adjust_n(operand);
        adjust_z(ac.read_value() & operand);
        adjust_v(operand);
        break;
    case AND:
        ac.set_value(alu._and(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case EOR:
        ac.set_value(alu._xor(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case ORA:
        ac.set_value(alu._or(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case ASL_A: //ASL ACCUMULATOR
        ac.set_value(alu.shift_left(operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        break;
    case ASL: //ASL Memory
        temp_result = alu.shift_left(operand);
        data_bus->write(operand_address, temp_result);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case LSR_A: //LSR ACCUM.
        ac.set_value(alu.shift_right(operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        break;
    case LSR: //LSR Memory
        temp_result = alu.shift_right(operand);
        data_bus->write(operand_address, temp_result);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case ROL_A: //ROL ACCUM.
        adjust_alu_carry();
        ac.set_value(alu.rotate_left(operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        break;
    case ROL: //ROL Memory
        adjust_alu_carry();
        temp_result = alu.rotate_left(operand);
        data_bus->write(operand_address, temp_result);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case ROR_A: //ROR ACCUM.
        adjust_alu_carry();
        ac.set_value(alu.rotate_right(operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        break;
    case ROR: //ROR Memory
        adjust_alu_carry();
        temp_result = alu.rotate_right(operand);
        data_bus->write(operand_address, temp_result);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    //Flags register operations
    case CLC:
        flags.clear_carry();
        break;
    case SEC:
        flags.set_carry();
        break;
    case CLI:
        flags.clear_interrupt();
        break;
    case SEI:
        flags.set_interrupt();
        break;
    case CLV:
        flags.clear_overflow();
        break;
    case CLD:
        flags.clear_decimal();
        break;
    case SED:
        flags.set_decimal();
        break;
    //Register transfer operations
    case TXA:
        ac.set_value(x.read_value());
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case TYA:
        ac.set_value(y.read_value());
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case TXS:
        sp.set_value(x.read_value());
        break;
    case TAX:
        x.set_value(ac.read_value());
        adjust_n(x.read_value());
        adjust_z(x.read_value());
        break;
    case TAY:
        y.set_value(ac.read_value());
        adjust_n(y.read_value());
        adjust_z(y.read_value());
        break;
    case TSX:
        x.set_value(sp.read_value());
        adjust_n(x.read_value());
        adjust_z(x.read_value());
        break;
    //Conditional branch
    case BCC:
        if (!flags.read_carry())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BCS:
        if (flags.read_carry())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BEQ:
        if (flags.read_zero())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BMI:
        if (flags.read_negative())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BNE:
        if (!flags.read_zero())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BPL:
        if (!flags.read_negative())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BVC:
        if (!flags.read_overflow())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    case BVS:
        if (flags.read_overflow())
        {
            clocks++;
            if (pc.add_relative(operand))
                clocks++;
        }
        break;
    //Stack
    case PHA:
        push(ac.read_value());
        break;
    case PHP:
        temp_result = flags.read_value();
        temp_result |= 0x10; //Force set break flag
        push(temp_result);
        break;
    case PLA:
        ac.set_value(pop());
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case PLP:
        flags.set_value(pop());
        flags.set_unused();
        break;
    //Jumps
    case BRK:
        pc.increment();
        push(pc.read() & 0xFF);
        push((pc.read() >> 8) & 0xFF);
        flags.set_break();
        flags.set_unused();
        push(flags.read_value());
        flags.set_interrupt();
        jump_to_vector(irq_vector);
        break;
    case JMP:
        pc.set_value(operand_address);
        break;
    case JSR:
        pc.decrement();
        push(pc.read() >> 8 & 0xFF);
        push(pc.read() & 0xFF);
        pc.set_value(operand_address);
        break;
    case RTS:
        temp_result = pop();
        temp_result |= (pop() << 8);
        pc.set_value(temp_result);
        pc.increment();
        break;
    case RTI:
        flags.set_value(pop());
        flags.set_unused();
        temp_result = pop();
        temp_result |= (pop() << 8);
        pc.set_value(temp_result);
        break;
    case NOP:
        break;
    //================================================================
    //Unofficial opcodes
    //================================================================
    //LD/ST A/X
    case LAX:
        ac.set_value(operand);
        x.set_value(operand);
        adjust_n(operand);
        adjust_z(operand);
        break;
    case SAX: //AXS
        temp_result = alu._and(ac.read_value(), x.read_value());
        data_bus->write(operand_address, temp_result);
        break;
    //Combined ALU
    case SLO://ASO (ASL + ORA)
        temp_result = alu.shift_left(operand);
        data_bus->write(operand_address, temp_result);
        carry_in(alu.read_carry());
        ac.set_value(alu._or(ac.read_value(), temp_result));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case RLA://(ROL + AND)
        adjust_alu_carry();
        temp_result = alu.rotate_left(operand);
        data_bus->write(operand_address, temp_result);
        ac.set_value(alu._and(ac.read_value(), temp_result));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        break;
    case SRE://LSE (LSR + EOR)
        temp_result = alu.shift_right(operand);
        data_bus->write(operand_address, temp_result);
        carry_in(alu.read_carry());
        ac.set_value(alu._xor(ac.read_value(), temp_result));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case RRA://(ROR + ADC)
        adjust_alu_carry();
        temp_result = alu.rotate_right(operand);
        data_bus->write(operand_address, temp_result);
        ac.set_value(alu.add(ac.read_value(), temp_result));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        overflow_in(alu.read_overflow());
        break;
    case DCP://DCM (DEC + CMP)
        temp_result = (alu.decrement(operand));
        data_bus->write(operand_address, temp_result);
        temp_result = alu.compare(ac.read_value(), temp_result);
        adjust_n(temp_result);
        adjust_z(temp_result);
        carry_in(alu.read_carry());
        break;
    case ISB://INS/ISC (INC + SBC)
        temp_result = (alu.increment(operand));
        data_bus->write(operand_address, temp_result);
        adjust_alu_carry();
        ac.set_value(alu.subtract(ac.read_value(), temp_result));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        overflow_in(alu.read_overflow());
        break;
    //Other unofficial
    case ANC: //AND+ASL
        ac.set_value(alu._and(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(ac.read_value() & 0x80);
        break;
    case ALR: //ASR (AND+LSR)
        ac.set_value(alu._and(ac.read_value(), operand));
        ac.set_value(alu.shift_right(ac.read_value()));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        carry_in(alu.read_carry());
        break;
    case ARR: //AND+ROR
        ac.set_value(alu._and(ac.read_value(), operand));
        adjust_alu_carry();
        ac.set_value(alu.rotate_right(ac.read_value()));
    /*If both bits are 1: set C, clear V.
    If both bits are 0: clear C and V.
    If only bit 5 is 1: set V, clear C.
    If only bit 6 is 1: set C and V.*/
        if (ac.read_bit(5) and ac.read_bit(6))
        {
            carry_in(1);
            overflow_in(0);
        }
        else if (!ac.read_bit(5) and !ac.read_bit(6))
        {
            carry_in(0);
            overflow_in(0);
        }
        else if (ac.read_bit(5) and !ac.read_bit(6))
        {
            carry_in(0);
            overflow_in(1);
        }
        else
        {
            carry_in(1);
            overflow_in(1);
        }
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case XAA: //TXA+AND
        ac.set_value(x.read_value());
        ac.set_value(alu._and(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case SBN: //SBC+NOP
        std::cout << "Unimplemented opcode SBN" << std::endl;
        break;
    case AXS: //SBX, "SAX" in Adam Vardy's doc (A AND X, SBC -> X)
        temp_result = alu._and(ac.read_value(), x.read_value());
        carry_in(1); //Subtract without borrow
        adjust_alu_carry();
        x.set_value(alu.subtract(temp_result, operand));
        adjust_n(x.read_value());
        adjust_z(x.read_value());
        carry_in(alu.read_carry());
        break;
    case AHX: //Store (A AND X AND H)
        std::cout << "Unimplemented opcode AHX" << std::endl;
        break;
    case SHY: //Store (Y AND H)
        temp_result = ((operand_address & 0xFF00) >> 8) + 1;
        temp_result = alu._and(y.read_value(), temp_result);
        data_bus->write(operand_address, temp_result);
        break;
    case SHX: //Store (X AND H)
        temp_result = ((operand_address & 0xFF00) >> 8) + 1;
        temp_result = alu._and(x.read_value(), temp_result);
        data_bus->write(operand_address, temp_result);
        break;
    case TAS: //STA+TXS
        std::cout << "Unimplemented opcode TAS" << std::endl;
        break;
    case LAS: //LAS            
        ac.set_value(alu._and(ac.read_value(), operand));
        sp.set_value(ac.read_value());
        x.set_value(ac.read_value());
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        break;
    case LXA: //OAL (ORA #EE, AND operand, TAX)
        ac.set_value(alu._and(ac.read_value(), operand));
        adjust_n(ac.read_value());
        adjust_z(ac.read_value());
        x.set_value(ac.read_value());
        break;
    //NOP variants
    case SKB:
        break;
    case SKW:
        break;
    case HLT:
        break;
    }

    clocks += cycles[operation];
}

/*
============================================================================================================================================
Execution helpers - flags adjustment
============================================================================================================================================
*/
void CPU_2A03::adjust_n(unsigned value)
{
    if (value & 0x80)
        flags.set_negative();
    else
        flags.clear_negative();
}

void CPU_2A03::adjust_z(unsigned value)
{
    if (value == 0x00)
        flags.set_zero();
    else
        flags.clear_zero();
}

//For BIT opcode only
void CPU_2A03::adjust_v(unsigned value)
{
    if (value &= 0x40)
        flags.set_overflow();
    else
        flags.clear_overflow();
}

/*
============================================================================================================================================
Execution helpers - flags in/out transmission to ALU
============================================================================================================================================
*/
void CPU_2A03::carry_in(unsigned value)
{
if (value)
    flags.set_carry();
else
    flags.clear_carry();
}

void CPU_2A03::overflow_in(unsigned value)
{
if (value)
    flags.set_overflow();
else
    flags.clear_overflow();
}

void CPU_2A03::adjust_alu_carry()
{
if (flags.read_carry())
    alu.set_carry();
else
    alu.clear_carry();
}

/*
============================================================================================================================================
Execution helpers - Stack primitives
============================================================================================================================================
*/
void CPU_2A03::push(unsigned value)
{
    unsigned address = (0x100) | sp.read_value();
    data_bus->write(address, value);
    unsigned sp_value = (sp.read_value() - 1) & 0xFF;
    sp.set_value(sp_value);
}

unsigned CPU_2A03::pop()
{
    unsigned sp_value = (sp.read_value() + 1) & 0xFF;
    sp.set_value(sp_value);
    unsigned address = (0x100) | sp.read_value();
    return (data_bus->read(address));
}

/*
============================================================================================================================================
Execution helpers - NMI/RESET/IRQ handling
============================================================================================================================================
*/
void CPU_2A03::jump_to_vector(unsigned vector_address)
{
    unsigned address;
    unsigned final_addr_low, final_addr_high, final_address;

    //Set PC to RESET vector
    pc.set_value(vector_address);
    //Read addr low
    address = pc.read();
    pc.increment();
    final_addr_low = data_bus->read(address);
    //Read addr hi
    address = pc.read();
    pc.increment();
    final_addr_high = data_bus->read(address);
    //Construct vector addr
    final_address = (final_addr_high << 8) | final_addr_low;
    pc.set_value(final_address);
}

void CPU_2A03::handle_nmi()
{
    //std::cout << "NMI" << std::endl;
    *nmi = false;
    push(pc.read() >> 8 & 0xFF);
    push(pc.read() & 0xFF);
    flags.clear_break();
    push(flags.read_value());
    flags.set_interrupt();
    this->jump_to_vector(nmi_vector);
    clocks += 7;
}

/*
============================================================================================================================================
Execution helpers - Addressing mode generators
============================================================================================================================================
*/
unsigned CPU_2A03::read_8bit_address()
{
    unsigned address;

    //Read zero-page address
    address = data_bus->read(pc.read());
    pc.increment();
    return (address);
}

unsigned CPU_2A03::read_16bit_address()
{
    unsigned addr_hi, addr_lo;

    //Read addr low
    addr_lo = data_bus->read(pc.read());
    pc.increment();

    //Read addr hi
    addr_hi = data_bus->read(pc.read());
    pc.increment();

    //Construct 16 bit address
    return (addr_hi << 8) | addr_lo;
}

unsigned CPU_2A03::generate_absolute_address()
{
    return (this->read_16bit_address());
}

unsigned CPU_2A03::generate_absolute_x_address()
{
    return (this->read_16bit_address() + x.read_value());
}

unsigned CPU_2A03::generate_absolute_y_address()
{
    return (this->read_16bit_address() + y.read_value());
}

unsigned CPU_2A03::generate_zero_page_address()
{
    return (this->read_8bit_address());
}

unsigned CPU_2A03::generate_zero_page_x_address()
{
    return ((this->read_8bit_address() + x.read_value()) & 0xFF);
}

unsigned CPU_2A03::generate_zero_page_y_address()
{
    return ((this->read_8bit_address() + y.read_value()) & 0xFF);
}


unsigned CPU_2A03::generate_indirect_address()
{
    unsigned ind_addr_lo, ind_addr_hi, ind_address;
    unsigned direct_addr_lo, direct_addr_hi;

    //Read and construct indirect addr
    ind_addr_lo = this->read_8bit_address();
    ind_addr_hi = this->read_8bit_address();
    ind_address = (ind_addr_hi << 8) | ind_addr_lo;

    //Read final addr low
    direct_addr_lo = data_bus->read(ind_address);
    //Read final addr hi, with bug emulation
    ind_address = (ind_addr_hi << 8) | ((ind_addr_lo + 1) & 0xFF);
    direct_addr_hi = data_bus->read(ind_address);

    //Return final address
    return (direct_addr_hi << 8) | direct_addr_lo;
}

unsigned CPU_2A03::generate_indirect_pre_indexed()
{
    unsigned zero_page_addr;
    unsigned direct_addr_hi, direct_addr_lo;

    zero_page_addr = this->read_8bit_address();
    zero_page_addr += x.read_value();
    zero_page_addr &= 0xFF;

    direct_addr_lo = data_bus->read(zero_page_addr);
    zero_page_addr++;
    zero_page_addr &= 0xFF;
    direct_addr_hi = data_bus->read(zero_page_addr);

    //Return final address
    return (direct_addr_hi << 8) | direct_addr_lo;
}

unsigned CPU_2A03::generate_indirect_post_indexed()
{
    unsigned zero_page_addr;
    unsigned direct_addr_hi, direct_addr_lo, direct_addr;

    zero_page_addr = this->read_8bit_address();
    direct_addr_lo = data_bus->read(zero_page_addr);
    zero_page_addr++;
    zero_page_addr &= 0xFF;
    direct_addr_hi = data_bus->read(zero_page_addr);

    //Return final address
    direct_addr = (direct_addr_hi << 8) | direct_addr_lo;
    direct_addr += y.read_value();
    direct_addr &= 0xFFFF;
    return (direct_addr);
}


