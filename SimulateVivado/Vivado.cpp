#include "Vivado.h"

Vivado *Vivado::instence = NULL;

Vivado::Vivado() : commandProcessor(CommandProcessor::GetInstence())
{
	pane = new Pane();
	commandProcessor->SetVivado(this);
	while (commandProcessor->InputCommand())
	{
		
	}
}

void Vivado::ShowGateOptions(long selectedIndex)
{
	for (long i = 0; i < KNOWN_GATES; i++)
	{
		if (i == selectedIndex)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << i << ". " << str[i] << endl;
	}
}

void Vivado::ShowAddedGates(long selectedIndex, const list<Gate *> &gates)
{
	list<Gate *>::const_iterator it = gates.begin();
	for (int i = 0; i < (signed long)gates.size(); i++, it++)
	{
		if (i == selectedIndex)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << (*it)->GetID() << ". " << str[((*it)->GetType())] << endl;
	}
}

void Vivado::ShowPorts(long selectedIndex, const bool &isConstantAvailable, const bool &showConstantFromPane)
{
	if (selectedIndex == 0)
	{
		ShowWhite();
	}
	else
	{
		ShowBlack();
	}
	cout << "1. <Choose from a gate> " << endl;
	if (isConstantAvailable)
	{
		if (selectedIndex == 1)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << "2. VCC" << endl;
		if (selectedIndex == 2)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << "3. GND" << endl;
	}
	if (showConstantFromPane)
	{
		list<Port *>::iterator it = pane->GetConstPorts().begin();
		for (long i = 1; i - 1 < (signed long)pane->GetConstPorts().size(); i++, it++)
		{
			if (i == selectedIndex)
			{
				ShowWhite();
			}
			else
			{
				ShowBlack();
			}
			cout << (i + 1) << ". " << ((*it)->GetPortType() == VCC ? "VCC #" : "GND #") << (*it)->GetID() << endl;
		}
	}
}

void Vivado::ShowPortsFromGate(long selectedIndex, Gate *gate)
{
	list<Port *>::const_iterator it = gate->GetInputPorts().begin();
	long i;
	for (i = 0; i < (signed long)gate->GetInputPorts().size(); i++, it++)
	{
		if (i == selectedIndex)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << (*it)->GetID() << ". " << "input" << endl;
	}
	it = gate->GetOutputPorts().begin();
	for (; i < (signed long)gate->GetOutputPorts().size() + (signed long)gate->GetInputPorts().size(); i++, it++)
	{
		if (i == selectedIndex)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << (*it)->GetID() << ". " << "output" << endl;
	}
	FlexibleGate *dgate = dynamic_cast<FlexibleGate *>(gate);
	if (dgate != nullptr)
	{
		if (i == selectedIndex)
		{
			ShowWhite();
		}
		else
		{
			ShowBlack();
		}
		cout << " <Create input port> " << endl;
	}
}

Gate *Vivado::SelectOneGate()
{
	HideCursor();

	long selection = 0;
	bool canContinue = true;
	int t;

	list<Gate *> &gates = pane->GetGates();
	if (gates.empty())
	{
		ShowWhite();
		cout << "No gates are added.";
		_getch();
		ResetCursor();
		cout << endl;
		cout << "\033[1A";
		cout << "                    ";
		cout << endl;
		cout << "\033[1A";
	}
	else
	{
		cout << "The added gates are listed below." << endl
			<< "Use direction keys to select a gate you want, or 'q' to cancel." << endl;
		ShowAddedGates(selection, gates);
		while (canContinue)
		{
			t = _getch();
			if (t == 27)
			{
				t = _getch();
				if (t == 91)
				{
					t = _getch();
					t -= 64;
				}
			}
			else if (t == 'q' || t == 'Q')
			{
				ResetCursor();
				return nullptr;
			}
			switch (t)
			{
			case 1: // up
			case 4: // left
				selection += gates.size();
				selection--;
				selection %= gates.size();
				cout << "\033[" << gates.size() << "A";
				ShowAddedGates(selection, gates);
				break;
			case 2: // down
			case 3: // right
				selection++;
				selection %= gates.size();
				cout << "\033[" << gates.size() << "A";
				ShowAddedGates(selection, gates);
				break;
			case '\n':
				canContinue = false;
				break;
			}
		}
		ResetCursor();
		for (list<Gate *>::iterator i = gates.begin(); true; i++)
		{
			if (selection == 0)
			{
				return *i;
			}
			else
			{
				selection--;
			}
		}
	}
	return nullptr;
}

