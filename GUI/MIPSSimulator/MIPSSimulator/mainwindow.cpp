#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test.cpp"

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

void MainWindow::loadFile(){

}

void MainWindow::toTest(){
    ui->pushButton_3->setText("YEE");
    ui->pushButton_3->setVisible(0);
}
