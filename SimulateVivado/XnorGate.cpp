#include "XnorGate.h"

XnorGate::XnorGate() : Gate(Xnor)
{
	Port *port = new Port(output, this);
	outputPorts.push_back(port);
	port = new Port(input, this);
	inputPorts.push_back(port);
	port = new Port(input, this);
	inputPorts.push_back(port);
}

bool XnorGate::GenerateOutput(int times)
{
	if (inputPorts.front()->GetConnectedNetPort() == nullptr)
	{
		throw NetDisconnectedException();
	}
	else
	{
		if (inputPorts.back()->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		else
		{
			return !(inputPorts.front()->GetConnectedNetPort()->net->GetValue(times + 1) != inputPorts.back()->GetConnectedNetPort()->net->GetValue(times + 1));
		}
	}
}

XnorGate::~XnorGate()
{
}
