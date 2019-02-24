////////////////////////////////////////////////////////////
// X88000 Screen Image Drawer
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "X88ScreenDrawer.h"

////////////////////////////////////////////////////////////
// implementation of CX88ScreenDrawer

////////////////////////////////////////////////////////////
// attribute

// PC88

CPC88* CX88ScreenDrawer::m_pPC88;

// interlace mode

bool CX88ScreenDrawer::m_bInterlace;

// ratch buffer pane

int CX88ScreenDrawer::m_nCurPane;

// ratch buffer of text character

uint8_t CX88ScreenDrawer::m_abtTextChar[2][80*25];

// ratch buffer of text attribute

uint8_t CX88ScreenDrawer::m_abtTextAttr[2][80*25];

// screen data bits

uint8_t* CX88ScreenDrawer::m_pbtScreenDataBits;

// top of screen data bits

uint8_t* CX88ScreenDrawer::m_pbtScreenDataBitsTop;

// screen data bits2

uint8_t* CX88ScreenDrawer::m_pbtScreenDataBits2;

// top of screen data bits2

uint8_t* CX88ScreenDrawer::m_pbtScreenDataBits2Top;

//フレームバッファ
TFT_eSprite fb = TFT_eSprite(&M5.Lcd);

int COLOR_VALUE[18]={
TFT_BLACK,//0
TFT_BLUE,         //1
TFT_RED, //2
TFT_MAGENTA,//3
TFT_GREEN,//4
TFT_CYAN,//5
TFT_YELLOW,//6
TFT_WHITE,//7
TFT_BLACK,//8
TFT_BLUE ,        //9
TFT_RED,        //10
TFT_MAGENTA,       //11
TFT_GREEN,     //12
TFT_CYAN,        //13
TFT_YELLOW,      //14
TFT_WHITE ,      //15
TFT_BLACK ,      //16:BACK_COLOR
TFT_BLACK       //17:BLACK_COLOR
};

//http://hello.lumiere-couleur.com/app/16bit-colorpicker/
int MIX_COLOR_VALUE[8][8]={
//BLACK  BLUE  RED   MAGENTA  GREEN  CYAN YELLOW WHITE
	{BLACK,NAVY,MAROON,PURPLE,DARKGREEN,DARKCYAN,OLIVE,DARKGREY},//BLACK
	{NAVY, BLUE, MAGENTA, MAGENTA, CYAN, CYAN, WHITE, 0xaebc}, //BLUE
	{MAROON,MAGENTA, RED, MAGENTA, YELLOW,WHITE,YELLOW,0xfdb7}, //RED
	{PURPLE,MAGENTA, MAGENTA,MAGENTA,WHITE,WHITE,WHITE,0xec1d},//MAGENTA
	{DARKGREEN, CYAN,YELLOW,WHITE,GREEN, CYAN,GREENYELLOW,0x97d2},//GREEN
	{DARKCYAN,CYAN,WHITE,WHITE,CYAN,CYAN,WHITE,0xdfff},//CYAN
	{OLIVE,WHITE,YELLOW,WHITE,YELLOW,WHITE,YELLOW,0xfffb},//YELLOW
	{DARKGREY,0xaebc,0xfdb7,0xec1d,0x97d2,0xdfff,0xfffb,WHITE}//WHITE
};


#ifdef X88_GUI_WINDOWS

// screen DIB

HBITMAP CX88ScreenDrawer::m_hdibScreen;

// buffer for screen DIB-BITMAPINFO

uint8_t CX88ScreenDrawer::m_abtBmi[sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256];

// screen DIB-BITMAPINFO

BITMAPINFO* CX88ScreenDrawer::m_pbmiScreen;

// screen DIB-DIBSECTION

DIBSECTION CX88ScreenDrawer::m_dsScreen;

// screen dib-palette

RGBQUAD* CX88ScreenDrawer::m_prgbPalettes;

// screen palette

HPALETTE CX88ScreenDrawer::m_hpalScreen;

// all entries of screen palette

PALETTEENTRY CX88ScreenDrawer::m_aScreenPalEntryAll[256];

// entry of screen palette

PALETTEENTRY* CX88ScreenDrawer::m_pScreenPalEntry;

// screen DIB2

HBITMAP CX88ScreenDrawer::m_hdibScreen2;

// buffer for screen DIB2-BITMAPINFO

uint8_t CX88ScreenDrawer::m_abtBmi2[sizeof(BITMAPINFOHEADER)+sizeof(uint32_t)*3];

// screen DIB2-BITMAPINFO

BITMAPINFO* CX88ScreenDrawer::m_pbmiScreen2;

#elif defined(X88_GUI_GTK)

// color table

GdkColor CX88ScreenDrawer::m_aColorTable[COLOR_COUNT];

#endif // X88_GUI

// drawing font

uint8_t CX88ScreenDrawer::m_abtFonts[TXCHR_NUM][256][16];
//uint8_t* CX88ScreenDrawer::m_abtFonts;

// blank font flag

bool CX88ScreenDrawer::m_abBlankFonts[TXCHR_NUM][256];
//bool* CX88ScreenDrawer::m_abBlankFonts;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CX88ScreenDrawer::CX88ScreenDrawer() {
	m_pPC88 = NULL;
	m_nCurPane = 0;

	memset(m_abtTextChar, 0, sizeof(m_abtTextChar));
	memset(m_abtTextAttr, 0, sizeof(m_abtTextAttr));
	m_pbtScreenDataBits = m_pbtScreenDataBitsTop = NULL;
	m_pbtScreenDataBits2 = m_pbtScreenDataBits2Top = NULL;

#ifdef X88_GUI_WINDOWS

	m_hdibScreen = NULL;
	m_hpalScreen = NULL;
	m_hdibScreen2 = NULL;

#endif // X88_GUI

}

// destructor

CX88ScreenDrawer::~CX88ScreenDrawer() {
}

// create

