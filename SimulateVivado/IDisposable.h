#pragma once
#include "stdafx.h"

/*
 * 当使用 IDisposable 接口时，
 * 说明这个类将处理大量指针和内存问题，
 * 且该类中的数据存放应尽量使用指针。
 * 当不使用 IDisposable 接口时，
 * 应尽量避免处理内存问题。
 */

interface IDisposable
{
public:
	virtual void Dispose() = 0;
	virtual ~IDisposable() = 0;
};