#ifndef FORWARDINGUNIT_INCLUDED
#define FORWARDINGUNIT_INCLUDED
#include "PipelineRegisters.cpp"

class ForwardingUnit
{
public:
	int forwardA;
    int forwardB;

	ForwardingUnit()
	{
		forwardA = 0;
        forwardB = 0;
	}
    void setForward(ID_EX IDEX, EX_MEM EXMEM, MEM_WB MEMWB)
    {
        if (EXMEM.RegWrite == 1 && IDEX.Rs == EXMEM.Rd)
            forwardA = 2;
        else if (MEMWB.RegWrite == 1 && IDEX.Rs == MEMWB.Rd)
            forwardA = 1;
        if (EXMEM.RegWrite == 1 && IDEX.Rt == EXMEM.Rd)
            forwardB = 2;
        else if (MEMWB.RegWrite == 1 && IDEX.Rt == MEMWB.Rd)
            forwardB = 1;
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
