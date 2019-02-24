////////////////////////////////////////////////////////////
// PC-8801 USART Emulator
//
// Written by Manuke

#ifndef PC88Usart_DEFINED
#define PC88Usart_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Usart;

////////////////////////////////////////////////////////////
// include

#include "TapeImage.h"

////////////////////////////////////////////////////////////
// declaration of CPC88Usart

class CPC88Usart {
// typedef
public:
	// type of interrupt vector change callback function
	typedef void (*IntVectChangeCallback)();

// enum
public:
	// interrupt bit
	enum {
		INTERRUPT_BIT = 0x01
	};
	// baud rate
	enum {
		BAUDRATE_SYNC = 0,
		BAUDRATE_X1   = 1,
		BAUDRATE_X16  = 2,
		BAUDRATE_X64  = 3
	};
	// stop bit
	enum {
		STOPBIT_ERROR = 0,
		STOPBIT_1     = 1,
		STOPBIT_1_5   = 2,
		STOPBIT_2     = 3
	};
	// channel
	enum {
		CHANNEL_CMT600    = 0,
		CHANNEL_CMT1200   = 1,
		CHANNEL_RS_232C_A = 2,
		CHANNEL_RS_232C_S = 3
	};

// attribute
protected:
	// USART attribute
	// base clock
	static int m_nBaseClock;
	// load counter
	static int m_nUsartLoadCounter;
	// save counter
	static int m_nUsartSaveCounter;
	// USART counter max value
	static int m_nUsartCounterMax;
	// setting mode instruction
	static bool m_bModeInstruction;
	// baud rate
	static int m_nBaudRate;
	// character length
	static int m_nCharLength;
	// enable parity
	static bool m_bParityEnable;
	// even parity
	static bool m_bParityEven;
	// stop bit length
	static int m_nStopBit;
	// enable sending
	static bool m_bSendEnable;
	// enable receiving
	static bool m_nReceiveEnable;
	// DTR
	static bool m_bDTR;
	// RTS
	static bool m_bRTS;
	// send break character
	static bool m_bSendBreakChar;
	// sync character hunt
	static bool m_bSyncCharHunt;
	// parity error
	static bool m_bParityError;
	// overrun error
	static bool m_bOverrunError;
	// framing error
	static bool m_bFramingError;
	// receive interrupt requested
	static bool m_bReceiveInterruptRequest;
	// delay at data reading
	static int m_nDataReadDelay;

	// other
	// channel mode
	static int m_nChannelMode;
	// space carrier
	static bool m_bSpaceCarrier;
	// moter-on
	static bool m_bMotorOn;
	// skip character on moter-off
	static bool m_bSkipCharOnMotorOff;

	// tape image
	// tape image for loading
	static CTapeImage m_timageLoad;
	// tape image for saving
	static CTapeImage m_timageSave;

	// interrupt vector change callback function
	static IntVectChangeCallback m_pIntVectChangeCallback;

public:
	// USART attribute
	// get base clock
	static int GetBaseClock() {
		return m_nBaseClock;
	}
	// set base clock
	static void SetBaseClock(int nBaseClock) {
		m_nBaseClock = nBaseClock;
	}
	// is setting mode instruction
	static bool IsModeInstruction() {
		return m_bModeInstruction;
	}
	// get baud rate
	static int GetBaudRate() {
		return m_nBaudRate;
	}
	// get character length
	static int GetCharLength() {
		return m_nCharLength;
	}
	// is enable parity
	static bool IsParityEnable() {
		return m_bParityEnable;
	}
	// is even parity
	static bool IsParityEven() {
		return m_bParityEven;
	}
	// get stop bit length
	static int GetStopBit() {
		return m_nStopBit;
	}
	// is enable sending
	static bool IsSendEnable() {
		return m_bSendEnable;
	}
	// is enable receiving
	static bool IsReceiveEnable() {
		return m_nReceiveEnable;
	}
	// is DTR
	static bool IsDTR() {
		return m_bDTR;
	}
	// is RTS
	static bool IsRTS() {
		return m_bRTS;
	}
	// is send break character
	static bool IsSendBreakChar() {
		return m_bSendBreakChar;
	}
	// is sync character hunt
	static bool IsSyncCharHunt() {
		return m_bSyncCharHunt;
	}
	// is parity error
	static bool IsParityError() {
		return m_bParityError;
	}
	// is overrun error
	static bool IsOverrunError() {
		return m_bOverrunError;
	}
	// is framing error
	static bool IsFramingError() {
		return m_bFramingError;
	}
	// is receive interrupt requested
	static bool IsReceiveInterruptRequest() {
		return m_bReceiveInterruptRequest;
	}
	// set reseive interrupt requested
	static void SetReceiveInterruptRequest(bool bReceiveInterruptRequest) {
		m_bReceiveInterruptRequest = bReceiveInterruptRequest;
	}
	// get delay at data reading
	static int GetDataReadDelay() {
		return m_nDataReadDelay;
	}
	// set delay at data reading
	static void SetDataReadDelay(int nDataReadDelay) {
		m_nDataReadDelay = nDataReadDelay;
	}

	// other
	// get channel mode
	static int GetChannelMode() {
		return m_nChannelMode;
	}
	// set channel mode
	static void SetChannelMode(int nChannelMode) {
		m_nChannelMode = nChannelMode;
		m_timageSave.SetDataBaud(m_nChannelMode == CHANNEL_CMT1200);
	}
	// is space carrier
	static bool IsSpaceCarrier() {
		return m_bSpaceCarrier;
	}
	// set space carrier
	static void SetSpaceCarrier(bool bSpaceCarrier) {
		m_bSpaceCarrier = bSpaceCarrier;
		m_timageSave.SetSpaceCarrier(bSpaceCarrier);
	}
	// is moter-on
	static bool IsMotorOn() {
		return m_bMotorOn;
	}
	// is skip character on moter-off
	static bool IsSkipCharOnMotorOff() {
		return m_bSkipCharOnMotorOff;
	}
	// set skip character on moter-off
	static void SetSkipCharOnMotorOff(bool bSkipCharOnMotorOff) {
		m_bSkipCharOnMotorOff = bSkipCharOnMotorOff;
	}

