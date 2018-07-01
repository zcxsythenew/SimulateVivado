#include "NorGate.h"

NorGate::NorGate() : FlexibleGate(Nor)
{

}

bool NorGate::GenerateOutput(int times)
{
	bool val = true;
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			val = false;
		}
	}
	return val;
}


NorGate::~NorGate()
{
}
