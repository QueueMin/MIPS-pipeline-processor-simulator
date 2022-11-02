#include <string>
#define OP_ADD 0
#define FUNCT_ADD 32
class Reg{
	public:
		std::string PC;
		std::string Reg[32];
		
};
class ControlSignal{
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
};

class IF_ID{

};
class ID_EX{

};
class EX_MEM{

};
class MEM_WB{

};
int ALUControl(std::string funct, bool ALUOp1, bool ALUOp0){
	if(ALUOp1 == 0 && ALUOp0 == 0) return 2;
	else if(ALUOp1 == 0 && ALUOp0 == 1) return 6;
	else{
		if(funct == "100000") return 2;
		else if(funct == "100010") return 6;
		else if(funct == "100100") return 0;
		else if(funct == "100101") return 1;
		else if(funct == "101010") return 7;
	}
}
// add sub or and lui lw sw 
// slt beq j