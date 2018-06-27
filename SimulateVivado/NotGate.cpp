#include "NotGate.h"

NotGate::NotGate() : Gate(Not)
{
	Port *port = new Port(output, this);
	outputPorts.push_back(port);
	port = new Port(input, this);
	inputPorts.push_back(port);
}

bool NotGate::GenerateOutput(int times)
{
	if (inputPorts.front()->GetConnectedNetPort() == nullptr)
	{
		throw NetDisconnectedException();
	}
	else
	{
		return !inputPorts.front()->GetConnectedNetPort()->net->GetValue(times + 1);
	}
}

NotGate::~NotGate()
{
}
