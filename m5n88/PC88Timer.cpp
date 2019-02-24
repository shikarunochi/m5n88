////////////////////////////////////////////////////////////
// PC-8801 Timer Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Timer.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Timer

////////////////////////////////////////////////////////////
// attribute

// base clock

int CPC88Timer::m_nBaseClock;

// timer counter

int CPC88Timer::m_nTimerCounter;

// timer counter max value

int CPC88Timer::m_nTimerCounterMax;

// timer interrupt requested

bool CPC88Timer::m_bTimerInterruptRequest;

// interrupt vector change callback function

CPC88Timer::IntVectChangeCallback CPC88Timer::m_pIntVectChangeCallback;

////////////////////////////////////////////////////////////
// create & destroy

CPC88Timer::CPC88Timer() {
	m_pIntVectChangeCallback = NULL;
}

CPC88Timer::~CPC88Timer() {
}

////////////////////////////////////////////////////////////
// initialize

void CPC88Timer::Initialize() {
	m_nBaseClock = 4;
}

void CPC88Timer::Reset() {
	m_nTimerCounterMax = m_nTimerCounter = (1000*1000*m_nBaseClock)/600;
	m_bTimerInterruptRequest = false;
}
