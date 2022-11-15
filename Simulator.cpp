#include <string>
#include <bitset>
#include <map>
#include "FileEncode.cpp"
#include "ControlUnit.cpp"
#include "ForwardingUnit.cpp"
#include "HazardDetectionUnit.cpp"
#include "Translate.cpp"
#include "PipelineRegisters.cpp"

// PC, BranchAddress, 0~31번 레지스터들을 저장하고 관리하는 Simulator class.
class Simulator
{
public:
	ForwardingUnit ForwardUint;
	HazardDetectionUnit HazardUnit;
	ControlUnit ControlUnit;
	IF_ID IFID;
	ID_EX IDEX;
	EX_MEM EXMEM;
	MEM_WB MEMWB;

	std::bitset<32> PC; // 현재
	std::bitset<32> NextPC;
	std::bitset<32> BranchAddress;
	bool PCSrc;
	int nowIdx;
	std::bitset<32> Regi[32];

	Simulator(std::string fileName)
	{
		// 생성 시 입력받은 PC를 저장하고 각 레지스터를 초기화.
		encode(fileName);
		this->PC = startPC;
		this->PCSrc = 0;
		this->nowIdx = 0;
		for (int i = 0; i < 32; i++)
		{
			this->Regi[i].reset();
		}
	}

	// 시뮬레이터가 Instruction Fetch를 실행. 실행한 결과를 주소값을 받은 IF/ID register 객체에 저장한다.
	void IF()
	{
		std::bitset<32> tmpPC;							// PC를 다루기 위한 변수 tmpPC
		tmpPC = this->PC;										// 현재 simulator 객체가 가지고 있는 PC를 받아와서 10진수로 변환
		this->NextPC = binToDec(tmpPC) + 4; // 변환된 10진수 형식의 PC에 4를 더한 후 16진수로 변환,

		//
		if (this->PCSrc == 0)
		{
			this->PC = this->NextPC;
		}
		else
		{
			this->PC = this->BranchAddress;
		}

		//IFID.PC = bintoDec(tmpPC) + 4; 
		// IFID.inst = encode(op, rs, rt, rd);
		for(int i= 0;i<6;i++) IFID.Operation[i] = IFID.Inst[i];
		for(int i= 0;i<5;i++) IFID.Rs[i] = IFID.Inst[6+i];
		for(int i= 0;i<5;i++) IFID.Rt[i] = IFID.Inst[11+i];
		for(int i= 0;i<5;i++) IFID.Rd[i] = IFID.Inst[16+i];
		for(int i= 0;i<5;i++) IFID.Shamt[i] = IFID.Inst[21+i];
		for(int i= 0;i<6;i++) IFID.Function[i] = IFID.Inst[26+i];
		for(int i= 0;i<15;i++) IFID.Extend[i] = IFID.Inst[16+i];
	}

	// 시뮬레이터가 Instruction Decode를 실행.
	//  Instruction의 OPcode에 따라 control unit을 조정한 뒤, 주소값을 받은 ID_EX 레지스터 객체에 해당 값들을 저장한다.
	void ID()
	{
		HazardUnit.detect(IFID,IDEX);
		ControlUnit.setControl(IFID.Operation,IFID.Function);

		IDEX.RegDst = ControlUnit.RegDst;
		IDEX.Branch = ControlUnit.Branch;
		IDEX.MemRead = ControlUnit.MemRead;
		IDEX.MemtoReg = ControlUnit.MemtoReg;
		IDEX.ALUOp1 = ControlUnit.ALUOp1;
		IDEX.ALUOp0 = ControlUnit.ALUOp0;
		IDEX.MemWrite = ControlUnit.MemWrite;
		IDEX.ALUSrc = ControlUnit.ALUSrc;
		IDEX.RegWrite = ControlUnit.RegWrite;

		IDEX.Data1 = this->Regi[binToDec(IFID.Rs)];
		IDEX.Data2 = this->Regi[binToDec(IFID.Rt)];

		IDEX.Extend = signExtention(IFID.Extend);
		IDEX.Rt = IFID.Rt;
		IDEX.Rd = IFID.Rd;
	}

	// 시뮬레이터가 ID_EX 레지스터 객체를 바탕으로 Operation을 Excute하거나 주소값을 계산.
	// 이때 각 값들을 해당 Operation에서 사용하던 안하던 일단 계산은 하는 식으로 구현하는게 목표.
	// 따라서 코드 재 확인 필요.
	void EX()
	{
		ForwardUint.setForward(IDEX,EXMEM,MEMWB);

		EXMEM.Branch = IDEX.Branch;
		EXMEM.MemRead = IDEX.MemRead;
		EXMEM.MemtoReg = IDEX.MemtoReg;
		EXMEM.MemWrite = IDEX.MemWrite;
		EXMEM.RegWrite = IDEX.RegWrite;

		// int tmp = hexToDec(IDEX.PC) + binToDec(IDEX.Extend + "00");
		// EXMEM.PC = decToHex(tmp);

		bool Zero=0;
		std::bitset<32> data;
		std::bitset<32> ALUin1;
		std::bitset<32> ALUin2;
		
		if(ForwardUint.forwardA == 0) ALUin1 = IDEX.Data1;
		else if(ForwardUint.forwardA == 1) ALUin1 = ForwardUint.WBData;
		else if(ForwardUint.forwardA == 2) ALUin1 = ForwardUint.MEMData;
		
		if(ForwardUint.forwardB == 0) ALUin2 = IDEX.Data2;
		else if(ForwardUint.forwardB == 1) ALUin2 = ForwardUint.WBData;
		else if(ForwardUint.forwardB == 2) ALUin2 = ForwardUint.MEMData;
		// else if() ALUin2 = IDEX.Extend;

		if (ALUin1 == ALUin2)
			Zero = 1;
		else
			Zero = 0;

		if(Zero == 1 && IDEX.Branch == 1) PCSrc =1;

		int func = ALUControl(IDEX.Function, IDEX.ALUOp1, IDEX.ALUOp0);
		if (func == 0)
		{
			EXMEM.ALUResult = 0;
		} // AND OR 구현 ,16진수 반환
		EXMEM.Data2 = IDEX.Data2;

		if (IDEX.RegDst == 0)
			EXMEM.Rd = IDEX.Rt;
		else
			EXMEM.Rd = IDEX.Rd;
	}

	// Memory 계층에 접근하는 작업 수행.
	// 수행한 작업은 MEM_WB 객체에 저장.
	void MEM()
	{
		MEMWB.MemtoReg = EXMEM.MemtoReg;
		MEMWB.RegWrite = EXMEM.RegWrite;

		// this->BranchAddress = EXMEM.PC;

		MEMWB.Data = 0; // lw sw 구현
		MEMWB.Address = EXMEM.ALUResult;
		MEMWB.Rd = EXMEM.Rd;
	}

	// 레지스터에 수행한 작업 결과를 저장.
	void WB()
	{
		std::bitset<32> data;
		if (MEMWB.MemtoReg == false)
			data = MEMWB.Data;
		else
			data = MEMWB.Address;

		if (MEMWB.RegWrite == true)
		{
			this->Regi[binToDec(MEMWB.Rd)] = data;
		}
	}
	void run(){
		while(nowIdx<fileLength+4){
			WB();
			MEM();
			EX();
			ID();
			IF();
			if(!HazardUnit.stool) nowIdx++;
		}
	}
};