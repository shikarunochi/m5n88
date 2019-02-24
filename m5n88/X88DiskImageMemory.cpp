////////////////////////////////////////////////////////////
// X88000 DiskImage Memory Manager
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "X88DiskImageMemory.h"

#include "DiskImageFile.h"

////////////////////////////////////////////////////////////
// implementation of CX88DiskImageMemory
// (disk image memory management class)

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CX88DiskImageMemory::CX88DiskImageMemory() :
	m_bReadOnly(true),
	m_pbtData(NULL),
	m_dwSize(0)
{

#ifdef X88_PLATFORM_WINDOWS

	m_hFile = NULL;
	m_hFileMap = NULL;

#elif defined(X88_PLATFORM_UNIX)

	m_nFile = -1;
	m_bMemoryMappedFile = false;

#endif // X88_PLATFORM

}

// standard constructor(buffer specified)

CX88DiskImageMemory::CX88DiskImageMemory(uint8_t* btData) :
	m_bReadOnly(true),
	m_pbtData(btData),
	m_dwSize(0)
{

#ifdef X88_PLATFORM_WINDOWS

	m_hFile = NULL;
	m_hFileMap = NULL;

#elif defined(X88_PLATFORM_UNIX)

	m_nFile = -1;
	m_bMemoryMappedFile = false;

#endif // X88_PLATFORM

}

// copy constructor(shallow copy)

CX88DiskImageMemory::CX88DiskImageMemory(
		const CX88DiskImageMemory& dimOther) :
	m_bReadOnly(dimOther.m_bReadOnly),
	m_pbtData(dimOther.m_pbtData),
	m_dwSize(dimOther.m_dwSize)
{

#ifdef X88_PLATFORM_WINDOWS

	m_hFile = dimOther.m_hFile;
	m_hFileMap = dimOther.m_hFileMap;

#elif defined(X88_PLATFORM_UNIX)

	m_nFile = dimOther.m_nFile;
	m_bMemoryMappedFile = dimOther.m_bMemoryMappedFile;

#endif // X88_PLATFORM

}

// destructor

CX88DiskImageMemory::~CX88DiskImageMemory() {
}

////////////////////////////////////////////////////////////
// operator

// let(shallow copy)

CX88DiskImageMemory& CX88DiskImageMemory::operator=(
	const CX88DiskImageMemory& dimOther)
{
	m_bReadOnly = dimOther.m_bReadOnly;
	m_pbtData = dimOther.m_pbtData;
	m_dwSize = dimOther.m_dwSize;

#ifdef X88_PLATFORM_WINDOWS

	m_hFile = dimOther.m_hFile;
	m_hFileMap = dimOther.m_hFileMap;

#elif defined(X88_PLATFORM_UNIX)

	m_nFile = dimOther.m_nFile;
	m_bMemoryMappedFile = dimOther.m_bMemoryMappedFile;

#endif // X88_PLATFORM

	return *this;
}

// compare(equal)

bool CX88DiskImageMemory::operator==(
	const CX88DiskImageMemory& dimOther) const
{
	return m_pbtData == dimOther.m_pbtData;
}

// compare(less)

bool CX88DiskImageMemory::operator<(
	const CX88DiskImageMemory& dimOther) const
{
	return m_pbtData < dimOther.m_pbtData;
}

////////////////////////////////////////////////////////////
// operation

// create

