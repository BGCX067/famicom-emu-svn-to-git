#ifndef CPU_2A03_INSPECTOR_H
#define CPU_2A03_INSPECTOR_H

#include <QMainWindow>
#include <QModelIndex>

class CPU_2A03;
class Memory_Bank;

namespace Ui {
    class CPU_2A03_Inspector;
}

class CPU_2A03_Inspector : public QMainWindow {
    Q_OBJECT

public:
    CPU_2A03_Inspector(CPU_2A03* cpu, Memory_Bank* _bank, QWidget *parent = 0);
    ~CPU_2A03_Inspector();

public slots:
    void flags_changed();
    void ac_changed();
    void x_changed();
    void y_changed();
    void sp_changed();
    void pc_changed();
    void next_instruction();
    void address_clicked(QModelIndex i);
    void address_double_clicked(QModelIndex i);
    void run();

protected:
    void changeEvent(QEvent *e);

private:
    void update_edits();
    void update_flags();
    QString value_to_hex_string(unsigned value, unsigned hex_length);
    void update_disasm_view();

private:
    Ui::CPU_2A03_Inspector  *ui;
    CPU_2A03*               cpu;
};

#endif // CPU_2A03_INSPECTOR_H
