#pragma once
#include "stdafx.h"
#include "IUniqueID.h"

class Gate;
struct NetPort;

class Port : public IUniqueID
{
	PortType type;
	Gate *gate;
	NetPort *connectedNetPort;
	static int idGenerator;
	int id;

public:
	Port(const PortType &type = negative, Gate *gate = nullptr);
	int GetID() const;
	NetPort *GetConnectedNetPort() const;
	Gate *GetGate() const;
	void SetConnectedNetPort(NetPort *netPort);
	PortType GetPortType() const;
};