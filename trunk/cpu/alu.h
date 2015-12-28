#ifndef ALU_H
#define ALU_H

class ALU
{
public:
    ALU();
    unsigned shift_left(unsigned value);
    unsigned shift_right(unsigned value);
    unsigned rotate_left(unsigned value);
    unsigned rotate_right(unsigned value);
    unsigned add(unsigned v1, unsigned v2);
    unsigned subtract(unsigned v1, unsigned v2);
    unsigned compare(unsigned v1, unsigned v2);
    unsigned _and(unsigned v1, unsigned v2);
    unsigned _or(unsigned v1, unsigned v2);
    unsigned _xor(unsigned v1, unsigned v2);
    unsigned bit(unsigned v1);
    unsigned increment(unsigned v1);
    unsigned decrement(unsigned v1);

    unsigned read_carry();    
    void set_carry();
    void clear_carry();
    unsigned read_overflow();
    void set_overflow();
    void clear_overflow();
    unsigned read_zero();
    void set_zero();
    void clear_zero();
    unsigned read_negative();
    void set_negative();
    void clear_negative();

private:
    unsigned carry;
    unsigned overflow;
    unsigned negative;
    unsigned zero;
};

#endif // ALU_H