bool CX88ScreenDrawer::Create(CPC88& pc88, bool bInterlace,uint8_t* pbtScreenDataBits) {
	fb.setColorDepth(8);
    fb.createSprite(320, 200);
    fb.fillSprite(TFT_BLACK);
    fb.pushSprite(0, 0);
	bool bResult = true;
	m_pPC88 = &pc88;
	m_bInterlace = bInterlace;

	memset(m_abtFonts, 0x00, TXCHR_NUM * 256 * 16);
	int nCode;
	for (nCode = 0; nCode < 256; nCode++) {
		for (int y = 0; y < 8; y++) {
			m_abtFonts[TXCHR_NORMAL][nCode][y] =
				m_abtFonts[TXCHR_PCG][nCode][y] =
					PC88().Z80Main().GetKanjiRom(0, 256*16+nCode*8+y);
			m_abtFonts[TXCHR_HIRAGANA][nCode][y] =
				PC88().Z80Main().GetFont80SRRom(256*8*1+nCode*8+y);
			m_abtFonts[TXCHR_OPTION][nCode][y] =
				PC88().Z80Main().GetOptionFontRom(nCode*8+y);
		}
		for (int nBit = 0; nBit < 8; nBit++) {
			if ((nCode & (1 << nBit)) != 0) {
				uint8_t btOR = uint8_t(0xF0 >> ((nBit/4)*4));
				m_abtFonts[TXCHR_GRAPHIC][nCode][(nBit%4)*2] |= btOR;
				m_abtFonts[TXCHR_GRAPHIC][nCode][(nBit%4)*2+1] |= btOR;

			}
		}
	}
	memset(m_abBlankFonts, 0, TXCHR_NUM * 256);

	m_abBlankFonts[TXCHR_NORMAL][0x00] =
		m_abBlankFonts[TXCHR_NORMAL][0x20] =
		m_abBlankFonts[TXCHR_HIRAGANA][0x00] =
		m_abBlankFonts[TXCHR_HIRAGANA][0x20] =
		m_abBlankFonts[TXCHR_OPTION][0x00] =
		m_abBlankFonts[TXCHR_OPTION][0x20] =
		m_abBlankFonts[TXCHR_GRAPHIC][0x00] = true;

#ifdef X88_GUI_WINDOWS

	m_pbmiScreen = (BITMAPINFO*)m_abtBmi;
	memset(m_pbmiScreen, 0x00, sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256);
	m_pbmiScreen->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pbmiScreen->bmiHeader.biWidth = 640;
	m_pbmiScreen->bmiHeader.biHeight = 400;
	m_pbmiScreen->bmiHeader.biPlanes = 1;
	m_pbmiScreen->bmiHeader.biBitCount = 8;
	m_pbmiScreen->bmiHeader.biCompression = BI_RGB;
	int nPalNo;
	for (nPalNo = 0; nPalNo < 16; nPalNo++) {
		m_pbmiScreen->bmiColors[nPalNo].rgbRed =
			uint8_t(((nPalNo & 2) != 0)? 255: 0);
		m_pbmiScreen->bmiColors[nPalNo].rgbGreen =
			uint8_t(((nPalNo & 4) != 0)? 255: 0);
		m_pbmiScreen->bmiColors[nPalNo].rgbBlue =
			uint8_t(((nPalNo & 1) != 0)? 255: 0);
	}
	m_prgbPalettes = m_pbmiScreen->bmiColors;
	HDC hdc = GetDC(HWND_DESKTOP);
	m_hdibScreen = CreateDIBSection(
		hdc,
		m_pbmiScreen, DIB_RGB_COLORS, (void**)(&m_pbtScreenDataBits),
		NULL, 0);
	if (m_hdibScreen != NULL) {
		m_pbtScreenDataBitsTop = m_pbtScreenDataBits+640*399;
		m_pbmiScreen->bmiHeader.biClrUsed = COLOR_COUNT;
		GetObject(m_hdibScreen, sizeof(DIBSECTION), &m_dsScreen);
		memset(m_aScreenPalEntryAll, 0x00, sizeof(m_aScreenPalEntryAll));
		m_pScreenPalEntry = m_aScreenPalEntryAll+SYSPAL_COUNT/2;
		uint8_t abtPaletteBuf[
			sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*(COLOR_COUNT-1)];
		memset(abtPaletteBuf, 0x00, sizeof(abtPaletteBuf));
		LOGPALETTE* pLogPalette = (LOGPALETTE*)abtPaletteBuf;
		pLogPalette->palVersion = 0x0300;
		pLogPalette->palNumEntries = COLOR_COUNT;
		for (nPalNo = 0; nPalNo < COLOR_COUNT; nPalNo++) {
			m_pScreenPalEntry[nPalNo].peRed   = m_prgbPalettes[nPalNo].rgbRed;
			m_pScreenPalEntry[nPalNo].peGreen = m_prgbPalettes[nPalNo].rgbGreen;
			m_pScreenPalEntry[nPalNo].peBlue  = m_prgbPalettes[nPalNo].rgbBlue;
			m_pScreenPalEntry[nPalNo].peFlags = PC_RESERVED;
			pLogPalette->palPalEntry[nPalNo] = m_pScreenPalEntry[nPalNo];
		}
		m_hpalScreen = CreatePalette(pLogPalette);
		bResult = true;
	}
	ReleaseDC(HWND_DESKTOP, hdc);

#elif defined(X88_GUI_GTK)

	memset(m_aColorTable, 0, sizeof(m_aColorTable));
	for (int nPalNo = 0; nPalNo < 16; nPalNo++) {
		m_aColorTable[nPalNo].red = (gushort)(((nPalNo & 2) != 0)? 65535: 0);
		m_aColorTable[nPalNo].green = (gushort)(((nPalNo & 4) != 0)? 65535: 0);
		m_aColorTable[nPalNo].blue = (gushort)(((nPalNo & 1) != 0)? 65535: 0);
	}
	m_pbtScreenDataBits = m_pbtScreenDataBitsTop = new uint8_t[640*400];
	bResult = (m_pbtScreenDataBits != NULL);
	if (bResult) {
		memset(m_pbtScreenDataBits, 0, 640*400);
	}

#endif // X88_GUI
	 m_pbtScreenDataBits = pbtScreenDataBits;//(uint8_t*)ps_malloc(640*400);
	 m_pbtScreenDataBitsTop = m_pbtScreenDataBits;
	return bResult;
}

// destroy

bool CX88ScreenDrawer::Destroy() {

#ifdef X88_GUI_WINDOWS

	if (m_hdibScreen != NULL) {
		DeleteObject(m_hdibScreen);
		m_hdibScreen = NULL;
		m_pbtScreenDataBits = m_pbtScreenDataBitsTop = NULL;
	}
	if (m_hpalScreen != NULL) {
		DeleteObject(m_hpalScreen);
		m_hpalScreen = NULL;
	}
	if (m_hdibScreen2 != NULL) {
		DeleteObject(m_hdibScreen2);
		m_hdibScreen2 = NULL;
		m_pbtScreenDataBits2 = m_pbtScreenDataBits2Top = NULL;
	}

#elif defined(X88_GUI_GTK)

	if (m_pbtScreenDataBits != NULL) {
		delete [] m_pbtScreenDataBits;
		m_pbtScreenDataBits = m_pbtScreenDataBitsTop = NULL;
	}
	if (m_pbtScreenDataBits2 != NULL) {
		delete [] m_pbtScreenDataBits2;
		m_pbtScreenDataBits2 = m_pbtScreenDataBits2Top = NULL;
	}

#endif // X88_GUI

	return true;
}

////////////////////////////////////////////////////////////
// text VRAM operation

// ratch text VRAM

