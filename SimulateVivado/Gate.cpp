#include "Gate.h"

int Gate::idGenerator = 0;

Gate::Gate(const GateType &type) : type(type), id(idGenerator)
{
	idGenerator++;
}

int Gate::GetID() const
{
	return id;
}

GateType Gate::GetType() const
{
	return type;
}

const list<Port*> &Gate::GetInputPorts() const
{
	return inputPorts;
}

const list<Port*> &Gate::GetOutputPorts() const
{
	return outputPorts;
}

void Gate::Dispose()
{
	for (Port *&i : inputPorts)
	{
		delete i;
	}
	inputPorts.clear();
	for (Port *&i : outputPorts)
	{
		delete i;
	}
	outputPorts.clear();
}

Gate::~Gate()
{
	Dispose();
}