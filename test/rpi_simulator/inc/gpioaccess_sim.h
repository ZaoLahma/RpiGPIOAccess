#ifndef HEADER_GPIOACCESS_SIM
#define HEADER_GPIOACCESS_SIM

#include "../../../inc/gpioaccess_if.h"

#include <cstdint>
#include "sharedmemory.h"

struct ConnectPortsInfoS
{
	uint8_t fromPort;
	uint8_t fromBoard;
	uint8_t toPort;
	uint8_t toBoard;
};

class GPIOAccessSim : public GPIOAccessIf
{
	public:
	GPIOAccessSim();
	~GPIOAccessSim();

	int exportPort(const unsigned int portNo);
	int unexportPort(const unsigned int portNo);

	int setPortDirection(const unsigned int portNo, const GPIODirection direction);

	int setPortValue(const unsigned int portNo, const unsigned int value);
	int getPortValue(const unsigned int portNo);

	bool GPIOAccessSim_connectPorts(const ConnectPortsInfoS& connectPortsInfo);

	private:

	std::string GPIOAccessSim_getPortName(const unsigned int portNo,
			                                    const unsigned int boardNo);

	struct ConnectedToS
	{
		uint8_t connectedTo;
		uint8_t boardNo;
	};

	struct PortInfoS
	{
		GPIODirection direction;
		uint8_t portValue;
		ConnectedToS connectedToStruct;
	};

	const std::string PORT_NAME_BASE;

	unsigned int boardNo;

	typedef std::map<std::string, PortInfoS*> NameToPortInfoMapT;
	typedef std::map<unsigned int, PortInfoS*> PortNoToPortInfoMapT;

	NameToPortInfoMapT portNameToPortInfoMap;
	PortNoToPortInfoMapT portNoToPortInfoMap;

	SharedMemory shMIf;
};

#endif