Port *Vivado::SelectOnePort(const bool &isConstantAvailable, const bool &showConstantFromPane)
{
	HideCursor();

	long selection = 0;
	bool canContinue = true;
	int t;
	cout << "Choose from the following ports, or 'q' to cancel." << endl;
	ShowPorts(selection, isConstantAvailable, showConstantFromPane);
	while (canContinue)
	{
		t = _getch();
		if (t == 27)
		{
			t = _getch();
			if (t == 91)
			{
				t = _getch();
				t -= 64;
			}
		}
		else if (t == 'q' || t == 'Q')
		{
			ResetCursor();
			return nullptr;
		}
		switch (t)
		{
		case 1: // up
		case 4: // left
			if (isConstantAvailable || showConstantFromPane)
			{
				selection += (showConstantFromPane ? (1 + pane->GetConstPorts().size()) : 3);
				selection--;
				selection %= (showConstantFromPane ? (1 + pane->GetConstPorts().size()) : 3);
				cout << "\033[" << (showConstantFromPane ? (1 + pane->GetConstPorts().size()) : 3) << "A";
				ShowPorts(selection, isConstantAvailable, showConstantFromPane);
			}
			break;
		case 2: // down
		case 3: // right
			if (isConstantAvailable || showConstantFromPane)
			{
				selection++;
				selection %= (showConstantFromPane ? (1 + pane->GetConstPorts().size()) : 3);
				cout << "\033[" << (showConstantFromPane ? (1 + pane->GetConstPorts().size()) : 3) << "A";
				ShowPorts(selection, isConstantAvailable, showConstantFromPane);
			}
			break;
		case '\n':
			canContinue = false;
			break;
		}
	}
	ResetCursor();
	if (showConstantFromPane)
	{
		if (selection == 0)
		{
			return SelectOnePortFromGate(SelectOneGate());
		}
		else
		{
			selection--;
			for (list<Port *>::const_iterator i = pane->GetConstPorts().begin(); true; i++)
			{
				if (selection == 0)
				{
					return *i;
				}
				else
				{
					selection--;
				}
			}
		}
	}
	else
	{
		if (selection == 1)
		{
			return pane->CreateConstPort(VCC);
		}
		else if (selection == 2)
		{
			return pane->CreateConstPort(GND);
		}
		else
		{
			return SelectOnePortFromGate(SelectOneGate());
		}
	}
}

Port *Vivado::SelectOnePortFromGate(Gate *gate)
{
	if (gate == nullptr)
	{
		return nullptr;
	}
	HideCursor();

	long selection = 0;
	bool canContinue = true;
	int t;
	long total = gate->GetInputPorts().size() + gate->GetOutputPorts().size() + (dynamic_cast<FlexibleGate *>(gate) != nullptr);
	cout << "Choose from the following ports, or 'q' to cancel." << endl;
	ShowPortsFromGate(selection, gate);
	while (canContinue)
	{
		t = _getch();
		if (t == 27)
		{
			t = _getch();
			if (t == 91)
			{
				t = _getch();
				t -= 64;
			}
		}
		else if (t == 'q' || t == 'Q')
		{
			ResetCursor();
			return nullptr;
		}
		switch (t)
		{
		case 1: // up
		case 4: // left
			selection += total;
			selection--;
			selection %= total;
			cout << "\033[" << total << "A";
			ShowPortsFromGate(selection, gate);
			break;
		case 2: // down
		case 3: // right
			selection++;
			selection %= total;
			cout << "\033[" << total << "A";
			ShowPortsFromGate(selection, gate);
			break;
		case '\n':
			canContinue = false;
			break;
		}
	}
	ResetCursor();
	
	if (selection < (signed long)gate->GetInputPorts().size())
	{
		for (list<Port *>::const_iterator i = gate->GetInputPorts().begin(); true; i++)
		{
			if (selection == 0)
			{
				return *i;
			}
			else
			{
				selection--;
			}
		}
	}
	else if (selection - gate->GetInputPorts().size() < gate->GetOutputPorts().size())
	{
		selection -= gate->GetInputPorts().size();
		for (list<Port *>::const_iterator i = gate->GetOutputPorts().begin(); true; i++)
		{
			if (selection == 0)
			{
				return *i;
			}
			else
			{
				selection--;
			}
		}
	}
	else
	{
		return dynamic_cast<FlexibleGate *>(gate)->CreateInputPort();
	}
}

