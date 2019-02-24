////////////////////////////////////////////////////////////
// PC-8801 USART Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Usart.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Usart

////////////////////////////////////////////////////////////
// attribute

// USART attribute

// base clock

int CPC88Usart::m_nBaseClock;

// load counter

int CPC88Usart::m_nUsartLoadCounter;

// save counter

int CPC88Usart::m_nUsartSaveCounter;

// USART counter max value

int CPC88Usart::m_nUsartCounterMax;

// setting mode instruction

bool CPC88Usart::m_bModeInstruction;

// baud rate

int CPC88Usart::m_nBaudRate;

// character length

int CPC88Usart::m_nCharLength;

// enable parity

bool CPC88Usart::m_bParityEnable;

// even parity

bool CPC88Usart::m_bParityEven;

// stop bit length

int CPC88Usart::m_nStopBit;

// enable sending

bool CPC88Usart::m_bSendEnable;

// enable receiving

bool CPC88Usart::m_nReceiveEnable;

// DTR

bool CPC88Usart::m_bDTR;

// RTS

bool CPC88Usart::m_bRTS;

// send break character

bool CPC88Usart::m_bSendBreakChar;

// sync character hunt

bool CPC88Usart::m_bSyncCharHunt;

// parity error

bool CPC88Usart::m_bParityError;

// overrun error

bool CPC88Usart::m_bOverrunError;

// framing error

bool CPC88Usart::m_bFramingError;

// receive interrupt requested

bool CPC88Usart::m_bReceiveInterruptRequest;

// delay at data reading

int CPC88Usart::m_nDataReadDelay;

// other

// channel mode

int CPC88Usart::m_nChannelMode;

// space carrier

bool CPC88Usart::m_bSpaceCarrier;

// moter-on

bool CPC88Usart::m_bMotorOn;

// skip character on moter-off

bool CPC88Usart::m_bSkipCharOnMotorOff;

// tape image

// tape image for loading

CTapeImage CPC88Usart::m_timageLoad;

// tape image for saving

CTapeImage CPC88Usart::m_timageSave;

// interrupt vector change callback function

CPC88Usart::IntVectChangeCallback CPC88Usart::m_pIntVectChangeCallback;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Usart::CPC88Usart() {
	m_pIntVectChangeCallback = NULL;
}

// destructor

CPC88Usart::~CPC88Usart() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Usart::Initialize() {
	m_nBaseClock = 4;
	m_bSkipCharOnMotorOff = true;
}

// reset

void CPC88Usart::Reset() {
	m_nUsartCounterMax = m_nUsartLoadCounter = m_nUsartSaveCounter =
		(1000*1000*m_nBaseClock)/4800;
	m_bModeInstruction = true;
	m_nBaudRate = BAUDRATE_X1;
	m_nCharLength = 8;
	m_bParityEnable = false;
	m_bParityEven = true;
	m_nStopBit = STOPBIT_2;
	m_bSendEnable = m_nReceiveEnable = false;
	m_bDTR = m_bRTS = false;
	m_bSendBreakChar = false;
	m_bSyncCharHunt = false;
	m_bParityError = m_bOverrunError = m_bFramingError = false;
	m_bReceiveInterruptRequest = false;
	m_nDataReadDelay = 0;
	m_nChannelMode = CHANNEL_CMT600;
	m_bMotorOn = false;
}
