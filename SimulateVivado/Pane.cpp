#include "Pane.h"

Pane::Pane()
{
	
}

Net *Pane::CreateNet()
{
	Net *net = new Net();
	nets.push_back(net);
	return net;
}

void Pane::MergeNets(Net *dst, Net *src)
{
	list<NetPort *> tmplist;
	if (dst != src)
	{
		for (NetPort *&i : src->linkedPorts)
		{
			dst->AppendNetPort(i, false);
			tmplist.push_back(i);
		}
		for (NetPort *&i : tmplist)
		{
			src->RemoveNetPort(i, false);
		}
	}
}

Gate *Pane::CreateGate(const GateType &gateType)
{
	Gate *gate;
	switch (gateType)
	{
	case And:
		gate = new AndGate();
		break;
	case Or:
		gate = new OrGate();
		break;
	case Not:
		gate = new NotGate();
		break;
	case Nand:
		gate = new NandGate();
		break;
	case Nor:
		gate = new NorGate();
		break;
	case Xor:
		gate = new XorGate();
		break;
	case Xnor:
		gate = new XnorGate();
		break;
	}
	gates.push_back(gate);
	return gate;
}

void Pane::RemoveGate(Gate *gate)
{
	for (Port *i : gate->GetInputPorts())
	{
		DisConnect(i);
	}
	for (Port *i : gate->GetOutputPorts())
	{
		DisConnect(i);
	}
	delete gate;
	gates.remove(gate);
}

Port *Pane::CreateConstPort(const PortType & type)
{
	Port *port;
	if (type == VCC)
	{
		port = new Port(VCC);
	}
	else
	{
		port = new Port(GND);
	}
	constPorts.push_back(port);
	return port;
}

list<Port*> &Pane::GetConstPorts()
{
	return constPorts;
}

bool Pane::Connect(Port *a, Port *b)
{
	if (a->GetConnectedNetPort() == nullptr)
	{
		Net *net = CreateNet();
		NetPort *netPort = net->CreateNetPort(a->GetPortType(), a);
		a->SetConnectedNetPort(netPort);
	}
	if (b->GetConnectedNetPort() == nullptr)
	{
		Net *net = CreateNet();
		NetPort *netPort = net->CreateNetPort(b->GetPortType(), b);
		b->SetConnectedNetPort(netPort);
	}
	MergeNets(a->GetConnectedNetPort()->net, b->GetConnectedNetPort()->net);
	return true;
}

bool Pane::DisConnect(Port *port)
{
	NetPort *netPort = port->GetConnectedNetPort();
	if (netPort == nullptr)
	{
		return false;
	}
	else
	{
		netPort->net->RemoveNetPort(netPort);
		port->SetConnectedNetPort(nullptr);
		return true;
	}
}

Port *Pane::CreateInputPort(FlexibleGate *gate)
{
	Port *port = gate->CreateInputPort();
	return port;
}

list<Gate *> &Pane::GetGates()
{
	return gates;
}

list<Port *> Pane::GetInputPorts(const Gate *gate)
{
	return gate->inputPorts;
}

list<Port*> Pane::GetOutputPorts(const Gate *gate)
{
	return gate->outputPorts;
}

bool Pane::Watch(Port *port)
{
	if (port->GetPortType() == output)
	{
		return port->GetGate()->GenerateOutput(0);
	}
	else if (port->GetPortType() == VCC)
	{
		return true;
	}
	else if (port->GetPortType() == GND)
	{
		return false;
	}
	else
	{
		if (port->GetConnectedNetPort() == nullptr)
		{
			throw NetDisconnectedException();
		}
		else
		{
			return port->GetConnectedNetPort()->net->GetValue(0);
		}
	}
}

void Pane::View(const bool &exe)
{
	cout << "ID\tType\tNet";
	if (exe)
	{
		cout << "\tValue";
	}
	cout << endl;
	cout << "--Constant Ports--" << endl;
	for (Port *&i : constPorts)
	{
		if (i->GetConnectedNetPort() == nullptr)
		{
			cout << i->GetID() << '\t' << (i->GetPortType() == VCC ? "VCC" : "GND") << '\t' << '*';
			if (exe)
			{
				cout << "\t" << (i->GetPortType() == VCC);
			}
			cout << endl;
		}
		else
		{
			cout << i->GetID() << '\t' << (i->GetPortType() == VCC ? "VCC" : "GND") << '\t' << i->GetConnectedNetPort()->net->GetID();
			if (exe)
			{
				cout << "\t" << (i->GetPortType() == VCC);
			}
			cout << endl;
		}
	}
	cout << "--Normal Gates--" << endl;
	for (Gate *&i : gates)
	{
		cout << "Gate #" << i->GetID() << " - " << str[i->GetType()] << endl;
		for (Port *j : i->GetInputPorts())
		{
			if (j->GetConnectedNetPort() == nullptr)
			{
				cout << j->GetID() << '\t' << "input" << '\t' << '*';
				if (exe)
				{
					cout << "\t";
					try
					{
						if (j->GetPortType() == output)
						{
							cout << j->GetGate()->GenerateOutput(0);
						}
						else
						{
							cout << '*';
						}
					}
					catch (exception &)
					{
						cout << '*';
					}
				}
				cout << endl;
			}
			else
			{
				cout << j->GetID() << '\t' << "input" << '\t' << j->GetConnectedNetPort()->net->GetID();
				if (exe)
				{
					cout << "\t";
					try
					{
						if (j->GetPortType() == output)
						{
							cout << j->GetGate()->GenerateOutput(0);
						}
						else
						{
							cout << j->GetConnectedNetPort()->net->GetValue(0);
						}
					}
					catch (exception &)
					{
						cout << '*';
					}
				}
				cout << endl;
			}
		}
		for (Port *j : i->GetOutputPorts())
		{
			if (j->GetConnectedNetPort() == nullptr)
			{
				cout << j->GetID() << '\t' << "output" << '\t' << '*';
				if (exe)
				{
					cout << "\t";
					try
					{
						if (j->GetPortType() == output)
						{
							cout << j->GetGate()->GenerateOutput(0);
						}
						else
						{
							cout << '*';
						}
					}
					catch (exception &)
					{
						cout << '*';
					}
				}
				cout << endl;
			}
			else
			{
				cout << j->GetID() << '\t' << "output" << '\t' << j->GetConnectedNetPort()->net->GetID();
				if (exe)
				{
					cout << "\t";
					try
					{
						if (j->GetPortType() == output)
						{
							cout << j->GetGate()->GenerateOutput(0);
						}
						else
						{
							cout << j->GetConnectedNetPort()->net->GetValue(0);
						}
					}
					catch (exception &)
					{
						cout << '*';
					}
				}
				cout << endl;
			}
		}
	}
}

void Pane::Dispose()
{
	for (Net *&i : nets)
	{
		delete i;
	}
	nets.clear();
	for (Gate *&i : gates)
	{
		delete i;
	}
	gates.clear();
	for (Port *&i : constPorts)
	{
		delete i;
	}
	constPorts.clear();
}

Pane::~Pane()
{
	Dispose();
}