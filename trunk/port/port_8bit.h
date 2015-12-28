#ifndef PORT_8BIT_H
#define PORT_8BIT_H

class Port_8bit
{
public:
    Port_8bit();
    virtual ~Port_8bit();
    virtual void write(unsigned value) = 0;
    virtual unsigned read() = 0;
};

#endif // PORT_8BIT_H
