#ifndef SIMULATOR_INCLUDED
#define SIMULATOR_INCLUDED

#include <iostream>
#include <string>
#include <bitset>
#include <map>

#include "MemoryManager.cpp"
#include "ControlUnit.cpp"
#include "Operations.cpp"
#include "ForwardingUnit.cpp"
#include "HazardDetectionUnit.cpp"
#include "Translate.cpp"
#include "PipelineRegisters.cpp"

// PC, BranchAddress, 0~31번 레지스터들을 저장하고 관리하는 Simulator class.
class Simulator
{
public:
    MemoryManager MManager;

    ForwardingUnit ForwardUnit;
    HazardDetectionUnit HazardUnit;
    ControlUnit ControlUnit;

    std::bitset<32> branchAddress;
    std::bitset<32> jumpAddress;

    IF_ID IFID;
    ID_EX IDEX;
    EX_MEM EXMEM;
    MEM_WB MEMWB;

    std::bitset<32> PC; // 현재
    bool PCSrc;
    bool flush;
    bool Jump;
    int nowIdx=0;
    int cycle;
    std::bitset<32> Regi[32];
 
    Simulator()
    {
        // 생성 시 입력받은 PC를 저장하고 각 레지스터를 초기화.
        this->PC = MManager.getStartPC();
        this->PCSrc = 0;
        this->nowIdx = 0;
        this->cycle = 0;
        for (int i = 0; i < 32; i++)
        {
            this->Regi[i].reset();
        }
        this->Regi[28] = hexToBin("0x10008000");
        this->Regi[29] = hexToBin("0x7ffffe40");
    }

    void fileLoad(std::string fileName){
        this->MManager.fileRead(fileName);
        this->PC = MManager.getStartPC();
        this->PCSrc = 0;
        this->nowIdx = 0;
        this->cycle = 0;
        for (int i = 0; i < 32; i++)
        {
            this->Regi[i] = i;
        }
        this->Regi[28] = hexToBin("0x10008000");
        this->Regi[29] = hexToBin("0x7ffffe40");
    }

    // 시뮬레이터가 Instruction Fetch를 실행. 실행한 결과를 주소값을 받은 IF/ID register 객체에 저장한다.
    void IF()
    {
        if(HazardUnit.IFIDWrite == 1){
            this->IFID.PC = binToDec(this->PC)+4;

            if(this->flush)
                this->IFID.Inst = 0;

            else{
//				this->IFID.Inst = MManager.getProgram()[decToHex(binToDec(MManager.getStartPC()) + nowIdx * 4)];
                this->IFID.Inst = MManager.getProgram()[decToHex(binToDec(this->PC))];
            }
        }

        if(this->HazardUnit.PCWrite == 1){
            if (this->PCSrc == 1)
            {
                this->PC = this->branchAddress;
            }
            else if(this->ControlUnit.Jump == 1)
            {
                this->PC = this->jumpAddress;
            }
            else{
                this->PC = binToDec(this->PC)+4;
            }
        }
        std::cout  << "\nIFID\nPC :\t\t" << IFID.PC << "\nInst :\t\t" << IFID.Inst << "\n\n";
    }