bool CX88ScreenDrawer::RatchText() {
	m_nCurPane = 1-m_nCurPane;
	bool bUpdate = PC88().Crtc().IsCrtcUpdate() ||
		PC88().Z80Main().IsTVRamUpdate() ||
		PC88().Z80Main().IsGVRamUpdate();
	PC88().Crtc().SetCrtcUpdate(false);
	PC88().Z80Main().SetTVRamUpdate(false);
	PC88().Z80Main().SetGVRamUpdate(false);
	bool bHeight25 = PC88().Crtc().IsHeight25(),
		bCursorShow = PC88().Crtc().IsCursorEnable() &&
			PC88().Crtc().IsCursorBlinking(),
		bAttrBlinking = PC88().Crtc().IsAttrBlinking();
	uint8_t btAttr = PC88().Crtc().GetLastTextAttr();
	int nColor = (btAttr >> 5) & 0x07;
	bool bSecret = (btAttr & 0x01) != 0,
		bBlink = (btAttr & 0x02) != 0,
		bReverse = (btAttr & 0x04) != 0,
		bGraphic = (btAttr & 0x10) != 0;
	int nTextAddr = 0, nTextOfs = 0;
	// update PCG data
	if (PC88().Z80Main().IsPcgEnable()) {
		for (int nPos = 0; nPos < 2; nPos++) {
			if (PC88().Pcg().IsPcgUpdate(nPos)) {
				PC88().Pcg().SetPcgUpdate(nPos, false);
				bUpdate = true;
				for (int nCode = 0; nCode < 128; nCode++) {
					for (int y = 0; y < 8; y++) {
						m_abtFonts[TXCHR_PCG][(nPos*128+nCode)][y] =
							PC88().Pcg().GetCurTextFontData(
								nPos, nCode*8+y);
					}
				}
			}
		}
	}
	int nMaskX = ~(PC88().Crtc().IsWidth80()? 0: 1);
	if ((PC88().Crtc().GetAttrMode() == CPC88Crtc::ATTR_TRANSPARENT_MONO) ||
		(PC88().Crtc().GetAttrMode() == CPC88Crtc::ATTR_TRANSPARENT_COLOR))
	{
		// TRANSPARENT mode
		int nAttrPerLine = PC88().Crtc().GetAttrPerLine();
		for (int y = 0; y < 25; y++) {
			bool bOverLine = false, bUnderLine = false;
			uint8_t btFirstAttr = PC88().Z80Main().GetTVRam(nTextAddr+80);
			int nAttr, nAttrAddr, nAttrOfs;
			if (btFirstAttr != 0x00) {
				nAttr = -1;
				nAttrAddr = nTextAddr+80-2;
				nAttrOfs = -1;
			} else {
				nAttr = 0;
				nAttrAddr = nTextAddr+80;
				nAttrOfs = PC88().Z80Main().GetTVRam(nAttrAddr);
			}
			for (int x = 0; x < 80; x++) {
				uint8_t btChar = PC88().Z80Main().GetTVRam(nTextAddr);
				bool bUpdateAttr = false;
				if (btFirstAttr != 0x00) {
					if ((nAttr < nAttrPerLine - 1) && (x >= nAttrOfs)) {
						nAttrAddr += 2;
						btAttr = PC88().Z80Main().GetTVRam(nAttrAddr+1);
						nAttr++;
						nAttrOfs = PC88().Z80Main().GetTVRam(nAttrAddr);
						bUpdateAttr = true;
					}
				} else {
					if ((nAttr < nAttrPerLine) && (x >= nAttrOfs)) {
						btAttr = PC88().Z80Main().GetTVRam(nAttrAddr+1);
						nAttrAddr += 2;
						nAttr++;
						nAttrOfs = PC88().Z80Main().GetTVRam(nAttrAddr);
						bUpdateAttr = true;
					}
				}
				if (bUpdateAttr) {
					if (PC88().Crtc().IsColorMode() &&
						((btAttr & 0x08) != 0))
					{
						nColor = (btAttr >> 5) & 0x07;
						bGraphic = (btAttr & 0x10) != 0;
					} else {
						bSecret = (btAttr & 0x01) != 0;
						bBlink = (btAttr & 0x02) != 0;
						bReverse = (btAttr & 0x04) != 0;
						bOverLine = (btAttr & 0x10) != 0;
						bUnderLine = (btAttr & 0x20) != 0;
						if (!PC88().Crtc().IsColorMode()) {
							bGraphic = (btAttr & 0x80) != 0;
						}
					}
				}
				if (bSecret || (bBlink && bAttrBlinking)) {
					btChar = 0;
				}
				bool bReverse2 = bReverse;
				if (bCursorShow &&
					((x & nMaskX) == PC88().Crtc().GetCursorX()) &&
					(y == PC88().Crtc().GetCursorY()))
				{
					bReverse2 = !bReverse2;
				}
				if (PC88().Crtc().IsReverseDisp()) {
					bReverse2 = !bReverse2;
				}
				uint8_t btAttr = uint8_t(
					nColor |
					(bGraphic? TATTR_GRAPHIC: 0) |
					(bOverLine? TATTR_OVERLINE: 0) |
					(bUnderLine? TATTR_UNDERLINE: 0) |
					(bReverse2? TATTR_REVERSE: 0));
				m_abtTextChar[m_nCurPane][nTextOfs] = btChar;
				m_abtTextAttr[m_nCurPane][nTextOfs] = btAttr;
				nTextAddr++;
				nTextOfs++;
				if (!PC88().Crtc().IsWidth80()) {
					x++;
					m_abtTextChar[m_nCurPane][nTextOfs] = 0;
					m_abtTextAttr[m_nCurPane][nTextOfs] = btAttr;
					nTextAddr++;
					nTextOfs++;
				}
			}
			nTextAddr += nAttrPerLine * 2;
		}
	} else {
		// NONETRANSPARENT mode
		nColor = 7;
		bSecret = false;
		bBlink = false;
		bReverse = false;
		bGraphic = false;
		for (int y = 0; y < 25; y++) {
			for (int x = 0; x < 80; x++) {
				uint8_t btChar = PC88().Z80Main().GetTVRam(nTextAddr);

				bool bReverse2 = bCursorShow &&
					((x & nMaskX) == PC88().Crtc().GetCursorX()) &&
					(y == PC88().Crtc().GetCursorY());
				if (PC88().Crtc().IsReverseDisp()) {
					bReverse2 = !bReverse2;
				}
				uint8_t btAttr = uint8_t(
					nColor |
					(bReverse2? TATTR_REVERSE: 0));
				m_abtTextChar[m_nCurPane][nTextOfs] = btChar;
				m_abtTextAttr[m_nCurPane][nTextOfs] = btAttr;
				nTextAddr++;
				nTextOfs++;
				if (!PC88().Crtc().IsWidth80()) {
					x++;
					m_abtTextChar[m_nCurPane][nTextOfs] = 0;
					m_abtTextAttr[m_nCurPane][nTextOfs] = btAttr;
					nTextAddr++;
					nTextOfs++;
				}
			}
		}
	}
	PC88().Crtc().SetLastTextAttr(
		uint8_t(((nColor & 0x07) << 5) |
			(bSecret? 0x01: 0x00) |
			(bBlink? 0x02: 0x00) |
			(bReverse? 0x04: 0x00) |
			(bGraphic? 0x10: 0x00)));
	if (!bUpdate) {
		int nBytes = bHeight25? (80*25): (80*20);
		bUpdate =
			(memcmp(m_abtTextChar[0], m_abtTextChar[1], nBytes) != 0) ||
			(memcmp(m_abtTextAttr[0], m_abtTextAttr[1], nBytes) != 0);
	}
	return bUpdate;
}

// draw

// draw graphic