Vivado *Vivado::GetInstence()
{
	if (instence == NULL)
	{
		instence = new Vivado();
	}
	return instence;
}

void Vivado::AddGate()
{
	int selection = 0;
	bool canContinue = true;
	int t;
	HideCursor();
	cout << "Use direction keys to select the gate you want, or 'q' to cancel." << endl;
	ShowGateOptions(selection);
	while (canContinue)
	{
		t = _getch();
		if (t == 27)
		{
			t = _getch();
			if (t == 91)
			{
				t = _getch();
				t -= 64;
			}
		}
		else if (t == 'q' || t == 'Q')
		{
			ResetCursor();
			cout << "Canceled." << endl;
			return;
		}
		switch (t)
		{
		case 1: // up
		case 4: // left
			selection += KNOWN_GATES;
			selection--;
			selection %= KNOWN_GATES;
			cout << "\033[" << KNOWN_GATES << "A";
			ShowGateOptions(selection);
			break;
		case 2: // down
		case 3: // right
			selection++;
			selection %= KNOWN_GATES;
			cout << "\033[" << KNOWN_GATES << "A";
			ShowGateOptions(selection);
			break;
		case '\n':
			canContinue = false;
			break;
		}
	}
	ResetCursor();
	const Gate *const gate = pane->CreateGate((GateType)selection);
	cout << "$" << gate->GetID() << ": " << str[gate->GetType()] << " is created." << endl;
}

void Vivado::ViewGates()
{
	HideCursor();
	cout << "The gates are listed below." << endl;
	const list<Gate *> &gates = pane->GetGates();
	for (Gate *i : gates)
	{
		cout << i->GetID() << ". " << str[(i->GetType())] << endl;
	}
	ShowWhite();
	cout << "(END)";
	_getch();
	cout << endl;
	cout << "\033[1A";
	ResetCursor();
}

void Vivado::DeleteGate()
{
	cout << "You are going to remove a gate." << endl;
	Gate *gate = SelectOneGate();
	if (gate != nullptr)
	{
		pane->RemoveGate(gate);
	}
	else
	{
		cout << "Canceled." << endl;
	}
}

void Vivado::ConnectPort()
{
	cout << "Choose the first port from the below." << endl;
	Port *a = SelectOnePort();
	if (a != nullptr)
	{
		cout << "Choose the second port from the below." << endl;
		Port *b = SelectOnePort(a->GetPortType() != VCC && a->GetPortType() != GND);
		if (b != nullptr)
		{
			pane->Connect(a, b);
		}
		else
		{
			cout << "Canceled." << endl;
		}
	}
	else
	{
		cout << "Canceled." << endl;
	}
}

void Vivado::DisConnectPort()
{
	cout << "You are going to disconnect a port from a net." << endl;
	Port *port = SelectOnePort(false, true);
	if (port != nullptr)
	{
		if (pane->DisConnect(port))
		{
			cout << "Successfully disconnect port." << endl;
		}
		else
		{
			cout << "The port is not connected yet." << endl;
		}
		if (port->GetPortType() == VCC || port->GetPortType() == GND)
		{
			delete port;
			pane->GetConstPorts().remove(port);
		}
	}
	else
	{
		cout << "Canceled." << endl;
	}
}

void Vivado::Watch()
{
	cout << "You are going to run the diagram and watch a value of a port." << endl;
	Port *a = SelectOnePort(false);
	if (a == nullptr)
	{
		cout << "Canceled." << endl;
	}
	else
	{
		try
		{
			bool val = pane->Watch(a);
			cout << "Value: " << val << endl;
		}
		catch (exception &ex)
		{
			ShowWhite();
			cout << "ERROR";
			ResetCursor();
			cout << " " << ex.what() << endl;
		}
	}
}

void Vivado::View(const bool &exe)
{
	HideCursor();
	pane->View(exe);
	ShowWhite();
	cout << "(END)";
	_getch();
	cout << endl;
	cout << "\033[1A";
	ResetCursor();
}

Vivado::~Vivado()
{
	delete pane;
	CommandProcessor::DestoryInstence();
}

void Vivado::DestroyInstence()
{
	if (instence != NULL)
	{
		delete instence;
	}
	instence = NULL;
}
