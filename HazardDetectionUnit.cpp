#ifndef HAZARDDETECTIONUNIT_INCLUDED
#define HAZARDDETECTIONUNIT_INCLUDED
#include "PipelineRegisters.cpp"

class HazardDetectionUnit
{
public:
	bool PCWrite;
	bool IFIDWrite;
	bool stall;
	std::bitset<5> Rs;
	std::bitset<5> Rt;

	HazardDetectionUnit()
	{
		this->PCWrite = 1;
		this->IFIDWrite = 1;
		this->stall = 1; // 1일때는 control 0일때 nop
		this->Rs.reset();
		this->Rt.reset();
	}

	void detect(IF_ID &IFID, ID_EX IDEX)
	{
		for(int i = 0;i<5;i++) Rs[i] = IFID.Inst[i+21];
		for(int i = 0;i<5;i++) Rt[i] = IFID.Inst[i+16];
		if (IDEX.MemRead == 1)
		{
			if (IDEX.Rt == Rs || IDEX.Rt == Rt)
			{
				this->PCWrite = 0;
				this->IFIDWrite = 0;
				this->stall = 0;
			}
		}
		else
		{
			this->PCWrite = 1;
			this->IFIDWrite = 1;
			this->stall = 1;
		}
	}
};
#endif