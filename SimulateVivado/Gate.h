#pragma once
#include "stdafx.h"
#include "Port.h"
#include "Net.h"
#include "IDisposable.h"
#include "IUniqueID.h"
class Gate : public IDisposable
{
	friend class Pane;
	static int idGenerator;
protected:
	list<Port *> inputPorts;
	list<Port *> outputPorts;
	GateType type;
	int id;
public:
	Gate(const GateType &type);
	int GetID() const;
	GateType GetType() const;
	virtual bool GenerateOutput(int times) = 0;
	const list<Port *> &GetInputPorts() const;
	const list<Port *> &GetOutputPorts() const;
	void Dispose();
	virtual ~Gate() = 0;
};