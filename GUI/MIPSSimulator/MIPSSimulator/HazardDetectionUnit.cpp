#ifndef HAZARDDETECTIONUNIT_INCLUDED
#define HAZARDDETECTIONUNIT_INCLUDED
#include "PipelineRegisters.cpp"

class HazardDetectionUnit
{
public:
	bool PCWrite;
	bool IFIDWrite;
	bool notStall;
	std::bitset<6> oper;
	std::bitset<5> Rs;
	std::bitset<5> Rt;

	HazardDetectionUnit()
	{
		this->PCWrite = 1;
		this->IFIDWrite = 1;
		this->notStall = 1; // 1일때는 control 0일때 nop
		this->oper.reset();
		this->Rs.reset();
		this->Rt.reset();
	}

	void detect(IF_ID &IFID, ID_EX IDEX, EX_MEM EXMEM)
	{
		for (int i = 0; i < 6; i++){
			oper[i] = IFID.Inst[i + 26];
		}
		for (int i = 0; i < 5; i++){
			Rs[i] = IFID.Inst[i + 21];
		}
		for (int i = 0; i < 5; i++){
			Rt[i] = IFID.Inst[i + 16];
		}
		this->PCWrite = 1;
		this->IFIDWrite = 1;
		this->notStall = 1;
		// BEQ을 수행하려는 데 IDEX의 RegWrite값이 1이고, IDEX의 rd field가 유효하다면
		if(oper == OP_BEQ && IDEX.RegWrite == 1 && IDEX.Rd != 0){
			// 이 때, IDEX의 rd가 수행하려는 BEQ의 rs 혹은 rt 필드인 경우 스톨
			if (IDEX.Rd == Rs || IDEX.Rd == Rt)
			{
				this->PCWrite = 0;
				this->IFIDWrite = 0;
				this->notStall = 0;
			}
		}
		// IDEX의 MemRead값이 1인 경우. 즉,  lw를 수행하는 경우
		if (IDEX.MemRead == 1)
		{
			// 그런데 IDEX의 rt가 새로 수행하려는 다른 움직임의 rs 혹은 rt면 스톨
			if (IDEX.Rt == Rs || IDEX.Rt == Rt)
			{
				this->PCWrite = 0;
				this->IFIDWrite = 0;
				this->notStall = 0;
			}
		}
		if (EXMEM.MemRead == 1)
		// EXMEM에의 rd값이 새로 수행하려는 다른 움직임의 rs 혹은 rt인 경우에도 스톨. 
		{
			if (EXMEM.Rd == Rs || EXMEM.Rd == Rt)
			{
				this->PCWrite = 0;
				this->IFIDWrite = 0;
				this->notStall = 0;
			}
		}
	}
};
#endif
