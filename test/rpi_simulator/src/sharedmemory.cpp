#include "sharedmemory.h"

#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h> /* For O_* constants */
#include <unistd.h>


SharedMemory::~SharedMemory()
{
	shmAreaInfoMap.clear();
}

ShmAreaInfo SharedMemory::allocateShM(const std::string& areaName, const unsigned int areaSize)
{
	ShmAreaInfo retVal;
	retVal.areaAddress = NULL;
	retVal.areaSize = areaSize;
	retVal.areaFd = -1;

	retVal.areaFd = shm_open(areaName.c_str(), O_CREAT | O_RDWR, 0666);

	ftruncate(retVal.areaFd, retVal.areaSize);

	retVal.areaAddress = mmap(NULL,
			                  retVal.areaSize,
			                  PROT_READ | PROT_WRITE,
							  MAP_SHARED,
							  retVal.areaFd,
							  0);

	shmAreaInfoMap[areaName] = retVal;

	return retVal;
}

ShmAreaInfo SharedMemory::attachShM(const std::string& areaName, const unsigned int areaSize)
{

	ShmAreaInfoMapT::iterator areaIter = shmAreaInfoMap.find(areaName);

	if(shmAreaInfoMap.end() == areaIter)
	{
		ShmAreaInfo retVal;
		retVal.areaAddress = NULL;
		retVal.areaSize = areaSize;
		retVal.areaFd = -1;

		retVal.areaFd = shm_open(areaName.c_str(), O_RDWR, 0777);

		ftruncate(retVal.areaFd, retVal.areaSize);

		retVal.areaAddress = mmap(0,
				                  retVal.areaSize,
				                  PROT_READ | PROT_WRITE,
		                          MAP_SHARED,
								  retVal.areaFd,
								  0);

		munmap(retVal.areaAddress, retVal.areaSize);

		shmAreaInfoMap[areaName] = retVal;
	}

	return areaIter->second;
}

bool SharedMemory::detachShM(const std::string& areaName)
{
	ShmAreaInfoMapT::iterator areaIter = shmAreaInfoMap.find(areaName);

	bool retVal = false;

	if(shmAreaInfoMap.end() != areaIter)
	{
		retVal = true;

		shm_unlink(areaName.c_str());

		if(-1 == munmap(areaIter->second.areaAddress, areaIter->second.areaSize))
		{
			retVal = false;
		}

		close(areaIter->second.areaFd);
	}

	return retVal;
}
