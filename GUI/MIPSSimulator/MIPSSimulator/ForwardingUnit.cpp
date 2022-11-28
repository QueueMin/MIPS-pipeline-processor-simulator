#ifndef FORWARDINGUNIT_INCLUDED
#define FORWARDINGUNIT_INCLUDED
#include "PipelineRegisters.cpp"
#include <bitset>

class ForwardingUnit
{
public:
	int forwardA;
  int forwardB;
	std::bitset<32> EXMEMData;
	std::bitset<32> MEMWBData;

	ForwardingUnit()
	{
		forwardA = 0;
        forwardB = 0;
		EXMEMData = 0;
		MEMWBData = 0;
	}
    void setForward(ID_EX IDEX, EX_MEM EXMEM, MEM_WB MEMWB)
    {
        forwardA = 0;
        forwardB = 0;
        EXMEMData = 0;
        MEMWBData = 0;
        if(IDEX.Rs != 0){// MEMWB먼저 비교하고 EXMEM을 비교해 최근의 forwarding 값을 가져옴
			if (MEMWB.RegWrite == 1 && IDEX.Rs == MEMWB.Rd)
				forwardA = 1;
			if (EXMEM.RegWrite == 1 && IDEX.Rs == EXMEM.Rd)
				forwardA = 2;
		}
		if(IDEX.Rt != 0){
			if (MEMWB.RegWrite == 1 && IDEX.Rt == MEMWB.Rd)
				forwardB = 1;
			if (EXMEM.RegWrite == 1 && IDEX.Rt == EXMEM.Rd)
				forwardB = 2;
		}
    }
	int getForwardA()
	{
		return forwardA;
	}
	int getForwardB()
	{
		return forwardB;
	}
};

#endif
