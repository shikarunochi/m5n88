////////////////////////////////////////////////////////////
// X88000 Utility
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "X88Utility.h"

////////////////////////////////////////////////////////////
// implementation of NX88Utility

////////////////////////////////////////////////////////////
// JIS

// ASCII half-width -> JIS full-width table

static uint16_t s_awAscii[] = {
	0x2121, 0x212A, 0x2149, 0x2174, 0x2170, 0x2173, 0x2175, 0x2147,
	0x214A, 0x214B, 0x2176, 0x215C, 0x2124, 0x215D, 0x2125, 0x213F,
	0x2330, 0x2331, 0x2332, 0x2333, 0x2334, 0x2335, 0x2336, 0x2337,
	0x2338, 0x2339, 0x2127, 0x2128, 0x2163, 0x2161, 0x2164, 0x2129,
	0x2177, 0x2341, 0x2342, 0x2343, 0x2344, 0x2345, 0x2346, 0x2347,
	0x2348, 0x2349, 0x234A, 0x234B, 0x234C, 0x234D, 0x234E, 0x234F,
	0x2350, 0x2351, 0x2352, 0x2353, 0x2354, 0x2355, 0x2356, 0x2357,
	0x2358, 0x2359, 0x235A, 0x214E, 0x216F, 0x214F, 0x2130, 0x2132,
	0x2146, 0x2361, 0x2362, 0x2363, 0x2364, 0x2365, 0x2366, 0x2367,
	0x2368, 0x2369, 0x236A, 0x236B, 0x236C, 0x236D, 0x236E, 0x236F,
	0x2370, 0x2371, 0x2372, 0x2373, 0x2374, 0x2375, 0x2376, 0x2377,
	0x2378, 0x2379, 0x237A, 0x2150, 0x2143, 0x2151, 0x2131
};

// ANK katakana half-width -> JIS katakana full-width table

static uint16_t s_awKana[] = {
	        0x2123, 0x2156, 0x2157, 0x2122, 0x2126, 0x2572, 0x2521,
	0x2523, 0x2525, 0x2527, 0x2529, 0x2563, 0x2565, 0x2567, 0x2543,
	0x213C, 0x2522, 0x2524, 0x2526, 0x2528, 0x252A, 0x252B, 0x252D,
	0x252F, 0x2531, 0x2533, 0x2535, 0x2537, 0x2539, 0x253B, 0x253D,
	0x253F, 0x2541, 0x2544, 0x2546, 0x2548, 0x254A, 0x254B, 0x254C,
	0x254D, 0x254E, 0x254F, 0x2552, 0x2555, 0x2558, 0x255B, 0x255E,
	0x255F, 0x2560, 0x2561, 0x2562, 0x2564, 0x2566, 0x2568, 0x2569,
	0x256A, 0x256B, 0x256C, 0x256D, 0x256F, 0x2573, 0x212B, 0x212C
};

// exception character JIS full-width -> ANK half-width table

static uint16_t s_awZen2HanException[][2] = {
	{ 0x212D, 0x60 },
	{ 0x2141, 0x7E },
	{ 0x256E, 0xDC },
	{ 0x2570, 0xB2 },
	{ 0x2571, 0xB4 },
	{ 0x2575, 0xB6 },
	{ 0x2576, 0xB9 }
};

// full-width -> half-width map

static std::map<uint16_t, uint8_t> s_mapHankaku;

// is SJIS lead byte

bool NX88Utility::IsSJISLeadByte(uint8_t btSJIS) {
	return ((btSJIS >= 0x81) && (btSJIS <= 0x9F)) ||
		((btSJIS >= 0xE0) && (btSJIS <= 0xEF));
}

////////////////////////////////////////////////////////////
// encoding

// convert JIS to SJIS

