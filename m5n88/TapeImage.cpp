////////////////////////////////////////////////////////////
// TapeImage
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "TapeImage.h"

////////////////////////////////////////////////////////////
// implementation of CTapeImage

////////////////////////////////////////////////////////////
// attribute

// file id

char CTapeImage::m_szFileID[] = "PC-8801 Tape Image(T88)";

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CTapeImage::CTapeImage() {
	m_nCurBlock = m_nCurPos = 0;
	m_nTick = m_nTotalTick = 0;
	m_wDataType = GetStdDataType(false);
	m_nDataTick = GetStdDataTick(false);
}

// destructor

CTapeImage::~CTapeImage() {
	Erase();
}

////////////////////////////////////////////////////////////
// operation

// read data buffer

bool CTapeImage::ReadData(int nOfs, int nSize, FILE* pFile) {
	bool bResult = true;
	if (nSize > 0) {
		bResult = (fread(&m_vectData[nOfs], nSize, 1, pFile) >= 1);
	}
	return bResult;
}

// write data buffer

bool CTapeImage::WriteData(int nOfs, int nSize, FILE* pFile) {
	bool bResult = true;
	if (nSize > 0) {
		bResult = (fwrite(&m_vectData[nOfs], nSize, 1, pFile) >= 1);
	}
	return bResult;
}

// erase

void CTapeImage::Erase() {
	m_listTag.clear();
	m_nCurBlock = m_nCurPos = 0;
	m_nTick = m_nTotalTick = 0;
	m_vectData.clear();
	m_vectOfs.clear();
	m_vectSize.clear();
	m_vectWait.clear();
	m_fstrFileName = "";
}

// make block info

void CTapeImage::MakeBlockInfo() {
	m_nCurBlock = m_nCurPos = 0;
	m_nTick = 0;
	m_vectOfs.clear();
	m_vectSize.clear();
	m_vectWait.clear();
	uint32_t dwLastTick = 0;
	for (
		std::list<CTapeImageTag>::iterator itTag = m_listTag.begin();
		itTag != m_listTag.end();
		itTag++)
	{
		if ((*itTag).m_wTagType == TAG_DATA) {
			m_vectOfs.push_back((*itTag).m_dwDataOfs);
			m_vectSize.push_back((*itTag).m_wDataSize);
			m_vectWait.push_back((*itTag).m_dwBeginTick-dwLastTick);
			dwLastTick = (*itTag).m_dwBeginTick+(*itTag).m_dwSizeTick;
		}
	}
	SeekBlockCount(0);
}

// load T88 file

int CTapeImage::Load(const std::string& fstrFileName) {
	int nResult = ERR_NOERROR;
	Erase();
	FILE* fpt = NULL;
	uint8_t abtBuffer[256];
	uint32_t dwLastTick = 0, dwOfsTick = 0;
	try {
		if ((fpt = fopen(fstrFileName.c_str(), "rb")) == NULL) {
			throw int(ERR_CANNOTOPEN);
		}
		if (fread(abtBuffer, FILEID_LENGTH, 1, fpt) < 1) {
			throw int(ERR_IOERROR);
		}
		if (strcmp((char*)abtBuffer, m_szFileID) != 0) {
			throw int(ERR_BADSTRUCTURE);
		}
		uint16_t wTagType, wTagSize;
		UGptr gptr;
		while (true) {
			if (fread(abtBuffer, sizeof(uint16_t)*2, 1, fpt) < 1) {
				throw int(ERR_IOERROR);
			}
			gptr = abtBuffer;
			gptr >> wTagType >> wTagSize;
			if (wTagType == TAG_END) {
				if (fread(abtBuffer, FILEID_LENGTH, 1, fpt) < 1) {
					break;
				}
				if (strcmp((char*)abtBuffer, m_szFileID) != 0) {
					break;
				}
				dwOfsTick = dwLastTick;
				continue;
			}
			int nSize = CTapeImageTag::GetSize(wTagType);
			if (nSize > wTagSize) {
				throw int(ERR_BADSTRUCTURE);
			}
			m_listTag.push_back(CTapeImageTag(wTagType));
			std::list<CTapeImageTag>::iterator itTag = m_listTag.end();
			itTag--;
			if (nSize > 0) {
				if (fread(abtBuffer, nSize, 1, fpt) < 1) {
					throw int(ERR_IOERROR);
				}
				(*itTag).GetData(abtBuffer);
				wTagSize = uint16_t(wTagSize-nSize);
			}
			if ((*itTag).IsTick()) {
				(*itTag).m_dwBeginTick += dwOfsTick;
				dwLastTick = (*itTag).m_dwBeginTick+(*itTag).m_dwSizeTick;
			}
			if (wTagType == TAG_DATA) {
				uint16_t wDataSize = (*itTag).m_wDataSize;
				if (wDataSize > wTagSize) {
					throw int(ERR_BADSTRUCTURE);
				}
				int nOfs = (int)m_vectData.size();
				(*itTag).m_dwDataOfs = (uint32_t)nOfs;
				m_vectData.resize(nOfs+wDataSize);
				if (!ReadData(nOfs, wDataSize, fpt)) {
					throw int(ERR_IOERROR);
				}
				wTagSize = (uint16_t)(wTagSize-wDataSize);
			}
			if (wTagSize > 0) {
				if (fseek(fpt, wTagSize, SEEK_CUR) != 0) {
					throw int(ERR_IOERROR);
				}
			}
		}
		fclose(fpt);
		fpt = NULL;
		m_fstrFileName = fstrFileName;
		MakeBlockInfo();
	} catch (int nError) {
		if (fpt != NULL) {
			fclose(fpt);
		}
		Erase();
		SeekBlockCount(0);
		nResult = nError;
	}
	return nResult;
}

