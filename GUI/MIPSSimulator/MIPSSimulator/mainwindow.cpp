#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileEncode.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    encode(fileName.toStdString());
    ui->instructionTable->clearContents();


    for (int i = 0; i < 100; i++){
        QTableWidgetItem* pc = new QTableWidgetItem;
        QTableWidgetItem* inst = new QTableWidgetItem;
        pc->setText(QString::fromStdString(binToHex(startPC)));
        inst->setText(QString::fromStdString(binToHex(program[i])));

        ui->instructionTable->setItem(i, 0, pc);
        ui->instructionTable->setItem(i, 1, inst);

        startPC = (binToDec(startPC)+4);
    }


}

