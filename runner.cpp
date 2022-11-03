#include <iostream>
#include <fstream>
#include "translate.cpp"
using namespace std;


void IF(IF_ID &IFID,Reg &reg, string op, int rs, int rt, int rd){
	int tmp;
	if(reg.PCSrc == 0){
		tmp = HextoDec(reg.PC);
		IFID.PC = DectoHex(tmp+4);
	}
	else{
		tmp = HextoDec(reg.BranchAddress);
		IFID.PC = DectoHex(tmp+4);
	}

	IFID.inst = encode(op,rs,rt,rd);

}
void ID(IF_ID IFID, ID_EX &IDEX,MEM_WB MEMWB,Reg &reg, ControlSignal &controlSignal){
	control(IFID.inst.substr(0,6),controlSignal);

	IDEX.RegDst = controlSignal.RegDst;
	IDEX.Branch = controlSignal.Branch;
	IDEX.MemRead = controlSignal.MemRead;
	IDEX.MemtoReg = controlSignal.MemtoReg;
	IDEX.ALUOp1 = controlSignal.ALUOp1;
	IDEX.ALUOp0 = controlSignal.ALUOp0;
	IDEX.MemWrite = controlSignal.MemWrite;
	IDEX.ALUSrc = controlSignal.ALUSrc;
	IDEX.RegWrite = controlSignal.RegWrite;

	int tmp = HextoDec(IFID.PC);
	IDEX.PC = DectoHex(tmp+4);

	IDEX.Data1 = reg.Regi[BintoDec(IFID.inst.substr(6,11))];
	IDEX.Data2 = reg.Regi[BintoDec(IFID.inst.substr(11,16))];


	IDEX.Extend = signExtention(0,IFID.inst.substr(16,32));
	IDEX.Rt = IFID.inst.substr(11,16);
	IDEX.Rd = IFID.inst.substr(16,21);

}
void EX(ID_EX IDEX, EX_MEM &EXMEM){
		EXMEM.Branch=0;
		EXMEM.MemRead=0;
		EXMEM.MemtoReg=0;
		EXMEM.MemWrite=0;
		EXMEM.RegWrite=0;

		int tmp = HextoDec(IDEX.PC) + BintoDec(IDEX.Extend+"00");
		EXMEM.PC = DectoHex(tmp);

		string data;
		if(IDEX.ALUSrc == 0)
			data = IDEX.Data2;
		else
			data = BintoHex(IDEX.Extend);
		int ALUin1 = HextoDec(IDEX.Data1);
		int ALUin2 = HextoDec(data);
		if(ALUin1-ALUin2) 
			EXMEM.Zero = 1;
		else
			EXMEM.Zero = 0;
		
		int func = ALUControl(IDEX.Extend.substr(26,32),IDEX.ALUOp1,IDEX.ALUOp0);
		if(func == 0){
			EXMEM.ALUResult="";
		} // AND OR 구현 ,16진수 반환
		EXMEM.Data2 = IDEX.Data2;

		if(IDEX.RegDst == 0) EXMEM.Rd = IDEX.Rt;
		else EXMEM.Rd = IDEX.Rd;
}
void MEM(EX_MEM EXMEM, MEM_WB &MEMWB){
		MEMWB.MemtoReg = EXMEM.MemtoReg;
		MEMWB.RegWrite = EXMEM.RegWrite;

		MEMWB.Data="";// lw sw 구현
		MEMWB.Address = EXMEM.ALUResult;
		MEMWB.Rd = EXMEM.Rd;

}
void WB(MEM_WB MEMWB,Reg &reg){
	string data;
	if(MEMWB.MemtoReg == false) 
		data = MEMWB.Data;
	else
		data = MEMWB.Address;
	
	if(MEMWB.RegWrite == true){
		reg.Regi[BintoDec(MEMWB.Rd)] = data;
	}
}

int main(void){
	Reg reg();
	ControlSignal constolSignal;

	IF_ID IFID;
	ID_EX IDEX;
	EX_MEM EXMEM;
	MEM_WB MEMWB;

	string op = "add";
	int rs = 1,rt = 2,rd = 3;
	string str = encode(op,rs,rt,rd);
	cout << str << '\n';
	int x = BintoDec(str);
	cout << x << '\n';
	string h = DectoHex(x);
	cout << h << '\n';
	cout << HextoBin(h) << endl;

	// int cnt=0;
	// while(cnt<5){
	// 	if(file.eof() == false) cnt = 0;
	// 	cnt++;
	// }

	return 0;
}