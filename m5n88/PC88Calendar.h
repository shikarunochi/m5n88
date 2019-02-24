////////////////////////////////////////////////////////////
// PC-8801 Calendar Control Emulator
//
// Written by Manuke

#ifndef PC88Calendar_DEFINED
#define PC88Calendar_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Calendar;

////////////////////////////////////////////////////////////
// declaration of CPC88Calendar

class CPC88Calendar {
// enum
public:
	// calendar IC mode
	enum {
		MODE_COMMAND      = 1,
		MODE_SHIFT_DATA40 = 2,
		MODE_SHIFT_DATA48 = 3
	};

// attribute
protected:
	// base clock
	static int m_nBaseClock;
	// counter for calendar prosessing
	static int m_nCalendarCounter;
	// counter max value for calendar prosessing(1s)
	static int m_nCalendarCounterMax;
	// date/time data
	static uint8_t m_abtDateTime[6];
	// date/time data ratch
	static uint8_t m_abtDateTimeRatch[6+1];
	// second
	static int m_nSecond;
	// minute
	static int m_nMinute;
	// hour
	static int m_nHour;
	// day
	static int m_nDay;
	// week-day
	static int m_nWDay;
	// month
	static int m_nMonth;
	// year
	static int m_nYear;
	// leap year
	static bool m_bLeapYear;
	// last day of month
	static int m_anDayLast[12+1];
	// calendar IC mode
	static int m_nCalendarMode;
	// calendar IC command
	static int m_nCalendarCommand;
	// calendar IC data output
	static bool m_bCalendarDataOut;
	// calendar IC data input
	static bool m_bCalendarDataIn;
	// calendar IC strobe
	static bool m_bCalendarStrobe;
	// calendar IC shift
	static bool m_bCalendarShift;
	// check bit
	static int m_nCheckBit;

public:
	// set base clock
	static void SetBaseClock(int nBaseClock) {
		m_nBaseClock = nBaseClock;
	}
	// set secnd
	static void SetSecond(int nSecond) {
		m_nSecond = nSecond;
		m_abtDateTime[0] = uint8_t((m_nSecond/10)*16+(m_nSecond%10));
	}
	// set minute
	static void SetMinute(int nMinute) {
		m_nMinute = nMinute;
		m_abtDateTime[1] = uint8_t((m_nMinute/10)*16+(m_nMinute%10));
	}
	// set hour
	static void SetHour(int nHour) {
		m_nHour = nHour;
		m_abtDateTime[2] = uint8_t((m_nHour/10)*16+(m_nHour%10));
	}
	// set day
	static void SetDay(int nDay) {
		m_nDay = nDay;
		m_abtDateTime[3] = uint8_t((m_nDay/10)*16+(m_nDay%10));
	}
	// set week-day
	static void SetWDay(int nWDay) {
		m_nWDay = nWDay;
		m_abtDateTime[4] = uint8_t((m_abtDateTime[4] & 0xF0)+m_nWDay);
	}
	// set month
	static void SetMonth(int nMonth) {
		m_nMonth = nMonth;
		m_abtDateTime[4] = uint8_t(m_nMonth*16+(m_abtDateTime[4] & 0x0F));
	}
	// set year
	static void SetYear(int nYear) {
		m_nYear = nYear;
		m_anDayLast[2] = ((m_nYear%4) == 0)? 29: 28;
		m_abtDateTime[5] = uint8_t((m_nYear/10)*16+(m_nYear%10));
	}
	// set calendar IC command
	static void SetCalendarCommand(int nCalendarCommand) {
		m_nCalendarCommand = nCalendarCommand;
	}
	// set calendar IC data output
	static void SetCalendarDataOut(bool bCalendarDataOut) {
		m_bCalendarDataOut = bCalendarDataOut;
	}
	// is calendar IC data input
	static bool IsCalendarDataIn() {
		return m_bCalendarDataIn;
	}

// create & destroy
public:
	// default constructor
	CPC88Calendar();
	// destructor
	~CPC88Calendar();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
public:
	// pass clock
	static void PassClock(int nClock) {
		if ((m_nCalendarCounter -= nClock) <= 0) {
			do {
				IncCanendar();
				m_nCalendarCounter += m_nCalendarCounterMax;
			} while (m_nCalendarCounter <= 0);
		}
	}
	// strobe
	static void SetCalendarStrobe(bool bCalendarStrobe) {
		if ((m_bCalendarStrobe != bCalendarStrobe) && bCalendarStrobe) {
			int nCommand = m_nCalendarCommand;
			if (nCommand == 7) {
				nCommand = 0x10 | m_abtDateTimeRatch[6];
			}
			switch (nCommand) {
			case 0x01:
			case 0x11:
				m_nCalendarMode = (nCommand == 0x01)?
					MODE_SHIFT_DATA40: MODE_SHIFT_DATA48;
				m_nCheckBit = 0;
				m_bCalendarDataIn = ((m_abtDateTimeRatch[0] & 0x01) != 0);
				break;
			case 0x02:
			case 0x12:
				SetSecond(
					(m_abtDateTimeRatch[0]/16)*10+
					(m_abtDateTimeRatch[0]%16));
				SetMinute(
					(m_abtDateTimeRatch[1]/16)*10+
					(m_abtDateTimeRatch[1]%16));
				SetHour(
					(m_abtDateTimeRatch[2]/16)*10+
					(m_abtDateTimeRatch[2]%16));
				SetDay(
					(m_abtDateTimeRatch[3]/16)*10+
					(m_abtDateTimeRatch[3]%16));
				SetWDay(m_abtDateTimeRatch[4]%16);
				SetMonth(m_abtDateTimeRatch[4]/16);
				if (nCommand == 0x12) {
					SetYear(
						(m_abtDateTimeRatch[5]/16)*10+
						(m_abtDateTimeRatch[5]%16));
				}
				m_nCalendarCounter = m_nCalendarCounterMax;
				break;
			case 0x03:
			case 0x13:
				memcpy(
					m_abtDateTimeRatch, m_abtDateTime,
					(nCommand == 0x03)? 5: 6);
				break;
			}
		}
		m_bCalendarStrobe = bCalendarStrobe;
	}
	// set calendar data shift
	static void SetCalendarShift(bool bCalendarShift) {
		if ((m_bCalendarShift != bCalendarShift) && bCalendarShift) {
			if (m_nCheckBit >= 52) {
				m_nCheckBit = 51;
				m_abtDateTimeRatch[6] >>= 1;
			}
			int nOfs = m_nCheckBit/8;
			uint8_t btMask = uint8_t(0x01 << (m_nCheckBit%8));
			if (m_bCalendarDataOut) {
				m_abtDateTimeRatch[nOfs] |= btMask;
			} else {
				m_abtDateTimeRatch[nOfs] &= uint8_t(~btMask);
			}
			m_nCheckBit++;
			nOfs = m_nCheckBit/8;
			btMask = uint8_t(0x01 << (m_nCheckBit%8));
			m_bCalendarDataIn = ((m_abtDateTimeRatch[nOfs] & btMask) != 0);
			if (m_nCalendarMode == MODE_SHIFT_DATA40) {
				if (m_nCheckBit >= 40) {
					m_nCheckBit = 48;
					m_nCalendarMode = MODE_COMMAND;
				}
			} else if (m_nCalendarMode == MODE_SHIFT_DATA48) {
				if (m_nCheckBit >= 48) {
					m_nCalendarMode = MODE_COMMAND;
				}
			}
		}
		m_bCalendarShift = bCalendarShift;
	}
	// increment clendar
	static void IncCanendar();
};

#endif // PC88Calendar_DEFINED
