#ifndef MEMORY_BANK_MODEL_H
#define MEMORY_BANK_MODEL_H

#include <QAbstractTableModel>
#include "data_bus/memory_bank.h"

class Memory_Bank_Model : public QAbstractTableModel
{
public:
    Memory_Bank_Model(Memory_Bank* bank);

    Qt::ItemFlags   flags(const QModelIndex& index) const;
    QVariant        headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int             rowCount(const QModelIndex& parent = QModelIndex()) const;
    int             columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant        data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    Memory_Bank*    bank;
};

#endif // MEMORY_BANK_MODEL_H
