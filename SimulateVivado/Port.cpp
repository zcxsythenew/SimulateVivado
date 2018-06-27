#include "Port.h"
#include "Gate.h"
#include "NetPort.h"

int Port::idGenerator = 0;

Port::Port(const PortType &type, Gate *gate) : type(type), gate(gate), connectedNetPort(nullptr), id(idGenerator)
{
	idGenerator++;
}

int Port::GetID() const
{
	return id;
}

NetPort *Port::GetConnectedNetPort() const
{
	return connectedNetPort;
}

Gate *Port::GetGate() const
{
	return gate;
}

void Port::SetConnectedNetPort(NetPort *netPort)
{
	connectedNetPort = netPort;
}

PortType Port::GetPortType() const
{
	return type;
}
