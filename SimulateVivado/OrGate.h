#pragma once
#include "stdafx.h"
#include "FlexibleGate.h"
class OrGate : public FlexibleGate
{
public:
	OrGate();
	bool GenerateOutput(int times);
	~OrGate();
};

