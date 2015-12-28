#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

class Program_Counter
{
public:
    Program_Counter();
    unsigned read();
    void set_value(unsigned value);
    void increment();
    void decrement();
    bool add_relative(unsigned operand);

private:
    unsigned    value;
};

#endif // PROGRAM_COUNTER_H
