////////////////////////////////////////////////////////////
// X88000 Utility
//
// Written by Manuke

#ifndef X88Utility_DEFINED
#define X88Utility_DEFINED

////////////////////////////////////////////////////////////
// declaration of NX88Utility

namespace NX88Utility {
// JIS

	// is SJIS lead byte
	bool IsSJISLeadByte(uint8_t btSJIS);
	// convert JIS to SJIS
	unsigned JIS2SJIS(unsigned nJIS);
	// convert SJIS to JIS
	unsigned SJIS2JIS(unsigned nSJIS);
	// convert JIS-half-width -> JIS-full-width
	unsigned JISHan2Zen(unsigned nHan);
	// convert JIS-full-width -> JIS-half-width
	unsigned JISZen2Han(
		unsigned nZen,
		bool* pbDakuten = NULL, bool* pbHandakuten = NULL);

// encoding

	// convert string encoding(SJIS -> UTF-8)
	std::string ConvSJIStoUTF8(
		const std::string& strOrg);
	// convert string encoding(UTF-8 -> SJIS)
	std::string ConvUTF8toSJIS(
		const std::string& strOrg);
	// convert string encoding(source -> UTF-8)
	std::string ConvSRCtoUTF8(
		const std::string& strOrg);
	// convert string encoding(GUI -> UTF-8)
	std::string ConvGUItoUTF8(
		const std::string& strOrg);
	// convert string encoding(UTF-8 -> GUI)
	std::string ConvUTF8toGUI(
		const std::string& strOrg);
	// convert string encoding(source -> GUI)
	std::string ConvSRCtoGUI(
		const std::string& strOrg);
	// convert string encoding(locale -> UTF-8)
	std::string ConvLOCtoUTF8(
		const std::string& strOrg);
	// convert string encoding(UTF-8 -> locale)
	std::string ConvUTF8toLOC(
		const std::string& strOrg);
	// convert string encoding(filesystem -> UTF-8)
	std::string ConvFStoUTF8(
		const std::string& strOrg);
	// convert string encoding(UTF-8 -> filesystem)
	std::string ConvUTF8toFS(
		const std::string& strOrg);
	// convert string encoding(filesystem -> GUI)
	std::string ConvFStoGUI(
		const std::string& strOrg);

// string
	// compare string(ignore case)
	int StrCaseCmp(
		const std::string& strL, const std::string& strR);
	// to lower string
	void StrToLwr(std::string& strTarget);
	// convert string to integer
	int AtoI(const std::string& strNum);
	// format string
	std::string FormatStrV(
		const char* pszFormat, va_list ap);
	std::string FormatStr(
		const char* pszFormat, ...);
	// is contained non-ascii character
	bool IsContainedNonASCII(const char* pszTarget);

// filename
	// get file ext(filesystem encoding)
	std::string GetFileExt(const std::string& fstrFileName);
};

#endif // X88Utility_DEFINED
