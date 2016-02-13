#ifndef HEADER_SHAREDMEMORY
#define HEADER_SHAREDMEMORY

#include <string>
#include <map>

struct ShmAreaInfo
{
	void* areaAddress;
	unsigned int areaSize;
	int areaFd;
};

typedef std::map<std::string, ShmAreaInfo> ShmAreaInfoMapT;

class SharedMemory
{
	public:
	~SharedMemory();

	ShmAreaInfo allocateShM(const std::string& areaName, const unsigned int areaSize);
	ShmAreaInfo attachShM(const std::string& areaName, const unsigned int areaSize);

	bool detachShM(const std::string& areaName);

	private:
	ShmAreaInfoMapT shmAreaInfoMap;
};

#endif
