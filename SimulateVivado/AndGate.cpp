#include "AndGate.h"

AndGate::AndGate() : FlexibleGate(And)
{

}

bool AndGate::GenerateOutput(int times)
{
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (!i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			return false;
		}
	}
	return true;
}

AndGate::~AndGate()
{
}
