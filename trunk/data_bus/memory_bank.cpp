#include "memory_bank.h"
#include <QFile>
#include <QDataStream>
#include <iostream>

Memory_Bank::Memory_Bank(unsigned sz, bool r_only) : memory_size(sz), read_only(r_only)
{
    this->memory = new unsigned char[this->memory_size];
    //Bzero apparently not present in Win32
    for (unsigned i = 0; i < this->memory_size; i++)
        this->memory[i] = 0;
}

Memory_Bank::~Memory_Bank()
{
    delete[] this->memory;
}

Memory_Bank::Memory_Bank(const Memory_Bank& b)
{
    this->memory_size = b.memory_size;
    this->read_only = b.read_only;
    this->memory = new unsigned char[this->memory_size];
    memcpy(this->memory, b.memory, this->memory_size);
}

Memory_Bank*
Memory_Bank::copy()
{
    Memory_Bank* m = new Memory_Bank(*this);
    return (m);
}

unsigned
Memory_Bank::read(unsigned address)
{
    if (address > this->memory_size)
    {
        QString s("Memory_Bank::read - address: " + QString::number(address, 16));
        std::cout << s.toStdString() << std::endl;
        throw new std::string(s.toStdString());//EXCEPTION
    }

    return (unsigned) this->memory[address];
}

void
Memory_Bank::write(unsigned address, unsigned value)
{
    if (this->read_only)
        return;

    if (address > this->memory_size)
    {
        QString s("Memory_Bank::write - address: " + QString::number(address, 16));
        std::cout << s.toStdString() << std::endl;
        std::cout << memory_size << std::endl;
        throw new std::string(s.toStdString());//EXCEPTION
    }

    this->memory[address] = (unsigned char) value;
    //emit memory_changed(address, value);
}

unsigned
Memory_Bank::get_size()
{
    return this->memory_size;
}


void
Memory_Bank::load_buffer_to_memory(char* buf, unsigned load_address, unsigned load_size)
{
    if (load_address + load_size > memory_size)
    {
        QString s("Memory_Bank::load exceeds size");
        throw new std::string(s.toStdString());//EXCEPTION
    }
    memcpy(memory + load_address, buf, load_size);
}

/*
void
Memory_Bank::save_memory_to_file(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QDataStream out(&file);

    const char* temp = new char [memory_size];
    memcpy((void*)temp, memory, memory_size);
    out.writeRawData(temp, memory_size);
    delete[] temp;
    file.close();
}

void
Memory_Bank::load_file_to_memory(QString filename, unsigned load_address)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    unsigned load_size = file.size();
    if (load_address + load_size > memory_size)
        load_size = memory_size - load_address;

    in.readRawData((char*) memory + load_address, load_size);
    file.close();

    for (unsigned i = 0; i < load_size; i++)
        emit memory_changed(load_address + i, memory[load_address+i]);
}

*/
