#include <string>
#include "translate.cpp"
#include "pipelineRegisters.cpp"


// PC, BranchAddress, 0~31번 레지스터들을 저장하고 관리하는 Simulator class.
class Simulator
{
public:
    std::string PC; // 현재 
    std::string NextPC;
    std::string BranchAddress;
    bool PCSrc;
    std::string Regi[32];

    Simulator(std::string PC = "")
    {
        // 생성 시 입력받은 PC를 저장하고 각 레지스터를 초기화.
        this->PC = PC;
        this->PCSrc = 0;
        for (int i = 0; i < 32; i++)
        {
            this->Regi[i] = "";
        }
    }

    // 시뮬레이터가 Instruction Fetch를 실행. 실행한 결과를 주소값을 받은 IF/ID register 객체에 저장한다.
    void IF(IF_ID &IFID, std::string op, int rs, int rt, int rd)
    {
        int tmpPC; // PC를 다루기 위한 변수 tmpPC
        tmpPC = hexToDec(this->PC); // 현재 simulator 객체가 가지고 있는 PC를 받아와서 10진수로 변환
        this->NextPC = decToHex(tmpPC + 4); // 변환된 10진수 형식의 PC에 4를 더한 후 16진수로 변환, 

        // 
        if (this->PCSrc == 0)
        {
            this->PC = this->NextPC;
        }
        else
        {
            this->PC = this->BranchAddress;
        }
        tmpPC = hexToDec(this->PC);

        IFID.PC = decToHex(tmpPC + 4); // 
        IFID.inst = encode(op, rs, rt, rd);
    }

    // 시뮬레이터가 Instruction Decode를 실행.
    //  Instruction의 OPcode에 따라 control unit을 조정한 뒤, 주소값을 받은 ID_EX 레지스터 객체에 해당 값들을 저장한다.
    void ID(IF_ID IFID, ID_EX &IDEX, MEM_WB MEMWB, ControlUnit &cUnit)
    {
        cUnit.control(IFID.inst.substr(0, 6));

        IDEX.RegDst = cUnit.RegDst;
        IDEX.Branch = cUnit.Branch;
        IDEX.MemRead = cUnit.MemRead;
        IDEX.MemtoReg = cUnit.MemtoReg;
        IDEX.ALUOp1 = cUnit.ALUOp1;
        IDEX.ALUOp0 = cUnit.ALUOp0;
        IDEX.MemWrite = cUnit.MemWrite;
        IDEX.ALUSrc = cUnit.ALUSrc;
        IDEX.RegWrite = cUnit.RegWrite;

        int tmp = hexToDec(IFID.PC);
        IDEX.PC = decToHex(tmp + 4);

        IDEX.Data1 = this->Regi[binToDec(IFID.inst.substr(6, 11))];
        IDEX.Data2 = this->Regi[binToDec(IFID.inst.substr(11, 16))];

        IDEX.Extend = signExtention(0, IFID.inst.substr(16, 32));
        IDEX.Rt = IFID.inst.substr(11, 16);
        IDEX.Rd = IFID.inst.substr(16, 21);
    }
    
    // 시뮬레이터가 ID_EX 레지스터 객체를 바탕으로 Operation을 Excute하거나 주소값을 계산.
    // 이때 각 값들을 해당 Operation에서 사용하던 안하던 일단 계산은 하는 식으로 구현하는게 목표.
    // 따라서 코드 재 확인 필요.
    void EX(ID_EX IDEX, EX_MEM &EXMEM)
    {
        EXMEM.Branch = 0;
        EXMEM.MemRead = 0;
        EXMEM.MemtoReg = 0;
        EXMEM.MemWrite = 0;
        EXMEM.RegWrite = 0;

        int tmp = hexToDec(IDEX.PC) + binToDec(IDEX.Extend + "00");
        EXMEM.PC = decToHex(tmp);

        std::string data;
        if (IDEX.ALUSrc == 0)
            data = IDEX.Data2;
        else
            data = binToHex(IDEX.Extend);
        int ALUin1 = hexToDec(IDEX.Data1);
        int ALUin2 = hexToDec(data);
        if (ALUin1 - ALUin2)
            EXMEM.Zero = 1;
        else
            EXMEM.Zero = 0;

        int func = ALUControl(IDEX.Extend.substr(26, 32), IDEX.ALUOp1, IDEX.ALUOp0);
        if (func == 0)
        {
            EXMEM.ALUResult = "";
        } // AND OR 구현 ,16진수 반환
        EXMEM.Data2 = IDEX.Data2;

        if (IDEX.RegDst == 0)
            EXMEM.Rd = IDEX.Rt;
        else
            EXMEM.Rd = IDEX.Rd;
    }

    // Memory 계층에 접근하는 작업 수행.
    // 수행한 작업은 MEM_WB 객체에 저장.
    void MEM(EX_MEM EXMEM, MEM_WB &MEMWB)
    {
        MEMWB.MemtoReg = EXMEM.MemtoReg;
        MEMWB.RegWrite = EXMEM.RegWrite;

        this->BranchAddress = EXMEM.PC;

        if (EXMEM.Branch == 1 && EXMEM.Zero == 1)
        {
            this->PCSrc = 1;
        }

        MEMWB.Data = ""; // lw sw 구현
        MEMWB.Address = EXMEM.ALUResult;
        MEMWB.Rd = EXMEM.Rd;
    }

    // 레지스터에 수행한 작업 결과를 저장.
    void WB(MEM_WB MEMWB)
    {
        std::string data;
        if (MEMWB.MemtoReg == false)
            data = MEMWB.Data;
        else
            data = MEMWB.Address;

        if (MEMWB.RegWrite == true)
        {
            this->Regi[binToDec(MEMWB.Rd)] = data;
        }
    }
};