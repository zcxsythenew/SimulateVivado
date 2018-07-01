#include "FlexibleGate.h"

FlexibleGate::FlexibleGate(const GateType &type) : Gate(type)
{
	Port *outputPort = new Port(output, this);
	outputPorts.push_back(outputPort);
}

Port *FlexibleGate::CreateInputPort()
{
	Port *port = new Port(input, this);
	inputPorts.push_back(port);
	return port;
}

Port *FlexibleGate::GetOutputPort()
{
	return outputPorts.front();
}

FlexibleGate::~FlexibleGate()
{

}