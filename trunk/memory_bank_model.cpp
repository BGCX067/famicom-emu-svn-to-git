#include "memory_bank_model.h"

Memory_Bank_Model::Memory_Bank_Model(Memory_Bank* _bank) : bank(_bank)
{
}

Qt::ItemFlags
Memory_Bank_Model::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return (Qt::NoItemFlags);

    return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

QVariant
Memory_Bank_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
     return QVariant();

 if (orientation == Qt::Horizontal)
    return QString::number(section, 16).toUpper().rightJustified(2, '0');
 else
    return QString::number(section * 16, 16).toUpper().rightJustified(4, '0');
}

int
Memory_Bank_Model::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return (0);

    unsigned rows = this->bank->get_size() / 16;
    if ((this->bank->get_size() % 16) != 0)
        rows++;

    return (rows);
}

int
Memory_Bank_Model::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return (0);

    return (16);
}

QVariant
Memory_Bank_Model::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    unsigned address = index.row() * 16 + index.column();
    return QString::number(this->bank->read(address), 16).toUpper().rightJustified(2, '0');
}
