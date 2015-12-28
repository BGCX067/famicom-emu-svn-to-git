#ifndef CPU_DATA_BUS_M0_H
#define CPU_DATA_BUS_M0_H
#include "cpu_data_bus.h"
#include <vector>

class CPU_Data_Bus;
class Memory_Bank;

class CPU_Data_Bus_M0 : public CPU_Data_Bus
{
public:
    CPU_Data_Bus_M0();
    ~CPU_Data_Bus_M0();

    void connect_rom_bank(unsigned bank_num, Memory_Bank* _rom_bank);
    Memory_Bank*    get_rom_bank(unsigned bank_num) {return this->rom_banks[bank_num];};
    unsigned        get_total_rom_banks() {return this->rom_banks.size();};

    unsigned    read(unsigned address);
    void        write(unsigned address, unsigned value);

private:
    std::vector<Memory_Bank*>   rom_banks;
    unsigned                    rom_size;
};

#endif // CPU_DATA_BUS_M0_H
