/********************************************************************************
** Form generated from reading UI file 'cpu_2a03_inspector.ui'
**
** Created: Fri 12. Jul 02:47:39 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPU_2A03_INSPECTOR_H
#define UI_CPU_2A03_INSPECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPU_2A03_Inspector
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QLabel *negative_label;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_2;
    QLabel *overflow_label;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer_9;
    QLabel *break_label;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_22;
    QSpacerItem *horizontalSpacer_10;
    QLabel *decimal_label;
    QWidget *horizontalLayoutWidget_13;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_35;
    QSpacerItem *horizontalSpacer_13;
    QLabel *carry_label;
    QWidget *horizontalLayoutWidget_14;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_37;
    QSpacerItem *horizontalSpacer_14;
    QLabel *zero_label;
    QWidget *horizontalLayoutWidget_15;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_39;
    QSpacerItem *horizontalSpacer_15;
    QLabel *unused_label;
    QWidget *horizontalLayoutWidget_16;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_41;
    QSpacerItem *horizontalSpacer_16;
    QLabel *interrupt_label;
    QListView *disasm_view;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLineEdit *pc_edit;
    QLineEdit *ac_edit;
    QLabel *label_2;
    QLineEdit *x_edit;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *y_edit;
    QLabel *label_9;
    QLineEdit *sp_edit;
    QLineEdit *flags_edit;
    QLabel *label_17;

    void setupUi(QMainWindow *CPU_2A03_Inspector)
    {
        if (CPU_2A03_Inspector->objectName().isEmpty())
            CPU_2A03_Inspector->setObjectName(QString::fromUtf8("CPU_2A03_Inspector"));
        CPU_2A03_Inspector->setWindowModality(Qt::NonModal);
        CPU_2A03_Inspector->setEnabled(true);
        CPU_2A03_Inspector->resize(559, 584);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CPU_2A03_Inspector->sizePolicy().hasHeightForWidth());
        CPU_2A03_Inspector->setSizePolicy(sizePolicy);
        CPU_2A03_Inspector->setMinimumSize(QSize(192, 210));
        CPU_2A03_Inspector->setMaximumSize(QSize(1000, 600));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(10);
        font.setKerning(true);
        CPU_2A03_Inspector->setFont(font);
        CPU_2A03_Inspector->setFocusPolicy(Qt::NoFocus);
        CPU_2A03_Inspector->setAnimated(false);
        CPU_2A03_Inspector->setDocumentMode(false);
        CPU_2A03_Inspector->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(CPU_2A03_Inspector);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QFont font1;
        font1.setPointSize(11);
        font1.setKerning(true);
        centralWidget->setFont(font1);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(120, 30, 42, 20));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMinimumSize(QSize(12, 12));
        label_6->setMaximumSize(QSize(12, 12));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Fixedsys"));
        label_6->setFont(font2);
        label_6->setFocusPolicy(Qt::NoFocus);
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        negative_label = new QLabel(horizontalLayoutWidget);
        negative_label->setObjectName(QString::fromUtf8("negative_label"));
        sizePolicy.setHeightForWidth(negative_label->sizePolicy().hasHeightForWidth());
        negative_label->setSizePolicy(sizePolicy);
        negative_label->setMinimumSize(QSize(12, 12));
        negative_label->setMaximumSize(QSize(12, 12));
        negative_label->setFont(font2);
        negative_label->setCursor(QCursor(Qt::OpenHandCursor));
        negative_label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(negative_label);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(120, 50, 41, 20));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_18 = new QLabel(horizontalLayoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setMinimumSize(QSize(12, 12));
        label_18->setMaximumSize(QSize(12, 12));
        label_18->setFont(font2);
        label_18->setFocusPolicy(Qt::NoFocus);
        label_18->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_18);

        horizontalSpacer_2 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        overflow_label = new QLabel(horizontalLayoutWidget_2);
        overflow_label->setObjectName(QString::fromUtf8("overflow_label"));
        sizePolicy.setHeightForWidth(overflow_label->sizePolicy().hasHeightForWidth());
        overflow_label->setSizePolicy(sizePolicy);
        overflow_label->setMinimumSize(QSize(12, 12));
        overflow_label->setMaximumSize(QSize(12, 12));
        overflow_label->setFont(font2);
        overflow_label->setCursor(QCursor(Qt::OpenHandCursor));
        overflow_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(overflow_label);

        horizontalLayoutWidget_9 = new QWidget(centralWidget);
        horizontalLayoutWidget_9->setObjectName(QString::fromUtf8("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(120, 90, 41, 20));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(horizontalLayoutWidget_9);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);
        label_20->setMinimumSize(QSize(12, 12));
        label_20->setMaximumSize(QSize(12, 12));
        label_20->setFont(font2);
        label_20->setFocusPolicy(Qt::NoFocus);
        label_20->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_20);

        horizontalSpacer_9 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        break_label = new QLabel(horizontalLayoutWidget_9);
        break_label->setObjectName(QString::fromUtf8("break_label"));
        sizePolicy.setHeightForWidth(break_label->sizePolicy().hasHeightForWidth());
        break_label->setSizePolicy(sizePolicy);
        break_label->setMinimumSize(QSize(12, 12));
        break_label->setMaximumSize(QSize(12, 12));
        break_label->setFont(font2);
        break_label->setCursor(QCursor(Qt::OpenHandCursor));
        break_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(break_label);

        horizontalLayoutWidget_10 = new QWidget(centralWidget);
        horizontalLayoutWidget_10->setObjectName(QString::fromUtf8("horizontalLayoutWidget_10"));
        horizontalLayoutWidget_10->setGeometry(QRect(120, 110, 41, 20));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(horizontalLayoutWidget_10);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);
        label_22->setMinimumSize(QSize(12, 12));
        label_22->setMaximumSize(QSize(12, 12));
        label_22->setFont(font2);
        label_22->setFocusPolicy(Qt::NoFocus);
        label_22->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_22);

        horizontalSpacer_10 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_10);

        decimal_label = new QLabel(horizontalLayoutWidget_10);
        decimal_label->setObjectName(QString::fromUtf8("decimal_label"));
        sizePolicy.setHeightForWidth(decimal_label->sizePolicy().hasHeightForWidth());
        decimal_label->setSizePolicy(sizePolicy);
        decimal_label->setMinimumSize(QSize(12, 12));
        decimal_label->setMaximumSize(QSize(12, 12));
        decimal_label->setFont(font2);
        decimal_label->setCursor(QCursor(Qt::OpenHandCursor));
        decimal_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(decimal_label);

        horizontalLayoutWidget_13 = new QWidget(centralWidget);
        horizontalLayoutWidget_13->setObjectName(QString::fromUtf8("horizontalLayoutWidget_13"));
        horizontalLayoutWidget_13->setGeometry(QRect(120, 170, 41, 20));
        horizontalLayout_14 = new QHBoxLayout(horizontalLayoutWidget_13);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_35 = new QLabel(horizontalLayoutWidget_13);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        sizePolicy.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy);
        label_35->setMinimumSize(QSize(12, 12));
        label_35->setMaximumSize(QSize(12, 12));
        label_35->setFont(font2);
        label_35->setFocusPolicy(Qt::NoFocus);
        label_35->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_35);

        horizontalSpacer_13 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        carry_label = new QLabel(horizontalLayoutWidget_13);
        carry_label->setObjectName(QString::fromUtf8("carry_label"));
        sizePolicy.setHeightForWidth(carry_label->sizePolicy().hasHeightForWidth());
        carry_label->setSizePolicy(sizePolicy);
        carry_label->setMinimumSize(QSize(12, 12));
        carry_label->setMaximumSize(QSize(12, 12));
        carry_label->setFont(font2);
        carry_label->setCursor(QCursor(Qt::OpenHandCursor));
        carry_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(carry_label);

        horizontalLayoutWidget_14 = new QWidget(centralWidget);
        horizontalLayoutWidget_14->setObjectName(QString::fromUtf8("horizontalLayoutWidget_14"));
        horizontalLayoutWidget_14->setGeometry(QRect(120, 150, 41, 20));
        horizontalLayout_15 = new QHBoxLayout(horizontalLayoutWidget_14);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        label_37 = new QLabel(horizontalLayoutWidget_14);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        sizePolicy.setHeightForWidth(label_37->sizePolicy().hasHeightForWidth());
        label_37->setSizePolicy(sizePolicy);
        label_37->setMinimumSize(QSize(12, 12));
        label_37->setMaximumSize(QSize(12, 12));
        label_37->setFont(font2);
        label_37->setFocusPolicy(Qt::NoFocus);
        label_37->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(label_37);

        horizontalSpacer_14 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        zero_label = new QLabel(horizontalLayoutWidget_14);
        zero_label->setObjectName(QString::fromUtf8("zero_label"));
        sizePolicy.setHeightForWidth(zero_label->sizePolicy().hasHeightForWidth());
        zero_label->setSizePolicy(sizePolicy);
        zero_label->setMinimumSize(QSize(12, 12));
        zero_label->setMaximumSize(QSize(12, 12));
        zero_label->setFont(font2);
        zero_label->setCursor(QCursor(Qt::OpenHandCursor));
        zero_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(zero_label);

        horizontalLayoutWidget_15 = new QWidget(centralWidget);
        horizontalLayoutWidget_15->setObjectName(QString::fromUtf8("horizontalLayoutWidget_15"));
        horizontalLayoutWidget_15->setGeometry(QRect(120, 70, 41, 20));
        horizontalLayout_16 = new QHBoxLayout(horizontalLayoutWidget_15);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        label_39 = new QLabel(horizontalLayoutWidget_15);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        sizePolicy.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy);
        label_39->setMinimumSize(QSize(12, 12));
        label_39->setMaximumSize(QSize(12, 12));
        label_39->setFont(font2);
        label_39->setFocusPolicy(Qt::NoFocus);
        label_39->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_39);

        horizontalSpacer_15 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);

        unused_label = new QLabel(horizontalLayoutWidget_15);
        unused_label->setObjectName(QString::fromUtf8("unused_label"));
        sizePolicy.setHeightForWidth(unused_label->sizePolicy().hasHeightForWidth());
        unused_label->setSizePolicy(sizePolicy);
        unused_label->setMinimumSize(QSize(12, 12));
        unused_label->setMaximumSize(QSize(12, 12));
        unused_label->setFont(font2);
        unused_label->setCursor(QCursor(Qt::OpenHandCursor));
        unused_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(unused_label);

        horizontalLayoutWidget_16 = new QWidget(centralWidget);
        horizontalLayoutWidget_16->setObjectName(QString::fromUtf8("horizontalLayoutWidget_16"));
        horizontalLayoutWidget_16->setGeometry(QRect(120, 130, 41, 20));
        horizontalLayout_17 = new QHBoxLayout(horizontalLayoutWidget_16);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        label_41 = new QLabel(horizontalLayoutWidget_16);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        sizePolicy.setHeightForWidth(label_41->sizePolicy().hasHeightForWidth());
        label_41->setSizePolicy(sizePolicy);
        label_41->setMinimumSize(QSize(12, 12));
        label_41->setMaximumSize(QSize(12, 12));
        label_41->setFont(font2);
        label_41->setFocusPolicy(Qt::NoFocus);
        label_41->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(label_41);

        horizontalSpacer_16 = new QSpacerItem(2, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_16);

        interrupt_label = new QLabel(horizontalLayoutWidget_16);
        interrupt_label->setObjectName(QString::fromUtf8("interrupt_label"));
        sizePolicy.setHeightForWidth(interrupt_label->sizePolicy().hasHeightForWidth());
        interrupt_label->setSizePolicy(sizePolicy);
        interrupt_label->setMinimumSize(QSize(12, 12));
        interrupt_label->setMaximumSize(QSize(12, 12));
        interrupt_label->setFont(font2);
        interrupt_label->setCursor(QCursor(Qt::OpenHandCursor));
        interrupt_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(interrupt_label);

        disasm_view = new QListView(centralWidget);
        disasm_view->setObjectName(QString::fromUtf8("disasm_view"));
        disasm_view->setGeometry(QRect(190, 10, 351, 461));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 330, 176, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 380, 106, 26));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 260, 31, 21));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Courier"));
        font3.setBold(false);
        font3.setWeight(50);
        font3.setKerning(true);
        label->setFont(font3);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        label->setTextInteractionFlags(Qt::NoTextInteraction);
        pc_edit = new QLineEdit(centralWidget);
        pc_edit->setObjectName(QString::fromUtf8("pc_edit"));
        pc_edit->setGeometry(QRect(70, 260, 60, 30));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pc_edit->sizePolicy().hasHeightForWidth());
        pc_edit->setSizePolicy(sizePolicy1);
        pc_edit->setMinimumSize(QSize(40, 20));
        pc_edit->setMaximumSize(QSize(60, 30));
        pc_edit->setSizeIncrement(QSize(1, 1));
        pc_edit->setBaseSize(QSize(30, 0));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Courier"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setUnderline(false);
        font4.setWeight(50);
        font4.setStrikeOut(false);
        font4.setKerning(true);
        pc_edit->setFont(font4);
        pc_edit->setMaxLength(4);
        pc_edit->setCursorPosition(1);
        pc_edit->setAlignment(Qt::AlignCenter);
        pc_edit->setDragEnabled(false);
        ac_edit = new QLineEdit(centralWidget);
        ac_edit->setObjectName(QString::fromUtf8("ac_edit"));
        ac_edit->setGeometry(QRect(51, 51, 30, 30));
        sizePolicy.setHeightForWidth(ac_edit->sizePolicy().hasHeightForWidth());
        ac_edit->setSizePolicy(sizePolicy);
        ac_edit->setMinimumSize(QSize(10, 10));
        ac_edit->setMaximumSize(QSize(30, 30));
        ac_edit->setSizeIncrement(QSize(1, 1));
        ac_edit->setBaseSize(QSize(30, 0));
        ac_edit->setFont(font4);
        ac_edit->setMaxLength(2);
        ac_edit->setCursorPosition(0);
        ac_edit->setAlignment(Qt::AlignCenter);
        ac_edit->setDragEnabled(false);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 60, 16, 20));
        label_2->setMinimumSize(QSize(11, 20));
        label_2->setMaximumSize(QSize(20, 20));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Monospace"));
        label_2->setFont(font5);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        x_edit = new QLineEdit(centralWidget);
        x_edit->setObjectName(QString::fromUtf8("x_edit"));
        x_edit->setGeometry(QRect(51, 81, 30, 30));
        sizePolicy.setHeightForWidth(x_edit->sizePolicy().hasHeightForWidth());
        x_edit->setSizePolicy(sizePolicy);
        x_edit->setMinimumSize(QSize(10, 10));
        x_edit->setMaximumSize(QSize(30, 30));
        x_edit->setSizeIncrement(QSize(1, 1));
        x_edit->setBaseSize(QSize(30, 0));
        x_edit->setFont(font4);
        x_edit->setMaxLength(2);
        x_edit->setCursorPosition(0);
        x_edit->setAlignment(Qt::AlignCenter);
        x_edit->setDragEnabled(false);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 90, 16, 20));
        label_7->setMinimumSize(QSize(11, 20));
        label_7->setMaximumSize(QSize(20, 20));
        label_7->setFont(font5);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 120, 16, 20));
        label_8->setMinimumSize(QSize(11, 20));
        label_8->setMaximumSize(QSize(20, 20));
        label_8->setFont(font5);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        y_edit = new QLineEdit(centralWidget);
        y_edit->setObjectName(QString::fromUtf8("y_edit"));
        y_edit->setGeometry(QRect(51, 111, 30, 30));
        sizePolicy.setHeightForWidth(y_edit->sizePolicy().hasHeightForWidth());
        y_edit->setSizePolicy(sizePolicy);
        y_edit->setMinimumSize(QSize(10, 10));
        y_edit->setMaximumSize(QSize(30, 30));
        y_edit->setSizeIncrement(QSize(1, 1));
        y_edit->setBaseSize(QSize(30, 0));
        y_edit->setFont(font4);
        y_edit->setMaxLength(2);
        y_edit->setCursorPosition(0);
        y_edit->setAlignment(Qt::AlignCenter);
        y_edit->setDragEnabled(false);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 150, 16, 20));
        label_9->setMinimumSize(QSize(11, 20));
        label_9->setMaximumSize(QSize(20, 20));
        label_9->setFont(font5);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sp_edit = new QLineEdit(centralWidget);
        sp_edit->setObjectName(QString::fromUtf8("sp_edit"));
        sp_edit->setGeometry(QRect(51, 141, 30, 30));
        sizePolicy.setHeightForWidth(sp_edit->sizePolicy().hasHeightForWidth());
        sp_edit->setSizePolicy(sizePolicy);
        sp_edit->setMinimumSize(QSize(10, 10));
        sp_edit->setMaximumSize(QSize(30, 30));
        sp_edit->setSizeIncrement(QSize(1, 1));
        sp_edit->setBaseSize(QSize(30, 0));
        sp_edit->setFont(font4);
        sp_edit->setMaxLength(2);
        sp_edit->setCursorPosition(0);
        sp_edit->setAlignment(Qt::AlignCenter);
        sp_edit->setDragEnabled(false);
        flags_edit = new QLineEdit(centralWidget);
        flags_edit->setObjectName(QString::fromUtf8("flags_edit"));
        flags_edit->setGeometry(QRect(51, 171, 30, 30));
        sizePolicy.setHeightForWidth(flags_edit->sizePolicy().hasHeightForWidth());
        flags_edit->setSizePolicy(sizePolicy);
        flags_edit->setMinimumSize(QSize(10, 10));
        flags_edit->setMaximumSize(QSize(30, 30));
        flags_edit->setSizeIncrement(QSize(1, 1));
        flags_edit->setBaseSize(QSize(30, 0));
        flags_edit->setFont(font4);
        flags_edit->setMaxLength(2);
        flags_edit->setCursorPosition(0);
        flags_edit->setAlignment(Qt::AlignCenter);
        flags_edit->setDragEnabled(false);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(30, 180, 16, 20));
        label_17->setMinimumSize(QSize(11, 20));
        label_17->setMaximumSize(QSize(20, 20));
        label_17->setFont(font5);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CPU_2A03_Inspector->setCentralWidget(centralWidget);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(pc_edit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(pc_edit, ac_edit);
        QWidget::setTabOrder(ac_edit, x_edit);
        QWidget::setTabOrder(x_edit, y_edit);
        QWidget::setTabOrder(y_edit, sp_edit);
        QWidget::setTabOrder(sp_edit, flags_edit);
        QWidget::setTabOrder(flags_edit, label_6);
        QWidget::setTabOrder(label_6, label_18);
        QWidget::setTabOrder(label_18, label_39);
        QWidget::setTabOrder(label_39, label_20);
        QWidget::setTabOrder(label_20, label_22);
        QWidget::setTabOrder(label_22, label_41);
        QWidget::setTabOrder(label_41, label_37);
        QWidget::setTabOrder(label_37, label_35);

        retranslateUi(CPU_2A03_Inspector);
        QObject::connect(pc_edit, SIGNAL(editingFinished()), CPU_2A03_Inspector, SLOT(pc_changed()));
        QObject::connect(ac_edit, SIGNAL(editingFinished()), CPU_2A03_Inspector, SLOT(ac_changed()));
        QObject::connect(x_edit, SIGNAL(editingFinished()), CPU_2A03_Inspector, SLOT(x_changed()));
        QObject::connect(y_edit, SIGNAL(editingFinished()), CPU_2A03_Inspector, SLOT(y_changed()));
        QObject::connect(sp_edit, SIGNAL(editingFinished()), CPU_2A03_Inspector, SLOT(sp_changed()));
        QObject::connect(flags_edit, SIGNAL(editingFinished()), CPU_2A03_Inspector, SLOT(flags_changed()));
        QObject::connect(pushButton, SIGNAL(pressed()), CPU_2A03_Inspector, SLOT(next_instruction()));
        QObject::connect(pushButton_2, SIGNAL(pressed()), CPU_2A03_Inspector, SLOT(run()));

        QMetaObject::connectSlotsByName(CPU_2A03_Inspector);
    } // setupUi

    void retranslateUi(QMainWindow *CPU_2A03_Inspector)
    {
        CPU_2A03_Inspector->setWindowTitle(QApplication::translate("CPU_2A03_Inspector", "6502", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_6->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Negative</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_6->setText(QApplication::translate("CPU_2A03_Inspector", "N", 0, QApplication::UnicodeUTF8));
        negative_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_18->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">oVerflow</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_18->setText(QApplication::translate("CPU_2A03_Inspector", "V", 0, QApplication::UnicodeUTF8));
        overflow_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_20->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Break</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_20->setText(QApplication::translate("CPU_2A03_Inspector", "B", 0, QApplication::UnicodeUTF8));
        break_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_22->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Decimal</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("CPU_2A03_Inspector", "D", 0, QApplication::UnicodeUTF8));
        decimal_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_35->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Carry</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_35->setText(QApplication::translate("CPU_2A03_Inspector", "C", 0, QApplication::UnicodeUTF8));
        carry_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_37->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Zero</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_37->setText(QApplication::translate("CPU_2A03_Inspector", "Z", 0, QApplication::UnicodeUTF8));
        zero_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_39->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Unused</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_39->setText(QApplication::translate("CPU_2A03_Inspector", "U", 0, QApplication::UnicodeUTF8));
        unused_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_41->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Interrupt</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_41->setText(QApplication::translate("CPU_2A03_Inspector", "I", 0, QApplication::UnicodeUTF8));
        interrupt_label->setText(QApplication::translate("CPU_2A03_Inspector", "0", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CPU_2A03_Inspector", "Next Instruction", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("CPU_2A03_Inspector", "Run", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Program Counter</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("CPU_2A03_Inspector", "PC", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pc_edit->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Program Counter</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pc_edit->setInputMask(QApplication::translate("CPU_2A03_Inspector", "HHHH; ", 0, QApplication::UnicodeUTF8));
        pc_edit->setText(QApplication::translate("CPU_2A03_Inspector", "0000", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ac_edit->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Accumulator</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ac_edit->setInputMask(QApplication::translate("CPU_2A03_Inspector", "HH; ", 0, QApplication::UnicodeUTF8));
        ac_edit->setText(QApplication::translate("CPU_2A03_Inspector", "00", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Accumulator</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("CPU_2A03_Inspector", "A", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        x_edit->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">X Register</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        x_edit->setInputMask(QApplication::translate("CPU_2A03_Inspector", "HH; ", 0, QApplication::UnicodeUTF8));
        x_edit->setText(QApplication::translate("CPU_2A03_Inspector", "00", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">X Register</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("CPU_2A03_Inspector", "X", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_8->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Y Register</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("CPU_2A03_Inspector", "Y", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        y_edit->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Y Register</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        y_edit->setInputMask(QApplication::translate("CPU_2A03_Inspector", "HH; ", 0, QApplication::UnicodeUTF8));
        y_edit->setText(QApplication::translate("CPU_2A03_Inspector", "00", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_9->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Stack Pointer</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("CPU_2A03_Inspector", "S", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sp_edit->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Stack Pointer</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sp_edit->setInputMask(QApplication::translate("CPU_2A03_Inspector", "HH; ", 0, QApplication::UnicodeUTF8));
        sp_edit->setText(QApplication::translate("CPU_2A03_Inspector", "00", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        flags_edit->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Processor Status</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        flags_edit->setInputMask(QApplication::translate("CPU_2A03_Inspector", "HH; ", 0, QApplication::UnicodeUTF8));
        flags_edit->setText(QApplication::translate("CPU_2A03_Inspector", "00", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_17->setToolTip(QApplication::translate("CPU_2A03_Inspector", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Fixedsys'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Processor Status</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_17->setText(QApplication::translate("CPU_2A03_Inspector", "P", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CPU_2A03_Inspector: public Ui_CPU_2A03_Inspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPU_2A03_INSPECTOR_H