void CX88ScreenDrawer::DrawGraphics() {
	uint8_t* pbtBits = m_pbtScreenDataBitsTop;
	int pixelPos = 0;

	bool bHeight25 = PC88().Crtc().IsHeight25();
	int nVDotCount = bHeight25? 8: 10;
	int nTextPalOfs =
		(!PC88().Z80Main().IsGraphicDisplayAnalog() ||
			PC88().Z80Main().IsGraphicDisplayColor())? 8: 0;
	int nTAddr;
	uint8_t* pbtTextAttrBuf = m_abtTextAttr[m_nCurPane];
	enum {
		MODE_BLACK,
		MODE_BACK,
		MODE_COLOR_640_200,
		MODE_COLOR_320_200_N80V1,
		MODE_COLOR_320_200_N80V2,
		MODE_MONO_640_200,
		MODE_MONO_320_200_N80V2,
		MODE_MONO_640_400
	};
	int nMode;
	bool bError400 = false;
	if (!PC88().Z80Main().IsGraphicDisplayEnable()) {
		if (PC88().Z80Main().IsGraphicDisplayColor()) {
			nMode = MODE_BLACK;
		} else {
			nMode = MODE_BACK;
		}
	} else {
		if (PC88().Z80Main().IsGraphicDisplayColor()) {
			nMode = MODE_COLOR_640_200;
			if (PC88().Z80Main().IsN80V2BasicRomMode()) {
				if (PC88().Z80Main().IsGraphicDisplay320Line()) {
					if (PC88().Z80Main().IsGVRamOverlayDisable(0) &&
						PC88().Z80Main().IsGVRamOverlayDisable(1))
					{
						nMode = MODE_BLACK;
					} else {
						nMode = MODE_COLOR_320_200_N80V2;
					}
				} else if (PC88().Z80Main().IsGVRamOverlayDisable(0)) {
					nMode = MODE_BLACK;
				}
			} else if (PC88().Z80Main().IsN80BasicMode()) {
				if (PC88().Z80Main().IsGraphicDisplay320Line()) {
					nMode = MODE_COLOR_320_200_N80V1;
				}
			}
		} else if (PC88().Z80Main().IsGraphicDisplay200Line()) {
			nMode = MODE_MONO_640_200;
			if (PC88().Z80Main().IsGraphicDisplay320Line()) {
				nMode = MODE_MONO_320_200_N80V2;
			}
		} else {
			if (PC88().Crtc().IsHiresolution()) {
				nMode = MODE_MONO_640_400;
			} else {
				nMode = MODE_MONO_640_200;
				bError400 = true;
			}
		}
	}
	if (nMode == MODE_COLOR_640_200) {
		// display graphic for color 640x200
		uint8_t* pbtGVRamX = PC88().Z80Main().GetGVRamXPtr();
		int y = 200;
		int pixel_y = 0;
		int preBtColor = 0;
		int btColor = 0;
		if (!IsInterlace()) {
			do {
				for(int pixel_x = 0;pixel_x < 640;pixel_x++){
					if(pixel_x % 2 == 0){
						int leftBtColor = *pbtGVRamX;
						pbtGVRamX++;
						int rightBtColor = *pbtGVRamX;
						int drawColor = CalcBtColor(leftBtColor, rightBtColor);
						fb.drawPixel(pixel_x / 2, pixel_y ,drawColor);
						pbtGVRamX++;
					}
				}
				pixel_y++;
				preBtColor = 0;
			} while (--y != 0);
		} else {
			do {
				memcpy(pbtBits, pbtGVRamX, 640);
				memset(pbtBits+LINESTEP, BLACK_COLOR, 640);
				pbtGVRamX += 640;
				pbtBits += LINESTEP*2;
			} while (--y != 0);
		}
	} else if (nMode == MODE_MONO_640_200) {
		// display graphic for monochrome 640x200
		uint8_t abtColorTbl[16][8];
		bool abGVRamEnable[3];
		if (!bError400) {
			abGVRamEnable[0] = !PC88().Z80Main().IsGVRamOverlayDisable(0);
			abGVRamEnable[1] = !PC88().Z80Main().IsGVRamOverlayDisable(1);
			abGVRamEnable[2] = !PC88().Z80Main().IsGVRamOverlayDisable(2);
		} else {
			abGVRamEnable[0] = true;
			abGVRamEnable[1] = true;
			abGVRamEnable[2] = false;
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((((j & 1) != 0) && abGVRamEnable[0]) ||
					(((j & 2) != 0) && abGVRamEnable[1]) ||
					(((j & 4) != 0) && abGVRamEnable[2]))
				{
					abtColorTbl[i][j] = uint8_t(i+nTextPalOfs);
					abtColorTbl[i+8][j] = BACK_COLOR;
				} else {
					abtColorTbl[i][j] = BACK_COLOR;
					abtColorTbl[i+8][j] = uint8_t(i+nTextPalOfs);
				}
				if (PC88().Z80Main().IsTVRamOverlayDisable()) {
					abtColorTbl[i+8][j] = abtColorTbl[i][j];
				}
			}
		}
		uint8_t* pbtGVRamX = PC88().Z80Main().GetGVRamXPtr();
		int y = 200;
		if (!IsInterlace()) {
			do {
				nTAddr = ((200-y)/nVDotCount)*80;
				int x = 80;
				do {
					uint8_t* pbtColorTbl = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		} else {
			do {
				nTAddr = ((200-y)/nVDotCount)*80;
				int x = 80;
				do {
					uint8_t* pbtColorTbl = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		}
	} else if (nMode == MODE_MONO_640_400) {
		// display graphic for monochrome 640x400
		for (int nPlane = 0; nPlane < 2; nPlane++) {
			uint8_t abtColorTbl[16][8];
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (((j & (1 << nPlane)) != 0) &&
							!PC88().Z80Main().IsGVRamOverlayDisable(nPlane))
					{
						abtColorTbl[i][j] = uint8_t(i+nTextPalOfs);
						abtColorTbl[i+8][j] = BACK_COLOR;
					} else {
						abtColorTbl[i][j] = BACK_COLOR;
						abtColorTbl[i+8][j] = uint8_t(i+nTextPalOfs);
					}
					if (PC88().Z80Main().IsTVRamOverlayDisable()) {
						abtColorTbl[i+8][j] = abtColorTbl[i][j];
					}
				}
			}
			uint8_t* pbtGVRamX = PC88().Z80Main().GetGVRamXPtr();
			int y = 200, yOfs = nPlane*200;
			do {
				nTAddr = ((200-y+yOfs)/(nVDotCount*2))*80;
				int x = 80;
				do {
					uint8_t* pbtColorTbl = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					*pbtBits = pbtColorTbl[*(pbtGVRamX++)];
					pbtBits++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP-640;
			} while (--y != 0);
		}
	} else if (nMode == MODE_COLOR_320_200_N80V1) {
		// display graphic for color 320x200(N80V1)
		uint8_t* pbtGVRamX = PC88().Z80Main().GetGVRamXPtr();
		int y = 200;
		if (!IsInterlace()) {
			do {
				int x = 320;
				do {
					*pbtBits = *(pbtBits+1) =
						*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) =
							(uint8_t)(((*pbtGVRamX & 0x01)) << 1 |
								(*(pbtGVRamX+1) & 0x01));
					pbtBits += 2;
					pbtGVRamX += 2;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		} else {
			do {
				int x = 320;
				do {
					*pbtBits = *(pbtBits+1) =
						(uint8_t)(((*pbtGVRamX & 0x01)) << 1 |
							(*(pbtGVRamX+1) & 0x01));
					*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) = BLACK_COLOR;
					pbtBits += 2;
					pbtGVRamX += 2;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		}
	} else if (nMode == MODE_COLOR_320_200_N80V2) {
		// display graphic for color 320x200(N80V2)
		uint8_t* pbtGVRamX0 = PC88().Z80Main().GetGVRamXPtr();
		uint8_t* pbtGVRamX1 = pbtGVRamX0;
		int nTopPage;
		if (PC88().Z80Main().IsGraphicPriority()) {
			pbtGVRamX0 += 0x2000*8;
			nTopPage = 1;
		} else {
			pbtGVRamX1 += 0x2000*8;
			nTopPage = 0;
		}
		int y = 200;
		if (!IsInterlace()) {
			if (PC88().Z80Main().IsGVRamOverlayDisable(nTopPage) ||
				PC88().Z80Main().IsGVRamOverlayDisable(1-nTopPage))
			{
				uint8_t* pbtGVRamX =
					PC88().Z80Main().IsGVRamOverlayDisable(nTopPage)?
					pbtGVRamX1: pbtGVRamX0;
				do {
					int x = 320;
					do {
						*pbtBits = *(pbtBits+1) = *pbtGVRamX;
						pbtBits += 2;
						pbtGVRamX++;
					} while (--x != 0);
					memcpy(pbtBits-640+LINESTEP, pbtBits-640, 640);
					pbtBits += LINESTEP*2-640;
				} while (--y != 0);
			} else {
				do {
					int x = 320;
					do {
						if (*pbtGVRamX0 != 0) {
							*pbtBits = *(pbtBits+1) = *pbtGVRamX0;
						} else {
							*pbtBits = *(pbtBits+1) = *pbtGVRamX1;
						}
						pbtBits += 2;
						pbtGVRamX0++;
						pbtGVRamX1++;
					} while (--x != 0);
					memcpy(pbtBits-640+LINESTEP, pbtBits-640, 640);
					pbtBits += LINESTEP*2-640;
				} while (--y != 0);
			}
		} else {
			if (PC88().Z80Main().IsGVRamOverlayDisable(nTopPage) ||
				PC88().Z80Main().IsGVRamOverlayDisable(1-nTopPage))
			{
				uint8_t* pbtGVRamX =
					PC88().Z80Main().IsGVRamOverlayDisable(nTopPage)?
					pbtGVRamX1: pbtGVRamX0;
				do {
					int x = 320;
					do {
						*pbtBits = *(pbtBits+1) = *pbtGVRamX;
						pbtBits += 2;
						pbtGVRamX++;
					} while (--x != 0);
					memset(pbtBits-640+LINESTEP, BLACK_COLOR, 640);
					pbtBits += LINESTEP*2-640;
				} while (--y != 0);
			} else {
				do {
					int x = 320;
					do {
						if (*pbtGVRamX0 != 0) {
							*pbtBits = *(pbtBits+1) = *pbtGVRamX0;
						} else {
							*pbtBits = *(pbtBits+1) = *pbtGVRamX1;
						}
						pbtBits += 2;
						pbtGVRamX0++;
						pbtGVRamX1++;
					} while (--x != 0);
					memset(pbtBits-640+LINESTEP, BLACK_COLOR, 640);
					pbtBits += LINESTEP*2-640;
				} while (--y != 0);
			}
		}
	} else if (nMode == MODE_MONO_320_200_N80V2) {
		// display graphic for monochrome 320x200(N80V2)
		uint8_t abtColorTbl[16][64];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 64; j++) {
				if ((((j &  1) != 0) &&
						!PC88().Z80Main().IsGVRamOverlayDisable(0)) ||
					(((j &  2) != 0) &&
						!PC88().Z80Main().IsGVRamOverlayDisable(1)) ||
					(((j &  4) != 0) &&
						!PC88().Z80Main().IsGVRamOverlayDisable(2)) ||
					(((j &  8) != 0) &&
						!PC88().Z80Main().IsGVRamOverlayDisable(3)) ||
					(((j & 16) != 0) &&
						!PC88().Z80Main().IsGVRamOverlayDisable(4)) ||
					(((j & 32) != 0) &&
						!PC88().Z80Main().IsGVRamOverlayDisable(5)))
				{
					abtColorTbl[i][j] = uint8_t(i+nTextPalOfs);
					abtColorTbl[i+8][j] = BACK_COLOR;
				} else {
					abtColorTbl[i][j] = BACK_COLOR;
					abtColorTbl[i+8][j] = uint8_t(i+nTextPalOfs);
				}
				if (PC88().Z80Main().IsTVRamOverlayDisable()) {
					abtColorTbl[i+8][j] = abtColorTbl[i][j];
				}
			}
		}
		uint8_t* pbtGVRamX = PC88().Z80Main().GetGVRamXPtr();
		int y = 200;
		if (!IsInterlace()) {
			do {
				nTAddr = ((200-y)/nVDotCount)*80;
				int x = 80;
				do {
					uint8_t* pbtColorTbl = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = *(pbtBits+1) =
						*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) =
							pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					pbtBits += 2;
					pbtGVRamX++;
					*pbtBits = *(pbtBits+1) =
						*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) =
							pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					pbtBits += 2;
					pbtGVRamX++;
					*pbtBits = *(pbtBits+1) =
						*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) =
							pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					pbtBits += 2;
					pbtGVRamX++;
					*pbtBits = *(pbtBits+1) =
						*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) =
							pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					pbtBits += 2;
					pbtGVRamX++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		} else {
			do {
				nTAddr = ((200-y)/nVDotCount)*80;
				int x = 80;
				do {
					uint8_t* pbtColorTbl = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = *(pbtBits+1) =
						pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) = BLACK_COLOR;
					pbtBits += 2;
					pbtGVRamX++;
					*pbtBits = *(pbtBits+1) =
						pbtColorTbl[*pbtGVRamX + *(pbtGVRamX+0x2000*8)*8];
					*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) = BLACK_COLOR;
					pbtBits += 2;
					pbtGVRamX++;
					*pbtBits = *(pbtBits+1) =
						pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) = BLACK_COLOR;
					pbtBits += 2;
					pbtGVRamX++;
					*pbtBits = *(pbtBits+1) =
						pbtColorTbl[*pbtGVRamX+*(pbtGVRamX+0x2000*8)*8];
					*(pbtBits+LINESTEP) = *(pbtBits+LINESTEP+1) = BLACK_COLOR;
					pbtBits += 2;
					pbtGVRamX++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		}
	} else if (nMode == MODE_BLACK) {
		// not display graphic(black)
		memset(m_pbtScreenDataBits, BLACK_COLOR, 640*400);
	} else {
		// not display graphic(background color)
		uint8_t abtColorTbl[16];
		for (int i = 0; i < 8; i++) {
			abtColorTbl[i] = BACK_COLOR;
			abtColorTbl[i+8] = uint8_t(i+nTextPalOfs);
			if (PC88().Z80Main().IsTVRamOverlayDisable()) {
				abtColorTbl[i+8] = BACK_COLOR;
			}
		}
		int y = 200;
		if (!IsInterlace()) {
			do {
				nTAddr = ((200-y)/nVDotCount)*80;
				int x = 80;
				do {
					uint8_t btColor = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					*pbtBits = *(pbtBits+LINESTEP) = btColor;
					pbtBits++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		} else {
			do {
				nTAddr = ((200-y)/nVDotCount)*80;
				int x = 80;
				do {
					uint8_t btColor = abtColorTbl[
						pbtTextAttrBuf[nTAddr] & (TATTR_COLOR | TATTR_REVERSE)];
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					*pbtBits = btColor;
					*(pbtBits+LINESTEP) = BLACK_COLOR;
					pbtBits++;
					nTAddr++;
				} while (--x != 0);
				pbtBits += LINESTEP*2-640;
			} while (--y != 0);
		}
	}
}

// draw text

void CX88ScreenDrawer::DrawText() {
	bool bHeight25 = PC88().Crtc().IsHeight25();
	int nLineCount = bHeight25? 25: 20,
		nVDotCount = bHeight25? 8: 10;
	int nTextPalOfs =
		(!PC88().Z80Main().IsGraphicDisplayAnalog() ||
			PC88().Z80Main().IsGraphicDisplayColor())? 8: 0;
	int nFontType;
	if (PC88().Z80Main().IsPcgEnable()) {
		nFontType = TXCHR_PCG;
	} else if (PC88().Z80Main().IsOptionFont()) {
		nFontType = TXCHR_OPTION;
	} else if (PC88().Z80Main().IsHiraMode()) {
		nFontType = TXCHR_HIRAGANA;
	} else {
		nFontType = TXCHR_NORMAL;
	}
	int nTAddr;
	uint8_t* pbtTextCharBuf = m_abtTextChar[m_nCurPane];
	//Serial.print("DrawText:");
	

	uint8_t* pbtTextAttrBuf = m_abtTextAttr[m_nCurPane];
	uint8_t* pbtBits = m_pbtScreenDataBitsTop;
	int pixel_x = 0; 
	int pixel_y = 0;
	int preBtColor = 0;
	if (!PC88().Crtc().IsDisplayActive() ||
		PC88().Z80Main().IsTVRamOverlayDisable())
	{
		// not display text
	} else if (PC88().Crtc().IsWidth80() && !IsInterlace()) {
		// display text at 80 columns non-interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x++) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr];
				int btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				if(btColor >= 0 && btColor < 18){
					btColor = COLOR_VALUE[btColor];
				}
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				int pixel_x2 = pixel_x;
				int pixel_y2 = pixel_y;
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if (((btAttr & TATTR_REVERSE) != 0) &&
					!PC88().Z80Main().IsGraphicDisplayColor())
				{
					btAttr &= ~TATTR_REVERSE;
					btColor = BACK_COLOR;
				}
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							//*pbtBits2 = *(pbtBits2+LINESTEP) = btColor;
							if(pixel_x2 % 2 == 0){
								fb.drawPixel(pixel_x2 / 2, pixel_y2 ,btColor);
								preBtColor = btColor;
							}else{
								fb.drawPixel((pixel_x2-1) / 2, pixel_y2 ,btColor | preBtColor);
								preBtColor = 0;
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2++;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr++;
						pixel_x += 8;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}

					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								//*pbtBits2 = *(pbtBits2+LINESTEP) = btColor;
								if(pixel_x2 % 2 == 0){
									fb.drawPixel(pixel_x2 / 2, pixel_y2 ,btColor);
									preBtColor = btColor;
								}else{
									fb.drawPixel((pixel_x2-1) / 2, pixel_y2 ,btColor | preBtColor);
									preBtColor = 0;
								}
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							//*pbtBits2 = *(pbtBits2+LINESTEP) = btColor;
							if(pixel_x2 % 2 == 0){
								fb.drawPixel(pixel_x2 / 2, pixel_y2 ,btColor);
								preBtColor = btColor;
							}else{
								fb.drawPixel((pixel_x2-1) / 2, pixel_y2 ,btColor | preBtColor);
								preBtColor = 0;
							}
							pixel_x2 -= 8;
							pixel_y2 ++;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pixel_y2++;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								//*pbtBits2 = *(pbtBits2+LINESTEP) = btColor;
								if(pixel_x2 % 2 == 0){
									fb.drawPixel(pixel_x2 / 2, pixel_y2 ,btColor);
									preBtColor = btColor;
								}else{
									fb.drawPixel((pixel_x2-1) / 2, pixel_y2 ,btColor | preBtColor);
									preBtColor = 0;
								}
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
					}
				}
				nTAddr++;
				pixel_x += 8;
			}
			pixel_x = 0;
			pixel_y += bHeight25? 8: 10;
		}
	} else if (!PC88().Crtc().IsWidth80() && !IsInterlace()) {
		// display text at 40 columns non-interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x += 2) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr];
				int btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				if(btColor >= 0 && btColor < 18){
					btColor = COLOR_VALUE[btColor];
				}
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				int pixel_x2 = pixel_x;
				int pixel_y2 = pixel_y;
				//uint8_t* pbtBits2 = pbtBits;
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if (((btAttr & TATTR_REVERSE) != 0) &&
					!PC88().Z80Main().IsGraphicDisplayColor())
				{
					btAttr &= ~TATTR_REVERSE;
					btColor = BACK_COLOR;
				}
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							fb.drawPixel(pixel_x2 , pixel_y2 ,btColor);
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2++;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr += 2;
						pixel_x += 8;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								fb.drawPixel(pixel_x2, pixel_y2 ,btColor);
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							fb.drawPixel(pixel_x2, pixel_y2 ,btColor);
							pixel_x2++;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								fb.drawPixel(pixel_x2, pixel_y2 ,btColor);
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;					}
				}
				nTAddr += 2;
				pixel_x += 8;
			}
			pixel_x = 0;
			pixel_y += bHeight25? 8: 10;
		}
	} else if (PC88().Crtc().IsWidth80()) {
	/*
		// display text at 80 columns interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x++) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr],
					btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				uint8_t* pbtBits2 = pbtBits;
				//uint8_t* pbtFonts = &m_abtFonts[nFontType2 * 256 + btChar * 16];
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if (((btAttr & TATTR_REVERSE) != 0) &&
					!PC88().Z80Main().IsGraphicDisplayColor())
				{
					btAttr &= ~TATTR_REVERSE;
					btColor = BACK_COLOR;
				}
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 = btColor;
							pbtBits2++;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-8;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr++;
						pbtBits += 8;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								*pbtBits2 = btColor;
							}
							pbtBits2++;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-8;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 = btColor;
							pbtBits2++;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pbtBits2 += LINESTEP*2;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								*pbtBits2 = btColor;
							}
							pbtBits2++;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-8;
					}
				}
				nTAddr++;
				pbtBits += 8;
			}
			pbtBits += bHeight25? (LINESTEP*16-640): (LINESTEP*20-640);
		}
		*/
	} else {
		//Serial.print("Width40_Interlace");
	/*
		// display text at 40 columns interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x += 2) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr],
					btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				uint8_t* pbtBits2 = pbtBits;
				//uint8_t* pbtFonts = &m_abtFonts[nFontType2 * 256 + btChar * 16];
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if (((btAttr & TATTR_REVERSE) != 0) &&
					!PC88().Z80Main().IsGraphicDisplayColor())
				{
					btAttr &= ~TATTR_REVERSE;
					btColor = BACK_COLOR;
				}
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 = *(pbtBits2+1) = btColor;
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr += 2;
						pbtBits += 16;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								*pbtBits2 = *(pbtBits2+1) = btColor;
							}
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 = *(pbtBits2+1) = btColor;
							pbtBits2 += 2;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pbtBits2 += LINESTEP*2;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								*pbtBits2 = *(pbtBits2+1) = btColor;
							}
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
					}
				}
				nTAddr += 2;
				pbtBits += 16;
			}
			pbtBits += bHeight25? (LINESTEP*16-640): (LINESTEP*20-640);
		}
		*/
	}
}