    // 시뮬레이터가 Instruction Decode를 실행.
    //  Instruction의 OPcode에 따라 control unit을 조정한 뒤, 주소값을 받은 ID_EX 레지스터 객체에 해당 값들을 저장한다.
    void ID()
    {
        std::bitset<6> Operation;
        std::bitset<5> Rs;
        std::bitset<5> Rt;
        std::bitset<5> Rd;
        std::bitset<5> Shamt=0;
        std::bitset<6> Function;
        std::bitset<16> Extend;
        std::bitset<32> JumpDirection;
        std::bitset<32> BranchCompareData1;
        std::bitset<32> BranchCompareData2;
        for(int i = 0;i<6;i++) Operation[i] = this->IFID.Inst[i+26];
        for(int i = 0;i<5;i++) Rs[i] = this->IFID.Inst[i+21];
        for(int i = 0;i<5;i++) Rt[i] = this->IFID.Inst[i+16];
        for(int i = 0;i<5;i++) Rd[i] = this->IFID.Inst[i+11];
        for(int i = 0;i<6;i++) Function[i] = this->IFID.Inst[i];
        for(int i = 0;i<16;i++) Extend[i] = this->IFID.Inst[i];
        for(int i = 0;i<26;i++) JumpDirection[i+2] = this->IFID.Inst[i]; // shift 2

        // HazardUnit.detect(IFID,IDEX,EXMEM);
        ControlUnit.setControl(Operation);

        if(HazardUnit.notStall){
            IDEX.RegDst = ControlUnit.RegDst;
            IDEX.MemRead = ControlUnit.MemRead;
            IDEX.MemtoReg = ControlUnit.MemtoReg;
            IDEX.ALUOp1 = ControlUnit.ALUOp1;
            IDEX.ALUOp0 = ControlUnit.ALUOp0;
            IDEX.MemWrite = ControlUnit.MemWrite;
            IDEX.ALUSrc = ControlUnit.ALUSrc;
            IDEX.RegWrite = ControlUnit.RegWrite;
        }
        else{
            IDEX.RegDst = 0;
            IDEX.MemRead = 0;
            IDEX.MemtoReg = 0;
            IDEX.ALUOp1 = 0;
            IDEX.ALUOp0 = 0;
            IDEX.MemWrite = 0;
            IDEX.ALUSrc = 0;
            IDEX.RegWrite = 0;
        }

        IDEX.Data1 = this->Regi[binToDec(Rs)];
        IDEX.Data2 = this->Regi[binToDec(Rt)];
        IDEX.Extend = signExtention(Extend);
        if(ForwardUnit.BranchForwardA == 0) BranchCompareData1 = IDEX.Data1;
        else if(ForwardUnit.BranchForwardA == 1) BranchCompareData1 = ForwardUnit.MEMWBData;
        else if(ForwardUnit.BranchForwardA == 2) BranchCompareData1 = ForwardUnit.EXMEMData;

        if(ForwardUnit.BranchForwardB == 0) BranchCompareData2 = IDEX.Data2;
        else if(ForwardUnit.BranchForwardB == 1) BranchCompareData2 = ForwardUnit.MEMWBData;
        else if(ForwardUnit.BranchForwardB == 2) BranchCompareData2 = ForwardUnit.EXMEMData;
        std::cout << BranchCompareData1 << ' ' << BranchCompareData2;
        this->jumpAddress = JumpDirection;
        this->branchAddress = binToDec(IFID.PC) + ((int)binToDec(IDEX.Extend)<<2)-4;

        if(Operation == 2){ // j instruction
            this->flush = 1;
            this->PCSrc = 0;
            this->Jump = 1;
        }
        else if(BranchCompareData1 == BranchCompareData2 
        && ControlUnit.Branch && HazardUnit.IFIDWrite){ // beq instruction
            this->flush = 1;
            this->PCSrc = 1;
            this->Jump = 0;
        }
        else{
            this->flush = 0;
            this->PCSrc = 0;
            this->Jump = 0;
        }

        //레지스터에 저장은 WB()
        IDEX.Function = Function;
        IDEX.Rs = Rs;
        IDEX.Rt = Rt;
        IDEX.Rd = Rd;
        std::cout << "\nIDEX\nData1 :\t\t" << IDEX.Data1 << "\nData2 :\t\t" << IDEX.Data2 << "\nExtend :\t" << IDEX.Extend << '\n';
    }

