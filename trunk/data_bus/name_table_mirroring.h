#ifndef NAME_TABLE_MIRRORING_H
#define NAME_TABLE_MIRRORING_H

class Name_Table_Mirroring
{
public:
    Name_Table_Mirroring();

    enum Type
    {
    Horizontal = 0,
    Vertical = 1,
    Four_Screen = 2
    };
};
/*static unsigned Horizontal;
static unsigned Vertical;
static unsigned Four_Screen;


unsigned Name_Table_Mirroring::Horizontal = 0;
unsigned Name_Table_Mirroring::Vertical = 1;
unsigned Name_Table_Mirroring::Four_Screen = 2;*/

#endif // NAME_TABLE_MIRRORING_H
