#ifndef LOCK_H
#define LOCK_H

#include <Windows.h>

namespace BookLibrary
{

// Lock is a simple class to implement RAII
// idiom to enter and leave critical section.

class Lock
{
public:
	
	// Constructor enters the critical section
	Lock(CRITICAL_SECTION& criticalSection);

	// Destructor automatically ensures that
	// the critical section is left.
	~Lock();

private:

	CRITICAL_SECTION&  _criticalSection;
};

Lock::Lock(CRITICAL_SECTION& criticalSection)
:_criticalSection(criticalSection)
{
	EnterCriticalSection(&criticalSection);
}

Lock::~Lock()
{
	LeaveCriticalSection(&_criticalSection);
}

}

#endif