// save T88 file

int CTapeImage::Save(const std::string& fstrFileName) {
	CloseCarrierTag();
	bool bVersionExist = false;
	std::list<CTapeImageTag>::iterator itTag;
	for (
		itTag = m_listTag.begin();
		itTag != m_listTag.end();
		itTag++)
	{
		if ((*itTag).m_wTagType == TAG_VERSION) {
			bVersionExist = true;
			break;
		}
	}
	if (!bVersionExist) {
		m_listTag.push_front(CTapeImageTag(TAG_VERSION));
		itTag = m_listTag.begin();
		(*itTag).m_wDataType = 0x0100;
	}
	int nResult = ERR_NOERROR;
	FILE* fpt = NULL;
	uint8_t abtBuffer[256];
	try {
		if ((fpt = fopen(fstrFileName.c_str(), "wb")) == NULL) {
			throw int(ERR_CANNOTOPEN);
		}
		if (fwrite(m_szFileID, FILEID_LENGTH, 1, fpt) < 1) {
			throw int(ERR_IOERROR);
		}
		uint16_t wTagType, wTagSize;
		UGptr gptr;
		for (
			itTag = m_listTag.begin();
			itTag != m_listTag.end();
			itTag++)
		{
			int nSize = (*itTag).GetSize();
			wTagType = (*itTag).m_wTagType;
			wTagSize = uint16_t(nSize);
			if (wTagType == TAG_DATA) {
				wTagSize = uint16_t(wTagSize+(*itTag).m_wDataSize);
			}
			gptr = abtBuffer;
			gptr << wTagType << wTagSize;
			if (fwrite(abtBuffer, sizeof(uint16_t)*2, 1, fpt) < 1) {
				throw int(ERR_IOERROR);
			}
			if (nSize > 0) {
				(*itTag).SetData(abtBuffer);
				if (fwrite(abtBuffer, nSize, 1, fpt) < 1) {
					throw int(ERR_IOERROR);
				}
			}
			if (wTagType == TAG_DATA) {
				if (!WriteData(
						(*itTag).m_dwDataOfs, (*itTag).m_wDataSize, fpt))
				{
					throw int(ERR_IOERROR);
				}
			}
		}
		gptr = abtBuffer;
		gptr << uint16_t(TAG_END) << uint16_t(0);
		if (fwrite(abtBuffer, sizeof(uint16_t)*2, 1, fpt) < 1) {
			throw int(ERR_IOERROR);
		}
		if (fflush(fpt) != 0) {
			throw int(ERR_IOERROR);
		}
		fclose(fpt);
		fpt = NULL;
	} catch (int nError) {
		if (fpt != NULL) {
			fclose(fpt);
		}
		unlink(fstrFileName.c_str());
		nResult = nError;
	}
	return nResult;
}

// load CMT file

