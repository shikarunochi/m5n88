////////////////////////////////////////////////////////////
// PC-8801 Timer Emulator
//
// Written by Manuke

#ifndef PC88Timer_DEFINED
#define PC88Timer_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Timer;

////////////////////////////////////////////////////////////
// declaration of CPC88Timer

class CPC88Timer {
// typedef
public:
	// type of interrupt vector change callback function
	typedef void (*IntVectChangeCallback)();

// enum
public:
	// interrupt bit
	enum {
		INTERRUPT_BIT = 0x04
	};

// attribute
protected:
	// base clock
	static int m_nBaseClock;
	// timer counter
	static int m_nTimerCounter;
	// timer counter max value
	static int m_nTimerCounterMax;
	// timer interrupt requested
	static bool m_bTimerInterruptRequest;

	// interrupt vector change callback function
	static IntVectChangeCallback m_pIntVectChangeCallback;

public:
	// get base clock
	static int GetBaseClock() {
		return m_nBaseClock;
	}
	// set base clock
	static void SetBaseClock(int nBaseClock) {
		m_nBaseClock = nBaseClock;
	}
	// is timer interrupt requested
	static bool IsTimerInterruptRequest() {
		return m_bTimerInterruptRequest;
	}
	// set timer interrupt requested
	static void SetTimerInterruptRequest(bool bTimerInterruptRequest) {
		m_bTimerInterruptRequest = bTimerInterruptRequest;
	}

	// set interrupt vector change callback function
	static void SetIntVectChangeCallback(
		IntVectChangeCallback pIntVectChangeCallback)
	{
		m_pIntVectChangeCallback = pIntVectChangeCallback;
	}

// create & destroy
public:
	// default constructor
	CPC88Timer();
	// destructor
	~CPC88Timer();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
protected:
	// update interrupt request
	static void UpdateInterruptRequest(bool bTimerInterruptRequest) {
		if (bTimerInterruptRequest != m_bTimerInterruptRequest) {
			m_bTimerInterruptRequest = bTimerInterruptRequest;
			m_pIntVectChangeCallback();
		}
	}

public:
	// pass clock
	static void PassClock(int nClock) {
		if ((m_nTimerCounter -= nClock) <= 0) {
			UpdateInterruptRequest(true);
			do {
				m_nTimerCounter += m_nTimerCounterMax;
			} while (m_nTimerCounter <= 0);
		}
	}
};

#endif // PC88Timer_DEFINED
