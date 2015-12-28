#ifndef CONTROLLER_INPUTS_H
#define CONTROLLER_INPUTS_H

class Controller_Inputs
{
friend class Controller_Port;

public:
    Controller_Inputs();

    void set_up() {up = true;};
    void set_down() {down = true;};
    void set_left() {left = true;};
    void set_right() {right = true;};
    void set_a_button() {a_button = true;};
    void set_b_button() {b_button = true;};
    void set_select() {select = true;};
    void set_start() {start = true;};

    void clear_up() {up = false;};
    void clear_down() {down = false;};
    void clear_left() {left = false;};
    void clear_right() {right = false;};
    void clear_a_button() {a_button = false;};
    void clear_b_button() {b_button = false;};
    void clear_select() {select = false;};
    void clear_start() {start = false;};

private:
    bool    up;
    bool    down;
    bool    left;
    bool    right;
    bool    a_button;
    bool    b_button;
    bool    select;
    bool    start;
};

#endif // CONTROLLER_INPUTS_H
