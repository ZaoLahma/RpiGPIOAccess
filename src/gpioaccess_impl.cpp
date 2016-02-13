#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <chrono>

#include "../inc/gpioaccess_impl.h"

GPIOAccessImpl::GPIOAccessImpl()
{
	//Export all usable ports and set direction to in.
	for(unsigned int i = 0; i < 40; ++i)
	{
		if(-1 != boardToBcm(i))
		{
			exportPort(i);
			std::chrono::milliseconds ms(50);
			std::this_thread::sleep_for(ms);
			setPortDirection(i, GPIODirection::IN);
			
			PortInfoS portInfo;
			portInfo.direction = GPIODirection::IN;
			portInfo.portValueFd = getPortFileDescriptor(i);
			portInfoMap[i] = portInfo;
		}
	}
}

GPIOAccessImpl::~GPIOAccessImpl()
{
	PortNoToPortInfoMapT::iterator portInfoIter = portInfoMap.begin();

	for( ; portInfoIter != portInfoMap.end(); ++portInfoIter)
	{
		close(portInfoIter->second.portValueFd);		
		unexportPort(portInfoIter->first);
	}

	portInfoMap.clear();
}

int GPIOAccessImpl::setPortDirection(const unsigned int portNo, const GPIODirection direction)
{
	const int bcmPortNo = boardToBcm(portNo);
	
	if(bcmPortNo < 0)
	{
		return -1;		
	}
	
	std::string setPortDirectionString = "/sys/class/gpio/gpio";
	setPortDirectionString += std::to_string(bcmPortNo);
	setPortDirectionString += "/direction";
	
	const int setPortDirectionFd = open(setPortDirectionString.c_str(), O_WRONLY | O_SYNC);
	
	if(-1 == setPortDirectionFd)
	{
		return -1;
	}
	
	std::string portDirectionString = portDirectionToString(direction);
	
	write(setPortDirectionFd, portDirectionString.c_str(), portDirectionString.length());
	
	close(setPortDirectionFd);
	
	return 0;	
}

int GPIOAccessImpl::setPortValue(const unsigned int portNo, const unsigned int value)
{
	std::string valueString = std::to_string(value);
	
	PortNoToPortInfoMapT::iterator portInfoIter = portInfoMap.find(portNo);
	
	write(portInfoIter->second.portValueFd, valueString.c_str(), valueString.length());

	return 0;	
}

int GPIOAccessImpl::getPortValue(const unsigned int portNo)
{
	char valChar[2];
	
	PortNoToPortInfoMapT::iterator portInfoIter = portInfoMap.find(portNo);
	
	read(portInfoIter->second.portValueFd, valChar, 1);
	
	valChar[1] = '\0';

	const unsigned int value = std::stoi(valChar);
	
	return value;
}

//Private

int GPIOAccessImpl::exportPort(const unsigned int portNo)
{
	const int bcmPortNo = boardToBcm(portNo);

	if(bcmPortNo < 0)
	{
		return -1;
	}

	const std::string exportCommandString = "/sys/class/gpio/export";

	int exportPortFd = -1;

	exportPortFd = open(exportCommandString.c_str(), O_WRONLY|O_SYNC);

	if(-1 == exportPortFd)
	{
		return -1;
	}

	std::string exportPortNo = std::to_string(bcmPortNo);

	write(exportPortFd, exportPortNo.c_str(), exportPortNo.length());

	close(exportPortFd);

	return 0;
}

int GPIOAccessImpl::unexportPort(const unsigned int portNo)
{
	const int bcmPortNo = boardToBcm(portNo);

	if(bcmPortNo < 0)
	{
		return -1;
	}

	const std::string unexportCommandString = "/sys/class/gpio/unexport";

	int unexportPortFd = -1;

	unexportPortFd = open(unexportCommandString.c_str(), O_WRONLY|O_SYNC);

	if(-1 == unexportPortFd)
	{
		return -1;
	}

	std::string unexportPortNo = std::to_string(bcmPortNo);

	write(unexportPortFd, unexportPortNo.c_str(), unexportPortNo.length());

	close(unexportPortFd);

	return 0;
}

int GPIOAccessImpl::getPortFileDescriptor(const unsigned int portNo)
{
	const int bcmPortNo = boardToBcm(portNo);

	if(bcmPortNo < 0)
	{
		return -1;
	}

	std::string valueString = "/sys/class/gpio/gpio";
	valueString += std::to_string(bcmPortNo);
	valueString += "/value";

	const int fd = open(valueString.c_str(), O_RDWR | O_SYNC);

	if(fd < 0)
	{
		return -1;
	}

	return fd;
}