unsigned NX88Utility::JIS2SJIS(unsigned nJIS) {
	unsigned nSJIS = 0,
		nHi = (nJIS >> 8) & 0xFF,
		nLo = nJIS & 0xFF;
	if ((nHi == 0x00) &&
		(((nLo >= 0x21) && (nLo <= 0x7E)) ||
			((nLo >= 0xA0) && (nLo <= 0xDF))))
	{
		nSJIS = nLo;
	} else if (
		(nHi >= 0x21) && (nHi <= 0x7E) &&
		(nLo >= 0x21) && (nLo <= 0x7E))
	{
		unsigned nSerial = ((nHi-0x21)*0x5E)+(nLo-0x21);
		nHi = nSerial/(0x5E*2)+0x81;
		nLo = (nSerial%(0x5E*2))+0x40;
		if (nHi >= 0xA0) {
			nHi += 0x40;
		}
		if (nLo >= 0x7F) {
			nLo++;
		}
		nSJIS = (nHi << 8) | nLo;
	}
	return nSJIS;
}

// convert SJIS to JIS

unsigned NX88Utility::SJIS2JIS(unsigned nSJIS) {
	unsigned nJIS = 0,
		nHi = (nSJIS >> 8) & 0xFF,
		nLo = nSJIS & 0xFF;
	if ((nHi == 0x00) &&
		(((nLo >= 0x21) && (nLo <= 0x7E)) ||
			((nLo >= 0xA0) && (nLo <= 0xDF))))
	{
		nJIS = nLo;
	} else if (
		(((nHi >= 0x81) && (nHi <= 0x9F)) ||
			((nHi >= 0xE0) && (nHi <= 0xEF))) &&
		(((nLo >= 0x40) && (nLo <= 0x7E)) ||
			((nLo >= 0x80) && (nLo <= 0xFC))))
	{
		if (nHi >= 0xE0) {
			nHi -= 0x40;
		}
		if (nLo >= 0x80) {
			nLo--;
		}
		unsigned nSerial = (nHi-0x81)*(0x5E*2)+(nLo-0x40);
		nHi = (nSerial/0x5E)+0x21;
		nLo = (nSerial%0x5E)+0x21;
		nJIS = (nHi << 8) | nLo;
	}
	return nJIS;
}

// convert JIS-half-width -> JIS-full-width

unsigned NX88Utility::JISHan2Zen(unsigned nHan) {
	unsigned nZen = 0;
	if (nHan < 0x80) {
		if ((nHan >= 0x20) && (nHan <= 0x7E)) {
			nZen = s_awAscii[nHan-0x20];
		}
	} else {
		if ((nHan >= 0xA1) && (nHan <= 0xDF)) {
			nZen = s_awKana[nHan-0xA1];
		}
	}
	return nZen;
}

// convert JIS-full-width -> JIS-half-width

unsigned NX88Utility::JISZen2Han(
	unsigned nZen,
	bool* pbDakuten, bool* pbHandakuten)
{
	if (s_mapHankaku.size() <= 0) {
		int i;
		for (i = 0x20; i <= 0x7E; i++) {
			s_mapHankaku.insert(
				std::make_pair(s_awAscii[i-0x20], (uint8_t)i));
		}
		for (i = 0xA1; i <= 0xDF; i++) {
			s_mapHankaku.insert(
				std::make_pair(s_awKana[i-0xA1], (uint8_t)i));
		}
		for (
			i = 0;
			i < sizeof(s_awZen2HanException)/sizeof(s_awZen2HanException[0]);
			i++)
		{
		s_mapHankaku.insert(
			std::make_pair(
				s_awZen2HanException[i][0],
				(uint8_t)s_awZen2HanException[i][1]));
		}
	}
	unsigned nHan = 0;
	bool bDakuten = false, bHandakuten = false;
	if ((nZen >= 0x2421) && (nZen <= 0x2473)) {
		nZen = 0x2500 | (nZen & 0xFF);
	}
	if ((nZen >= 0x2521) && (nZen <= 0x2576)) {
		if ((nZen >= 0x252B) && (nZen <= 0x2542)) {
			int n = nZen-0x252B;
			nZen = 0x252B+(n/2)*2;
			switch (n%2) {
			case 1:
				bDakuten = true;
				break;
			}
		} else if ((nZen >= 0x2544) && (nZen <= 0x2549)) {
			int n = nZen-0x2544;
			nZen = 0x2544+(n/2)*2;
			switch (n%2) {
			case 1:
				bDakuten = true;
				break;
			}
		} else if ((nZen >= 0x254F) && (nZen <= 0x255D)) {
			int n = nZen-0x254F;
			nZen = 0x254F+(n/3)*3;
			switch (n%3) {
			case 1:
				bDakuten = true;
				break;
			case 2:
				bHandakuten = true;
				break;
			}
		} else if (nZen == 0x2574) {
			nZen = 0x2526;
			bDakuten = true;
		}
	}
	std::map<uint16_t, uint8_t>::const_iterator itHankaku =
		s_mapHankaku.find((uint16_t)nZen);
	if (itHankaku != s_mapHankaku.end()) {
		nHan = (*itHankaku).second;
	}
	if (pbDakuten != NULL) {
		*pbDakuten = bDakuten;
	}
	if (pbHandakuten != NULL) {
		*pbHandakuten = bHandakuten;
	}
	return nHan;
}

