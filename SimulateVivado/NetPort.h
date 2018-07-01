#pragma once
#include "stdafx.h"
#include "Port.h"

class Net;
class Port;

struct NetPort
{
	PortType type;
	Net *net;
	Port *port;

	bool val;
	NetPort(const PortType &type = negative, Net *net = nullptr, Port *port = nullptr);
};