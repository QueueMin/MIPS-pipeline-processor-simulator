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
	bool Jump;

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
		this->Jump = 0;
	}

	void setControl(std::bitset<6> operation)
	{
		if (operation == 0)
		{
			this->RegDst = 1;
			this->Branch = 0;
			this->MemRead = 0;
			this->MemtoReg = 0;
			this->ALUOp1 = 1;
			this->ALUOp0 = 0;
			this->MemWrite = 0;
			this->ALUSrc = 0;
			this->RegWrite = 1;
			this->Jump = 0;
		}
		else if (operation == 35)
		{
			this->RegDst = 0;
			this->Branch = 0;
			this->MemRead = 1;
			this->MemtoReg = 1;
			this->ALUOp1 = 0;
			this->ALUOp0 = 0;
			this->MemWrite = 0;
			this->ALUSrc = 1;
			this->RegWrite = 1;
			this->Jump = 0;
		}
		else if (operation == 43)
		{
			this->RegDst = 0;
			this->Branch = 0;
			this->MemRead = 0;
			this->MemtoReg = 0;
			this->ALUOp1 = 0;
			this->ALUOp0 = 0;
			this->MemWrite = 1;
			this->ALUSrc = 1;
			this->RegWrite = 0;
			this->Jump = 0;
		}
		else if (operation == 4)
		{
			this->RegDst = 0;
			this->Branch = 1;
			this->MemRead = 0;
			this->MemtoReg = 0;
			this->ALUOp1 = 0;
			this->ALUOp0 = 1;
			this->MemWrite = 0;
			this->ALUSrc = 0;
			this->RegWrite = 0;
			this->Jump = 0;
		}
		else if (operation == 2)
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
			this->Jump = 1;
		}
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
