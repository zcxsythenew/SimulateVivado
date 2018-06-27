#pragma once
#include "stdafx.h"
#include "ISingleInstence.h"

class Vivado;

class CommandProcessor : public ISingleInstence
{
	static CommandProcessor *instence;
	Vivado *vivado;

	CommandProcessor();
	SingleInstence(CommandProcessor);

	// ����falseʱΪ��Ч����
	bool ParseCommand(const string &);
	void PrintFail(const string &);
public:
	static CommandProcessor *GetInstence();
	static void DestoryInstence();
	void SetVivado(Vivado *);
	void PrintWelcome();
	void PrintHints(const string &);
	void PrintHints();

	// ����falseʱ��ֹ����
	bool InputCommand();

	virtual ~CommandProcessor();
};

