#ifndef EMU_6502_H
#define EMU_6502_H

#include <string>
#include "register/register_8bit.h"
#include "program_counter.h"
#include "flags_register.h"
#include "alu.h"
#include "data_bus/cpu/cpu_data_bus.h"
#include <set>
#include <QObject>

class ALU;
class Flags_Register;
class Program_Counter;
class Register_8bit;

class CPU_2A03 : public QObject
{
    Q_OBJECT

public:
    CPU_2A03();
    ~CPU_2A03();
    void connect_data_bus(CPU_Data_Bus* db);
    void execute();
    void execute_clocks(unsigned clocks);
    void raise_nmi() { *nmi = true;};
    void init_cpu();
    void toggle_breakpoint(unsigned address);
    void debug_run();

signals:
    void breakpoint_occurred();

private:
    void adjust_n(unsigned value);
    void adjust_z(unsigned value);
    void adjust_v(unsigned value);
    void carry_in(unsigned value);
    void overflow_in(unsigned value);
    void adjust_alu_carry();

    void push(unsigned value);
    unsigned pop();

    void jump_to_vector(unsigned vector_address);
    void handle_nmi();

    unsigned generate_absolute_address();
    unsigned generate_absolute_x_address();
    unsigned generate_absolute_y_address();
    unsigned generate_zero_page_address();
    unsigned generate_zero_page_x_address();
    unsigned generate_zero_page_y_address();
    unsigned generate_indirect_address();
    unsigned generate_indirect_pre_indexed();
    unsigned generate_indirect_post_indexed();

    unsigned read_8bit_address();
    unsigned read_16bit_address();


    static const unsigned reset_vector = 0xFFFC;
    static const unsigned irq_vector = 0xFFFE;
    static const unsigned nmi_vector = 0xFFFA;

private:
    unsigned    clocks;

public:
    //Internal registers and components
    Register_8bit   ac;
    Register_8bit   x;
    Register_8bit   y;
    Register_8bit   sp;
    Program_Counter pc;
    Flags_Register  flags;
    ALU             alu;

    //External connections
    CPU_Data_Bus*   data_bus;
    bool*           nmi;

    //Debugging facilities
    bool            has_breakpoints;
    std::set<unsigned>   breakpoints;
};

#endif // EMU_6502_H
