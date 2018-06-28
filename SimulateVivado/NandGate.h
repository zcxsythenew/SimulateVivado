#pragma once
#include "stdafx.h"
#include "FlexibleGate.h"
class NandGate : public FlexibleGate
{
public:
	NandGate();

	bool GenerateOutput(int times);

	virtual ~NandGate();
};