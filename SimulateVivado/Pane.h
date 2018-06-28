#pragma once
#include "stdafx.h"
#include "IDisposable.h"
#include "Net.h"
#include "Gate.h"
#include "FlexibleGate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "NorGate.h"
#include "NandGate.h"
#include "XorGate.h"
#include "XnorGate.h"

class Pane : public IDisposable
{
	list<Net *> nets;
	list<Gate *> gates;
	list<Port *> constPorts;

	Net *CreateNet();
	void MergeNets(Net *dst, Net *src);

public:
	Pane();

	Gate *CreateGate(const GateType &gateType);
	void RemoveGate(Gate *gate);
	Port *CreateConstPort(const PortType &type);
	list<Port *> &GetConstPorts();
	bool Connect(Port *a, Port *b);
	bool DisConnect(Port *port);
	static Port *CreateInputPort(FlexibleGate *gate);
	list<Gate *> &GetGates();
	static list<Port *> GetInputPorts(const Gate *gate);
	static list<Port *> GetOutputPorts(const Gate *gate);
	bool Watch(Port *port);
	void View(const bool &exe = false);
	void Dispose();

	~Pane();
};

