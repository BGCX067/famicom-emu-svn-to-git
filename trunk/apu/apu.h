#ifndef APU_H
#define APU_H

class APU_Port_Interface;

class APU
{
public:
    APU();
    ~APU();
    APU_Port_Interface*         get_port_interface() {return port_interface;};
private:
    APU_Port_Interface*     port_interface;
};

#endif // APU_H
