////////////////////////////////////////////////////////////
// Parallel Device Emulator
//
// Written by Manuke

#ifndef ParallelDevice_DEFINED
#define ParallelDevice_DEFINED

////////////////////////////////////////////////////////////
// declare

class CParallelDevice;

////////////////////////////////////////////////////////////
// declaration of CParallelDevice

class CParallelDevice {
// attribute
public:
	// get device id
	virtual std::string GetDeviceID() const = 0;

// create & destroy
public:
	// default constructor
	CParallelDevice();
	// destructor
	virtual ~CParallelDevice();

// initialize
public:
	// initialize at first
	virtual void Initialize() = 0;
	// reset
	virtual void Reset() = 0;

// communication
public:
	// is busy
	virtual bool IsBusy() = 0;
	// set strobe(negative logic)
	virtual void SetStrobe(bool bNStrobe) = 0;
	// output data
	virtual void SetData(uint8_t btData) = 0;

// implementation
public:
	// is pause mode
	virtual bool IsPause() = 0;
	// set pause mode
	virtual void SetPause(bool bPause) = 0;
	// is pending mode
	virtual bool IsPending() = 0;
	// set pending mode
	virtual void SetPending(bool bPending) = 0;
	// flush data
	virtual void Flush() = 0;
	// idle process
	virtual void OnIdle(int nMilliSecond) = 0;
};

#endif // ParallelDevice_DEFINED
