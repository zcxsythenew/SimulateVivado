#pragma once
#include "stdafx.h"
#include "FlexibleGate.h"
class NorGate : public FlexibleGate
{
public:
	NorGate();

	bool GenerateOutput(int times);

	virtual ~NorGate();
};