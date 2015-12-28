#include "ui_data_bus_inspector.h"
#include "data_bus_inspector.h"
#include "data_bus/data_bus.h"
#include <iostream>

Data_Bus_Inspector::Data_Bus_Inspector(Data_Bus* _bus, QString window_title, QWidget* parent)
    :
    QMainWindow(parent),
    ui(new Ui::Data_Bus_Inspector),
    bus(_bus)
{
    ui->setupUi(this);
    setWindowTitle(window_title);
    setup_memory_table();
}

Data_Bus_Inspector::~Data_Bus_Inspector()
{
    delete ui;
}

void Data_Bus_Inspector::changeEvent(QEvent *e)
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

void
Data_Bus_Inspector::setup_memory_table()
{
    //Calculate total rows and columns
    unsigned total_cols = 16;
    unsigned total_rows = bus->get_size() / total_cols;
    std::cout << "Total Cols:"  << total_cols << std::endl;
    std::cout << "Total Rows:"  << total_rows << std::endl;

    //Set alternating row colors
    ui->memory_table->setAlternatingRowColors(true);

    //Set row/col count
    ui->memory_table->setRowCount(total_rows);
    ui->memory_table->setColumnCount(total_cols);

    //Set row/col headers
    QStringList col_header_labels;
    for (unsigned col = 0; col < total_cols; col++)
    {
        ui->memory_table->setColumnWidth(col, 40);
        col_header_labels << QString::number(col, 16).toUpper().rightJustified(2, '0');
    }
    ui->memory_table->setHorizontalHeaderLabels(col_header_labels);

    QStringList row_header_labels;
    for (unsigned row = 0; row < total_rows; row++)
    {
        ui->memory_table->setRowHeight(row, 30);
        row_header_labels << QString::number(row * total_cols, 16).toUpper().rightJustified(4, '0');
    }
    ui->memory_table->setVerticalHeaderLabels(row_header_labels);

    //Fill in items
    unsigned address = 0;
    for (unsigned row = 0; row < total_rows; row++)
    {
        for (unsigned col = 0; col < total_cols; col++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(bus->read(address), 16).toUpper().rightJustified(2, '0'));
//            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(0, 16).toUpper().rightJustified(2, '0'));
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->memory_table->setItem(row, col, newItem);
            address++;
        }
    }

    //Connect to RAM Bank
    //QObject::connect(bus->get_ram_bank(0), SIGNAL(memory_changed(uint,uint)), this, SLOT(memory_ram_changed(uint,uint)));
}

