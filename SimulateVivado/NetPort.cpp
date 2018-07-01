#include "NetPort.h"
#include "Net.h"

NetPort::NetPort(const PortType &type, Net *net, Port *port) : type(type), net(net), port(port)
{

}