// draw text(reverse order)

void CX88ScreenDrawer::DrawText2() {
	bool bHeight25 = PC88().Crtc().IsHeight25();
	int nLineCount = bHeight25? 25: 20,
		nVDotCount = bHeight25? 8: 10;
	int nTextPalOfs =
		(!PC88().Z80Main().IsGraphicDisplayAnalog() ||
			PC88().Z80Main().IsGraphicDisplayColor())? 8: 0;
	int nFontType;
	if (PC88().Z80Main().IsPcgEnable()) {
		nFontType = TXCHR_PCG;
	} else if (PC88().Z80Main().IsOptionFont()) {
		nFontType = TXCHR_OPTION;
	} else if (PC88().Z80Main().IsHiraMode()) {
		nFontType = TXCHR_HIRAGANA;
	} else {
		nFontType = TXCHR_NORMAL;
	}
	int pixel_x = 0; 
	int pixel_y = 0;

	int nTAddr;
	uint8_t* pbtTextCharBuf = m_abtTextChar[m_nCurPane];
	uint8_t* pbtTextAttrBuf = m_abtTextAttr[m_nCurPane];
	uint8_t* pbtBits = m_pbtScreenDataBitsTop;
	uint8_t abtColorTbl[256];
	memset(abtColorTbl, 0, sizeof(abtColorTbl));
	for (int i = 1; i < BACK_COLOR; i++) {
		abtColorTbl[i] = (uint8_t)i;
	}
	if (!PC88().Crtc().IsDisplayActive() ||
		PC88().Z80Main().IsTVRamOverlayDisable())
	{
		// not display text
	} else if (PC88().Crtc().IsWidth80() && !IsInterlace()) {
		// display text at 80 columns non-interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x++) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr];
				int btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				if(btColor >= 0 && btColor < 18){
					btColor = COLOR_VALUE[btColor];
				}
				abtColorTbl[0] =
					abtColorTbl[BACK_COLOR] =
						abtColorTbl[BLACK_COLOR] = btColor;
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				//uint8_t* pbtBits2 = pbtBits;
				int pixel_x2 = pixel_x;
				int pixel_y2 = pixel_y;
				//uint8_t* pbtFonts = &m_abtFonts[nFontType2 * 256 + btChar * 16];
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							int color = COLOR_VALUE[abtColorTbl[pixel_x2 + (pixel_y2*2) * 640]];
							fb.drawPixel(pixel_x2, pixel_y2 ,color);
							//*(pbtBits2+LINESTEP) =
							//	abtColorTbl[*(pbtBits2+LINESTEP)];
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2++;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr++;
						pixel_x += 8;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								int color = COLOR_VALUE[abtColorTbl[pixel_x2 + (pixel_y2*2) * 640]];
								fb.drawPixel(pixel_x2, pixel_y2 ,color);
								//*pbtBits2 =
								//	abtColorTbl[*pbtBits2];
								//*(pbtBits2+LINESTEP) =
								//	abtColorTbl[*(pbtBits2+LINESTEP)];
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							int color = COLOR_VALUE[abtColorTbl[pixel_x2 + (pixel_y2*2) * 640]];
							fb.drawPixel(pixel_x2, pixel_y2 ,color);
							//*pbtBits2 =
							//	abtColorTbl[*pbtBits2];
							//*(pbtBits2+LINESTEP) =
							//	abtColorTbl[*(pbtBits2+LINESTEP)];
							pixel_x2++;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								int color = COLOR_VALUE[abtColorTbl[pixel_x2 + (pixel_y2*2) * 640]];
								fb.drawPixel(pixel_x2, pixel_y2 ,color);
								//*pbtBits2 =
								//	abtColorTbl[*pbtBits2];
								//*(pbtBits2+LINESTEP) =
								//	abtColorTbl[*(pbtBits2+LINESTEP)];
							}
							pixel_x2++;
						}
						pbtFonts++;
						pixel_x2 -= 8;
						pixel_y2 ++;
					}
				}
				nTAddr++;
				pixel_x += 8;
			}
			pixel_y += bHeight25? 8: 10;
		}
	} else if (!PC88().Crtc().IsWidth80() && !IsInterlace()) {
		// display text at 40 columns non-interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x += 2) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr],
					btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				abtColorTbl[0] =
					abtColorTbl[BACK_COLOR] =
						abtColorTbl[BLACK_COLOR] = btColor;
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				uint8_t* pbtBits2 = pbtBits;
				//uint8_t* pbtFonts = &m_abtFonts[nFontType2 * 256 + btChar * 16];
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 =
								abtColorTbl[*pbtBits2];
							*(pbtBits2+1) =
								abtColorTbl[*(pbtBits2+1)];
							*(pbtBits2+LINESTEP) =
								abtColorTbl[*(pbtBits2+LINESTEP)];
							*(pbtBits2+LINESTEP+1) =
								abtColorTbl[*(pbtBits2+LINESTEP+1)];
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr += 2;
						pbtBits += 16;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								*pbtBits2 =
									abtColorTbl[*pbtBits2];
								*(pbtBits2+1) =
									abtColorTbl[*(pbtBits2+1)];
								*(pbtBits2+LINESTEP) =
									abtColorTbl[*(pbtBits2+LINESTEP)];
								*(pbtBits2+LINESTEP+1) =
									abtColorTbl[*(pbtBits2+LINESTEP+1)];
							}
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 =
								abtColorTbl[*pbtBits2];
							*(pbtBits2+1) =
								abtColorTbl[*(pbtBits2+1)];
							*(pbtBits2+LINESTEP) =
								abtColorTbl[*(pbtBits2+LINESTEP)];
							*(pbtBits2+LINESTEP+1) =
								abtColorTbl[*(pbtBits2+LINESTEP+1)];
							pbtBits2 += 2;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pbtBits2 += LINESTEP*2;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								*pbtBits2 =
									abtColorTbl[*pbtBits2];
								*(pbtBits2+1) =
									abtColorTbl[*(pbtBits2+1)];
								*(pbtBits2+LINESTEP) =
									abtColorTbl[*(pbtBits2+LINESTEP)];
								*(pbtBits2+LINESTEP+1) =
									abtColorTbl[*(pbtBits2+LINESTEP+1)];
							}
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
					}
				}
				nTAddr += 2;
				pbtBits += 16;
			}
			pbtBits += bHeight25? (LINESTEP*16-640): (LINESTEP*20-640);
		}
	} else if (PC88().Crtc().IsWidth80()) {
		// display text at 80 columns interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x++) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr],
					btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				abtColorTbl[0] =
					abtColorTbl[BACK_COLOR] =
						abtColorTbl[BLACK_COLOR] = btColor;
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				uint8_t* pbtBits2 = pbtBits;
				//uint8_t* pbtFonts = &m_abtFonts[nFontType2 * 256 + btChar * 16];
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 =
								abtColorTbl[*pbtBits2];
							pbtBits2++;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-8;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr++;
						pbtBits += 8;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								*pbtBits2 =
									abtColorTbl[*pbtBits2];
							}
							pbtBits2++;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-8;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 =
								abtColorTbl[*pbtBits2];
							pbtBits2++;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pbtBits2 += LINESTEP*2;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								*pbtBits2 =
									abtColorTbl[*pbtBits2];
							}
							pbtBits2++;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-8;
					}
				}
				nTAddr++;
				pbtBits += 8;
			}
			pbtBits += bHeight25? (LINESTEP*16-640): (LINESTEP*20-640);
		}
	} else {
		// display text at 40 columns interlace mode
		nTAddr = 0;
		for (int y = 0; y < nLineCount; y++) {
			for (int x = 0; x < 80; x += 2) {
				uint8_t btChar = pbtTextCharBuf[nTAddr],
					btAttr = pbtTextAttrBuf[nTAddr],
					btColor = uint8_t((btAttr & TATTR_COLOR)+nTextPalOfs);
				abtColorTbl[0] =
					abtColorTbl[BACK_COLOR] =
						abtColorTbl[BLACK_COLOR] = btColor;
				int nFontType2 = ((btAttr & TATTR_GRAPHIC) != 0)?
						TXCHR_GRAPHIC:
						nFontType;
				uint8_t* pbtBits2 = pbtBits;
				//uint8_t* pbtFonts = &m_abtFonts[nFontType2 * 256 + btChar * 16];
				uint8_t* pbtFonts = m_abtFonts[nFontType2][btChar];
				int y2 = 0, nVDotCount2 = nVDotCount;
				if ((btAttr & TATTR_REVERSE) == 0) {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 =
								abtColorTbl[*pbtBits2];
							*(pbtBits2+1) =
								abtColorTbl[*(pbtBits2+1)];
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
						y2++;
					} else if (
						((btAttr & TATTR_UNDERLINE) == 0) &&
						m_abBlankFonts[nFontType2][btChar])
					{
						nTAddr += 2;
						pbtBits += 16;
						continue;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) != 0) {
								*pbtBits2 =
									abtColorTbl[*pbtBits2];
								*(pbtBits2+1) =
									abtColorTbl[*(pbtBits2+1)];
							}
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						for (int x2 = 0; x2 < 8; x2++) {
							*pbtBits2 =
								abtColorTbl[*pbtBits2];
							*(pbtBits2+1) =
								abtColorTbl[*(pbtBits2+1)];
							pbtBits2 += 2;
						}
					}
				} else {
					if ((btAttr & TATTR_OVERLINE) != 0) {
						pbtFonts++;
						pbtBits2 += LINESTEP*2;
						y2++;
					}
					if ((btAttr & TATTR_UNDERLINE) != 0) {
						nVDotCount2--;
					}
					for (; y2 < nVDotCount2; y2++) {
						for (int x2 = 0; x2 < 8; x2++) {
							if ((*pbtFonts & (0x80 >> x2)) == 0) {
								*pbtBits2 =
									abtColorTbl[*pbtBits2];
								*(pbtBits2+1) =
									abtColorTbl[*(pbtBits2+1)];
							}
							pbtBits2 += 2;
						}
						pbtFonts++;
						pbtBits2 += LINESTEP*2-16;
					}
				}
				nTAddr += 2;
				pbtBits += 16;
			}
			pbtBits += bHeight25? (LINESTEP*16-640): (LINESTEP*20-640);
		}
	}
}