int CX88DiskImageMemory::Create(
	const std::string& fstrFileName, bool bReadOnly)
{
	m_bReadOnly = bReadOnly;
	m_pbtData = NULL;
	m_dwSize = 0;

#ifdef X88_PLATFORM_WINDOWS

	m_hFile = NULL;
	m_hFileMap = NULL;
	int nResult = CDiskImageFile::ERR_NOERROR;
	try {
		m_hFile = CreateFile(
			fstrFileName.c_str(),
			m_bReadOnly? GENERIC_READ: (GENERIC_READ | GENERIC_WRITE),
			m_bReadOnly? FILE_SHARE_READ: 0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (m_hFile == INVALID_HANDLE_VALUE) {
			if (m_bReadOnly) {
				m_hFile = NULL;
				throw int(CDiskImageFile::ERR_CANNOTOPEN);
			}
			m_bReadOnly = true;
			m_hFile = CreateFile(
				fstrFileName.c_str(),
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (m_hFile == INVALID_HANDLE_VALUE) {
				m_hFile = NULL;
				throw int(CDiskImageFile::ERR_CANNOTOPEN);
			}
		}
		BY_HANDLE_FILE_INFORMATION hfi;
		if (!GetFileInformationByHandle(m_hFile, &hfi) ||
			(hfi.nFileSizeLow == 0))
		{
			throw int(CDiskImageFile::ERR_IOERROR);
		}
		m_dwSize = hfi.nFileSizeLow;
		if (!m_bReadOnly) {
			if ((m_hFileMap = CreateFileMapping(
					m_hFile,
					NULL, PAGE_READWRITE, 0, 0,
					NULL)) != NULL)
			{
				if ((m_pbtData = (uint8_t*)MapViewOfFile(
						m_hFileMap,
						FILE_MAP_WRITE, 0, 0, m_dwSize)) == NULL)
				{
					CloseHandle(m_hFileMap);
					m_hFileMap = NULL;
				}
			}
		}
		if (m_hFileMap == NULL) {
			if ((m_pbtData = (uint8_t*)malloc(m_dwSize)) == NULL) {
				throw int(CDiskImageFile::ERR_FEWMEMORY);
			}
			uint32_t dwReadSize;
			if (!ReadFile(
					m_hFile, m_pbtData, m_dwSize, &dwReadSize, NULL))
			{
				throw int(CDiskImageFile::ERR_IOERROR);
			}
			if (m_bReadOnly) {
				CloseHandle(m_hFile);
				m_hFile = NULL;
			}
		}
	} catch (int nError) {
		Destroy();
		m_pbtData = NULL;
		m_dwSize = 0;
		m_hFile = NULL;
		m_hFileMap = NULL;
		nResult = nError;
	}

#elif defined(X88_PLATFORM_UNIX)

	File file;

	m_nFile = -1;
	m_bMemoryMappedFile = false;
	int nResult = CDiskImageFile::ERR_NOERROR;
/*
	try {
		m_nFile = open(
			fstrFileName.c_str(),
			m_bReadOnly? O_RDONLY: O_RDWR);
		if (m_nFile == -1) {
			if (m_bReadOnly) {
				throw int(CDiskImageFile::ERR_CANNOTOPEN);
			}
			m_bReadOnly = true;
			m_nFile = open(
				fstrFileName.c_str(),
				O_RDONLY);
			if (m_nFile == -1) {
				throw int(CDiskImageFile::ERR_CANNOTOPEN);
			}
		}
		off_t nLength = lseek(m_nFile, 0, SEEK_END);
		if (nLength <= 0) {
			throw int(CDiskImageFile::ERR_IOERROR);
		}
*/
		file = SD.open(String("/PC88ROM/pc8801disk.d88"));
		Serial.println("OpenDiskImage");
		int nLength = file.size();
		Serial.print("length:");
		Serial.println(nLength);
		m_dwSize = nLength;

		//if (!m_bReadOnly) {
		//	m_pbtData = (uint8_t*)mmap(
		//		NULL, m_dwSize,
		//		PROT_READ | PROT_WRITE, MAP_SHARED,
		//		m_nFile, 0);
		//	if (m_pbtData != NULL) {
		//		m_bMemoryMappedFile = true;
		//	}
		//}
		if (!m_bMemoryMappedFile) {
			if ((m_pbtData = (uint8_t*)ps_malloc(m_dwSize)) == NULL) {
				Serial.print("Memory Over!!!!!");
				throw int(CDiskImageFile::ERR_FEWMEMORY);
			}
			int offset = 0;
			while (file.available()) {
				*(m_pbtData + offset) = file.read();
      			offset++;
	  			if(offset >= nLength){
					  break;
	  			}
 			}

			if (m_bReadOnly) {
				file.close();
				m_nFile = -1;
			}
		}
	
		Serial.println("OpenDiskImage:DONE!");
#endif // X88_PLATFORM

	return nResult;
}

// destroy

int CX88DiskImageMemory::Destroy() const {

#ifdef X88_PLATFORM_WINDOWS

	if (m_hFileMap != NULL) {
		if (m_pbtData != NULL) {
			UnmapViewOfFile(m_pbtData);
		}
	} else {
		if (m_pbtData != NULL) {
			free(m_pbtData);
		}
	}
	if (m_hFileMap != NULL) {
		CloseHandle(m_hFileMap);
	}
	if (m_hFile != NULL) {
		CloseHandle(m_hFile);
	}

#elif defined(X88_PLATFORM_UNIX)

	//if (m_bMemoryMappedFile) {
	//	if (m_pbtData != NULL) {
	//		munmap((caddr_t)m_pbtData, m_dwSize);
	//	}
	//} else {
	if (m_pbtData != NULL) {
			free(m_pbtData);
		}
	//}
	if (m_nFile != -1) {
		close(m_nFile);
	}

#endif // X88_PLATFORM

	return CDiskImageFile::ERR_NOERROR;
}

// flush data

int CX88DiskImageMemory::Flush() const {
	int nResult = CDiskImageFile::ERR_NOERROR;

#ifdef X88_PLATFORM_WINDOWS

	if (m_pbtData != NULL) {
		if (m_hFileMap != NULL) {
		} else if (!m_bReadOnly && (m_hFile != NULL)) {
			uint32_t dwWriteSize;
			if (!WriteFile(
					m_hFile, m_pbtData, m_dwSize, &dwWriteSize, NULL))
			{
				nResult = CDiskImageFile::ERR_IOERROR;
			}
		}
	}

#elif defined(X88_PLATFORM_UNIX)

	if (m_pbtData != NULL) {
		//if (m_bMemoryMappedFile) {
		//	if (msync((caddr_t)m_pbtData, m_dwSize, MS_ASYNC) == -1) {
		//		nResult = CDiskImageFile::ERR_IOERROR;
		//	}
		//} else
		if (!m_bReadOnly && (m_nFile != -1)) {
			if (write(m_nFile, m_pbtData, m_dwSize) == -1) {
				nResult = CDiskImageFile::ERR_IOERROR;
			}
		}
	}

#endif // X88_PLATFORM

	return nResult;
}
