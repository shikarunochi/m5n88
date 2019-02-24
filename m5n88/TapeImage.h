////////////////////////////////////////////////////////////
// TapeImage
//
// Written by Manuke

#ifndef TapeImage_DEFINED
#define TapeImage_DEFINED
#include <list>

////////////////////////////////////////////////////////////
// declare

class CTapeImage;

////////////////////////////////////////////////////////////
// include

#include "Gptr.h"

////////////////////////////////////////////////////////////
// declaration of CTapeImage

class CTapeImage {
// enum
public:
	// tag type
	enum {
		TAG_VERSION = 0x0001,
		TAG_BLANK   = 0x0100,
		TAG_DATA    = 0x0101,
		TAG_SPACE   = 0x0102,
		TAG_MARK    = 0x0103,
		TAG_END     = 0x0000
	};
	// data type
	enum {
		DATATYPE_DATABIT     = 0x000C,
		DATATYPE_DATABIT_5   = 0x0000,
		DATATYPE_DATABIT_6   = 0x0004,
		DATATYPE_DATABIT_7   = 0x0008,
		DATATYPE_DATABIT_8   = 0x000C,
		DATATYPE_PARITY      = 0x0030,
		DATATYPE_PARITY_NONE = 0x0000,
		DATATYPE_PARITY_ODD  = 0x0010,
		DATATYPE_PARITY_EVEN = 0x0030,
		DATATYPE_STOPBIT     = 0x00C0,
		DATATYPE_STOPBIT_1   = 0x0040,
		DATATYPE_STOPBIT_15  = 0x0080,
		DATATYPE_STOPBIT_2   = 0x00C0,
		DATATYPE_BAUD        = 0x0100,
		DATATYPE_BAUD_600    = 0x0000,
		DATATYPE_BAUD_1200   = 0x0100
	};
	// error code
	enum {
		ERR_NOERROR,
		ERR_CANNOTOPEN,
		ERR_IOERROR,
		ERR_BADSTRUCTURE
	};
	// constant value
	enum {
		TICK_HZ       = 4800,
		GAP_MAX       = 2,
		DATATAG_MAX   = 32768,
		FILEID_LENGTH = 24
	};

// class
protected:
	// declaration and implementation of CTapeImageTag
	class CTapeImageTag {
	// attribute
	public:
		// tag type
		uint16_t m_wTagType;
		// begin tick
		uint32_t m_dwBeginTick;
		// length of tick
		uint32_t m_dwSizeTick;
		// data size
		uint16_t m_wDataSize;
		// data type
		uint16_t m_wDataType;
		// data offset
		uint32_t m_dwDataOfs;

	// create & destroy
	public:
		// default constructor
		CTapeImageTag() :
			m_wTagType(0),
			m_dwBeginTick(0),
			m_dwSizeTick(0),
			m_wDataSize(0),
			m_wDataType(0),
			m_dwDataOfs(0)
		{
		}
		// constructor(parameter specified)
		CTapeImageTag(
				uint16_t wTagType,
				uint32_t dwBeginTick = 0, uint32_t dwSizeTick = 0,
				uint16_t wDataSize = 0, uint16_t wDataType = 0,
				uint32_t dwDataOfs = 0) :
			m_wTagType(wTagType),
			m_dwBeginTick(dwBeginTick),
			m_dwSizeTick(dwSizeTick),
			m_wDataSize(wDataSize),
			m_wDataType(wDataType),
			m_dwDataOfs(dwDataOfs)
		{
		}
		// copy constructor
		CTapeImageTag(const CTapeImageTag& titOther) :
			m_wTagType(titOther.m_wTagType),
			m_dwBeginTick(titOther.m_dwBeginTick),
			m_dwSizeTick(titOther.m_dwSizeTick),
			m_wDataSize(titOther.m_wDataSize),
			m_wDataType(titOther.m_wDataType),
			m_dwDataOfs(titOther.m_dwDataOfs)
		{
		}

	// operator
	public:
		// let
		CTapeImageTag& operator=(const CTapeImageTag& titOther) {
			m_wTagType = titOther.m_wTagType;
			m_dwBeginTick = titOther.m_dwBeginTick;
			m_dwSizeTick = titOther.m_dwSizeTick;
			m_wDataSize = titOther.m_wDataSize;
			m_wDataType = titOther.m_wDataType;
			m_dwDataOfs = titOther.m_dwDataOfs;
			return *this;
		}

