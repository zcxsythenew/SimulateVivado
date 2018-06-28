#pragma once
#include <iostream>
#include <string>
#include <list>
#include <exception>
#include <sstream>
#include <typeinfo>

#define interface class

#define SingleInstence(T) \
	T(const T &); \
	T &operator=(const T &)

#define KNOWN_GATES 7

using namespace std;

enum PortType
{
	negative, 
	input,
	output,
	VCC,
	GND
};

enum GateType
{
	And,
	Or,
	Not,
	Nand,
	Nor,
	Xor,
	Xnor
};

const string str[] = { "And Gate","Or Gate","Not Gate","Nand Gate","Nor Gate","Xor Gate","Xnor Gate" };

int _getch();
void HideCursor();
void ResetCursor();
void ShowWhite();
void ShowBlack();