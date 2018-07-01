#pragma once
#include "stdafx.h"
#include "Gate.h"

class NotGate : public Gate
{
public:
	NotGate();

	bool GenerateOutput(int times);

	virtual ~NotGate();
};

