#ifndef FLIP_FLOP
#define FLIP_FLOP

class Flip_Flop
{
public:
    Flip_Flop();
    void set();
    void reset();
    void invert();
    bool output();

private:
    bool    flip_flop;
};

#endif // FLIP_FLOP
