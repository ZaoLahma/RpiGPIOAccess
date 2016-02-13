#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sys/mman.h>
#include <iostream>

#include "gpioaccess_sim.h"

GPIOAccessSim::GPIOAccessSim() :
PORT_NAME_BASE("port_"),
boardNo(0)
{
	const std::string portCtrl = "port_ctrl";

	ShmAreaInfo areaInfo = shMIf.allocateShM(portCtrl, sizeof(int));

	int* boardNoPtr = (int*)areaInfo.areaAddress;

	if(*boardNoPtr != 1 && boardNoPtr != 0)
	{
		*boardNoPtr = 0;
	}

	boardNo = *boardNoPtr;
	*boardNoPtr = *boardNoPtr + 1;

	const unsigned int portSize = sizeof(PortInfoS);

	for(unsigned int boardNoIndex = 0; boardNoIndex < 2; ++boardNoIndex)
	{
		for(unsigned int i = 0; i < 40; ++i)
		{
			const int bcmPortNo = boardToBcm(i);

			if(-1 != bcmPortNo)
			{
				std::string portName = GPIOAccessSim_getPortName(i, boardNoIndex);
				areaInfo = shMIf.allocateShM(portName, portSize);

				PortInfoS* portInfoPtr = (PortInfoS*)areaInfo.areaAddress;

				if(boardNo == 0)
				{
					portInfoPtr->connectedToStruct.connectedTo = i;
					portInfoPtr->connectedToStruct.boardNo = boardNoIndex;
					portInfoPtr->direction = GPIODirection::IN;
					portInfoPtr->portValue = 0;
				}
				portNameToPortInfoMap[portName] = portInfoPtr;
				portNoToPortInfoMap[i + boardNoIndex] = portInfoPtr;
			}
		}
	}
}

GPIOAccessSim::~GPIOAccessSim()
{
	NameToPortInfoMapT::iterator portIter = portNameToPortInfoMap.begin();

	shMIf.detachShM("port_ctrl");

	for( ; portIter != portNameToPortInfoMap.end(); ++portIter)
	{
		shMIf.detachShM(portIter->first);
	}

	portNameToPortInfoMap.clear();
}

int GPIOAccessSim::exportPort(const unsigned int portNo)
{
	exportedPorts.insert(portNo);

	return 0;
}

int GPIOAccessSim::unexportPort(const unsigned int portNo)
{
	exportedPorts.erase(portNo);

	return 0;
}

int GPIOAccessSim::setPortDirection(const unsigned int portNo, const GPIODirection direction)
{
	PortInfoS* portStructPtr = portNoToPortInfoMap.find(portNo)->second;

	portStructPtr->direction = direction;

	return 0;
}

int GPIOAccessSim::setPortValue(const unsigned int portNo, const unsigned int value)
{

	PortInfoS* portStructPtr = portNoToPortInfoMap.find(portNo)->second;

	portStructPtr->portValue = value;

	if(portStructPtr->connectedToStruct.connectedTo != portNo)
	{
		uint8_t otherPortNo = portStructPtr->connectedToStruct.connectedTo +
							  portStructPtr->connectedToStruct.boardNo;

		PortInfoS* connectedPortStructPtr = portNoToPortInfoMap.find(otherPortNo)->second;
		connectedPortStructPtr->portValue = portStructPtr->portValue;
	}

	return 0;
}

int GPIOAccessSim::getPortValue(const unsigned int portNo)
{
	PortInfoS* portStructPtr = portNoToPortInfoMap.find(portNo)->second;

	const unsigned int value = portStructPtr->portValue;

	return value;
}

bool GPIOAccessSim::GPIOAccessSim_connectPorts(const ConnectPortsInfoS& connectPortsInfo)
{

	PortInfoS* fromPortInfo = portNoToPortInfoMap.find(connectPortsInfo.fromPort)->second;
	PortInfoS* toPortInfo = portNoToPortInfoMap.find(connectPortsInfo.toPort)->second;

	fromPortInfo->connectedToStruct.boardNo = connectPortsInfo.toBoard;
	fromPortInfo->connectedToStruct.connectedTo = connectPortsInfo.toPort + connectPortsInfo.toBoard;
	toPortInfo->connectedToStruct.boardNo = connectPortsInfo.fromBoard;
	toPortInfo->connectedToStruct.connectedTo = connectPortsInfo.fromPort + connectPortsInfo.fromBoard;

	toPortInfo->portValue = fromPortInfo->portValue;

	return true;
}


std::string GPIOAccessSim::GPIOAccessSim_getPortName(const unsigned int portNo,
		                                                   const unsigned int boardNo)
{
	std::string retVal = "";

	retVal = PORT_NAME_BASE + std::to_string(boardNo) + "_" + std::to_string(portNo);

	return retVal;
}
