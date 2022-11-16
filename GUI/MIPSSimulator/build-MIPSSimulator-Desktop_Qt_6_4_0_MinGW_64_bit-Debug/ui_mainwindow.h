/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_instruction_file;
    QWidget *mainWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QHBoxLayout *materials;
    QTabWidget *statBar;
    QWidget *instTab;
    QGridLayout *gridLayout_2;
    QTableWidget *instructionTable;
    QWidget *regTab;
    QGridLayout *gridLayout_3;
    QTextEdit *textEdit;
    QWidget *tab_3;
    QGraphicsView *graphicMIPS;
    QMenuBar *menubar;
    QMenu *menuMIPS_Pipeline_Simulator;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1440, 960);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1440, 960));
        actionLoad_instruction_file = new QAction(MainWindow);
        actionLoad_instruction_file->setObjectName("actionLoad_instruction_file");
        mainWidget = new QWidget(MainWindow);
        mainWidget->setObjectName("mainWidget");
        sizePolicy.setHeightForWidth(mainWidget->sizePolicy().hasHeightForWidth());
        mainWidget->setSizePolicy(sizePolicy);
        mainWidget->setMinimumSize(QSize(1440, 917));
        mainWidget->setMaximumSize(QSize(100000, 100000));
        verticalLayout = new QVBoxLayout(mainWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButton = new QPushButton(mainWidget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(30, 30));
        pushButton->setMaximumSize(QSize(30, 30));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("folder-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton->setIcon(icon);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        pushButton_2 = new QPushButton(mainWidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(30, 30));
        pushButton_2->setMaximumSize(QSize(30, 30));
        pushButton_2->setIcon(icon);

        gridLayout->addWidget(pushButton_2, 0, 2, 1, 1);

        pushButton_3 = new QPushButton(mainWidget);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(30, 30));
        pushButton_3->setMaximumSize(QSize(30, 30));
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("application-exit")));
        pushButton_3->setIcon(icon1);

        gridLayout->addWidget(pushButton_3, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        materials = new QHBoxLayout();
        materials->setObjectName("materials");
        materials->setSizeConstraint(QLayout::SetNoConstraint);
        statBar = new QTabWidget(mainWidget);
        statBar->setObjectName("statBar");
        statBar->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(statBar->sizePolicy().hasHeightForWidth());
        statBar->setSizePolicy(sizePolicy2);
        statBar->setMaximumSize(QSize(280, 16777215));
        statBar->setTabPosition(QTabWidget::North);
        statBar->setTabShape(QTabWidget::Rounded);
        statBar->setElideMode(Qt::ElideMiddle);
        statBar->setUsesScrollButtons(false);
        statBar->setDocumentMode(false);
        instTab = new QWidget();
        instTab->setObjectName("instTab");
        instTab->setMaximumSize(QSize(280, 16777215));
        instTab->setLayoutDirection(Qt::LeftToRight);
        gridLayout_2 = new QGridLayout(instTab);
        gridLayout_2->setObjectName("gridLayout_2");
        instructionTable = new QTableWidget(instTab);
        if (instructionTable->columnCount() < 2)
            instructionTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        instructionTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        instructionTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (instructionTable->rowCount() < 40)
            instructionTable->setRowCount(40);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        instructionTable->setVerticalHeaderItem(0, __qtablewidgetitem2);
        instructionTable->setObjectName("instructionTable");
        sizePolicy.setHeightForWidth(instructionTable->sizePolicy().hasHeightForWidth());
        instructionTable->setSizePolicy(sizePolicy);
        instructionTable->setContextMenuPolicy(Qt::NoContextMenu);
        instructionTable->setFrameShadow(QFrame::Sunken);
        instructionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        instructionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        instructionTable->setTextElideMode(Qt::ElideNone);
        instructionTable->setShowGrid(true);
        instructionTable->setGridStyle(Qt::SolidLine);
        instructionTable->setSortingEnabled(false);
        instructionTable->setWordWrap(false);
        instructionTable->setCornerButtonEnabled(false);
        instructionTable->setRowCount(40);
        instructionTable->horizontalHeader()->setVisible(true);
        instructionTable->horizontalHeader()->setMinimumSectionSize(118);
        instructionTable->horizontalHeader()->setDefaultSectionSize(118);
        instructionTable->horizontalHeader()->setHighlightSections(true);
        instructionTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        instructionTable->horizontalHeader()->setStretchLastSection(false);
        instructionTable->verticalHeader()->setVisible(false);
        instructionTable->verticalHeader()->setMinimumSectionSize(25);
        instructionTable->verticalHeader()->setDefaultSectionSize(25);
        instructionTable->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(instructionTable, 0, 0, 1, 1);

        statBar->addTab(instTab, QString());
        regTab = new QWidget();
        regTab->setObjectName("regTab");
        gridLayout_3 = new QGridLayout(regTab);
        gridLayout_3->setObjectName("gridLayout_3");
        textEdit = new QTextEdit(regTab);
        textEdit->setObjectName("textEdit");

        gridLayout_3->addWidget(textEdit, 0, 0, 1, 1);

        statBar->addTab(regTab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        statBar->addTab(tab_3, QString());

        materials->addWidget(statBar);

        graphicMIPS = new QGraphicsView(mainWidget);
        graphicMIPS->setObjectName("graphicMIPS");
        graphicMIPS->setDragMode(QGraphicsView::NoDrag);

        materials->addWidget(graphicMIPS);


        verticalLayout->addLayout(materials);

        MainWindow->setCentralWidget(mainWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1440, 21));
        menuMIPS_Pipeline_Simulator = new QMenu(menubar);
        menuMIPS_Pipeline_Simulator->setObjectName("menuMIPS_Pipeline_Simulator");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(statBar, graphicMIPS);
        QWidget::setTabOrder(graphicMIPS, instructionTable);

        menubar->addAction(menuMIPS_Pipeline_Simulator->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(pushButton_3, SIGNAL(clicked(bool)), MainWindow, SLOT(toTest()));

        statBar->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad_instruction_file->setText(QCoreApplication::translate("MainWindow", "Load instruction file...", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = instructionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "PC", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = instructionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Insturctions(Hex)", nullptr));
        statBar->setTabText(statBar->indexOf(instTab), QCoreApplication::translate("MainWindow", "Instructions", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"</style></head><body style=\" font-family:'\353\247\221\354\235\200 \352\263\240\353\224\225'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">PC\302\240\302\240\302\240\302\240\302\240\302\240</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Co"
                        "urier'; font-size:10pt; color:#000000;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">HI\302\240\302\240\302\240\302\240\302\240\302\240</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">LO\302\240\302\240\302\240\302\240\302\240\302\240</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R0\302\240\302\240[r0]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302"
                        "\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R1\302\240\302\240[at]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R2\302\240\302\240[v0]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R3\302\240\302\240[v1]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R4\302\240\302\240[a0]</span><span style=\" font-family:'Courier'; font-size:10p"
                        "t; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R5\302\240\302\240[a1]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R6\302\240\302\240[a2]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R7\302\240\302\240[a3]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R8\302\240\302\240[t0"
                        "]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R9\302\240\302\240[t1]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R10\302\240[t2]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R11\302\240[t3]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; back"
                        "ground-color:#ffffff;\">R12\302\240[t4]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R13\302\240[t5]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R14\302\240[t6]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R15\302\240[t7]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-"
                        "weight:600; color:#000000; background-color:#ffffff;\">R16\302\240[s0]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R17\302\240[s1]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R18\302\240[s2]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R19\302\240[s3]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'"
                        "Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R20\302\240[s4]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R21\302\240[s5]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R22\302\240[s6]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R23\302\240[s7]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></sp"
                        "an><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R24\302\240[t8]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R25\302\240[t9]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R26\302\240[k0]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R27\302\240[k1]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;"
                        "\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R28\302\240[gp]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\24010008000<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R29\302\240[sp]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2407ffffe40<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R30\302\240[s8]</span><span style=\" font-family:'Courier'; font-size:10pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400<br /></span><span style=\" font-family:'Courier'; font-size:10pt; font-weight:600; color:#000000; background-color:#ffffff;\">R31\302\240[ra]</span><span style=\" font-family:'Courier'; font-size:1"
                        "0pt; color:#000000; background-color:#ffffff;\">\302\240=\302\2400</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        statBar->setTabText(statBar->indexOf(regTab), QCoreApplication::translate("MainWindow", "Registers", nullptr));
        statBar->setTabText(statBar->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Page", nullptr));
        menuMIPS_Pipeline_Simulator->setTitle(QCoreApplication::translate("MainWindow", "MIPS Pipeline Simulator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
