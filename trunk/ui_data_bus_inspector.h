/********************************************************************************
** Form generated from reading UI file 'data_bus_inspector.ui'
**
** Created: Fri 12. Jul 02:47:39 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_BUS_INSPECTOR_H
#define UI_DATA_BUS_INSPECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Data_Bus_Inspector
{
public:
    QTableWidget *memory_table;

    void setupUi(QWidget *Data_Bus_Inspector)
    {
        if (Data_Bus_Inspector->objectName().isEmpty())
            Data_Bus_Inspector->setObjectName(QString::fromUtf8("Data_Bus_Inspector"));
        Data_Bus_Inspector->resize(814, 676);
        memory_table = new QTableWidget(Data_Bus_Inspector);
        memory_table->setObjectName(QString::fromUtf8("memory_table"));
        memory_table->setGeometry(QRect(14, 23, 771, 621));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(memory_table->sizePolicy().hasHeightForWidth());
        memory_table->setSizePolicy(sizePolicy);
        memory_table->setMinimumSize(QSize(457, 380));
        memory_table->setMaximumSize(QSize(1200, 800));

        retranslateUi(Data_Bus_Inspector);

        QMetaObject::connectSlotsByName(Data_Bus_Inspector);
    } // setupUi

    void retranslateUi(QWidget *Data_Bus_Inspector)
    {
        Data_Bus_Inspector->setWindowTitle(QApplication::translate("Data_Bus_Inspector", "CPU Data Bus Inspector", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Data_Bus_Inspector: public Ui_Data_Bus_Inspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_BUS_INSPECTOR_H
