////////////////////////////////////////////////////////////
// PC-8801 OPNA Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Opna.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Opna

////////////////////////////////////////////////////////////
// attribute

// base clock

int CPC88Opna::m_nBaseClock;

// status

uint8_t CPC88Opna::m_btStatus;

// address

int CPC88Opna::m_nAddress;

// CH3 mode

int CPC88Opna::m_nCh3Mode;

// FM synthesis pre-scaler

int CPC88Opna::m_nPreScalerFM;

// PSG synthesis pre-scaler

int CPC88Opna::m_nPreScalerPSG;

// timer A active

bool CPC88Opna::m_bTimerAAcvive;

// timer A set flag

bool CPC88Opna::m_bTimerASetFlag;

// timer A value

int CPC88Opna::m_nTimerAValue;

// timer A counter

int CPC88Opna::m_nTimerACounter;

// timer A counter max value

int CPC88Opna::m_nTimerACounterMax;

// timer B active

bool CPC88Opna::m_bTimerBAcvive;

// timer B set flag

bool CPC88Opna::m_bTimerBSetFlag;

// timer B value

int CPC88Opna::m_nTimerBValue;

// timer B counter

int CPC88Opna::m_nTimerBCounter;

// timer B counter max value

int CPC88Opna::m_nTimerBCounterMax;

// OPNA interrupt requested

bool CPC88Opna::m_bOpnaInterruptRequest;

// interrupt vector change callback function

CPC88Opna::IntVectChangeCallback CPC88Opna::m_pIntVectChangeCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Opna::CPC88Opna() {
	m_pIntVectChangeCallback = NULL;
}

// destructor

CPC88Opna::~CPC88Opna() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Opna::Initialize() {
	m_nBaseClock = 4;
}

// reset

void CPC88Opna::Reset() {
	m_btStatus = 0;
	m_nAddress = 0;
	m_nCh3Mode = 0;
	m_nPreScalerFM = 6;
	m_nPreScalerPSG = 4;
	m_bTimerAAcvive = m_bTimerASetFlag = false;
	m_nTimerAValue = 0;
	SetTimerACounterMax();
	m_nTimerACounter = m_nTimerACounterMax;
	m_bTimerBAcvive = m_bTimerBSetFlag = false;
	m_nTimerBValue = 0;
	SetTimerBCounterMax();
	m_nTimerBCounter = m_nTimerBCounterMax;
	m_bOpnaInterruptRequest = false;
}

////////////////////////////////////////////////////////////
// operation

// timer A overflow

void CPC88Opna::TimerAOverFlow() {
	if (m_bTimerASetFlag) {
		if ((m_btStatus & 0x01) == 0) {
			UpdateInterruptRequest(true);
		}
		m_btStatus |= 0x01;
	}
	do {
		m_nTimerACounter += m_nTimerACounterMax;
	} while (m_nTimerACounter <= 0);
}

// timer B overflow

void CPC88Opna::TimerBOverFlow() {
	if (m_bTimerBSetFlag) {
		if ((m_btStatus & 0x02) == 0) {
			UpdateInterruptRequest(true);
		}
		m_btStatus |= 0x02;
	}
	do {
		m_nTimerBCounter += m_nTimerBCounterMax;
	} while (m_nTimerBCounter <= 0);
}

// set timer A counter max value

void CPC88Opna::SetTimerACounterMax() {
	m_nTimerACounterMax = 12*(1024-m_nTimerAValue)*m_nPreScalerFM*
		(m_nBaseClock/4);
}

// set timer B counter max value

void CPC88Opna::SetTimerBCounterMax() {
	m_nTimerBCounterMax = 192*(256-m_nTimerBValue)*m_nPreScalerFM*
		(m_nBaseClock/4);
}

// set pre-scaler

void CPC88Opna::SetPreScaler(int nPreScalerFM, int nPreScalerPSG) {
	m_nTimerACounter = (m_nTimerACounter*nPreScalerFM)/m_nPreScalerFM;
	m_nTimerBCounter = (m_nTimerBCounter*nPreScalerFM)/m_nPreScalerFM;
	m_nPreScalerFM = nPreScalerFM;
	m_nPreScalerPSG = nPreScalerPSG;
	SetTimerACounterMax();
	SetTimerBCounterMax();
}

// read data

uint8_t CPC88Opna::ReadData() {
	return 0xFF;
}

// write address

void CPC88Opna::WriteAddress(uint8_t btAddress) {
	m_nAddress = btAddress;
	switch (m_nAddress) {
	case 0x2D:
		SetPreScaler(6, 4);
		break;
	case 0x2E:
		SetPreScaler(3, 2);
		break;
	case 0x2F:
		SetPreScaler(2, 1);
		break;
	}
}

// write data

void CPC88Opna::WriteData(uint8_t btData) {
	switch (m_nAddress) {
	case 0x24:
		m_nTimerAValue = (m_nTimerAValue & 0x0003) | (btData << 2);
		SetTimerACounterMax();
		break;
	case 0x25:
		m_nTimerAValue = (m_nTimerAValue & 0x03FC) | (btData & 0x03);
		SetTimerACounterMax();
		break;
	case 0x26:
		m_nTimerBValue = btData;
		SetTimerBCounterMax();
		break;
	case 0x27:
		if ((btData & 0x01) != 0) {
			if (!m_bTimerAAcvive) {
				m_bTimerAAcvive = true;
				m_nTimerACounter = m_nTimerACounterMax;
			}
		} else {
			m_bTimerAAcvive = false;
		}
		if ((btData & 0x02) != 0) {
			if (!m_bTimerBAcvive) {
				m_bTimerBAcvive = true;
				m_nTimerBCounter = m_nTimerBCounterMax;
			}
		} else {
			m_bTimerBAcvive = false;
		}
		m_bTimerASetFlag = ((btData & 0x04) != 0);
		m_bTimerBSetFlag = ((btData & 0x08) != 0);
		if ((btData & 0x10) != 0) {
			m_btStatus &= 0xFE;
		}
		if ((btData & 0x20) != 0) {
			m_btStatus &= 0xFD;
		}
		m_nCh3Mode = (btData >> 6) & 0x03;
		break;
	}
}
