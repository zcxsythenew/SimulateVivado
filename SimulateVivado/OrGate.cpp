#include "OrGate.h"

OrGate::OrGate() : FlexibleGate(Or)
{

}

bool OrGate::GenerateOutput(int times)
{
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			return true;
		}
	}
	return false;
}


OrGate::~OrGate()
{
}
