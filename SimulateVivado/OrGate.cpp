#include "OrGate.h"

OrGate::OrGate() : FlexibleGate(Or)
{

}

bool OrGate::GenerateOutput(int times)
{
	bool val = false;
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			val = true;
		}
	}
	return val;
}


OrGate::~OrGate()
{
}
