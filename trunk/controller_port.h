#ifndef CONTROLLER_PORT_H
#define CONTROLLER_PORT_H

#include "port/port_8bit.h"
#include "register/register_8bit.h"

class Controller_Inputs;

class Controller_Port : Port_8bit
{
    enum Status
    {
        Reload_States = 0,
        Stop_Reload = 1
    };

public:
    Controller_Port(Controller_Inputs* inputs);
    ~Controller_Port();
    void write(unsigned value);
    unsigned read();

private:
    Controller_Port::Status status;
    Controller_Inputs*  gamepad_1;
//    Register_8bit       shift_register;
    unsigned            shift_position;
};

#endif // CONTROLLER_PORT_H