#ifdef X88_ENCODE_WINDOWS

static std::string ConvXtoUTF8(
	int nCodePage,
	const std::string& strOrg)
{
	int nLength = MultiByteToWideChar(
		nCodePage, MB_PRECOMPOSED,
		strOrg.c_str(), (int)strOrg.length(),
		NULL, 0);
	if (nLength <= 0) {
		return "";
	}
	std::vector<wchar_t> vectWide;
	vectWide.resize(nLength, 0);
	MultiByteToWideChar(
		nCodePage, MB_PRECOMPOSED,
		strOrg.c_str(), (int)strOrg.length(),
		&vectWide[0], nLength);
	std::string strConv;
	strConv.reserve(nLength*3);
	const wchar_t* pszWide = &vectWide[0];
	for (int i = 0; i < nLength; i++) {
		uint32_t uch = *pszWide++;
		if ((uch >= 0xD800U) && (uch <= 0xDBFFU)) {
			// surrogate pair
			if (i < nLength+1) {
				i++;
				uint32_t uch2 = *pszWide++;
				if ((uch2 >= 0xDC00U) && (uch2 <= 0xDFFFU)) {
					uch = 0x10000U+
						((uch & 0x03FFU) << 10)+
						(uch2 & 0x03FFU);
				} else {
					// surrogate-low error
					uch = (uint32_t)'?';
				}
			} else {
				// surrogate pair error
				uch = (uint32_t)'?';
			}
		}
		if (uch < 0x80U) {
			strConv += (char)uch;
		} else if (uch < 0x800U) {
			strConv += (char)(((uch >> 6) & 0x3F) | 0xC0);
			strConv += (char)((uch & 0x3F) | 0x80);
		} else if (uch < 0x10000U) {
			strConv += (char)(((uch >> 12) & 0x3F) | 0xE0);
			strConv += (char)(((uch >> 6) & 0x3F) | 0x80);
			strConv += (char)((uch & 0x3F) | 0x80);
		} else if (uch < 0x200000U) {
			strConv += (char)(((uch >> 18) & 0x3F) | 0xF0);
			strConv += (char)(((uch >> 12) & 0x3F) | 0x80);
			strConv += (char)(((uch >> 6) & 0x3F) | 0x80);
			strConv += (char)((uch & 0x3F) | 0x80);
		} else if (uch < 0x4000000U) {
			strConv += (char)(((uch >> 24) & 0x3F) | 0xF8);
			strConv += (char)(((uch >> 18) & 0x3F) | 0x80);
			strConv += (char)(((uch >> 12) & 0x3F) | 0x80);
			strConv += (char)(((uch >> 6) & 0x3F) | 0x80);
			strConv += (char)((uch & 0x3F) | 0x80);
		} else if (uch < 0x8000000U) {
			strConv += (char)(((uch >> 30) & 0x3F) | 0xFC);
			strConv += (char)(((uch >> 24) & 0x3F) | 0x80);
			strConv += (char)(((uch >> 18) & 0x3F) | 0x80);
			strConv += (char)(((uch >> 12) & 0x3F) | 0x80);
			strConv += (char)(((uch >> 6) & 0x3F) | 0x80);
			strConv += (char)((uch & 0x3F) | 0x80);
		} else {
			strConv += '?';
		}
	}
	return strConv;
}

