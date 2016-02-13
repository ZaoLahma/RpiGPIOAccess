#ifndef HEADER_GPIOACCESS
#define HEADER_GPIOACCESS

#include <string>
#include <set>

enum GPIODirection
{
	IN,
	OUT
};

class GPIOAccessIf
{
	public:
	GPIOAccessIf();
	virtual ~GPIOAccessIf();
	
	virtual int setPortDirection(const unsigned int portNo, const GPIODirection direction) = 0;
	
	virtual int setPortValue(const unsigned int portNo, const unsigned int value) = 0;
	virtual int getPortValue(const unsigned int portNo) = 0;
	
		
	protected:
	
	std::set<int> exportedPorts;
	
	int boardToBcm(const unsigned int portNo);
	std::string portDirectionToString(const GPIODirection direction);
};

#endif
