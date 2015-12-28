#ifndef DATA_BUS_H
#define DATA_BUS_H

class Data_Bus
{
public:
    Data_Bus(unsigned size);
    virtual ~Data_Bus();
    virtual unsigned read(unsigned address) = 0;
    virtual void write(unsigned address, unsigned value) = 0;
    unsigned    get_size();

private:
    unsigned size;
};

#endif // DATA_BUS_H
