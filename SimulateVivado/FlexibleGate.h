#pragma once
#include "stdafx.h"
#include "Gate.h"

interface FlexibleGate : public Gate
{
	friend class Pane;
public:
	FlexibleGate(const GateType &type);
	virtual Port *CreateInputPort();
	virtual Port *GetOutputPort();
	virtual ~FlexibleGate() = 0;
};