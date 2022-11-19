#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->sim = new Simulator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// select file and load for simulator
void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    this->sim->fileLoad(fileName.toStdString());

    ui->instructionTable->clearContents();


    int sPC = binToDec(sim->MManager.getStartPC());
    for (int i = 0; i < sim->MManager.getFileLength(); i++){
        QTableWidgetItem* pc = new QTableWidgetItem;
        QTableWidgetItem* inst = new QTableWidgetItem;

        pc->setText(QString::fromStdString(decToHex(sPC+4*i)));
        inst->setText(QString::fromStdString(binToHex(sim->MManager.getProgram(decToHex(sPC)))));


        ui->instructionTable->setItem(i, 0, pc);
        ui->instructionTable->setItem(i, 1, inst);

    }


}

