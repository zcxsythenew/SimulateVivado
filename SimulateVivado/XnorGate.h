#pragma once
#include "stdafx.h"
#include "Gate.h"

class XnorGate : public Gate
{
public:
	XnorGate();

	bool GenerateOutput(int times);

	~XnorGate();
};