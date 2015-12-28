#ifndef CPU_DATA_BUS_INSPECTOR_H
#define CPU_DATA_BUS_INSPECTOR_H

#include <QMainWindow>

class Data_Bus;

namespace Ui {
    class Data_Bus_Inspector;
}

class Data_Bus_Inspector : public QMainWindow
{
    Q_OBJECT

public:
    Data_Bus_Inspector(Data_Bus* bus, QString window_title, QWidget* parent = 0);
    ~Data_Bus_Inspector();

protected:
    void changeEvent(QEvent *e);

private:
    void setup_memory_table();

private:
    Ui::Data_Bus_Inspector*     ui;
    Data_Bus*                   bus;
};

#endif // CPU_DATA_BUS_INSPECTOR_H
