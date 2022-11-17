#ifndef PIPELINEREGISTERS_INCLUDED
#define PIPELINEREGISTERS_INCLUDED
#include <string>
#include <bitset>

// IF/ID 레지스터 클래스. PC와 instruction을 저장하며 write가 1일때만 쓸 수 있도록 한다.
class IF_ID
{
public:
	std::bitset<32> PC = 0;
	std::bitset<32> Inst = 0;
	std::bitset<32> Operation;
	
};

// ID/EX 레지스터 클래스. Fetch한 Instruction에 알맞는 ControlSignal들을 받아서 저장하고,
// 명령을 수행할 수 있도록 구성 요소들을 분리하여 저장한다.
class ID_EX
{
public:
	bool RegDst = 0;
	bool MemRead = 0;
	bool MemtoReg = 0;
	bool ALUOp1 = 0;
	bool ALUOp0 = 0;
	bool MemWrite = 0;
	bool ALUSrc = 0;
	bool RegWrite = 0;

	std::bitset<32> Data1 = 0;
	std::bitset<32> Data2 = 0;

	std::bitset<32> Extend = 0;
	std::bitset<6> Function = 0;
	std::bitset<5> Rs = 0;
	std::bitset<5> Rt = 0;
	std::bitset<5> Rd = 0;
};

// EX/MEM 레지스터 클래스.
class EX_MEM
{
public:
	bool MemRead = 0;
	bool MemtoReg = 0;
	bool MemWrite = 0;
	bool RegWrite = 0;

	std::bitset<32> ALUResult = 0;
	std::bitset<32> Data2 = 0;

	std::bitset<5> Rd = 0;
};

// MEM/WB 레지스터 클래스.
class MEM_WB
{
public:
	bool MemtoReg = 0;
	bool RegWrite = 0;

	std::bitset<32> Data = 0;
	std::bitset<32> Address = 0;
	std::bitset<5> Rd = 0;
};
#endif