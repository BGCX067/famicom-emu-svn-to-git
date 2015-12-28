#include "controller_port.h"
#include "register/register_8bit.h"
#include "controller_inputs.h"

Controller_Port::Controller_Port(Controller_Inputs* _gamepad_1) : gamepad_1(_gamepad_1)
{
    shift_position = 0;
    status = Controller_Port::Stop_Reload;
}

Controller_Port::~Controller_Port()
{
}

void
Controller_Port::write(unsigned value)
{
    if (value & 1)
    {
        status = Controller_Port::Reload_States;
        return;
    }

    if (value == 0)
    {
        status = Controller_Port::Stop_Reload;
        shift_position = 0;
    }
}

unsigned
Controller_Port::read()
{
    unsigned return_value = 0;

    switch (shift_position)
    {
        case 0:
            return_value = (gamepad_1->a_button) ? 1 : 0;
            break;
        case 1:
            return_value = (gamepad_1->b_button) ? 1 : 0;
            break;
        case 2:
            return_value = (gamepad_1->select) ? 1 : 0;
            break;
        case 3:
            return_value = (gamepad_1->start) ? 1 : 0;
            break;
        case 4:
            return_value = (gamepad_1->up) ? 1 : 0;
            break;
        case 5:
            return_value = (gamepad_1->down) ? 1 : 0;
            break;
        case 6:
            return_value = (gamepad_1->left) ? 1 : 0;
            break;
        case 7:
            return_value = (gamepad_1->right) ? 1 : 0;
            break;
        default:
            return_value = 1;
            break;
    }
    shift_position++;
    if (shift_position > 8)
        shift_position = 8;

    return return_value;
}
