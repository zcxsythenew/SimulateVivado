#pragma once
#include "stdafx.h"
#include "Gate.h"

class XorGate : public Gate
{
public:
	XorGate();

	bool GenerateOutput(int times);

	~XorGate();
};