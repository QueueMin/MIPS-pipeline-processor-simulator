#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsscene.h"
#include "qpainter.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsItem>
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

    QFont font_K;
    QFont font_B;
    QFont font_Y;
    QFont font_R;

    QBrush brushK;
    QBrush brushB;
    QBrush brushY;
    QBrush brushR;

private slots:

    void on_openButton_clicked();
    void on_cycleButton_clicked();

    void regToBin();
    void regToDec();
    void regToHex();

    void refreshRegTable(int code);
    void refreshMemTable(int code);

    void memToBin();
    void memToDec();
    void memToHex();

    void resetImg();
    void refreshImgInfo();


    QGraphicsTextItem* addText(QString s, int x = 0, int y = 0, QString color = "K");

private:
    void fontK(QGraphicsTextItem*);
    void fontB(QGraphicsTextItem*);
    void fontY(QGraphicsTextItem*);
    void fontR(QGraphicsTextItem*);

    int RegEncodeTo = 16;
    int MEMEncodeTo = 16;
    Ui::MainWindow *ui;

    QGraphicsScene circuitScene;
    QGraphicsItemGroup sceneTexts;


};
#endif // MAINWINDOW_H
