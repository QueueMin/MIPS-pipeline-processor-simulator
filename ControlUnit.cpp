#include <bitset>
#include "Elements.cpp"

// control signal을 통제하는 ControlUnit class.
class ControlUnit
{
public:
	bool RegDst;
	bool Branch;
	bool MemRead;
	bool MemtoReg;
	bool ALUOp1;
	bool ALUOp0;
	bool MemWrite;
	bool ALUSrc;
	bool RegWrite;

	// ControlUnit 객체의 field들을 초기화하고
	ControlUnit()
	{
		this->RegDst = 0;
		this->Branch = 0;
		this->MemRead = 0;
		this->MemtoReg = 0;
		this->ALUOp1 = 0;
		this->ALUOp0 = 0;
		this->MemWrite = 0;
		this->ALUSrc = 0;
		this->RegWrite = 0;
	}
	
	// 미완성. 주어진 instruction에 알맞게 field를 설정
	void setControl(std::bitset<6> operation,std::bitset<6> function){

	}

};

// control unit에서 받은 ALUOp1, ALUOp2 신호와 funct String을 바탕으로 수행할 연산의 값을 반환.
int ALUControl(std::bitset<6> funct, bool ALUOp1, bool ALUOp0)
{
	if (ALUOp1 == 0 && ALUOp0 == 0)
		return ALU_ADD;
	else if (ALUOp1 == 0 && ALUOp0 == 1)
		return ALU_SUB;
	else
	{
		if (funct == 32)
			return ALU_ADD;
		else if (funct == 34)
			return ALU_SUB;
		else if (funct == 36)
			return ALU_AND;
		else if (funct == 37)
			return ALU_OR;
		else if (funct == 40)
			return ALU_SLT;
	}
}
