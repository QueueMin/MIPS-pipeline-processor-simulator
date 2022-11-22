#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Simulator.cpp"

#include <QDebug>

Simulator* sim = new Simulator();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionBinary, &QAction::triggered, this, &MainWindow::regToBin);
    connect(ui->actionDecimal, &QAction::triggered, this, &MainWindow::regToDec);
    connect(ui->actionHex, &QAction::triggered, this, &MainWindow::regToHex);

    ui->loadedCiruit->hide();
    resetImg();



    this->font_K = QFont("Consolas",14,900);
    this->brushK = QColor(0, 0, 0, 255);
    paintK.setBrush(brushK);


    this->font_B = QFont("Consolas",14,900);
    this->brushB = QColor(0, 100, 255, 255);
    paintB.setBrush(brushK);

    this->font_Y = QFont("Consolas",14,900);
    this->brushY = QColor(225, 200, 0, 255);
    paintY.setBrush(brushY);

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

void MainWindow::resetImg(){
    QPixmap item = ui->loadedCiruit->pixmap();
//    QGraphicsPixmapItem *a = circuitScene.addPixmap(item);
    circuitScene.addPixmap(item);
    ui->circuitView->setScene(&circuitScene);

//    a->setOffset(0,0);
//    circuitScene.addText();
}

std::string rbool(bool a){
    return a?"1":"0";
}

void MainWindow::refreshImgInfo(){
    circuitScene.clear();
    resetImg();

    // MEM/WB Register

    // EX/MEM Register

    // ID/EX Register
    QString RegDst = QString::fromStdString(rbool(sim->IDEX.RegDst));
    QString MemRead = QString::fromStdString(rbool(sim->IDEX.MemRead));
    QString MemtoReg = QString::fromStdString(rbool(sim->IDEX.MemtoReg));
    QString ALUOp1 = QString::fromStdString(rbool(sim->IDEX.ALUOp1));
    QString ALUOp0 = QString::fromStdString(rbool(sim->IDEX.ALUOp0));
    QString MemWrite = QString::fromStdString(rbool(sim->IDEX.MemWrite));
    QString ALUSrc = QString::fromStdString(rbool(sim->IDEX.ALUSrc));
    QString RegWrite = QString::fromStdString(rbool(sim->IDEX.RegWrite));

    QGraphicsTextItem* gRegWrite = this->circuitScene.addText(RegWrite);
    fontY(gRegWrite);
    gRegWrite->setPos(580, 20);

//    gRegWrite->setPos(580, 20);



    QString Data1 = QString::fromStdString(binToHex(sim->IDEX.Data1));
    QString Data2 = QString::fromStdString(binToHex(sim->IDEX.Data2));
    QGraphicsTextItem* gData1 = this->circuitScene.addText(Data1);
    fontY(gData1);
    gData1->setPos(580, 322);
    QGraphicsTextItem* gData2 = this->circuitScene.addText(Data2);
    fontY(gData2);
    gData2->setPos(580, 420);


    QString Extend = QString::fromStdString(binToHex(sim->IDEX.Extend));
    QString Function = QString::fromStdString(sim->IDEX.Function.to_string());
    QString Rs = QString::fromStdString(sim->IDEX.Rs.to_string());
    QString Rt = QString::fromStdString(sim->IDEX.Rt.to_string());
    QString Rd = QString::fromStdString(sim->IDEX.Rd.to_string());

    QGraphicsTextItem* gExtend = this->circuitScene.addText(Extend);
    fontY(gExtend);
    gExtend->setPos(580, 513);
    QGraphicsTextItem* gFunction = this->circuitScene.addText(Function);
    fontY(gFunction);
    gFunction->setPos(596, 563);
    QGraphicsTextItem* gRs = this->circuitScene.addText(Rs);
    fontY(gRs);
    gRs->setPos(600, 583);
    QGraphicsTextItem* gRt = this->circuitScene.addText(Rt);
    fontY(gRt);
    gRt->setPos(600, 603);
    QGraphicsTextItem* gRd = this->circuitScene.addText(Rd);
    fontY(gRd);
    gRd->setPos(600, 623);


    // IF/ID Register
    QString PC = QString::fromStdString(binToHex(sim->IFID.PC));
    QString Inst = QString::fromStdString(binToHex(sim->IFID.Inst));

    QGraphicsTextItem* gPC = this->circuitScene.addText(PC);
    gPC->setPos(200, 300);
    fontB(gPC);

    QGraphicsTextItem* gInst = this->circuitScene.addText(Inst);
    gInst->setPos(200, 540);
    fontB(gInst);
//    addText(Inst, 200, 540, "B");

    // After all
    this->update();
}

void MainWindow::fontK(QGraphicsTextItem* ptr){
    ptr->setFont(font_K);
    ptr->setDefaultTextColor(brushK.color());
}
void MainWindow::fontB(QGraphicsTextItem* ptr){
    ptr->setFont(font_B);
    ptr->setDefaultTextColor(brushB.color());
}

void MainWindow::fontY(QGraphicsTextItem* ptr){
    ptr->setFont(font_Y);
    ptr->setDefaultTextColor(brushY.color());
}

void MainWindow::on_pushButton_clicked()
{
    refreshImgInfo();
}

void MainWindow::on_cycleButton_clicked()
{
    sim->runSingleCycle();
    refreshImgInfo();
}

QGraphicsTextItem* MainWindow::addText(QString s, int x, int y, QString color){
    QGraphicsTextItem* g = this->circuitScene.addText(s);
    this->sceneTexts.addToGroup(g);

    if (color == "K"){
        fontK(g);
    }else if (color == "Y"){
        fontY(g);
    }else if (color == "B"){
        fontB(g);
    }

    g->setPos(x, y);
    return g;
}
