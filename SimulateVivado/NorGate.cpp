#include "NorGate.h"

NorGate::NorGate() : FlexibleGate(Nor)
{
}

bool NorGate::GenerateOutput(int times)
{
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			return false;
		}
	}
	return true;
}


NorGate::~NorGate()
{
}
