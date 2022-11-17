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
    QTableWidgetItem* s = new QTableWidgetItem;
    s->setText("SEX");
    s->text();
    ui->instructionTable->clearContents();
    ui->instructionTable->setItem(0, 0, s);

}

