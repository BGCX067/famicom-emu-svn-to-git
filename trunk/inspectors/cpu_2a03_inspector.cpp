#include "cpu_2a03_inspector.h"
#include "ui_cpu_2a03_inspector.h"
#include "cpu/cpu_2a03.h"
#include "memory_bank_model.h"
#include "disassembler.h"
#include "disassembler_model.h"

#include <QTableView>
#include <QModelIndex>

CPU_2A03_Inspector::CPU_2A03_Inspector(CPU_2A03* _cpu, Memory_Bank* _bank, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CPU_2A03_Inspector), cpu(_cpu)
{
    ui->setupUi(this);
    update_edits();
    update_flags();

    Disassembler dis;
    std::map<unsigned, std::string> m = dis.debugger_disassemble_bank(_bank, 0xC000);

    Disassembler_Model* model = new Disassembler_Model(m);
    ui->disasm_view->setModel(model);
    update_disasm_view();
    QObject::connect(ui->disasm_view, SIGNAL(clicked(QModelIndex)), this, SLOT(address_clicked(QModelIndex)));
    QObject::connect(ui->disasm_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(address_double_clicked(QModelIndex)));
}

CPU_2A03_Inspector::~CPU_2A03_Inspector()
{
    delete ui;
}

void CPU_2A03_Inspector::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
// SLOTS
/*
  Each of the slots changes the corresponding value of a register in the CPU emulator class.
  Afterwards, it updates the register widgets (via either "update_flags" or "update_edits")
  to convert to uppercase the entered value.
*/
void CPU_2A03_Inspector::flags_changed()
{
    cpu->flags.set_value(ui->flags_edit->text().toUInt(NULL, 16));
    update_flags();
}

void CPU_2A03_Inspector::ac_changed()
{
    cpu->ac.set_value(ui->ac_edit->text().toUInt(NULL, 16));
    update_edits();
}

void CPU_2A03_Inspector::x_changed()
{
    cpu->x.set_value(ui->x_edit->text().toUInt(NULL, 16));
    update_edits();
}

void CPU_2A03_Inspector::y_changed()
{
    cpu->y.set_value(ui->y_edit->text().toUInt(NULL, 16));
    update_edits();
}

void CPU_2A03_Inspector::sp_changed()
{
    cpu->sp.set_value(ui->sp_edit->text().toUInt(NULL, 16));
    update_edits();
}

void CPU_2A03_Inspector::pc_changed()
{
    cpu->pc.set_value(ui->pc_edit->text().toUInt(NULL, 16));
    update_edits();
}

void CPU_2A03_Inspector::next_instruction()
{
    cpu->execute();
    update_flags();
    update_edits();
    update_disasm_view();
}

void CPU_2A03_Inspector::address_clicked(QModelIndex i)
{
    Disassembler_Model* model = dynamic_cast<Disassembler_Model*> (ui->disasm_view->model());
    unsigned address = model->get_index_address(i);
    cpu->toggle_breakpoint(address);
    model->toggle_breakpoint(address);
    update_disasm_view();
}

void CPU_2A03_Inspector::address_double_clicked(QModelIndex i)
{
/*    Disassembler_Model* model = dynamic_cast<Disassembler_Model*> (ui->disasm_view->model());
    unsigned address = model->get_index_address(i);
    cpu->pc.set_value(address);
    update_edits();*/
}


void CPU_2A03_Inspector::update_disasm_view()
{
    Disassembler_Model* model = dynamic_cast<Disassembler_Model*> (ui->disasm_view->model());
    QModelIndex pc_index(model->get_address_index(cpu->pc.read()));
    ui->disasm_view->scrollTo(pc_index, QAbstractItemView::PositionAtCenter);
    QItemSelection selection(pc_index, pc_index);
    ui->disasm_view->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
}

void CPU_2A03_Inspector::run()
{
    cpu->debug_run();
    update_flags();
    update_edits();
    update_disasm_view();
}


/*
  Updates the registers' QLineEdit widgets with the CPU values. Uses
  value_to_hex_string to format the value into a proper QString, zero-padded.
*/
void CPU_2A03_Inspector::update_edits()
{
    ui->ac_edit->setText(value_to_hex_string(cpu->ac.read_value(), 2));
    ui->x_edit->setText(value_to_hex_string(cpu->x.read_value(), 2));
    ui->y_edit->setText(value_to_hex_string(cpu->y.read_value(), 2));
    ui->sp_edit->setText(value_to_hex_string(cpu->sp.read_value(), 2));
    ui->pc_edit->setText(value_to_hex_string(cpu->pc.read(), 4));
}

/*
  Updates the flags QLineEdit widget with the CPU values. Uses
  value_to_hex_string to format the value into a proper QString, zero-padded.
  It also updates the QLabel for each bit of the flags register.
*/
void CPU_2A03_Inspector::update_flags()
{
    ui->flags_edit->setText(value_to_hex_string(cpu->flags.read_value(), 2));
    ui->break_label->setText(value_to_hex_string(cpu->flags.read_break(), 1));
    ui->carry_label->setText(value_to_hex_string(cpu->flags.read_carry(), 1));
    ui->decimal_label->setText(value_to_hex_string(cpu->flags.read_decimal(), 1));
    ui->interrupt_label->setText(value_to_hex_string(cpu->flags.read_interrupt(), 1));
    ui->negative_label->setText(value_to_hex_string(cpu->flags.read_negative(), 1));
    ui->overflow_label->setText(value_to_hex_string(cpu->flags.read_overflow(), 1));
    ui->unused_label->setText(value_to_hex_string(cpu->flags.read_unused(), 1));
    ui->zero_label->setText(value_to_hex_string(cpu->flags.read_zero(), 1));
}