// draw screen

void CX88ScreenDrawer::DrawScreen() {
	fb.fillSprite(TFT_BLACK);
	DrawGraphics();
	if (PC88().Z80Main().IsN80V2BasicRomMode() &&
		PC88().Z80Main().IsTextPriority() &&
		PC88().Z80Main().IsGraphicDisplayColor())
	{
		// draw text under graphic
		DrawText2();
	} else {
		// draw text over graphic
		DrawText();
	}
	fb.pushSprite(0, 0);   
}

// update palette

bool CX88ScreenDrawer::UpdatePalette() {
	if (!PC88().Z80Main().IsPaletteUpdate()) {
		return false;
	}
	PC88().Z80Main().SetPaletteUpdate(false);
	int nPalNo, nPalR, nPalG, nPalB;
	for (nPalNo = 0; nPalNo < ANIMATE_COUNT; nPalNo++) {
		int nPalNo2 = (nPalNo < 8)? nPalNo: BACK_COLOR;
		nPalR = (PC88().Z80Main().GetColorPalette(nPalNo) >> 3) & 7;
		nPalG = (PC88().Z80Main().GetColorPalette(nPalNo) >> 6) & 7;
		nPalB = PC88().Z80Main().GetColorPalette(nPalNo) & 7;

#ifdef X88_GUI_WINDOWS

		m_prgbPalettes[nPalNo2].rgbRed   = uint8_t(
			(nPalR << 5) | (nPalR << 2) | (nPalR >> 1));
		m_prgbPalettes[nPalNo2].rgbGreen = uint8_t(
			(nPalG << 5) | (nPalG << 2) | (nPalG >> 1));
		m_prgbPalettes[nPalNo2].rgbBlue  = uint8_t(
			(nPalB << 5) | (nPalB << 2) | (nPalB >> 1));

#elif defined(X88_GUI_GTK)

		m_aColorTable[nPalNo2].red = (gushort)(
			(((nPalR << 5) | (nPalR << 2) | (nPalR >> 1)) & 0xFF)*0x0101);
		m_aColorTable[nPalNo2].green = (gushort)(
			(((nPalG << 5) | (nPalG << 2) | (nPalG >> 1)) & 0xFF)*0x0101);
		m_aColorTable[nPalNo2].blue = (gushort)(
			(((nPalB << 5) | (nPalB << 2) | (nPalB >> 1)) & 0xFF)*0x0101);

#endif // X88_GUI

	}

#ifdef X88_GUI_WINDOWS

	HWND hwndDesktop = GetDesktopWindow();
	HDC hdcDesktop = GetDC(hwndDesktop);
	HDC hdcMem = CreateCompatibleDC(hdcDesktop);
	if (hdcMem != NULL) {
		HBITMAP hbmpOrg = (HBITMAP)SelectObject(hdcMem, m_hdibScreen);
		SetDIBColorTable(hdcMem, 0, COLOR_COUNT-1, m_prgbPalettes);
		SelectObject(hdcMem, hbmpOrg);
		DeleteDC(hdcMem);
	}
	ReleaseDC(hwndDesktop, hdcDesktop);
	if (m_hpalScreen != NULL) {
		for (nPalNo = 0; nPalNo < COLOR_COUNT-1; nPalNo++) {
			m_pScreenPalEntry[nPalNo].peRed   = m_prgbPalettes[nPalNo].rgbRed;
			m_pScreenPalEntry[nPalNo].peGreen = m_prgbPalettes[nPalNo].rgbGreen;
			m_pScreenPalEntry[nPalNo].peBlue  = m_prgbPalettes[nPalNo].rgbBlue;
		}
	}

#endif // X88_GUI

	return true;
}

