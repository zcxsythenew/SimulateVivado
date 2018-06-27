#include "Net.h"
#include "Gate.h"

int Net::idGenerator = 0;

Net::Net() : id(idGenerator)
{
	idGenerator++;
}

bool Net::HasError() const noexcept
{
	bool detectedOutput = false;
	for (auto &i : linkedPorts)
	{
		if (i->type == output || i->type == VCC || i->type == GND)
		{
			if (detectedOutput)
			{
				return true;
			}
			else
			{
				detectedOutput = true;
			}
		}
	}
	return !detectedOutput;
}

bool Net::GetValue(int times) const
{
	bool detectedOutput = false;
	for (auto &i : linkedPorts)
	{
		if (i->type == output || i->type == VCC || i->type == GND)
		{
			if (detectedOutput)
			{
				throw NetConflictException();
			}
			else
			{
				detectedOutput = true;
			}
		}
	}
	if (!detectedOutput)
	{
		throw NetDisconnectedException();
	}
	else if (times > 10000)
	{
		throw IterationTooMuchException();
	}
	else
	{
		for (NetPort *i : linkedPorts)
		{
			if (i->type == output)
			{
				return i->port->GetGate()->GenerateOutput(times + 1);
			}
			else if (i->type == VCC)
			{
				return true;
			}
			else if (i->type == GND)
			{
				return false;
			}
		}
		throw NetDisconnectedException();
	}
}

NetPort *Net::CreateNetPort(const PortType &portType, Port *p)
{
	NetPort *port = new NetPort(portType, this, p);
	linkedPorts.push_back(port);
	return port;
}

void Net::AppendNetPort(NetPort *netPort, const bool &remove)
{
	if (remove)
	{
		netPort->net->RemoveNetPort(netPort, false);
	}
	netPort->net = this;
	linkedPorts.push_back(netPort);
}

void Net::RemoveNetPort(NetPort *netPort, const bool &dispose)
{
	if (dispose)
	{
		delete netPort;
	}
	for (list<NetPort *>::iterator i = linkedPorts.begin(); i != linkedPorts.end(); i++)
	{
		if (*i == netPort)
		{
			linkedPorts.erase(i);
			break;
		}
	}
}

int Net::GetID() const
{
	return id;
}

void Net::Dispose()
{
	for (list<NetPort *>::iterator i = linkedPorts.begin(); i != linkedPorts.end(); i++)
	{
		delete *i;
	}
	linkedPorts.clear();
}

Net::~Net()
{
	Dispose();
}

const char *NetConflictException::what() const noexcept
{
	return "Some net has more than one output.";
}

const char * NetDisconnectedException::what() const noexcept
{
	return "The diagram is incomplete.";
}

const char * IterationTooMuchException::what() const noexcept
{
	return "Too many iterations. Note that this program does not support timing.";
}
