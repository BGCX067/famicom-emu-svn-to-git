/********************************************************************************
** Form generated from reading UI file 'emulator.ui'
**
** Created: Fri 12. Jul 02:47:39 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATOR_H
#define UI_EMULATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Emulator
{
public:
    QPushButton *run_push_button;
    QPushButton *load_push_button;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Emulator)
    {
        if (Emulator->objectName().isEmpty())
            Emulator->setObjectName(QString::fromUtf8("Emulator"));
        Emulator->resize(738, 557);
        run_push_button = new QPushButton(Emulator);
        run_push_button->setObjectName(QString::fromUtf8("run_push_button"));
        run_push_button->setEnabled(false);
        run_push_button->setGeometry(QRect(570, 450, 121, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Sans Serif"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        run_push_button->setFont(font);
        load_push_button = new QPushButton(Emulator);
        load_push_button->setObjectName(QString::fromUtf8("load_push_button"));
        load_push_button->setGeometry(QRect(40, 450, 121, 51));
        load_push_button->setFont(font);
        label = new QLabel(Emulator);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 40, 190, 24));
        label->setFont(font);
        label_2 = new QLabel(Emulator);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 100, 651, 336));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/pixmaps/Famicom-Console-Set-scaled.JPG")));
        label_2->setScaledContents(true);

        retranslateUi(Emulator);
        QObject::connect(load_push_button, SIGNAL(pressed()), Emulator, SLOT(load_rom()));
        QObject::connect(run_push_button, SIGNAL(pressed()), Emulator, SLOT(execute_loop()));

        QMetaObject::connectSlotsByName(Emulator);
    } // setupUi

    void retranslateUi(QWidget *Emulator)
    {
        Emulator->setWindowTitle(QApplication::translate("Emulator", "Fami", 0, QApplication::UnicodeUTF8));
        run_push_button->setText(QApplication::translate("Emulator", "Run", 0, QApplication::UnicodeUTF8));
        load_push_button->setText(QApplication::translate("Emulator", "Load...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Emulator", "Famicom Emulator", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Emulator: public Ui_Emulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATOR_H
