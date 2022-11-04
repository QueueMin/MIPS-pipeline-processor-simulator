#include <string>
#define OP_ADD 0
#define FUNCT_ADD 32
#define OP_SUB 0
#define FUNCT_SUB 34
#define OP_AND 0
#define FUNCT_AND 36
#define OP_OR 0
#define FUNCT_OR 37
#define OP_LUI 15
#define OP_LW 35
#define OP_SW 43
class Reg{
	public:
		std::string PC;
		std::string NextPC;
		std::string BranchAddress;
		bool PCSrc;
		std::string Regi[32];
		
		Reg(std::string PC = ""){
			this->PC = PC;
			this->PCSrc = 0;
			for(int i = 0;i<32;i++){
				this->Regi[i] = "";
			}
		}
};
class ControlSignal{
	public:
		bool RegDst=0;
		bool Branch=0;
		bool MemRead=0;
		bool MemtoReg=0;
		bool ALUOp1=0;
		bool ALUOp0=0;
		bool MemWrite=0;
		bool ALUSrc=0;
		bool RegWrite=0;
		
};

class IF_ID{
	public:
		std::string PC="";
		std::string inst="";
};
class ID_EX{
	public:
		bool RegDst=0;
		bool Branch=0;
		bool MemRead=0;
		bool MemtoReg=0;
		bool ALUOp1=0;
		bool ALUOp0=0;
		bool MemWrite=0;
		bool ALUSrc=0;
		bool RegWrite=0;

		std::string PC="";
		std::string Data1="";
		std::string Data2="";

		std::string Extend="";
		std::string Rt="";
		std::string Rd="";
};
class EX_MEM{
	public:
		bool Branch=0;
		bool MemRead=0;
		bool MemtoReg=0;
		bool MemWrite=0;
		bool RegWrite=0;

		std::string PC="";
		bool Zero=0;
		std::string ALUResult="";
		std::string Data2="";

		std::string Rd="";
};
class MEM_WB{
	public:
		bool MemtoReg=0;
		bool RegWrite=0;

		std::string Data="";
		std::string Address="";
		std::string Rd="";
};
std::string signExtention(bool S, std::string Bin){
	std::string tmp = "";
	if(S == 0){
		for(int i = 0;i<16;i++) tmp += "0";
	}
	else{
		for(int i = 0;i<16;i++) tmp += "1";
	}
	return tmp+Bin;
}
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
void control(std::string instruct, ControlSignal &controlSignal){
	controlSignal.RegDst=0;
	controlSignal.Branch=0;
	controlSignal.MemRead=0;
	controlSignal.MemtoReg=0;
	controlSignal.ALUOp1=0;
	controlSignal.ALUOp0=0;
	controlSignal.MemWrite=0;
	controlSignal.ALUSrc=0;
	controlSignal.RegWrite=0;
}