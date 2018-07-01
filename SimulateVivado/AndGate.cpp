#include "AndGate.h"

AndGate::AndGate() : FlexibleGate(And)
{

}

bool AndGate::GenerateOutput(int times)
{
	bool val = true;
	for (Port *&i : inputPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		if (!i->GetConnectedNetPort()->net->GetValue(times + 1))
		{
			val = false;
		}
	}
	return val;
}

AndGate::~AndGate()
{

}