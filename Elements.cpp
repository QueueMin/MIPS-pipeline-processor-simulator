#include <string>

#define OP_ADD 0
#define OP_SUB 0
#define OP_AND 0
#define OP_OR 0
#define OP_LUI 15
#define OP_LW 35
#define OP_SW 43

#define FUNCT_ADD 32
#define FUNCT_SUB 34
#define FUNCT_AND 36
#define FUNCT_OR 37

#define ALU_AND 0
#define ALU_OR 1
#define ALU_ADD 2
#define ALU_SUB 6
#define ALU_SLT 7


// control signal을 통제하는 ControlUnit class.
class ControlUnit{
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

		// 미완성.
		// ControlUnit 객체의 field들을 초기화하고, 주어진 instruction에 알맞게 field를 설정 
		void control(std::string inst){
			this->RegDst=0;
			this->Branch=0;
			this->MemRead=0;
			this->MemtoReg=0;
			this->ALUOp1=0;
			this->ALUOp0=0;
			this->MemWrite=0;
			this->ALUSrc=0;
			this->RegWrite=0;
	}
		
};


// sign S가 0이냐 1이냐에 따라 string으로 입력받은 이진수 Bin을 16자리만큼 sign extend하여 반환.
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

// control unit에서 받은 ALUOp1, ALUOp2 신호와 funct String을 바탕으로 수행할 연산의 값을 반환.
int ALUControl(std::string funct, bool ALUOp1, bool ALUOp0){
	if(ALUOp1 == 0 && ALUOp0 == 0) return ALU_ADD;
	else if(ALUOp1 == 0 && ALUOp0 == 1) return ALU_SUB;
	else{
		if(funct == "100000") return ALU_ADD;
		else if(funct == "100010") return ALU_SUB;
		else if(funct == "100100") return ALU_AND;
		else if(funct == "100101") return ALU_OR;
		else if(funct == "101010") return ALU_SLT;
	}
}
