#pragma once
#include "stdafx.h"
#include "ISingleInstence.h"
#include "CommandProcessor.h"
#include "Pane.h"

class Vivado : public ISingleInstence
{
	static Vivado *instence;
	CommandProcessor *commandProcessor;
	Pane *pane;

	Vivado();
	void ShowGateOptions(long selectedIndex);
	void ShowAddedGates(long selectedIndex, const list<Gate *> &gates);
	void ShowPorts(long selectedIndex, const bool &isConstantAvailable = true, const bool &showConstantFromPane = false);
	void ShowPortsFromGate(long selectedIndex, Gate *gate);
	Gate *SelectOneGate();
	Port *SelectOnePort(const bool &isConstantAvailable = true, const bool &showConstantFromPane = false);
	Port *SelectOnePortFromGate(Gate *gate);
	SingleInstence(Vivado);

public:
	static Vivado *GetInstence();

	void AddGate();
	void ViewGates();
	void DeleteGate();
	
	void ConnectPort();
	void DisConnectPort();

	void Watch();
	void View(const bool &exe = false);

	static void DestroyInstence();
	~Vivado();
};