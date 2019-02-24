////////////////////////////////////////////////////////////
// PC-8801 Calendar Control Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "PC88Calendar.h"

////////////////////////////////////////////////////////////
// implementation of CPC88Calendar

////////////////////////////////////////////////////////////
// attribute

// base clock

int CPC88Calendar::m_nBaseClock;

// counter for calendar prosessing

int CPC88Calendar::m_nCalendarCounter;

// counter max value for calendar prosessing(1s)

int CPC88Calendar::m_nCalendarCounterMax;

// date/time data

uint8_t CPC88Calendar::m_abtDateTime[6];

// date/time data ratch

uint8_t CPC88Calendar::m_abtDateTimeRatch[6+1];

// second

int CPC88Calendar::m_nSecond;

// minute

int CPC88Calendar::m_nMinute;

// hour

int CPC88Calendar::m_nHour;

// day

int CPC88Calendar::m_nDay;

// week-day

int CPC88Calendar::m_nWDay;

// month

int CPC88Calendar::m_nMonth;

// month

int CPC88Calendar::m_nYear;

// leap year

bool CPC88Calendar::m_bLeapYear;

// last day of month

int CPC88Calendar::m_anDayLast[12+1];

// calendar IC mode

int CPC88Calendar::m_nCalendarMode;

// calendar IC command

int CPC88Calendar::m_nCalendarCommand;

// calendar IC data output

bool CPC88Calendar::m_bCalendarDataOut;

// calendar IC data input

bool CPC88Calendar::m_bCalendarDataIn;

// calendar IC strobe

bool CPC88Calendar::m_bCalendarStrobe;

// calendar IC shift

bool CPC88Calendar::m_bCalendarShift;

// check bit

int CPC88Calendar::m_nCheckBit;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPC88Calendar::CPC88Calendar() {
}

// destructor

CPC88Calendar::~CPC88Calendar() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPC88Calendar::Initialize() {
	m_nBaseClock = 4;
	m_anDayLast[0] = 0;
	m_anDayLast[1] = 31;
	m_anDayLast[2] = 28;
	m_anDayLast[3] = 31;
	m_anDayLast[4] = 30;
	m_anDayLast[5] = 31;
	m_anDayLast[6] = 30;
	m_anDayLast[7] = 31;
	m_anDayLast[8] = 31;
	m_anDayLast[9] = 30;
	m_anDayLast[10] = 31;
	m_anDayLast[11] = 30;
	m_anDayLast[12] = 31;
	SetYear(0);
	SetMonth(1);
	SetDay(1);
	SetWDay(0);
	SetHour(0);
	SetMinute(0);
	SetSecond(0);
}

// reset

void CPC88Calendar::Reset() {
	m_nCalendarCounterMax = m_nCalendarCounter = m_nBaseClock*1000*1000;
	m_abtDateTimeRatch[6] = 0;
	m_nCalendarMode = MODE_COMMAND;
	m_nCalendarCommand = 0;
	m_bCalendarDataOut = false;
	m_bCalendarDataIn = false;
	m_bCalendarStrobe = false;
	m_bCalendarShift = false;
	m_nCheckBit = 48;
}

////////////////////////////////////////////////////////////
// operation

	// increment clendar

void CPC88Calendar::IncCanendar() {
	int nSecond = m_nSecond+1;
	if (nSecond >= 60) {
		nSecond = 0;
		int nMinute = m_nMinute+1;
		if (nMinute >= 60) {
			nMinute = 0;
			int nHour = m_nHour+1;
			if (nHour >= 24) {
				nHour = 0;
				int nWDay = (m_nWDay+1)%7;
				int nDay = m_nDay+1;
				if (nDay > m_anDayLast[m_nMonth]) {
					nDay = 1;
					int nMonth = m_nMonth+1;
					if (nMonth > 12) {
						nMonth = 1;
						int nYear = (m_nYear+1)%100;
						SetYear(nYear);
					}
					SetMonth(nMonth);
				}
				SetDay(nDay);
				SetWDay(nWDay);
			}
			SetHour(nHour);
		}
		SetMinute(nMinute);
	}
	SetSecond(nSecond);
}
