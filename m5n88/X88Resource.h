////////////////////////////////////////////////////////////
// X88000 Resource
//
// Written by Manuke

#ifndef X88Resource_DEFINED
#define X88Resource_DEFINED

////////////////////////////////////////////////////////////
// include

#include "resource.h"

////////////////////////////////////////////////////////////
// declaration of NX88Resource

namespace NX88Resource {

// enum

	// language
	enum {
		X88LANG_AUTO     = 0,
		X88LANG_JAPANESE = 1,
		X88LANG_ENGLISH  = 2
	};

#ifdef X88_GUI_WINDOWS

#elif defined(X88_GUI_GTK)

	// internal resource
	enum {
		IDD_NONE                  = 0,
		IDD_MESSAGEBOX            = 1,
		IDD_ENV_SET               = 2,
		IDC_MESSAGE               = 1000,
		IDC_ENV_GENERAL           = 1000,
		IDC_ENV_DISPLAY           = 1001,
		IDC_ENV_INPUT             = 1002,
		IDC_PRINTER_PREVIEW_ALIGN = 1000
	};

#endif // X88_GUI

// struct

#ifdef X88_GUI_WINDOWS

#elif defined(X88_GUI_GTK)

	// declaration of SDialogEntry
	struct SDialogEntry {
		// kind
		const char* pszItemType;
		// text(source encoding)
		const char* psszText;
		// rule
		unsigned nRule;
		// id
		int nID;
		// global option
		const char* pszGlobalOption;
		// local option
		const char* pszLocalOption;
	};

#endif // X88_GUI

// language

	// get UI language
	int GetUILanguage();
	// set UI language
	void SetUILanguage(int nUILanguage);
	// get locale language
	int GetLocaleLanguage();
	// get resource language
	int GetResLanguage();
	// is resource language japanese mode
	bool IsResJapanese();

// string resource

	// get version(GUI encoding)
	std::string GetVersion();
	// get resource string(GUI encoding)
	const char* GetResStr(const char* psszOrg);
	// get formatted resource string(GUI encoding)
	std::string FormatResStr(const char* psszOrg, ...);
	// get parallel device name from id(GUI encoding)
	std::string GetParallelDeviceNameFromID(
		const std::string& strDeviceID);

// dialog resource

#ifdef X88_GUI_GTK

	// get dialog entries
	SDialogEntry* GetDialogEntries(int nID, int& nItemCount);

#endif // X88_GUI

// menu resource

#ifdef X88_GUI_GTK

	// get menu entries
	GtkItemFactoryEntry* GetMenuEntries(int& nItemCount);

#endif // X88_GUI

};

////////////////////////////////////////////////////////////
// macro

#define RSTR	NX88Resource::GetResStr
#define RSTRF	NX88Resource::FormatResStr

#endif // X88Resource_DEFINED