static std::string ConvUTF8toX(
	int nCodePage,
	const std::string& strOrg)
{
	if (strOrg.length() <= 0) {
		return "";
	}
	std::vector<wchar_t> vectWide;
	vectWide.reserve(strOrg.length());
	const char* pszSrc = strOrg.c_str();
	const char* pszSrcLast = pszSrc+strOrg.length();
	while (pszSrc != pszSrcLast) {
		uint8_t bt = *(pszSrc++);
		uint32_t uch = 0, minimum = 0;
		int trail = 0;
		if (bt < 0x80) {
			uch = bt;
		} else if (bt < 0xC0) {
			// trail byte
		} else if (bt < 0xE0) {
			minimum = 0x80U;
			uch = bt & 0x1F;
			trail = 1;
		} else if (bt < 0xF0) {
			minimum = 0x800U;
			uch = bt & 0x0F;
			trail = 2;
		} else if (bt < 0xF8) {
			minimum = 0x10000U;
			uch = bt & 0x07;
			trail = 3;
		} else if (bt < 0xFC) {
			minimum = 0x200000U;
			uch = bt & 0x03;
			trail = 4;
		} else if (bt < 0xFE) {
			minimum = 0x4000000U;
			uch = bt & 0x01;
			trail = 5;
		} else {
			// unknown
		}
		while ((trail > 0) && (pszSrc != pszSrcLast)) {
			uch = (uch << 6) | ((uint8_t)*(pszSrc++) & 0x3F);
			trail--;
		}
		if (uch < minimum) {
			uch = 0;
		}
		if (uch < 0x10000U) {
			vectWide.push_back(
				(wchar_t)uch);
		} else if (uch < 0x110000U) {
			vectWide.push_back(
				(wchar_t)((((uch-0x10000U) >> 10) & 0x03FFU) | 0xD800U));
			vectWide.push_back(
				(wchar_t)(((uch-0x10000U) & 0x03FFU) | 0xDC00U));
		} else {
			// out of range
		}
	}
	if (vectWide.size() <= 0) {
		return "";
	}
	int nLength = WideCharToMultiByte(
		nCodePage, 0,
		&vectWide[0], (int)vectWide.size(),
		NULL, 0,
		NULL, NULL);
	if (nLength <= 0) {
		return "";
	}
	std::vector<char> vectConv(nLength);
	WideCharToMultiByte(
		nCodePage, 0,
		&vectWide[0], (int)vectWide.size(),
		&vectConv[0], nLength,
		NULL, NULL);
	std::string strConv(&vectConv[0], &vectConv[0]+nLength);
	return strConv;
}

#elif defined(X88_ENCODE_GTK)

// special encoding

static const char s_szEncUTF8[] = "UTF-8";
static const char s_szEncSJIS[] = "CP932";
static const char s_szEncLOC[] = "locale";
static const char s_szEncFS[] = "filesystem";

// convert string encoding(specified 2 encodings)