	// operation
	public:
		// get size from tag type
		static int GetSize(uint16_t wTagType) {
			int nSize = 0;
			switch (wTagType) {
			case TAG_VERSION:
				nSize = sizeof(uint16_t);
				break;
			case TAG_BLANK:
			case TAG_SPACE:
			case TAG_MARK:
				nSize = sizeof(uint32_t)*2;
				break;
			case TAG_DATA:
				nSize = sizeof(uint32_t)*2+sizeof(uint16_t)*2;
				break;
			}
			return nSize;
		}
		// get size
		int GetSize() const {
			return GetSize(m_wTagType);
		}
		// is exist passage of time from tag type
		static bool IsTick(uint16_t wTagType) {
			bool bTick = false;
			switch (wTagType) {
			case TAG_BLANK:
			case TAG_SPACE:
			case TAG_MARK:
			case TAG_DATA:
				bTick = true;
				break;
			}
			return bTick;
		}
		// is exist passage of time
		bool IsTick() {
			return IsTick(m_wTagType);
		}
		// get data
		uint8_t* GetData(uint8_t* pbtBuffer) {
			UGptr gptr = pbtBuffer;
			switch (m_wTagType) {
			case TAG_VERSION:
				gptr >> m_wDataType;
				break;
			case TAG_BLANK:
			case TAG_SPACE:
			case TAG_MARK:
				gptr >> m_dwBeginTick >> m_dwSizeTick;
				break;
			case TAG_DATA:
				gptr >> m_dwBeginTick >> m_dwSizeTick;
				gptr >> m_wDataSize >> m_wDataType;
				break;
			}
			return gptr.m_pByte;
		}
		// set data
		uint8_t* SetData(uint8_t* pbtBuffer) {
			UGptr gptr = pbtBuffer;
			switch (m_wTagType) {
			case TAG_VERSION:
				gptr << m_wDataType;
				break;
			case TAG_BLANK:
			case TAG_SPACE:
			case TAG_MARK:
				gptr << m_dwBeginTick << m_dwSizeTick;
				break;
			case TAG_DATA:
				gptr << m_dwBeginTick << m_dwSizeTick;
				gptr << m_wDataSize << m_wDataType;
				break;
			}
			return gptr.m_pByte;
		}
		// is 1200 baud
		bool IsBaud1200() {
			return (m_wDataType & DATATYPE_BAUD) == DATATYPE_BAUD_1200;
		}
	};

// attribute
protected:
	// tag list
	std::list<CTapeImageTag> m_listTag;
	// data buffer
	std::vector<uint8_t> m_vectData;
	// offset buffer
	std::vector<int> m_vectOfs;
	// size buffer
	std::vector<int> m_vectSize;
	// wait buffer
	std::vector<int> m_vectWait;
	// current block
	int m_nCurBlock;
	// current position in block
	int m_nCurPos;
	// tick
	int m_nTick;
	// data tick
	int m_nDataTick;
	// total tick
	int m_nTotalTick;
	// data type
	uint16_t m_wDataType;
	// is space carrier
	bool m_bSpaceCarrier;
	// file name(filesystem encoding)
	std::string m_fstrFileName;

	// file id
	static char m_szFileID[];

public:
	// get standard data type
	static uint16_t GetStdDataType(bool bBaud1200) {
		return uint16_t(
			DATATYPE_DATABIT_8 |
			DATATYPE_PARITY_NONE |
			DATATYPE_STOPBIT_2 |
			(bBaud1200? DATATYPE_BAUD_1200: DATATYPE_BAUD_600));
	}
	// get standard data tick
	static int GetStdDataTick(bool bBaud1200) {
		return bBaud1200? (4*11): (8*11);
	}

