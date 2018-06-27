#pragma once
#include "stdafx.h"

/*
 * ��ʹ�� IDisposable �ӿ�ʱ��
 * ˵������ཫ�������ָ����ڴ����⣬
 * �Ҹ����е����ݴ��Ӧ����ʹ��ָ�롣
 * ����ʹ�� IDisposable �ӿ�ʱ��
 * Ӧ�������⴦���ڴ����⡣
 */

interface IDisposable
{
public:
	virtual void Dispose() = 0;
	virtual ~IDisposable() = 0;
};