int CTapeImage::LoadCMT(const std::string& fstrFileName) {
	int nResult = ERR_NOERROR;
	Erase();
	FILE* fpt = NULL;
	try {
		if ((fpt = fopen(fstrFileName.c_str(), "rb")) == NULL) {
			throw int(ERR_CANNOTOPEN);
		}
		if (fseek(fpt, 0, SEEK_END) != 0) {
			throw int(ERR_IOERROR);
		}
		int nLength = int(ftell(fpt));
		if (nLength == -1) {
			throw int(ERR_IOERROR);
		}
		m_vectData.resize(nLength);
		if (fseek(fpt, 0, SEEK_SET) != 0) {
			throw int(ERR_IOERROR);
		}
		if (!ReadData(0, nLength, fpt)) {
			throw int(ERR_IOERROR);
		}
		fclose(fpt);
		fpt = NULL;
		m_fstrFileName = fstrFileName;
		if (nLength > 0) {
			int nTotalTick = 0;
			int nTick = TICK_HZ*2;
			m_listTag.push_back(
				CTapeImageTag(
					TAG_MARK,
				nTotalTick, nTick));
			nTotalTick += nTick;
			int nStartPos = 0;
			for (int nPos = 0; nPos <= nLength; ) {
				bool bUnknown = true, bDataOut = false;
				int nData = -1;
				if (nPos < nLength) {
					nData = m_vectData[nPos];
				}
				switch (nData) {
				case 0xD3:
					{ // dummy block
						if (nPos+10+6 > nLength) {
							break;
						}
						int nPos2;
						for (nPos2 = 0; nPos2 < 10; nPos2++) {
							if (m_vectData[nPos+nPos2] != 0xD3) {
								break;
							}
						}
						if (nPos2 < 10) {
							break;
						}
						nPos += 10+6;
						bUnknown = false;
						int nSize = nPos-nStartPos;
						nTick = GetStdDataTick(false)*nSize;
						m_listTag.push_back(
							CTapeImageTag(
								TAG_DATA,
								nTotalTick, nTick,
								uint16_t(nSize), GetStdDataType(false),
								nStartPos));
						nTotalTick += nTick;
						nStartPos += nSize;
						nTick = TICK_HZ/5;
						m_listTag.push_back(
							CTapeImageTag(
								TAG_MARK,
							nTotalTick, nTick));
						nTotalTick += nTick;
						if (nPos >= nLength) {
							break;
						}
						int nZeroCounter = 0;
						while (nPos < nLength) {
							if (m_vectData[nPos++] == 0x00) {
								if (++nZeroCounter >= 1+2+9) {
									break;
								}
							} else {
								if (nZeroCounter >= 10) {
									nPos--;
									break;
								}
								nZeroCounter = 0;
							}
						}
						if ((nPos < nLength) &&
							(m_vectData[nPos] == 0x00))
						{
							nPos++;
						}
						bDataOut = true;
					}
					break;
				case 0x24:
					{ // dummy block
						if (nPos+3+6 > nLength) {
							break;
						}
						int nPos2;
						for (nPos2 = 0; nPos2 < 3; nPos2++) {
							if (m_vectData[nPos+nPos2] != 0x24) {
								break;
							}
						}
						if (nPos2 < 3) {
							break;
						}
						nPos += 3+6;
						int nSize = nPos-nStartPos;
						nTick = GetStdDataTick(false)*nSize;
						m_listTag.push_back(
							CTapeImageTag(
								TAG_DATA,
								nTotalTick, nTick,
								uint16_t(nSize), GetStdDataType(false),
								nStartPos));
						nTotalTick += nTick;
						nStartPos += nSize;
						nTick = TICK_HZ/5;
						m_listTag.push_back(
							CTapeImageTag(
								TAG_MARK,
							nTotalTick, nTick));
						nTotalTick += nTick;
						if ((nPos >= nLength) ||
							(m_vectData[nPos] != 0x3A))
						{
							bUnknown = false;
							break;
						}
					}
					// no break
				case 0x3A:
				case 0x6E:
					{ // dummy block
						if (nPos+4 > nLength) {
							break;
						}
						nPos += 4;
						bUnknown = false;
						while (
							(nPos < nLength) &&
							(m_vectData[nPos] == 0x3A))
						{
							nPos++;
							if (nPos >= nLength) {
								break;
							}
							int nDataLength = m_vectData[nPos++];
							if (nPos+nDataLength+1 > nLength) {
								break;
							}
							nPos += nDataLength+1;
							if (nPos >= nLength) {
								break;
							}
							if (nDataLength <= 0) {
								break;
							}
						}
						if ((nPos < nLength) &&
							(m_vectData[nPos] == 0x00))
						{
							nPos++;
						}
						bDataOut = true;
					}
					break;
				case 0x9C:
					{ // dummy block
						if (nPos+6 > nLength) {
							break;
						}
						int nPos2;
						for (nPos2 = 0; nPos2 < 6; nPos2++) {
							if (m_vectData[nPos+nPos2] != 0x9C) {
								break;
							}
						}
						if (nPos2 < 6) {
							break;
						}
						nPos += 6;
						bUnknown = false;
						while (nPos < nLength) {
							if (m_vectData[nPos++] == 0x0D) {
								break;
							}
						}
						if ((nPos < nLength) &&
							(m_vectData[nPos] == 0x0A))
						{
							nPos++;
						}
						if ((nPos < nLength) &&
							(m_vectData[nPos] == 0x00))
						{
							nPos++;
						}
						bDataOut = true;
					}
					break;
				case -1:
					if (nStartPos < nPos) {
						bDataOut = true;
					}
					break;
				}
				if (bDataOut) {
					do {
						int nSize = nPos-nStartPos;
						if (nSize > DATATAG_MAX) {
							nSize = DATATAG_MAX;
						}
						nTick = GetStdDataTick(false)*nSize;
						m_listTag.push_back(
							CTapeImageTag(
								TAG_DATA,
								nTotalTick, nTick,
								uint16_t(nSize), GetStdDataType(false),
								nStartPos));
						nTotalTick += nTick;
						nStartPos += nSize;
					} while (nStartPos < nPos);
					nTick = TICK_HZ*2;
					m_listTag.push_back(
						CTapeImageTag(
							TAG_MARK,
						nTotalTick, nTick));
					nTotalTick += nTick;
				}
				if (bUnknown) {
					nPos++;
				}
			}
		}
		MakeBlockInfo();
	} catch (int nError) {
		if (fpt != NULL) {
			fclose(fpt);
		}
		Erase();
		SeekBlockCount(0);
		nResult = nError;
	}
	return nResult;
}

