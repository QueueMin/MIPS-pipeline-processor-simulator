#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Simulator.cpp"

Simulator* sim = new Simulator();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionBinary, &QAction::triggered, this, &MainWindow::regToBin);
    connect(ui->actionDecimal, &QAction::triggered, this, &MainWindow::regToDec);
    connect(ui->actionHex, &QAction::triggered, this, &MainWindow::regToHex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// select file and load for simulator
void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
//    this->sim->fileLoad(fileName.toStdString());
    sim->fileLoad(fileName.toStdString());

    ui->instructionTable->clearContents();


    int sPC = binToDec(sim->MManager.getStartPC());
    for (int i = 0; i <= sim->MManager.getFileLength(); i++){
        QTableWidgetItem* pc = new QTableWidgetItem;
        QTableWidgetItem* inst = new QTableWidgetItem;

        pc->setText(QString::fromStdString(decToHex(sPC+4*i)));
        inst->setText(QString::fromStdString(binToHex(sim->MManager.getProgram(decToHex(sPC+4*i)))));

        ui->instructionTable->setItem(i, 0, pc);
        ui->instructionTable->setItem(i, 1, inst);
    }

    refreshRegTable(16);
}

void MainWindow::refreshRegTable(int code){
    QTableWidgetItem* reg = new QTableWidgetItem;
    if (code == 2){
        QString tmp = "";
        for (int i = 0; i < 4; i++){
            tmp += QString::fromStdString((sim->PC).to_string().substr(i*4, 4));
            tmp += " ";
        }
        tmp+="\n";
        for (int i = 4; i < 8; i++){
            tmp += QString::fromStdString((sim->PC).to_string().substr(i*4, 4));
            tmp += " ";
        }

        reg->setText(tmp);

    }else if (code == 10){
        reg->setText(QString::fromStdString(std::to_string(binToDec(sim->PC))));
    }else if (code == 16){
        reg->setText(QString::fromStdString(binToHex(sim->PC)));
    }else{
        delete(reg);
        return;
    }
    ui->regTable->setItem(0, 0, reg);


    for (int i = 1; i <= 32; i++){
        reg = new QTableWidgetItem;

        if (code == 2){
            QString tmp = "";
            for (int j = 0; j < 4; j++){
                tmp += QString::fromStdString((sim->Regi[i]).to_string().substr(j*4, 4));
                tmp += " ";
            }
            tmp+="\n";
            for (int j = 4; j < 8; j++){
                tmp += QString::fromStdString((sim->Regi[i]).to_string().substr(j*4, 4));
                tmp += " ";
            }
            reg->setText(tmp);
        }else if (code == 10){
            reg->setText(QString::fromStdString(std::to_string(binToDec(sim->Regi[i]))));
        }else if (code == 16){
            reg->setText(QString::fromStdString(binToHex(sim->Regi[i])));
        }else{
            break;
        }
        ui->regTable->setItem(i, 0, reg);
    }
}

void MainWindow::regToBin(){
    this->encodeTo = 2;
    refreshRegTable(this->encodeTo);
}

void MainWindow::regToDec(){
    this->encodeTo = 10;
    refreshRegTable(this->encodeTo);
}

void MainWindow::regToHex(){
    this->encodeTo = 16;
    refreshRegTable(this->encodeTo);
}

