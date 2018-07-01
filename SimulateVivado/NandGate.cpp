#include "NandGate.h"

NandGate::NandGate() : FlexibleGate(Nand)
{

}

bool NandGate::GenerateOutput(int times)
{
	bool val = false;
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (!i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			val = true;
		}
	}
	return val;
}

NandGate::~NandGate()
{

}