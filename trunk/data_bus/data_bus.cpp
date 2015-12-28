#include "data_bus.h"

Data_Bus::Data_Bus(unsigned _size) : size(_size)
{
}

Data_Bus::~Data_Bus()
{

}

unsigned
Data_Bus::get_size()
{
 return size;
}

