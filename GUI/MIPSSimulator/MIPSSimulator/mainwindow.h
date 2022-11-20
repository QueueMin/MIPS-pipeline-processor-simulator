#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
//#include "Simulator.cpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_openButton_clicked();

    void regToBin();
    void regToDec();
    void regToHex();
    void refreshRegTable(int code);

private:
    int encodeTo = 16;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
