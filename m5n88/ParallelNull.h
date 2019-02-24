////////////////////////////////////////////////////////////
// Parallel Null Device Emulator
//
// Written by Manuke

#ifndef ParallelNull_DEFINED
#define ParallelNull_DEFINED

////////////////////////////////////////////////////////////
// declare

class CParallelNull;

////////////////////////////////////////////////////////////
// include

#include "ParallelDevice.h"

////////////////////////////////////////////////////////////
// declaration of CParallelNull

class CParallelNull :
	public CParallelDevice
{
// attribute
protected:
	// pause mode
	bool m_bPause;
	// pending mode
	bool m_bPending;

public:
	// get device id
	virtual std::string GetDeviceID() const;

// create & destroy
public:
	// default constructor
	CParallelNull();
	// destructor
	virtual ~CParallelNull();

// initialize
public:
	// initialize at first
	virtual void Initialize();
	// reset
	virtual void Reset();

// communication
public:
	// is busy
	virtual bool IsBusy();
	// set strobe(negative logic)
	virtual void SetStrobe(bool bNStrobe);
	// output data
	virtual void SetData(uint8_t btData);

// implementation
public:
	// is pause mode
	virtual bool IsPause();
	// set pause mode
	virtual void SetPause(bool bPause);
	// is pending mode
	virtual bool IsPending();
	// set pending mode
	virtual void SetPending(bool bPending);
	// flush data
	virtual void Flush();
	// idle process
	virtual void OnIdle(int nMilliSecond);
};

#endif // ParallelNull_DEFINED
