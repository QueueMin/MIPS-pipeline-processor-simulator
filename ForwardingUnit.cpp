#ifndef FORWARDINGUNIT_INCLUDED
#define FORWARDINGUNIT_INCLUDED
#include "PipelineRegisters.cpp"
#include <bitset>

class ForwardingUnit
{
public:
	int forwardA;
    int forwardB;
	int BranchForwardA;
    int BranchForwardB;
    std::bitset<5> Rs;
    std::bitset<5> Rt;
	std::bitset<32> EXMEMData;
	std::bitset<32> MEMWBData;

	ForwardingUnit()
	{
		forwardA = 0;
        forwardB = 0;
        BranchForwardA = 0;
        BranchForwardB = 0;
		Rs = 0;
		Rt = 0;
		EXMEMData = 0;
		MEMWBData = 0;
	}
    void setForward(IF_ID IFID, ID_EX IDEX, EX_MEM EXMEM, MEM_WB MEMWB)
    {
        forwardA = 0;
        forwardB = 0;
        BranchForwardA = 0;
        BranchForwardB = 0;
        Rs = 0;
        Rt = 0;
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
			// branch Forwarding을 기존의 Unit에서 실행함
			// MEMWB먼저 비교하고 EXMEM을 비교해 최근의 forwarding 값을 가져옴
        for(int i = 0;i<5;i++) Rs[i] = IFID.Inst[i+21];
        for(int i = 0;i<5;i++) Rt[i] = IFID.Inst[i+16];
			if(Rs != 0){
				if (MEMWB.RegWrite == 1 && Rs == MEMWB.Rd)
					BranchForwardA = 1;
				if (EXMEM.RegWrite == 1 && Rs == EXMEM.Rd)
					BranchForwardA = 2;
			}
			if(Rt != 0){
				if (MEMWB.RegWrite == 1 && Rt == MEMWB.Rd)
					BranchForwardB = 1;
				if (EXMEM.RegWrite == 1 && Rt == EXMEM.Rd)
					BranchForwardB = 2;
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
