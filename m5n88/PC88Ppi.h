////////////////////////////////////////////////////////////
// PC-8801 PPI Emulator
//
// Written by Manuke

#ifndef PC88Ppi_DEFINED
#define PC88Ppi_DEFINED

////////////////////////////////////////////////////////////
// declare

class CPC88Ppi;

////////////////////////////////////////////////////////////
// declaration of CPC88Ppi

class CPC88Ppi {
// typedef
public:
	// type of ATN activate calback function
	typedef void (*ATNActivateCallback)();

// enum
public:
	// side
	enum {
		SIDE_MAIN = 0,
		SIDE_SUB  = 1
	};

// attribute
protected:
	// port data
	static uint8_t m_abtPortData[3];
	// port mode
	static int m_anPortMode[2][2];
	// port direction
	static bool m_abPortDir[2][4];
	// updated
	static bool m_bUpdate;

	// ATN activate calback function
	static ATNActivateCallback m_pATNActivateCallback;

public:
	// is updated
	static bool IsUpdate() {
		return m_bUpdate;
	}
	// set updated
	static void SetUpdate(bool bUpdate) {
		m_bUpdate = bUpdate;
	}

	// set ATN activate calback function
	static void SetATNActivateCallback(
		ATNActivateCallback pATNActivateCallback)
	{
		m_pATNActivateCallback = pATNActivateCallback;
	}

// create & destroy
public:
	// default constructor
	CPC88Ppi();
	// destructor
	~CPC88Ppi();

// initialize
public:
	// initialize at first
	static void Initialize();
	// reset
	static void Reset();

// operation
public:
	// read port A
	static uint8_t ReadPortA(int nSide) {
		if (nSide == SIDE_MAIN) {
			m_pATNActivateCallback();
		}
		return m_abtPortData[nSide];
	}
	// read port B
	static uint8_t ReadPortB(int nSide) {
		if (nSide == SIDE_MAIN) {
			m_pATNActivateCallback();
		}
		return m_abtPortData[1-nSide];
	}
	// read port C
	static uint8_t ReadPortC(int nSide) {
		uint8_t btPortData = m_abtPortData[2];
		if (nSide == SIDE_MAIN) {
			m_pATNActivateCallback();
		} else {
			btPortData = uint8_t((btPortData << 4) | (btPortData >> 4));
		}
		return btPortData;
	}
	// write port A
	static void WritePortA(int nSide, uint8_t btPortData) {
		if (!m_abPortDir[nSide][0]) {
			m_abtPortData[nSide] = btPortData;
		}
		m_bUpdate = true;
		m_pATNActivateCallback();
	}
	// write port B
	static void WritePortB(int nSide, uint8_t btPortData) {
		if (!m_abPortDir[nSide][1]) {
			m_abtPortData[1-nSide] = btPortData;
		}
		m_bUpdate = true;
		m_pATNActivateCallback();
	}
	// write port C
	static void WritePortC(int nSide, uint8_t btPortData) {
		if ((m_abPortDir[nSide][2]) || (m_abPortDir[nSide][3])) {
			uint8_t btPortData2 = m_abtPortData[2];
			if (nSide != SIDE_MAIN) {
				btPortData = uint8_t((btPortData << 4) | (btPortData >> 4));
			}
			if (((nSide == SIDE_MAIN) && !m_abPortDir[nSide][2]) ||
				((nSide != SIDE_MAIN) && !m_abPortDir[nSide][3]))
			{
				btPortData2 = uint8_t((btPortData2 & 0xF0) | (btPortData & 0x0F));
			}
			if (((nSide == SIDE_MAIN) && !m_abPortDir[nSide][3]) ||
				((nSide != SIDE_MAIN) && !m_abPortDir[nSide][2]))
			{
				btPortData2 = uint8_t((btPortData2 & 0x0F) | (btPortData & 0xF0));
			}
			m_abtPortData[2] = btPortData2;
		}
		m_bUpdate = true;
		m_pATNActivateCallback();
	}
	// write command
	static void WriteCommand(int nSide, uint8_t btCommand) {
		m_bUpdate = true;
		if ((btCommand & 0x80) != 0) {
			m_anPortMode[nSide][0] = (btCommand >> 6) & 0x03;
			m_anPortMode[nSide][1] = (btCommand >> 2) & 0x01;
			m_abPortDir[nSide][0] = (btCommand & 0x10) != 0;
			m_abPortDir[nSide][1] = (btCommand & 0x02) != 0;
			m_abPortDir[nSide][2] = (btCommand & 0x01) != 0;
			m_abPortDir[nSide][3] = (btCommand & 0x08) != 0;
			WritePortA(nSide, 0);
			WritePortB(nSide, 0);
			WritePortC(nSide, 0);
		} else {
			int nBit = (btCommand & 0x0E) >> 1;
			if (!m_abPortDir[nSide][2+nBit/4]) {
				if (nSide != SIDE_MAIN) {
					nBit ^= 4;
				}
				if ((btCommand & 0x01) != 0) {
					m_abtPortData[2] = uint8_t(m_abtPortData[2] | (1 << nBit));
				} else {
					m_abtPortData[2] = uint8_t(m_abtPortData[2] & ~(1 << nBit));
				}
			}
		}
		m_bUpdate = true;
		m_pATNActivateCallback();
	}
};

#endif // PC88Ppi_DEFINED
