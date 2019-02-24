////////////////////////////////////////////////////////////
// PC-8801 PPI Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Ppi.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Ppi

////////////////////////////////////////////////////////////
// attribute

// port data

uint8_t CPC88Ppi::m_abtPortData[3];

// port mode

int CPC88Ppi::m_anPortMode[2][2];

// port direction

bool CPC88Ppi::m_abPortDir[2][4];

// updated

bool CPC88Ppi::m_bUpdate;

// ATN activate calback function

CPC88Ppi::ATNActivateCallback CPC88Ppi::m_pATNActivateCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Ppi::CPC88Ppi() {
	m_pATNActivateCallback = NULL;
}

// destructor

CPC88Ppi::~CPC88Ppi() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Ppi::Initialize() {
}

// reset

void CPC88Ppi::Reset() {
	m_abtPortData[0] = m_abtPortData[1] = m_abtPortData[2] = 0;
	for (int nSide = SIDE_MAIN; nSide <= SIDE_SUB; nSide++) {
		m_anPortMode[nSide][0] = m_anPortMode[nSide][1] = 0;
		m_abPortDir[nSide][0] = m_abPortDir[nSide][1] =
			m_abPortDir[nSide][2] = m_abPortDir[nSide][2] = true;
	}
	m_bUpdate = true;
}
