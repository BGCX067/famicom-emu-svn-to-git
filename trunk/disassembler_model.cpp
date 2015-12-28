#include "disassembler_model.h"
#include <map>
#include <iostream>
#include <QBrush>

Disassembler_Model::Disassembler_Model(std::map<unsigned, std::string>& s) : pc_to_disassembly(s)
{
    std::map<unsigned, std::string>::iterator it = pc_to_disassembly.begin();
    unsigned row_number = 0;
    while (it != pc_to_disassembly.end())
    {
        pc_to_row_number[it->first] = row_number;
        row_number_to_pc[row_number] = it->first;
        it++;
        row_number++;
    }

/*    std::map<unsigned, unsigned>::iterator it2 = pc_to_row_number.begin();
    while (it2 != pc_to_row_number.end())
    {
        std::cout << " " << std::hex << it2->first << " -> " << std::dec << it2->second << std::endl;
        it2++;
    }*/

}


Qt::ItemFlags
Disassembler_Model::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return (Qt::NoItemFlags);

    return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

QVariant
Disassembler_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
     return QVariant();
}

int
Disassembler_Model::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return (0);

    return (this->row_number_to_pc.size());
}

QVariant
Disassembler_Model::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();


    const unsigned row_number = index.row();
    const unsigned pc = this->row_number_to_pc.find(row_number)->second;

    if (role == Qt::BackgroundRole)
    {
    if (this->breakpoints.find(pc) == this->breakpoints.end())
        return (QBrush(Qt::white));
    else
        return (QBrush(Qt::red));
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    const std::string s = this->pc_to_disassembly.find(pc)->second;
    return (QString(s.c_str()));
}

QModelIndex
Disassembler_Model::get_address_index(unsigned address) const
{
    const unsigned row_number = this->pc_to_row_number.find(address)->second;
    return (this->createIndex(row_number + 1, 0));
}

unsigned
Disassembler_Model::get_index_address(QModelIndex& i) const
{
    const unsigned address = this->row_number_to_pc.find(i.row())->second;
    return (address);
}


void
Disassembler_Model::toggle_breakpoint(unsigned address)
{
    if (this->breakpoints.find(address) == this->breakpoints.end())
        this->breakpoints.insert(address);
    else
        this->breakpoints.erase(address);
}

