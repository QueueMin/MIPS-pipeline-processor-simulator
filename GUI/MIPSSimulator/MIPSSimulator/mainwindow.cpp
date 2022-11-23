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

    this->setWindowTitle("MIPS Pipeline Simulator - by queue_min and parkjs82");

    connect(ui->actionBinary, &QAction::triggered, this, &MainWindow::regToBin);
    connect(ui->actionDecimal, &QAction::triggered, this, &MainWindow::regToDec);
    connect(ui->actionHex, &QAction::triggered, this, &MainWindow::regToHex);

    connect(ui->actionValuetoBin, &QAction::triggered, this, &MainWindow::memToBin);
    connect(ui->actionValuetoDecimal, &QAction::triggered, this, &MainWindow::memToDec);
    connect(ui->actionValuetoHex, &QAction::triggered, this, &MainWindow::memToHex);

    ui->loadedCiruit->hide();

    this->font_K = QFont("Consolas",14,900);
    this->brushK = QColor(0, 0, 0, 255);
    paintK.setBrush(brushK);


    this->font_B = QFont("Consolas",14,900);
    this->brushB = QColor(0, 100, 255, 255);
    paintB.setBrush(brushK);

    this->font_Y = QFont("Consolas",14,900);
    this->brushY = QColor(225, 200, 0, 255);
    paintY.setBrush(brushY);

    refreshImgInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// select file and load for simulator
void MainWindow::on_openButton_clicked()
{
    delete(sim);
    sim = new Simulator();
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

    refreshImgInfo();
    refreshRegTable(this->RegEncodeTo);
    refreshMemTable(this->MEMEncodeTo);
}

void MainWindow::memToBin(){
    this->MEMEncodeTo = 2;
    refreshMemTable(this->MEMEncodeTo);
}
void MainWindow::memToDec(){
    this->MEMEncodeTo = 10;
    refreshMemTable(this->MEMEncodeTo);
}
void MainWindow::memToHex(){
    this->MEMEncodeTo = 16;
    refreshMemTable(this->MEMEncodeTo);
}

void MainWindow::refreshMemTable(int code){
    ui->MemoryTable->clearContents();

    int idx = 0;

    for (auto item = sim->MManager.getWords()->begin(); item != sim->MManager.getWords()->end(); item++){
        QTableWidgetItem* address = new QTableWidgetItem;
        QTableWidgetItem* data = new QTableWidgetItem;

        address->setText(QString::fromStdString(item->first));
        if (code == 2){
            QString tmp = "";
            for (int j = 0; j < 4; j++){
                tmp += QString::fromStdString(std::bitset<32>(item->second).to_string().substr(j*4, 4));
                tmp += " ";
            }
            tmp+="\n";
            for (int j = 4; j < 8; j++){
                tmp += QString::fromStdString(std::bitset<32>(item->second).to_string().substr(j*4, 4));
                tmp += " ";
            }
            data->setText(tmp);
        }else if (code == 10){
            data->setText(QString::fromStdString(std::to_string(item->second)));
        }else if (code == 16){
            data->setText(QString::fromStdString(decToHex(item->second)));
        }
        ui->MemoryTable->setItem(idx, 0, address);
        ui->MemoryTable->setItem(idx, 1, data);

        idx++;
        std::cout << idx << " " << item->first << "\n";
    }
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


    for (int i = 0; i < 32; i++){
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
        ui->regTable->setItem(i+1, 0, reg);
    }
}

void MainWindow::regToBin(){
    this->RegEncodeTo = 2;
    refreshRegTable(this->RegEncodeTo);
}

void MainWindow::regToDec(){
    this->RegEncodeTo = 10;
    refreshRegTable(this->RegEncodeTo);
}

