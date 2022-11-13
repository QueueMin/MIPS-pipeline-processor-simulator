#include "PipelineRegisters.cpp"

class HazardDetectionUnit
{
public:
	bool PCWrite;
	bool IFIDWrite;
	bool stool;
	std::bitset<5> Rs;
	std::bitset<5> Rd;

	HazardDetectionUnit()
	{
		this->PCWrite = 0;
		this->IFIDWrite = 0;
		this->stool = 0;
		this->Rs.reset();
		this->Rd.reset();
	}

	void detect(IF_ID &IFID, ID_EX IDEX)
	{
		if (IDEX.MemRead == 1)
		{
			if (IDEX.Rt == IFID.Rs || IDEX.Rt == IFID.Rt)
			{
				this->PCWrite = 0;
				this->IFIDWrite = 0;
				this->stool = 0;
			}
		}
		else
		{
			this->PCWrite = 1;
			this->IFIDWrite = 1;
			this->stool = 1;
		}
	}
};