// save CMT file

int CTapeImage::SaveCMT(const std::string& fstrFileName) {
	int nResult = ERR_NOERROR;
	FILE* fpt = NULL;
	try {
		if ((fpt = fopen(fstrFileName.c_str(), "wb")) == NULL) {
			throw int(ERR_CANNOTOPEN);
		}
		if (!WriteData(0, (int)m_vectData.size(), fpt)) {
			throw int(ERR_IOERROR);
		}
		if (fflush(fpt) != 0) {
			throw int(ERR_IOERROR);
		}
		fclose(fpt);
		fpt = NULL;
	} catch (int nError) {
		if (fpt != NULL) {
			fclose(fpt);
		}
		unlink(fstrFileName.c_str());
		nResult = nError;
	}
	return nResult;
}

// get valid block count

int CTapeImage::GetRealDataBlockCount() {
	int nRealDataBlockCount = 0;
	for (int nBlock = 0; nBlock < GetDataBlockCount(); nBlock++) {
		if ((nBlock <= 0) || (m_vectWait[nBlock] > 0)) {
			nRealDataBlockCount++;
		}
	}
	return nRealDataBlockCount;
}

// get total tick

int CTapeImage::GetTotalTick() {
	int nTick = 0;
	if (GetTagCount() > 0) {
		std::list<CTapeImageTag>::iterator itTag = m_listTag.end();
		do {
			itTag--;
			switch ((*itTag).m_wTagType) {
			case TAG_BLANK:
			case TAG_DATA:
			case TAG_MARK:
			case TAG_SPACE:
				nTick = (*itTag).m_dwBeginTick+(*itTag).m_dwSizeTick;
				break;
			}
		} while ((nTick <= 0) && (itTag != m_listTag.begin()));
	}
	return nTick;
}

// get counter tick

int CTapeImage::GetCounterTick() {
	int nTick = 0;
	if (GetDataBlockCount() > 0) {
		int nBlock = m_nCurBlock, nPos = m_nCurPos;
		if (nBlock >= GetDataBlockCount()) {
			nBlock = GetDataBlockCount()-1;
			nPos = m_vectSize[nBlock];
		}
		int nOfs = m_vectOfs[nBlock];
		for (
			std::list<CTapeImageTag>::iterator itTag = m_listTag.begin();
			itTag != m_listTag.end();
			itTag++)
		{
			if (((*itTag).m_wTagType == TAG_DATA) &&
				(int((*itTag).m_dwDataOfs) == nOfs))
			{
				nTick = (*itTag).m_dwBeginTick;
				if (m_nTick > 0) {
					nTick -= m_nTick;
					int nGapMax = m_vectWait[nBlock];
					if (nGapMax > TICK_HZ*GAP_MAX) {
						nTick -= nGapMax-TICK_HZ*GAP_MAX;
					}
				} else {
					nTick += nPos*GetStdDataTick((*itTag).IsBaud1200());
				}
			}
		}
	}
	return nTick;
}

// forward counter

void CTapeImage::CounterFWD() {
	if (m_nCurBlock < GetDataBlockCount()) {
		int nNewBlock = m_nCurBlock+1;
		SeekBlockCount(nNewBlock);
	}
}

// rewind counter

void CTapeImage::CounterREW() {
	int nNewBlock = m_nCurBlock;
	if ((nNewBlock > 0) &&
		((nNewBlock >= GetDataBlockCount()) || (m_nTick > 0)))
	{
		nNewBlock--;
	}
	while (true) {
		SeekBlockCount(nNewBlock);
		if ((nNewBlock <= 0) || (m_nTick > 0)) {
			break;
		}
		nNewBlock--;
	}
}