void MainWindow::regToHex(){
    this->RegEncodeTo = 16;
    refreshRegTable(this->RegEncodeTo);
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

    QString Cycle = QString::fromStdString(std::to_string(sim->cycle));
    QGraphicsTextItem* gCycle = this->circuitScene.addText("Cycle Count= "+Cycle);
    fontK(gCycle);
    gCycle->setScale(2);
    gCycle->setPos(20, 720);
    // MEM/WB Register

    QString MMemtoReg = QString::fromStdString(rbool(sim->MEMWB.MemtoReg));
    QGraphicsTextItem* gMMemtoReg = this->circuitScene.addText("= "+MMemtoReg);
    fontB(gMMemtoReg);
    gMMemtoReg->setPos(1346, 234);

    QString MRegWrite = QString::fromStdString(rbool(sim->MEMWB.RegWrite));
    QGraphicsTextItem* gMRegWrite = this->circuitScene.addText("RegWrite= "+MRegWrite);
    fontB(gMRegWrite);
    gMRegWrite->setPos(1266, 216);

    QString MRd = QString::fromStdString(sim->MEMWB.Rd.to_string());
    QGraphicsTextItem* gMRd = this->circuitScene.addText(MRd);
    fontB(gMRd);
    gMRd->setPos(1196, 616);

    QString Address = QString::fromStdString(binToHex(sim->MEMWB.Address));
    QGraphicsTextItem* gAddress = this->circuitScene.addText(Address);
    fontB(gAddress);
    gAddress->setPos(1144, 474);

    QString MemData = QString::fromStdString(binToHex(sim->MEMWB.Data));
    QGraphicsTextItem* gMemData = this->circuitScene.addText(MemData);
    fontB(gMemData);
    gMemData->setPos(1188, 384);

    // EX/MEM Register

    QString ForwardA = QString::fromStdString(std::bitset<2>(sim->ForwardUnit.getForwardA()).to_string());
    QGraphicsTextItem* gForwardA = this->circuitScene.addText(ForwardA);
    fontY(gForwardA);
    gForwardA->setPos(820, 324);

    QString ForwardB = QString::fromStdString(std::bitset<2>(sim->ForwardUnit.getForwardB()).to_string());
    QGraphicsTextItem* gForwardB = this->circuitScene.addText(ForwardB);
    fontY(gForwardB);
    gForwardB->setPos(820, 400);

    QString ExData = QString::fromStdString(binToHex(sim->EXMEM.Data2));
    QGraphicsTextItem* gExData = this->circuitScene.addText(ExData);
    fontB(gExData);
    gExData->setPos(980, 420);
    QGraphicsTextItem* gExData2 = this->circuitScene.addText(ExData);
    fontB(gExData2);
    gExData2->setPos(1096, 76);

    QString ALUResult = QString::fromStdString(binToHex(sim->EXMEM.ALUResult));
    QGraphicsTextItem* gALUResult = this->circuitScene.addText(ALUResult);
    fontB(gALUResult);
    gALUResult->setPos(980, 392);

    QString ERd = QString::fromStdString(sim->EXMEM.Rd.to_string());
    QGraphicsTextItem* gERd = this->circuitScene.addText(ERd);
    fontB(gERd);
    gERd->setPos(996, 616);
    QGraphicsTextItem* gERd2 = this->circuitScene.addText("= "+ERd);
    fontB(gERd2);
    gERd2->setPos(960, 76);


    QString EXMemtoReg = QString::fromStdString(rbool(sim->EXMEM.MemtoReg));
    QGraphicsTextItem* gEXMemtoReg = this->circuitScene.addText("MemToReg=" + EXMemtoReg);
    fontB(gEXMemtoReg);
    gEXMemtoReg->setPos(1090, 190);

    QString EXRegWrite = QString::fromStdString(rbool(sim->EXMEM.RegWrite));
    QGraphicsTextItem* gEXRegWrite = this->circuitScene.addText("="+EXRegWrite);
    fontB(gEXRegWrite);
    gEXRegWrite->setPos(1076, 302);

    QString EXMemWrite = QString::fromStdString(rbool(sim->EXMEM.MemWrite));
    QGraphicsTextItem* gEXMemWrite = this->circuitScene.addText(EXMemWrite);
    fontB(gEXMemWrite);
    gEXMemWrite->setPos(1164, 282);

    QString EXMemRead = QString::fromStdString(rbool(sim->EXMEM.MemRead));
    QGraphicsTextItem* gEXMemRead = this->circuitScene.addText(EXMemRead);
    fontB(gEXMemRead);
    gEXMemRead->setPos(1110, 282);

    QGraphicsTextItem* gEXMemRead2 = this->circuitScene.addText("="+EXMemRead);
    fontB(gEXMemRead2);
    gEXMemRead2->setPos(918, 20);

    // ID/EX Register


    //    QString Jump = QString::fromStdString("="+rbool(sim->ControlUnit.Jump));
//    QGraphicsTextItem* gJump = this->circuitScene.addText(Jump);
//    fontB(gJump);
//    gJump->setPos(480, 212);
    QString PCWrite = QString::fromStdString(rbool(sim->HazardUnit.PCWrite));
    QGraphicsTextItem* gPCWrite = this->circuitScene.addText(PCWrite);
    fontY(gPCWrite);
    gPCWrite->setPos(65, 434);

    QString NotStall = QString::fromStdString(rbool(sim->HazardUnit.notStall));
    QGraphicsTextItem* gNotStall = this->circuitScene.addText(NotStall);
    fontY(gNotStall);
    gNotStall->setPos(180, 640);

    QString Flush = QString::fromStdString(rbool(sim->flush));
    QGraphicsTextItem* gFlush = this->circuitScene.addText(Flush);
    fontB(gFlush);
    gFlush->setPos(180, 640);

    QGraphicsTextItem* gFlush2 = this->circuitScene.addText("IFFlush= "+Flush);
    fontB(gFlush2);
    gFlush2->setPos(368, 142);

    QString Branch = QString::fromStdString("Branch= "  + rbool(sim->ControlUnit.Branch));
    QGraphicsTextItem* gBranch = this->circuitScene.addText(Branch);
    fontB(gBranch);
    gBranch->setPos(480, 142);

    QString PCSrc = QString::fromStdString(rbool(sim->PCSrc));
    QGraphicsTextItem* gPCSrc = this->circuitScene.addText("= "+PCSrc);
    fontB(gPCSrc);
    gPCSrc->setPos(604, 16);

    QGraphicsTextItem* gPCSrc2 = this->circuitScene.addText(PCSrc);
    fontB(gPCSrc2);
    gPCSrc2->setPos(170, 180);


    QString Jump = QString::fromStdString(rbool(sim->ControlUnit.Jump));
    QGraphicsTextItem* gJump = this->circuitScene.addText(Jump);
    fontB(gJump);
    gJump->setPos(480, 212);

    QGraphicsTextItem* gJump2 = this->circuitScene.addText(Jump);
    fontB(gJump2);
    gJump2->setPos(120, 180);

    QString ALUOp = QString::fromStdString("ALUOP = "+rbool(sim->IDEX.ALUOp1)+rbool(sim->IDEX.ALUOp0));
    QGraphicsTextItem* gALUOp = this->circuitScene.addText(ALUOp);
    fontB(gALUOp);
    gALUOp->setPos(662, 253);
//    QString ALUSrc = QString::fromStdString(rbool(sim->IDEX.ALUSrc));
//    QGraphicsTextItem* gALUSrc = this->circuitScene.addText(ALUSrc);
//    fontB(gALUSrc);
//    gALUSrc->setPos(670, 146);

    QString RegDst = QString::fromStdString("= " + rbool(sim->IDEX.RegDst));
    QGraphicsTextItem* gRegDst1 = this->circuitScene.addText(RegDst);
    fontB(gRegDst1);
    gRegDst1->setPos(712, 232);
    QGraphicsTextItem* gRegDst2 = this->circuitScene.addText(RegDst);
    fontB(gRegDst2);
    gRegDst2->setPos(817, 532);

    QString MemToReg = QString::fromStdString("MemToReg = " + rbool(sim->IDEX.MemtoReg));
    QGraphicsTextItem* gMemToReg = this->circuitScene.addText(MemToReg);
    fontB(gMemToReg);
    gMemToReg->setPos(670, 146);

    QString RegWrite = QString::fromStdString("RegWrite = "+rbool(sim->IDEX.RegWrite));
    QGraphicsTextItem* gRegWrite = this->circuitScene.addText(RegWrite);
    fontB(gRegWrite);
    gRegWrite->setPos(670, 166);

    QString MemRead = QString::fromStdString(rbool(sim->IDEX.MemRead));
    QGraphicsTextItem* gMemRead = this->circuitScene.addText("MemRead = "+MemRead);
    fontB(gMemRead);
    gMemRead->setPos(670, 192);
    QGraphicsTextItem* gMemRead2 = this->circuitScene.addText("= "+MemRead);
    fontB(gMemRead2);
    gMemRead2->setPos(776, 112);

    QString MemWrite = QString::fromStdString("MemWrite = "+rbool(sim->IDEX.MemWrite));
    QGraphicsTextItem* gMemWrite = this->circuitScene.addText(MemWrite);
    fontB(gMemWrite);
    gMemWrite->setPos(670, 212);


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
    QString HRs = QString::fromStdString(sim->HazardUnit.Rs.to_string());
    QGraphicsTextItem* gHRs = this->circuitScene.addText("rs= \n"+HRs);
    gHRs->setPos(296, 140);
    fontB(gHRs);

    QString HRt = QString::fromStdString(sim->HazardUnit.Rt.to_string());
    QGraphicsTextItem* gHRt = this->circuitScene.addText("rt= \n"+HRt);
    gHRt->setPos(296, 100);
    fontB(gHRt);

    QString PC = QString::fromStdString(binToHex(sim->IFID.PC));
    QGraphicsTextItem* gPC = this->circuitScene.addText(PC);
    gPC->setPos(200, 300);
    fontB(gPC);

    QString Inst = QString::fromStdString(binToHex(sim->IFID.Inst));
    QGraphicsTextItem* gInst = this->circuitScene.addText(Inst);
    gInst->setPos(200, 540);
    fontB(gInst);

    QString BranchAdress = QString::fromStdString(binToHex(sim->branchAddress));
    QGraphicsTextItem* gBranchAdress = this->circuitScene.addText("BranchAdress= "+BranchAdress);
    gBranchAdress->setPos(160, -8);
    fontB(gBranchAdress);

    QString JumpAdress = QString::fromStdString(binToHex(sim->jumpAddress));
    QGraphicsTextItem* gJumpAdress = this->circuitScene.addText("JumpAdress= "+JumpAdress);
    gJumpAdress->setPos(160, 12);
    fontB(gJumpAdress);

    QString FetchedPC = QString::fromStdString(binToHex(sim->PC));
    QGraphicsTextItem* gFetchedPC = this->circuitScene.addText(FetchedPC);
    gFetchedPC->setPos(2, 572);
    fontB(gFetchedPC);

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
    refreshMemTable(this->MEMEncodeTo);
    refreshRegTable(this->RegEncodeTo);
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
