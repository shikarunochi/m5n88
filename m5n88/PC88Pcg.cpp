////////////////////////////////////////////////////////////
// PCG-8800 Emulator
//
// Written by Manuke
//
// Assisted by apaslothy
// (PCG-8800 Support)

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Pcg.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Pcg

////////////////////////////////////////////////////////////
// attribute

// PCG RAM

uint8_t CPC88Pcg::m_abtPcgRam[2][1024];

// PCG bank

int CPC88Pcg::m_anPcgBank[2];

// PCG displaying

bool CPC88Pcg::m_abPcgDisplay[2];
// PCG updated

bool CPC88Pcg::m_abPcgUpdate[2];
// PCG address

int CPC88Pcg::m_nPcgAddress;
// PCG data

uint8_t CPC88Pcg::m_btPcgData;

// PCG data setting bank

int CPC88Pcg::m_nPcgSetBank;

// PCG sound port status

bool CPC88Pcg::m_abPcgSoundPortStatus[3];

// interval timer(8253) counter setting mode

int CPC88Pcg::m_anITimerMode[3];

// interval timer(8253) counter

int CPC88Pcg::m_anITimerCounter[3];

// interval timer(8253) counter setting flag

bool CPC88Pcg::m_abITimerMsb[3];

// interval timer(8253) counter BCD

bool CPC88Pcg::m_abITimerBcd[3];

// current text font ROM get callback function

CPC88Pcg::CurTextFontRomGetCallback CPC88Pcg::m_pCurTextFontRomGetCallback;

// PCG sound output callback function

CPC88Pcg::PcgSoundOutputCallback CPC88Pcg::m_pPcgSoundOutputCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Pcg::CPC88Pcg() {
	m_pCurTextFontRomGetCallback = NULL;
	m_pPcgSoundOutputCallback = NULL;
}

// destructor

CPC88Pcg::~CPC88Pcg() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Pcg::Initialize() {
	memset(m_abtPcgRam, 0, sizeof(m_abtPcgRam));
}

// reset

void CPC88Pcg::Reset() {
	// PCG
	for (int nPcgBank = 0; nPcgBank < 2; nPcgBank++) {
		for (int nCode = 0; nCode < 128; nCode++) {
			for (int y = 0; y < 8; y++) {
				m_abtPcgRam[nPcgBank][nCode*8+y] =
					m_pCurTextFontRomGetCallback(1024+nCode*8+y);
			}
		}
		m_anPcgBank[nPcgBank] = 0;
		m_abPcgUpdate[nPcgBank] = true;
	}
	m_abPcgDisplay[0] = false;
	m_abPcgDisplay[1] = true;
	m_nPcgAddress = 0;
	m_btPcgData = 0;
	m_nPcgSetBank = 0;
	// interval timer
	for (int nChannel = 0; nChannel < 3; nChannel++) {
		m_abPcgSoundPortStatus[nChannel] = false;
		m_anITimerCounter[nChannel] = 1;
		m_abITimerMsb[nChannel] = false;
		m_abITimerBcd[nChannel] = false;
	}
	// PCG sound off
	m_pPcgSoundOutputCallback(0, -1);
	m_pPcgSoundOutputCallback(1, -1);
	m_pPcgSoundOutputCallback(2, -1);
}

////////////////////////////////////////////////////////////
// operation

// PCG port write

void CPC88Pcg::WritePcgPort(int nAddress, uint8_t btData) {
	int nPos;
	switch (nAddress) {
	case 0x00:
		m_btPcgData = btData;
		break;
	case 0x01:
		m_nPcgAddress = (m_nPcgAddress & 0xFF00) | btData;
		break;
	case 0x02:
		m_nPcgAddress = (m_nPcgAddress & 0x00FF) | (((int)btData) << 8);
		if (((btData & 0x08) != 0) != m_abPcgSoundPortStatus[0]) {
			m_abPcgSoundPortStatus[0] = !m_abPcgSoundPortStatus[0];
			m_pPcgSoundOutputCallback(0, GetITimerCounterValue(0));
		}
		if (((btData & 0x40) != 0) != m_abPcgSoundPortStatus[1]) {
			m_abPcgSoundPortStatus[1] = !m_abPcgSoundPortStatus[1];
			m_pPcgSoundOutputCallback(1, GetITimerCounterValue(1));
		}
		if (((btData & 0x80) != 0) != m_abPcgSoundPortStatus[2]) {
			m_abPcgSoundPortStatus[2] = !m_abPcgSoundPortStatus[2];
			m_pPcgSoundOutputCallback(2, GetITimerCounterValue(2));
		}
		break;
	case 0x03:
		for (nPos = 0; nPos < 2; nPos++) {
			int nShift = 2*nPos,
				nMode = btData >> nShift;
			bool bDisp = ((nMode & 2) != 0);
			int nBank = (nMode & 1);
			if (((m_anPcgBank[nPos] != nBank) && bDisp) ||
				(bDisp != m_abPcgDisplay[nPos]))
			{
				SetPcgUpdate(nPos, true);
			}
			m_abPcgDisplay[nPos] = bDisp;
			m_anPcgBank[nPos] = nBank;
		}
		m_nPcgSetBank = (btData & 0x10)? 1: 0;
		return;
	}
	if ((m_nPcgAddress & 0x1000) != 0) {
		int nPcgAdress = m_nPcgAddress & 0x03FF;
		uint8_t btWrite = ((m_nPcgAddress & 0x2000) != 0)?
			m_pCurTextFontRomGetCallback(1024+nPcgAdress):
			m_btPcgData;
		m_abtPcgRam[m_nPcgSetBank][nPcgAdress] = btWrite;
		for (nPos = 0; nPos < 2; nPos++) {
			if (m_abPcgDisplay[nPos] &&
				(m_anPcgBank[nPos] == m_nPcgSetBank))
			{
				SetPcgUpdate(nPos, true);
			}
		}
	}
}

// interval timer(8253) port write

void CPC88Pcg::WriteITimerPort(int nAddress, uint8_t btData) {
	int nChannel;
	switch(nAddress) {
	case 0x00: // channel 1 counter setting
	case 0x01: // channel 2
	case 0x02: // channel 3
		nChannel = nAddress;
		switch(m_anITimerMode[nChannel]) {
		case 1:
			m_anITimerCounter[nChannel]  = btData;
			break;
		case 2:
			m_anITimerCounter[nChannel]  = ((int)btData) << 8;
		case 3:
			if (m_abITimerMsb[nChannel]) {
				m_anITimerCounter[nChannel]  =
					(m_anITimerCounter[nChannel] & 0x00FF) |
						(((int)btData) << 8);
			} else {
				m_anITimerCounter[nChannel]  =
					(m_anITimerCounter[nChannel] & 0xFF00) |
						btData;
			}
			m_abITimerMsb[nChannel] = !m_abITimerMsb[nChannel];
			break;
		}
		m_pPcgSoundOutputCallback(
			nChannel,
			GetITimerCounterValue(nChannel));
		break;
	case 0x03: // mode setting
		nChannel = (btData >> 6) & 3;
		if (nChannel < 3) {
			m_anITimerMode[nChannel] = (btData >> 4) & 3;
			m_abITimerMsb[nChannel] = false;
			m_abITimerBcd[nChannel] = ((btData & 0x01) != 0);
		}
		break;
	}
}