/*
  Converts a value to a hexadecimal string, in uppercase, zero-padded to the left.
*/
QString
CPU_2A03_Inspector::value_to_hex_string(unsigned value, unsigned hex_length)
{
    return (QString::number(value, 16).toUpper().rightJustified(hex_length, '0'));
}

/*
void main_window::flags_break_changed()
{
    bool flag_set = (ui->flags_break_edit->text() == "1");
    if (flag_set)
        emu.flags.set_break();
    else
        emu.flags.clear_break();
    update_flags();
}

void main_window::flags_carry_changed()
{
    bool flag_set = (ui->flags_carry_edit->text() == "1");
    if (flag_set)
        emu.flags.set_carry();
    else
        emu.flags.clear_carry();
    update_flags();
}

void main_window::flags_decimal_changed()
{
    bool flag_set = (ui->flags_decimal_edit->text() == "1");
    if (flag_set)
        emu.flags.set_decimal();
    else
        emu.flags.clear_decimal();
    update_flags();
}

void main_window::flags_interrupt_changed()
{
    bool flag_set = (ui->flags_interrupt_edit->text() == "1");
    if (flag_set)
        emu.flags.set_interrupt();
    else
        emu.flags.clear_interrupt();
    update_flags();
}

void main_window::flags_negative_changed()
{
    bool flag_set = (ui->flags_negative_edit->text() == "1");
    if (flag_set)
        emu.flags.set_negative();
    else
        emu.flags.clear_negative();
    update_flags();
}

void main_window::flags_overflow_changed()
{
    bool flag_set = (ui->flags_overflow_edit->text() == "1");
    if (flag_set)
        emu.flags.set_overflow();
    else
        emu.flags.clear_overflow();
    update_flags();
}

void main_window::flags_unused_changed()
{
    bool flag_set = (ui->flags_unused_edit->text() == "1");
    if (flag_set)
        emu.flags.set_unused();
    else
        emu.flags.clear_unused();
    update_flags();
}

void main_window::flags_zero_changed()
{
    bool flag_set = (ui->flags_zero_edit->text() == "1");
    if (flag_set)
        emu.flags.set_zero();
    else
        emu.flags.clear_zero();
    update_flags();
}

void main_window::combo_opcode_changed(QString s)
{
    current_opcode = s;
}

void main_window::operand_changed()
{
    current_operand = ui->operand_edit->text().toUInt(NULL, 16);
}


void main_window::test_opcode()
{
    unsigned opcode;

    opcode = current_opcode.right(2).toUInt(NULL, 16);
    emu.execute();
    update_edits();
    update_flags();
    update_pc_highlight();
}
*/


/*
void main_window::memory_cell_changed(int row, int col)
{
    QString cell_value = ui->memory_table->item(row, col)->text();
    ui->memory_table->item(row, col)->setText(cell_value.toUpper());
    unsigned value = cell_value.toUInt(NULL, 16);
    unsigned address = row * 16 + col;//FIXME!
    data_bus.write(address, value);
    update_disasm_label();
}

void main_window::memory_ram_changed(unsigned address, unsigned value)
{
    unsigned row =  address / 16;
    unsigned col = address % 16;
    ui->memory_table->item(row, col)->setText(QString::number(value, 16).toUpper().rightJustified(2, '0'));
}

void main_window::load_memory()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load Memory"), ".", tr("*.*"));
    Memory_Bank* r = data_bus.get_ram_bank(0);
    r->load_file_to_memory(filename, 0);
}


void main_window::save_memory()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Memory"), ".", tr("*.*"));
    Memory_Bank* r = data_bus.get_ram_bank(0);
    r->save_memory_to_file(filename);
}

void main_window::update_pc_highlight()
{
    static unsigned old_row;
    static unsigned old_col;
    static QBrush old_brush;
    static bool old_highlight = false;


    //If there was a previously painted cell, undo the highlight and restore the old brush background
    if (old_highlight)
    {
        ui->memory_table->item(old_row, old_col)->setBackground(old_brush);
    }

    //Determine row/col of PC position in memory inspector
    unsigned address = emu.pc.read();
    unsigned row =  address / 16;
    unsigned col = address % 16;

    //Save current cell data (flag, row, col, brush) for a undo
    old_highlight = true;
    old_row = row;
    old_col = col;
    old_brush = ui->memory_table->item(row, col)->background();

    //Paint the current cell with the highlight brush
    QBrush highlight_brush(QColor(255, 255, 0), Qt::SolidPattern);
    ui->memory_table->item(row, col)->setBackground(highlight_brush);
}

void main_window::update_disasm_label()
{
    unsigned opcode = emu.data_bus->read(emu.pc.read());
    ui->disasm_label->setText(mnemonics[opcode]);
}

void main_window::create_image()
{
    QImage::Format format(QImage::Format_RGB32);
    this->tile_image = QImage::QImage( QSize::QSize(8, 8), format);
    for (unsigned row = 0; row < 8; row++)
        for (unsigned col = 0; col < 8; col++)
            this->tile_image.setPixel(row, col, 0xFF4020FF);

    ui->tile_label->setPixmap(QPixmap::fromImage(this->tile_image));
}
*/


//Fill opcode combo box with opcodes
/*ui->opcode_combo->setInsertPolicy(QComboBox::InsertAlphabetically);
for (unsigned i = 0; i < total_opcodes; i++)
{
    if (mnemonics[i] != "UNK")
        ui->opcode_combo->insertItem(i, mnemonics[i] + " - " + QString::number(i, 16).toUpper().rightJustified(2, '0'));
}
ui->opcode_combo->model()->sort(0); //Sort it
current_opcode = ui->opcode_combo->itemText(ui->opcode_combo->currentIndex());

setup_memory_inspector();
update_pc_highlight();
update_disasm_label();
create_image();*/
