#include <string>

class IF_ID{
	public:
		std::string PC="";
		std::string inst="";
        
        bool write = 1; // write 신호. 기본적으로 쓸 수 있는 상태로 설정.

        void setWrite(bool signal){
            // IF_ID 레지스터 객체의 write를 설정
            this->write = signal;
        }
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