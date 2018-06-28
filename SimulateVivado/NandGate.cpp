#include "NandGate.h"

NandGate::NandGate() : FlexibleGate(Nand)
{

}

bool NandGate::GenerateOutput(int times)
{
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (!i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			return true;
		}
	}
	return false;
}


NandGate::~NandGate()
{
}