	// get tag count
	int GetTagCount() const {
		return (int)m_listTag.size();
	}
	// get data size
	int GetDataSize() const {
		return (int)m_vectData.size();
	}
	// get data block count
	int GetDataBlockCount() const {
		return (int)m_vectOfs.size();
	}
	// is exist data
	bool IsExistData() const {
		return (m_nCurBlock < int(m_vectOfs.size()));
	}
	// is waiting
	bool IsWaiting() const {
		return m_nTick > 0;
	}
	// clear wait
	void ClearWait() {
		m_nTick = 0;
	}
	// get file name(filesystem encoding)
	const std::string GetFileName() {
		return m_fstrFileName;
	}
	// set data type
	void SetDataType(uint8_t btDataType) {
		m_wDataType = uint16_t((m_wDataType & 0xFF00) | btDataType);
	}
	// set data baud rate
	void SetDataBaud(bool bBaud1200) {
		m_wDataType = uint16_t(
			(m_wDataType & ~DATATYPE_BAUD) |
			(bBaud1200? DATATYPE_BAUD_1200: DATATYPE_BAUD_600));
		m_nDataTick = GetStdDataTick(bBaud1200);
	}

// create & destroy
public:
	// default constructor
	CTapeImage();
	// destructor
	~CTapeImage();

// operation
protected:
	// read data buffer
	bool ReadData(int nOfs, int nSize, FILE* pFile);
	// write data buffer
	bool WriteData(int nOfs, int nSize, FILE* pFile);

public:
	// pass tick at loading
	bool LoadPassTick(int nTick) {
		m_nTick -= nTick;
		return m_nTick <= 0;
	}
	// pass tick at saving
	void SavePassTick(int nTick) {
		m_nTick += nTick;
	}
	// get data
	uint8_t GetData() {
		uint8_t btData = m_vectData[m_vectOfs[m_nCurBlock]+m_nCurPos];
		if (++m_nCurPos >= m_vectSize[m_nCurBlock]) {
			int nNewBlock = m_nCurBlock+1;
			SeekBlockCount(nNewBlock);
		}
		return btData;
	}
	// close carrier tag
	void CloseCarrierTag() {
		if (m_nTick > 0) {
			if (m_bSpaceCarrier) {
				m_nTick = ((m_nTick+3)/4)*4;
			} else {
				m_nTick = ((m_nTick+1)/2)*2;
			}
			m_listTag.push_back(
				CTapeImageTag(
					uint16_t(m_bSpaceCarrier? TAG_SPACE: TAG_MARK),
				m_nTotalTick, m_nTick));
			m_nTotalTick += m_nTick;
			m_nTick = 0;
		}
	}
	// set space carrier
	void SetSpaceCarrier(bool bSpaceCarrier) {
		if (m_bSpaceCarrier != bSpaceCarrier) {
			CloseCarrierTag();
		}
		m_bSpaceCarrier = bSpaceCarrier;
	}
	// set data
	void SetData(uint8_t btData) {
		if (m_nTick > m_nDataTick) {
			CloseCarrierTag();
		}
		m_nTick = 0;
		std::list<CTapeImageTag>::iterator itTag = m_listTag.end();
		if (m_listTag.size() > 0) {
			itTag--;
			if (((*itTag).m_wTagType != TAG_DATA) |
				((*itTag).m_wDataType != m_wDataType) |
				((*itTag).m_wDataSize >= DATATAG_MAX))
			{
				itTag = m_listTag.end();
			}
		}
		if (itTag == m_listTag.end()) {
			m_listTag.push_back(
				CTapeImageTag(TAG_DATA, m_nTotalTick, 0));
			itTag = m_listTag.end();
			itTag--;
			(*itTag).m_wDataType = m_wDataType;
			(*itTag).m_dwDataOfs = (uint32_t)m_vectData.size();
		}
		(*itTag).m_dwSizeTick += m_nDataTick;
		(*itTag).m_wDataSize++;
		m_nTotalTick += m_nDataTick;
		m_vectData.push_back(btData);
	}
	// seek to top of block
	void SeekBlockCount(int nCurBlock) {
		m_nCurBlock = nCurBlock;
		m_nCurPos = 0;
		m_nTick = 0;
		if (IsExistData()) {
			m_nTick = m_vectWait[m_nCurBlock];
			if (m_nTick > TICK_HZ*GAP_MAX) {
				m_nTick = TICK_HZ*GAP_MAX;
			}
		}
	}
	// erase
	void Erase();
	// make block info
	void MakeBlockInfo();
	// load T88 file
	int Load(const std::string& fstrFileName);
	// save T88 file
	int Save(const std::string& fstrFileName);
	// load CMT file
	int LoadCMT(const std::string& fstrFileName);
	// save CMT file
	int SaveCMT(const std::string& fstrFileName);
	// get valid block count
	int GetRealDataBlockCount();
	// get total tick
	int GetTotalTick();
	// get counter tick
	int GetCounterTick();
	// forward counter
	void CounterFWD();
	// rewind counter
	void CounterREW();
};

#endif // TapeImage_DEFINED
