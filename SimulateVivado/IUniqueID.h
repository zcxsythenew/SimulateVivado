#pragma once
#include "stdafx.h"

interface IUniqueID
{
public:
	virtual int GetID() const = 0;
	virtual ~IUniqueID() = 0;
};