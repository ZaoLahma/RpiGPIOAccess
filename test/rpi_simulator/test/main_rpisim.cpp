#include <thread>
#include <chrono>
#include <iostream>

#include "../inc/gpioaccess_sim.h"
int main(void)
{
	GPIOAccessSim gpioAccess;
	GPIOAccessSim gpioAccess_1;

	gpioAccess.exportPort(7);

	gpioAccess_1.exportPort(10);

	ConnectPortsInfoS connectPortsInfo;
	connectPortsInfo.fromBoard = 0;
	connectPortsInfo.fromPort = 7;
	connectPortsInfo.toBoard = 0;
	connectPortsInfo.toPort = 10;

	if(true != gpioAccess.GPIOAccessSim_connectPorts(connectPortsInfo))
	{
		std::cout<<"Test failed to connect ports"<<std::endl;
		return -1;
	}

	gpioAccess.setPortDirection(7, GPIODirection::OUT);
	gpioAccess_1.setPortDirection(10, GPIODirection::IN);

	gpioAccess.setPortValue(7, 1);

	if(1 != gpioAccess_1.getPortValue(10))
	{
		std::cout<<"Test verified data NOK"<<std::endl;
		return -1;
	}

	std::cout<<"Test finished OK"<<std::endl;

	return 0;
}

/*
int main(void)
{
	PRINT_TO_FILE(true);

	GPIOAccessSim gpioAccess;

	gpioAccess.exportPort(3);
	gpioAccess.exportPort(5);
	gpioAccess.exportPort(7);
	gpioAccess.exportPort(10);

	ConnectPortsInfoS connectPortsInfo;
	connectPortsInfo.fromBoard = 0;
	connectPortsInfo.fromPort = 7;
	connectPortsInfo.toBoard = 1;
	connectPortsInfo.toPort = 10;

	if(true != gpioAccess.GPIOAccessSim_connectPorts(connectPortsInfo))
	{
		return -1;
	}

	std::chrono::milliseconds ms(200);
	std::this_thread::sleep_for(ms);

	gpioAccess.setPortDirection(3, GPIODirection::OUT);
	gpioAccess.setPortDirection(5, GPIODirection::OUT);
	gpioAccess.setPortDirection(7, GPIODirection::OUT);


	unsigned int noOfIterations = 10;
	while(noOfIterations != 0)
	{
		gpioAccess.setPortValue(5, 0);
		gpioAccess.setPortValue(3, 1);

		std::this_thread::sleep_for(ms);

		gpioAccess.setPortValue(3, 0);
		gpioAccess.setPortValue(5, 1);

		std::this_thread::sleep_for(ms);

		gpioAccess.setPortValue(5, 0);
		gpioAccess.setPortValue(7, 1);

		if(gpioAccess.getPortValue(7) != 1)
		{
			if(gpioAccess.getPortValue(10) != gpioAccess.getPortValue(7))
			{
				return -1;
			}

			return -1;
		}

		std::this_thread::sleep_for(ms);

		gpioAccess.setPortValue(7, 0);
		gpioAccess.setPortValue(5, 1);

		if(gpioAccess.getPortValue(10) != gpioAccess.getPortValue(7))
		{
			return -1;
		}

		std::this_thread::sleep_for(ms);

		noOfIterations--;
	}

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 1);
	gpioAccess.setPortValue(5, 1);
	gpioAccess.setPortValue(7, 1);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 1);
	gpioAccess.setPortValue(5, 1);
	gpioAccess.setPortValue(7, 1);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 1);
	gpioAccess.setPortValue(5, 1);
	gpioAccess.setPortValue(7, 1);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 1);
	gpioAccess.setPortValue(5, 1);
	gpioAccess.setPortValue(7, 1);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 1);
	gpioAccess.setPortValue(5, 1);
	gpioAccess.setPortValue(7, 1);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 1);
	gpioAccess.setPortValue(5, 1);
	gpioAccess.setPortValue(7, 1);

	std::this_thread::sleep_for(ms);

	gpioAccess.setPortValue(3, 0);
	gpioAccess.setPortValue(5, 0);
	gpioAccess.setPortValue(7, 0);

	std::this_thread::sleep_for(ms);

	//gpioAccess.unexportPort(3);
	//gpioAccess.unexportPort(5);
	//gpioAccess.unexportPort(7);

	return 0;
}
*/