// draw screen for video art board

bool CX88ScreenDrawer::DrawScreenVAB() {
	bool bUpdate = false;
	if (m_pbtScreenDataBits2 == NULL) {
		bUpdate = true;

#ifdef X88_GUI_WINDOWS

		m_pbmiScreen2 = (BITMAPINFO*)m_abtBmi2;
		memset(
			m_pbmiScreen2, 0x00,
			sizeof(BITMAPINFOHEADER)+sizeof(uint32_t)*3);
		m_pbmiScreen2->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pbmiScreen2->bmiHeader.biWidth = 640;
		m_pbmiScreen2->bmiHeader.biHeight = 400;
		m_pbmiScreen2->bmiHeader.biPlanes = 1;
		m_pbmiScreen2->bmiHeader.biBitCount = BITS_COUNT2;
		m_pbmiScreen2->bmiHeader.biCompression = BI_BITFIELDS;
		uint32_t* pdwMask = (uint32_t*)(m_pbmiScreen2->bmiColors);
		pdwMask[0] = 0x0000F800;
		pdwMask[1] = 0x000007E0;
		pdwMask[2] = 0x0000001F;
		HDC hdc = GetDC(HWND_DESKTOP);
		m_hdibScreen2 = CreateDIBSection(
			hdc,
			m_pbmiScreen2, DIB_RGB_COLORS, (void**)(&m_pbtScreenDataBits2),
			NULL, 0);
		if (m_hdibScreen2 != NULL) {
			m_pbtScreenDataBits2Top = m_pbtScreenDataBits2+LINELEN2*399;
		}
		ReleaseDC(HWND_DESKTOP, hdc);

#elif defined(X88_GUI_GTK)

		m_pbtScreenDataBits2 = m_pbtScreenDataBits2Top =
			new uint8_t[LINELEN2*400];
		if (m_pbtScreenDataBits2 != NULL) {
			memset(m_pbtScreenDataBits2, 0, LINELEN2*400);
		}

#endif // X88_GUI

		if (m_pbtScreenDataBits2 == NULL) {
			return false;
		}
	}
	if (!PC88().Z80Main().IsVABUpdate()) {
		return bUpdate;
	}
	PC88().Z80Main().SetVABUpdate(false);
	bUpdate = true;
	uint8_t* pbtBits = m_pbtScreenDataBits2Top;
	uint8_t* pbtVAB = PC88().Z80Main().GetExRamPtr(CPC88Z80Main::EX_RAM_VAB);
	int y = 200;
	do {
		int x = 320;
		do {
			unsigned nPixelVAB = *(pbtVAB++);
			nPixelVAB |= *(pbtVAB++) << 8;

#ifdef X88_GUI_WINDOWS

			uint16_t wPixelBits = (uint16_t)(
				((nPixelVAB & 0xFC00) >> 5) |
				((nPixelVAB & 0x03E0) << 6) |
				(nPixelVAB & 0x001F));
			*((uint16_t*)pbtBits) = wPixelBits;
			pbtBits += sizeof(uint16_t);
			*((uint16_t*)pbtBits) = wPixelBits;
			pbtBits += sizeof(uint16_t);

#elif defined(X88_GUI_GTK)

			unsigned nRed = (nPixelVAB & 0x03E0) >> 2,
				nGreen = (nPixelVAB & 0xFC00) >> 8,
				nBlue = (nPixelVAB & 0x001F) << 3;
			nRed |= nRed >> 5;
			nGreen |= nGreen >> 6;
			nBlue |= nBlue >> 5;
			*(pbtBits++) = (uint8_t)nRed;
			*(pbtBits++) = (uint8_t)nGreen;
			*(pbtBits++) = (uint8_t)nBlue;
			*(pbtBits++) = (uint8_t)nRed;
			*(pbtBits++) = (uint8_t)nGreen;
			*(pbtBits++) = (uint8_t)nBlue;

#endif // X88_GUI

		} while (--x != 0);
		pbtBits += LINESTEP2*2-LINELEN2;
		if (!IsInterlace()) {
			memcpy(pbtBits-LINESTEP2, pbtBits-LINESTEP2*2, LINELEN2);
		} else {
			memset(pbtBits-LINESTEP2, 0, LINELEN2);
		}
	} while (--y != 0);
	return bUpdate;
}


int CX88ScreenDrawer::CalcBtColor(int leftColor, int rightColor){
	if(leftColor == rightColor){
		return COLOR_VALUE[leftColor];
	}
	return MIX_COLOR_VALUE[leftColor][rightColor];
}