    // 시뮬레이터가 ID_EX 레지스터 객체를 바탕으로 Operation을 Excute하거나 주소값을 계산.
    // 이때 각 값들을 해당 Operation에서 사용하던 안하던 일단 계산은 하는 식으로 구현하는게 목표.
    void EX()
    {
        //ForwardUnit.setForward(IDEX,EXMEM,MEMWB);

        EXMEM.MemRead = IDEX.MemRead;
        EXMEM.MemtoReg = IDEX.MemtoReg;
        EXMEM.MemWrite = IDEX.MemWrite;
        EXMEM.RegWrite = IDEX.RegWrite;

        std::bitset<32> data;
        std::bitset<32> ALUin1;
        std::bitset<32> ALUin2;

        if(ForwardUnit.forwardA == 0) ALUin1 = IDEX.Data1;
        else if(ForwardUnit.forwardA == 1) ALUin1 = ForwardUnit.MEMWBData;
        else if(ForwardUnit.forwardA == 2) ALUin1 = ForwardUnit.EXMEMData;

        if(ForwardUnit.forwardB == 0) ALUin2 = IDEX.Data2;
        else if(ForwardUnit.forwardB == 1) ALUin2 = ForwardUnit.MEMWBData;
        else if(ForwardUnit.forwardB == 2) ALUin2 = ForwardUnit.EXMEMData;
        if (IDEX.MemRead || IDEX.MemWrite) ALUin2 = IDEX.Extend;

        int func = ALUControl(IDEX.Function, IDEX.ALUOp1, IDEX.ALUOp0);
        if (func == 0) // and
        {
            EXMEM.ALUResult = andOperation(ALUin1, ALUin2);
        }
        else if(func == 1) // or
        {
            EXMEM.ALUResult = orOperation(ALUin1, ALUin2);
        }
        else if(func == 2) // add
        {
            EXMEM.ALUResult = addOperation(ALUin1, ALUin2);
        }
        else if(func == 6) // sub
        {
            EXMEM.ALUResult = subOperation(ALUin1, ALUin2);
        }
        else if(func == 7) // slt
        {
            EXMEM.ALUResult = sltOperation(ALUin1, ALUin2);
        }
        EXMEM.Data2 = IDEX.Data2;

        if (IDEX.RegDst == 0)
            EXMEM.Rd = IDEX.Rt;
        else
            EXMEM.Rd = IDEX.Rd;
        std::cout << "\nEXMEM\nALUresult :\t" << EXMEM.ALUResult << "\nData :\t\t" << EXMEM.Data2 << "\nRd :\t\t" << EXMEM.Rd << '\n';
    }

    // Memory 계층에 접근하는 작업 수행.
    // 수행한 작업은 MEM_WB 객체에 저장.
    void MEM()
    {
        MEMWB.MemtoReg = EXMEM.MemtoReg;
        MEMWB.RegWrite = EXMEM.RegWrite;

        if (EXMEM.MemRead == 1){
            //
            if (MManager.getWords()->find(binToHex(EXMEM.ALUResult)) != MManager.getWords()->end()){
                MEMWB.Data = MManager.getWords()->at(binToHex(EXMEM.ALUResult));
            }
            else
                MEMWB.Data = 0;
        }
        else if(EXMEM.MemWrite == 1){
            // 쓰려고 하는 메모리의 주소에 값이 이미 존재한다면 해당 메모리 주소의 값을 수정
            if (MManager.getWords()->find(binToHex(EXMEM.ALUResult)) != MManager.getWords()->end()){
                MManager.setWords(binToHex(EXMEM.ALUResult), binToDec(EXMEM.Data2));
            }
            // 이외의 경우 map Mem에 주소값과 해당하는 데이터를 저장
            else{
                MManager.setWords(binToHex(EXMEM.ALUResult), binToDec(EXMEM.Data2));
            }
        }else{
            MEMWB.Data = 0;
        }

        MEMWB.Address = EXMEM.ALUResult;
        ForwardUnit.EXMEMData = MEMWB.Address;
        MEMWB.Rd = EXMEM.Rd;
        std::cout << "\nMEMWB\nData :\t\t" << MEMWB.Data << "\nAddress:\t" << EXMEM.ALUResult << "\nRd :\t\t" << EXMEM.Rd << '\n';
    }

    // 레지스터에 수행한 작업 결과를 저장.
    void WB()
    {
        std::bitset<32> data;
        if (MEMWB.MemtoReg == false)
            data = MEMWB.Address;
        else
            data = MEMWB.Data;

        if (MEMWB.RegWrite == true)
        {
            this->Regi[binToDec(MEMWB.Rd)] = data;
        }
        ForwardUnit.MEMWBData = data;
        std::cout << "cycle " << nowIdx <<'\n';
    }

    // 사이클을 한번 실행. WB부터 IF까지.
    void runSingleCycle(){
        if (this->MManager.getFileLength() == -1) return;
        WB();
        MEM();
        EX();
        ID();
        IF();
        if(HazardUnit.notStall) nowIdx++;
        cycle++;
        HazardUnit.detect(IFID,IDEX,EXMEM);
        ForwardUnit.setForward(IFID,IDEX,EXMEM,MEMWB);
    }

    void run(){
        while(nowIdx < this->MManager.getFileLength()+5){
            runSingleCycle();
        }
    }


};
#endif
