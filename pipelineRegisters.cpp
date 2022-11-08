#include <string>

// IF/ID 레지스터 클래스. PC와 instruction을 저장하며 write가 1일때만 쓸 수 있도록 한다.
class IF_ID{
	public:
		std::string PC="";
		std::string inst="";
        
        bool write = 1; // write 신호. 기본적으로 쓸 수 있는 상태로 설정.

        // IF_ID 레지스터 객체의 write를 설정
        void setWrite(bool signal){
            this->write = signal;
        }
};


// ID/EX 레지스터 클래스. Fetch한 Instruction에 알맞는 ControlSignal들을 받아서 저장하고,
// 명령을 수행할 수 있도록 구성 요소들을 분리하여 저장한다. 
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
		std::string Rs="";
		std::string Rt="";
		std::string Rd="";
};


// EX/MEM 레지스터 클래스. 
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

// MEM/WB 레지스터 클래스.
class MEM_WB{
	public:
		bool MemtoReg=0;
		bool RegWrite=0;

		std::string Data="";
		std::string Address="";
		std::string Rd="";
};