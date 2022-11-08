#include "pipelineRegisters.cpp"

class forwardingUnit{
	public:
		int forwardA;
		int forwardB;

		forwardingUnit(){
			forwardA = 0;
			forwardB = 0;
		}
		void setForward(ID_EX IDEX,EX_MEM EXMEM, MEM_WB MEMWB){
			if(IDEX.Rs == EXMEM.Rd) forwardA = 2;
			if(IDEX.Rs == MEMWB.Rd) forwardA = 1;
			if(IDEX.Rt == EXMEM.Rd) forwardB = 2;
			if(IDEX.Rt == MEMWB.Rd) forwardB = 1;
		}
		int getForwardA(){
			return forwardA;
		}
		int getForwardB(){
			return forwardB;
		}	
};
