#pragma once
#include "stdafx.h"
#include "NetPort.h"
#include "IDisposable.h"
#include "IUniqueID.h"

class Net : public IDisposable, public IUniqueID
{
	friend class Pane;

	list<NetPort *> linkedPorts;

	int id;
	static int idGenerator;

public:
	Net();

	bool HasError() const noexcept;
	bool GetValue(int times) const;

	NetPort *CreateNetPort(const PortType &portType, Port *port);
	void AppendNetPort(NetPort *netPort, const bool &remove = true);
	void RemoveNetPort(NetPort *netPort, const bool &dispose = true);
	int GetID() const;

	void Dispose();
	~Net();
};

struct NetConflictException : public exception
{
	const char *what() const noexcept;
};

struct NetDisconnectedException : public exception
{
	const char *what() const noexcept;
};

struct IterationTooMuchException : public exception
{
	const char *what() const noexcept;
};