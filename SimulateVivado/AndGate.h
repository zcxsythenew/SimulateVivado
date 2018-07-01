#pragma once
#include "stdafx.h"
#include "FlexibleGate.h"
class AndGate : public FlexibleGate
{
public:
	AndGate();

	bool GenerateOutput(int times);

	virtual ~AndGate();
};