static std::string ConvXtoY(
	const char* pszEncSrc,
	const char* pszEncDst,
	const std::string& strOrg)
{
	if (pszEncSrc == pszEncDst) {
		return strOrg;
	}
	gsize nWritten = 0;
	char* pszConv;
	if ((pszEncSrc == s_szEncLOC) && (pszEncDst == s_szEncUTF8)) {
		pszConv = g_locale_to_utf8(
			strOrg.c_str(), strOrg.length(),
			NULL, &nWritten, NULL);
	} else if ((pszEncSrc == s_szEncUTF8) && (pszEncDst == s_szEncLOC)) {
		pszConv = g_locale_from_utf8(
			strOrg.c_str(), strOrg.length(),
			NULL, &nWritten, NULL);
	} else if ((pszEncSrc == s_szEncFS) && (pszEncDst == s_szEncUTF8)) {
		pszConv = g_filename_to_utf8(
			strOrg.c_str(), strOrg.length(),
			NULL, &nWritten, NULL);
	} else if ((pszEncSrc == s_szEncUTF8) && (pszEncDst == s_szEncFS)) {
		pszConv = g_filename_from_utf8(
			strOrg.c_str(), strOrg.length(),
			NULL, &nWritten, NULL);
	} else {
		pszConv = g_convert(
			strOrg.c_str(), strOrg.length(),
			pszEncDst, pszEncSrc,
			NULL, &nWritten, NULL);
	}
	std::string strConv;
	if (pszConv != NULL) {
		strConv = std::string(pszConv, pszConv+nWritten);
		g_free(pszConv);
	}
	return strConv;
}

#endif // X88_ENCODE

// convert string encoding(SJIS -> UTF-8)

std::string NX88Utility::ConvSJIStoUTF8(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvXtoUTF8(932, strOrg);

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncSJIS, s_szEncUTF8, strOrg);

#endif // X88_ENCODE

}

// convert string encoding(UTF-8 -> SJIS)

std::string NX88Utility::ConvUTF8toSJIS(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvUTF8toX(932, strOrg);

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncUTF8, s_szEncSJIS, strOrg);

#endif // X88_ENCODE

}

// convert string encoding(source -> UTF-8)

std::string NX88Utility::ConvSRCtoUTF8(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvXtoUTF8(CP_OEMCP, strOrg);

#elif defined(X88_ENCODE_GTK)

	return strOrg;

#endif // X88_ENCODE

}

// convert string encoding(GUI -> UTF-8)

std::string NX88Utility::ConvGUItoUTF8(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

#ifdef X88_ENCODING_GUI_SJIS

	return ConvXtoUTF8(CP_OEMCP, strOrg);

#elif defined(X88_ENCODING_GUI_UTF8)

	return strOrg;

#endif // X88_ENCODING_GUI

#elif defined(X88_ENCODE_GTK)

	return strOrg;

#endif // X88_ENCODE

}

// convert string encoding(UTF-8 -> GUI)

std::string NX88Utility::ConvUTF8toGUI(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

#ifdef X88_ENCODING_GUI_SJIS

	return ConvUTF8toX(CP_OEMCP, strOrg);

#elif defined(X88_ENCODING_GUI_UTF8)

	return strOrg;

#endif // X88_ENCODING_GUI

#elif defined(X88_ENCODE_GTK)

	return strOrg;

#endif // X88_ENCODE
	return strOrg;
}

// convert string encoding(source -> GUI)

std::string NX88Utility::ConvSRCtoGUI(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

#ifdef X88_ENCODING_GUI_SJIS

	return strOrg;

#elif defined(X88_ENCODING_GUI_UTF8)

	return ConvXtoUTF8(CP_OEMCP, strOrg);

#endif // X88_ENCODING_GUI

#elif defined(X88_ENCODE_GTK)

	return strOrg;

#endif // X88_ENCODE

}

// convert string encoding(locale -> UTF-8)

std::string NX88Utility::ConvLOCtoUTF8(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvXtoUTF8(CP_OEMCP, strOrg);

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncLOC, s_szEncUTF8, strOrg);

#endif // X88_ENCODE

}

// convert string encoding(UTF-8 -> locale)

std::string NX88Utility::ConvUTF8toLOC(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvUTF8toX(CP_OEMCP, strOrg);

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncUTF8, s_szEncLOC, strOrg);

#endif // X88_ENCODE

}

// convert string encoding(filesystem -> UTF-8)

std::string NX88Utility::ConvFStoUTF8(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvXtoUTF8(CP_OEMCP, strOrg);

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncFS, s_szEncUTF8, strOrg);

#endif // X88_ENCODE

}

// convert string encoding(UTF-8 -> filesystem)

