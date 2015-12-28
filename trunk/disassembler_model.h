#ifndef DISASSEMBLER_MODEL_H
#define DISASSEMBLER_MODEL_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <QAbstractListModel>

class Disassembler_Model : public QAbstractListModel
{
public:
    Disassembler_Model(std::map<unsigned, std::string>& s);

    Qt::ItemFlags   flags(const QModelIndex& index) const;
    QVariant        headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int             rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant        data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QModelIndex     get_address_index(unsigned address) const;
    unsigned        get_index_address(QModelIndex& i) const;
    void            toggle_breakpoint(unsigned address);

private:
    std::map<unsigned, std::string>    pc_to_disassembly;
    std::map<unsigned, unsigned>       pc_to_row_number;
    std::map<unsigned, unsigned>       row_number_to_pc;
    std::set<unsigned>                  breakpoints;
};

#endif // DISASSEMBLER_MODEL_H
