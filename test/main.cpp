#include <thread>
#include <chrono>

#include "../inc/gpioaccess_impl.h"

int main(void)
{
	GPIOAccessImpl gpioAccess;
	
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
		
		std::this_thread::sleep_for(ms);
		
		gpioAccess.setPortValue(7, 0);
		gpioAccess.setPortValue(5, 1);
		
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