std::string NX88Utility::ConvUTF8toFS(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

	return ConvUTF8toX(CP_OEMCP, strOrg);

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncUTF8, s_szEncFS, strOrg);

#endif // X88_ENCODE
	//Not convert
	return strOrg;
}

// convert string encoding(filesystem -> GUI)

std::string NX88Utility::ConvFStoGUI(
	const std::string& strOrg)
{

#ifdef X88_ENCODE_WINDOWS

#ifdef X88_ENCODING_GUI_SJIS

	return strOrg;

#elif defined(X88_ENCODING_GUI_UTF8)

	return ConvXtoUTF8(CP_OEMCP, strOrg);

#endif // X88_ENCODING_GUI

#elif defined(X88_ENCODE_GTK)

	return ConvXtoY(s_szEncFS, s_szEncUTF8, strOrg);

#endif // X88_ENCODE

}

////////////////////////////////////////////////////////////
// string

// to lower string

void NX88Utility::StrToLwr(std::string& strTarget) {
	for (std::string::size_type i = 0; i < strTarget.size(); i++) {
		if (islower(strTarget[i])) {
			strTarget[i] = (char)tolower(strTarget[i]);
		}
	}
}

// compare string(ignore case)

int NX88Utility::StrCaseCmp(
	const std::string& strL, const std::string& strR)
{
	return strcasecmp(strL.c_str(), strR.c_str());
}

// convert string to integer

int NX88Utility::AtoI(const std::string& strNum) {
	return atoi(strNum.c_str());
}

// format string

// format string

std::string NX88Utility::FormatStrV(
	const char* pszFormat, va_list ap)
{
	size_t nLength = 64/2;
	char* pszBuf = NULL;
	int nResult;
	do {
		nLength *= 2;
		char* pszNewBuf;
		if (pszBuf == NULL) {
			pszNewBuf = (char*)malloc(nLength+1);
		} else {
			pszNewBuf = (char*)realloc(pszBuf, nLength+1);
		}
		if (pszNewBuf == NULL) {
			if (pszBuf != NULL) {
				free(pszBuf);
			}
			throw std::bad_alloc();
		}
		pszBuf = pszNewBuf;

#ifdef va_copy

		va_list ap2;
		va_copy(ap2, ap);
		nResult  = vsnprintf(pszBuf, nLength, pszFormat, ap2);
		va_end(ap2);

#else // !va_copy

		nResult  = vsnprintf(pszBuf, nLength, pszFormat, ap);

#endif // va_copy

		pszBuf[nLength] = '\0';

#ifdef X88_PLATFORM_UNIX

		if (nResult >= nLength) {
			nResult = -1;
		}

#endif // X88_PLATFORM

	} while (nResult < 0);
	std::string str = pszBuf;
	free(pszBuf);
	return str;
}

std::string NX88Utility::FormatStr(
	const char* pszFormat, ...)
{
	va_list ap;
	va_start(ap, pszFormat);
	std::string str = FormatStrV(pszFormat, ap);
	va_end(ap);
	return str;
}

// is contained non-ascii character

bool NX88Utility::IsContainedNonASCII(const char* pszTarget) {
	bool bContained = false;
	for (const char* pszCheck = pszTarget; *pszCheck != '\0'; pszCheck++) {
		if ((uint8_t)*pszCheck >= 0x80) {
			bContained = true;
			break;
		}
	}
	return bContained;
}

////////////////////////////////////////////////////////////
// filename

// get file ext(filesystem encoding)

std::string NX88Utility::GetFileExt(const std::string& fstrFileName) {
	std::string fstrExt;

#ifdef X88_PLATFORM_WINDOWS

	char fszExt[_MAX_EXT];
	_splitpath(
		fstrFileName.c_str(),
		NULL, NULL, NULL, fszExt);
	fstrExt = fszExt;

#elif defined(X88_PLATFORM_UNIX)

	const char* pfszExt = strrchr(fstrFileName.c_str(), '.');
	if (pfszExt != NULL) {
		fstrExt = pfszExt;
	}

#endif // X88_PLATFORM

	return fstrExt;
}