	// tape image
	// get tape image for loading
	static CTapeImage& GetLoadTapeImage() {
		return m_timageLoad;
	}
	// get tape image for saving
	static CTapeImage& GetSaveTapeImage() {
		return m_timageSave;
	}
	// is exist data
	static bool IsExistData() {
		return m_timageLoad.IsExistData();
	}
	// is waiting
	static bool IsWaiting() {
		return m_timageLoad.IsWaiting();
	}
	// clear wait
	static void ClearWait() {
		m_timageLoad.ClearWait();
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
	CPC88Usart();
	// destructor
	~CPC88Usart();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
protected:
	// update interrupt request
	static void UpdateInterruptRequest(bool bReceiveInterruptRequest) {
		if (bReceiveInterruptRequest != m_bReceiveInterruptRequest) {
			m_bReceiveInterruptRequest = bReceiveInterruptRequest;
			m_pIntVectChangeCallback();
		}
	}

public:
	// pass clock
	static void PassClock(int nClock) {
		if (m_bMotorOn) {
			if (m_nReceiveEnable) {
				if (m_timageLoad.IsWaiting()) {
					if ((m_nUsartLoadCounter -= nClock) <= 0) {
						int nTick = 0;
						do {
							nTick++;
							m_nUsartLoadCounter += m_nUsartCounterMax;
						} while (m_nUsartLoadCounter <= 0);
						if (m_timageLoad.LoadPassTick(nTick)) {
							UpdateInterruptRequest(true);
						}
					}
				}
				if (m_nDataReadDelay > 0) {
					if ((m_nDataReadDelay -= nClock) <= 0) {
						UpdateInterruptRequest(true);
					}
				}
			}
			if (m_bSendEnable) {
				if ((m_nUsartSaveCounter -= nClock) <= 0) {
					int nTick = 0;
					do {
						nTick++;
						m_nUsartSaveCounter += m_nUsartCounterMax;
					} while (m_nUsartSaveCounter <= 0);
					m_timageSave.SavePassTick(nTick);
				}
			}
		}
	}
	// read status
	static uint8_t ReadStatus() {
		uint8_t btData = uint8_t(
			0x85 |
			((IsExistData() && !IsWaiting())? 0x02: 0x00) |
			(m_bParityError? 0x08: 0x00) |
			(m_bOverrunError? 0x10: 0x00) |
			(m_bFramingError? 0x20: 0x00));
		return btData;
	}
	// write control
	static void WriteControl(uint8_t btControl) {
		if (m_bModeInstruction) {
			m_nBaudRate = btControl & 0x03;
			m_nCharLength = ((btControl >> 2) & 0x03)+5;
			m_bParityEnable = (btControl & 0x10) != 0;
			m_bParityEven = (btControl & 0x20) != 0;
			m_nStopBit = (btControl >> 6) & 0x03;
			m_timageSave.SetDataType(
				uint8_t(btControl & (!m_bParityEnable? 0xDC: 0xFC)));
			m_bModeInstruction = false;
		} else {
			m_bSendEnable = (btControl & 0x01) != 0;
			m_nReceiveEnable = (btControl & 0x04) != 0;
			m_bDTR = (btControl & 0x02) != 0;
			m_bRTS = (btControl & 0x20) != 0;
			m_bSendBreakChar = (btControl & 0x08) != 0;
			m_bSyncCharHunt = (btControl & 0x80) != 0;
			if ((btControl & 0x10) != 0) {
				m_bParityError = m_bOverrunError = m_bFramingError = false;
			}
			if ((btControl & 0x40) != 0) {
				m_bModeInstruction = true;
				m_bSendEnable = m_nReceiveEnable = false;
			}
			if (m_bMotorOn && m_nReceiveEnable &&
				IsExistData() && !IsWaiting())
			{
				UpdateInterruptRequest(true);
			} else {
				UpdateInterruptRequest(false);
			}
		}
	}
	// moter-on/off
	static void SetMotorOn(bool bMotorOn) {
		if (!bMotorOn && m_bMotorOn &&
			IsSkipCharOnMotorOff() &&
			IsExistData() && !IsWaiting())
		{
			m_timageLoad.GetData();
			m_nDataReadDelay = 0;
		}
		m_bMotorOn = bMotorOn;
		if (m_bMotorOn && m_nReceiveEnable &&
			IsExistData() && !IsWaiting())
		{
			UpdateInterruptRequest(true);
		} else {
			UpdateInterruptRequest(false);
		}
	}
	// read data
	static uint8_t ReadData() {
		uint8_t btData = 0;
		if (IsExistData() && !IsWaiting()) {
			btData = m_timageLoad.GetData();
		}
		if (m_bMotorOn && m_nReceiveEnable &&
			IsExistData() && !IsWaiting())
		{
			m_nDataReadDelay = 4000;
		} else {
			m_nDataReadDelay = 0;
		}
		UpdateInterruptRequest(false);
		return btData;
	}
	// write data
	static void WriteData(uint8_t btData) {
		m_timageSave.SetData(btData);
	}
	// read data(no wait)
	static int ReadData2() {
		int nData = -1;
		if (IsExistData()) {
			ClearWait();
			nData = ReadData();
		}
		return nData;
	}
};

#endif // PC88Usart_DEFINED
