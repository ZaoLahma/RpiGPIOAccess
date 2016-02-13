#ifndef HEADER_GPIOACCESS_IMPL
#define HEADER_GPIOACCESS_IMPL

#include "./gpioaccess_if.h"

#include <map>

class GPIOAccessImpl : public GPIOAccessIf
{
	public:
	GPIOAccessImpl();
	~GPIOAccessImpl();

	int setPortDirection(const unsigned int portNo, const GPIODirection direction);

	int setPortValue(const unsigned int portNo, const unsigned int value);
	int getPortValue(const unsigned int portNo);

	private:
	int exportPort(const unsigned int portNo);
	int unexportPort(const unsigned int portNo);
	int getPortFileDescriptor(const unsigned int portNo);

	struct PortInfoS
	{
		int portValueFd;
		GPIODirection direction;
	};

	typedef std::map<unsigned int, PortInfoS> PortNoToPortInfoMapT;

	PortNoToPortInfoMapT portInfoMap;
};

#endif
