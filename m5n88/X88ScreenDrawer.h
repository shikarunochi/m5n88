////////////////////////////////////////////////////////////
// X88000 Screen Image Drawer
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

#ifndef X88ScreenDrawer_DEFINED
#define X88ScreenDrawer_DEFINED

////////////////////////////////////////////////////////////
// declare

class CX88ScreenDrawer;

////////////////////////////////////////////////////////////
// include

#include "PC88.h"

////////////////////////////////////////////////////////////
// declaration of CX88ScreenDrawer

class CX88ScreenDrawer {
// enum
public:
	// text attribute
	enum {
		TATTR_COLOR     = 0x07,
		TATTR_REVERSE   = 0x08,
		TATTR_GRAPHIC   = 0x10,
		TATTR_OVERLINE  = 0x20,
		TATTR_UNDERLINE = 0x40
	};
	// color
	enum {
		COLOR_COUNT   = 18,
		ANIMATE_COUNT = 9,
		BACK_COLOR    = 16,
		BLACK_COLOR   = 17
	};
	// text character kind
	enum {
		TXCHR_NORMAL   = 0,  // normal text font
		TXCHR_HIRAGANA = 1,  // hiragana font(for N80V2)
		TXCHR_PCG      = 2,  // PCG declared font
		TXCHR_OPTION   = 3,  // international font
		TXCHR_GRAPHIC  = 4,  // semi-graphic font
		TXCHR_NUM
	};

#ifdef X88_GUI_WINDOWS

	// bit count / line length / line step
	enum {
		BITS_COUNT  = 8,
		LINELEN     = 640,
		LINESTEP    = -640,
		BITS_COUNT2 = 16,
		LINELEN2    = 1280,
		LINESTEP2   = -1280
	};
	// palette
	enum {
		SYSPAL_COUNT = 20
	};

#endif
//#elif defined(X88_GUI_GTK)

	// bit count / line length / line step
	enum {
		BITS_COUNT  = 8,
		LINELEN     = 640,
		LINESTEP    = 640,
		BITS_COUNT2 = 24,
		LINELEN2    = 1920,
		LINESTEP2   = 1920
	};

//#endif // X88_GUI

// attribute
protected:
	// PC88
	static CPC88* m_pPC88;

	// interlace mode
	static bool m_bInterlace;

	// ratch buffer pane
	static int m_nCurPane;
	// ratch buffer of text character
	static uint8_t m_abtTextChar[2][80*25];
	// ratch buffer of text attribute
	static uint8_t m_abtTextAttr[2][80*25];

	// screen data bits
	static uint8_t* m_pbtScreenDataBits;
	// top of screen data bits
	static uint8_t* m_pbtScreenDataBitsTop;
	// screen data bits2
	static uint8_t* m_pbtScreenDataBits2;
	// top of screen data bits2
	static uint8_t* m_pbtScreenDataBits2Top;

#ifdef X88_GUI_WINDOWS

	// screen DIB
	static HBITMAP m_hdibScreen;
	// buffer for screen DIB-BITMAPINFO
	static uint8_t m_abtBmi[sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256];
	// screen DIB-BITMAPINFO
	static BITMAPINFO* m_pbmiScreen;
	// screen DIB-DIBSECTION
	static DIBSECTION m_dsScreen;
	// screen dib-palette
	static RGBQUAD* m_prgbPalettes;
	// screen palette
	static HPALETTE m_hpalScreen;
	// all entries of screen palette
	static PALETTEENTRY m_aScreenPalEntryAll[256];
	// entry of screen palette
	static PALETTEENTRY* m_pScreenPalEntry;
	// screen DIB2
	static HBITMAP m_hdibScreen2;
	// buffer for screen DIB2-BITMAPINFO
	static uint8_t m_abtBmi2[sizeof(BITMAPINFOHEADER)+sizeof(uint32_t)*3];
	// screen DIB2-BITMAPINFO
	static BITMAPINFO* m_pbmiScreen2;

#elif defined(X88_GUI_GTK)

	// color table
	static GdkColor m_aColorTable[COLOR_COUNT];

#endif // X88_GUI

	// drawing font
	static uint8_t m_abtFonts[TXCHR_NUM][256][16];
	//static uint8_t *m_abtFonts;
	// blank font flag
	static bool m_abBlankFonts[TXCHR_NUM][256];
	//static bool *m_abBlankFonts;

public:
	// PC88
	static CPC88& PC88() {
		return *m_pPC88;
	}
	// is interlace mode
	static bool IsInterlace() {
		return m_bInterlace;
	}
	// set interlace mode
	static void SetInterlace(bool bInterlaceNew) {
		m_bInterlace = bInterlaceNew;
	}
	// get text character in ratch buffer
	static uint8_t GetTextChar(int nOfs) {
		return m_abtTextChar[m_nCurPane][nOfs];
	}
	// get text attribute in ratch buffer
	static uint8_t GetTextAttr(int nOfs) {
		return m_abtTextAttr[m_nCurPane][nOfs];
	}
	// get screen data bits
	static uint8_t* GetScreenDataBits() {
		return m_pbtScreenDataBits;
	}
	// get screen data bits2
	static uint8_t* GetScreenDataBits2() {
		return m_pbtScreenDataBits2;
	}

#ifdef X88_GUI_WINDOWS

	// get screen DIB
	static HBITMAP GetScreenDib() {
		return m_hdibScreen;
	}
	// get screen DIB-BITMAPINFO
	static BITMAPINFO* GetScreenBitmapInfo() {
		return m_pbmiScreen;
	}
	// get screen palette
	static HPALETTE GetScreenPalette() {
		return m_hpalScreen;
	}
	// get all entries of screen palette
	static PALETTEENTRY* GetScreenPalEntryAll() {
		return m_aScreenPalEntryAll;
	}
	// get entry of screen palette
	static PALETTEENTRY* GetScreenPalEntry() {
		return m_pScreenPalEntry;
	}
	// get screen DIB2
	static HBITMAP GetScreenDib2() {
		return m_hdibScreen2;
	}
	// get screen DIB2-BITMAPINFO
	static BITMAPINFO* GetScreenBitmapInfo2() {
		return m_pbmiScreen2;
	}

#elif defined(X88_GUI_GTK)

	// get color table
	static GdkColor* GetColorTable() {
		return m_aColorTable;
	}

#endif // X88_GUI

// create & destroy
public:
	// default constructor
	CX88ScreenDrawer();
	// destructor
	~CX88ScreenDrawer();

	// create
	static bool Create(CPC88& pc88, bool bInterlace, uint8_t* pbtScreenDataBits);
	// destroy
	static bool Destroy();

// text VRAM operation
public:
	// ratch text VRAM
	static bool RatchText();

// draw
protected:
	// draw graphic
	static void DrawGraphics();
	// draw text
	static void DrawText();
	// draw text(reverse order)
	static void DrawText2();

	static int CalcBtColor(int leftColor, int rightColor);

public:
	// draw screen
	static void DrawScreen();
	// update palette
	static bool UpdatePalette();
	// draw screen for video art board
	static bool DrawScreenVAB();
};

#endif // X88ScreenDrawer_DEFINED
