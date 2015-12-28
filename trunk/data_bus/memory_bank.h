#ifndef RAM_H
#define RAM_H

class Memory_Bank
{

public:
    Memory_Bank(unsigned size, bool read_only);
    Memory_Bank(const Memory_Bank&);
    ~Memory_Bank();
    Memory_Bank*    copy();

    void        load_buffer_to_memory(char* buf, unsigned load_address, unsigned size);

    unsigned    read(unsigned address);
    void        write(unsigned address, unsigned value);
    unsigned    get_size();


//    void        save_memory_to_file(QString filename);
//    void        load_file_to_memory(QString filename, unsigned load_address);

//signals:
//    void        memory_changed(unsigned address, unsigned value);

public:
    static const unsigned    Read_Only = 1;
    static const unsigned    Read_Write = 2;
private:
    unsigned char*  memory;
    unsigned        memory_size;
    bool            read_only;
};

#endif // RAM_H
