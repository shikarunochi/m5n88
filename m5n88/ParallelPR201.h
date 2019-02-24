////////////////////////////////////////////////////////////
// PC-PC201 Emulator
//
// Written by Manuke

#ifndef ParallelPR201_DEFINED
#define ParallelPR201_DEFINED

////////////////////////////////////////////////////////////
// declare

class CParallelPR201;

class CPR201CommandState;
class CPR201ANKCommandState;
class CPR201KanjiCommandState;
class CPR201ESCCommandState;
class CPR201FSCommandState;
class CPR201USCommandState;
class CPR201VFUCommandState;
class CPR201ImageCommandState;
class CPR201GaijiCommandState;

////////////////////////////////////////////////////////////
// include

#include "ParallelPrinter.h"

////////////////////////////////////////////////////////////
// declaration of CPR201CommandState

class CPR201CommandState {
// attribute
protected:
	// printer
	CParallelPR201* m_pPrinter;
	// previous command state
	CPR201CommandState* m_pPreCommandState;

public:
	// get printer
	CParallelPR201* GetPrinter() {
		return m_pPrinter;
	}
	// set printer
	void SetPrinter(CParallelPR201* pPrinterNew) {
		m_pPrinter = pPrinterNew;
	}
	// get previous command state
	CPR201CommandState* GetPreCommandState() {
		return m_pPreCommandState;
	}
	// set previous command state
	void SetPreCommandState(CPR201CommandState* pPreCommandStateNew) {
		m_pPreCommandState = pPreCommandStateNew;
	}

// create & destroy
public:
	// default constructor
	CPR201CommandState();
	// destructor
	virtual ~CPR201CommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201ANKCommandState

class CPR201ANKCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// singleton
	static CPR201ANKCommandState m_cstateANK;

public:
	// get singleton instance
	static CPR201ANKCommandState* GetInstance() {
		return &m_cstateANK;
	}

// create & destroy
public:
	// default constructor
	CPR201ANKCommandState();
	// destructor
	virtual ~CPR201ANKCommandState();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201KanjiCommandState

class CPR201KanjiCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// first byte
	uint8_t m_btFirst;

	// singleton
	static CPR201KanjiCommandState m_cstateKanji;

public:
	// get singleton instance
	static CPR201KanjiCommandState* GetInstance() {
		return &m_cstateKanji;
	}

// create & destroy
public:
	// default constructor
	CPR201KanjiCommandState();
	// destructor
	virtual ~CPR201KanjiCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201ESCCommandState

class CPR201ESCCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// parameters
	std::vector<uint8_t> m_vectParams;

	// singleton
	static CPR201ESCCommandState m_cstateESC;

public:
	// get singleton instance
	static CPR201ESCCommandState* GetInstance() {
		return &m_cstateESC;
	}

// create & destroy
public:
	// default constructor
	CPR201ESCCommandState();
	// destructor
	virtual ~CPR201ESCCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201FSCommandState

class CPR201FSCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// parameters
	std::vector<uint8_t> m_vectParams;

	// singleton
	static CPR201FSCommandState m_cstateFS;

public:
	// get singleton instance
	static CPR201FSCommandState* GetInstance() {
		return &m_cstateFS;
	}

// create & destroy
public:
	// default constructor
	CPR201FSCommandState();
	// destructor
	virtual ~CPR201FSCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201USCommandState

class CPR201USCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// parameters
	std::vector<uint8_t> m_vectParams;

	// singleton
	static CPR201USCommandState m_cstateUS;

public:
	// get singleton instance
	static CPR201USCommandState* GetInstance() {
		return &m_cstateUS;
	}

// create & destroy
public:
	// default constructor
	CPR201USCommandState();
	// destructor
	virtual ~CPR201USCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201VFUCommandState

class CPR201VFUCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// parameters
	std::vector<uint8_t> m_vectVFUParams;

	// singleton
	static CPR201VFUCommandState m_cstateVFU;

public:
	// get singleton instance
	static CPR201VFUCommandState* GetInstance() {
		return &m_cstateVFU;
	}

// create & destroy
public:
	// default constructor
	CPR201VFUCommandState();
	// destructor
	virtual ~CPR201VFUCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);
};

////////////////////////////////////////////////////////////
// declaration of CPR201ImageCommandState

class CPR201ImageCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// image kind
	uint8_t m_btImageKind;
	// x dot count of image
	int m_cxDot;
	// image data count
	int m_nImageDataCount;
	// image data
	std::vector<uint8_t> m_vectImageData;

	// singleton
	static CPR201ImageCommandState m_cstateImage;

public:
	// get singleton instance
	static CPR201ImageCommandState* GetInstance() {
		return &m_cstateImage;
	}

// create & destroy
public:
	// default constructor
	CPR201ImageCommandState();
	// destructor
	virtual ~CPR201ImageCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);

// operation
public:
	// set image info
	virtual bool SetImageInfo(uint8_t btImageKind, int cxDot);
};

////////////////////////////////////////////////////////////
// declaration of CPR201GaijiCommandState

class CPR201GaijiCommandState :
	public CPR201CommandState
{
// attribute
protected:
	// gaiji code
	uint16_t m_wCode;
	// x dot count for image
	int m_cxDot;
	// y dot count for image
	int m_cyDot;
	// left gap
	int m_nLeftGap;
	// right gap
	int m_nRightGap;
	// gaiji data count
	int m_nGaijiDataCount;
	// gaiji data
	std::vector<uint8_t> m_vectGaijiData;

	// singleton
	static CPR201GaijiCommandState m_cstateGaiji;

public:
	// get singleton instance
	static CPR201GaijiCommandState* GetInstance() {
		return &m_cstateGaiji;
	}

// create & destroy
public:
	// default constructor
	CPR201GaijiCommandState();
	// destructor
	virtual ~CPR201GaijiCommandState();

// initialize
public:
	// initialize at first
	virtual void Initialize();

// implementation
public:
	// process data
	virtual void ProcessData(uint8_t btData);

// operation
public:
	// set gaiji info
	virtual bool SetGaijiInfo(
		uint16_t wCode,
		int cxDot, int cyDot,
		int nLeftGap, int nRightGap);
};

////////////////////////////////////////////////////////////
// declaration of CParallelPR201

class CParallelPR201 :
	public CParallelPrinter
{
// enum
public:
	// constant value
	enum {
		PR201_DPI  = 160,
		PR201_HEAD = 24
	};
	// hi-resolution value
	enum {
		HIRES_X      = 6,
		HIRES_Y_NAT  = 9,
		HIRES_Y_COPY = 12
	};
	// printing method
	enum {
		METHOD_HDPICA       = 1,
		METHOD_HSPICA       = 2,
		METHOD_ELITE        = 3,
		METHOD_CONDENSE     = 4,
		METHOD_PROPORTIONAL = 5,
		METHOD_KANJI        = 6,
		METHOD_VKANJI       = 7
	};
	// script mode
	enum {
		SCRIPT_NONE  = 0,
		SCRIPT_SUPER = 1,
		SCRIPT_SUB   = 2
	};
	// size
	enum {
		PICA_WIDTH         = 16*HIRES_X,
		ELITE_WIDTH        = (15*160*HIRES_X)/180,
		CONDENSE_WIDTH     = (14*160*HIRES_X)/240,
		PROPORTIONAL_WIDTH = 14*HIRES_X,
		KANJI_070_WIDTH    = (24*160*HIRES_X)/240,
		KANJI_095_WIDTH    = (24*160*HIRES_X)/180,
		KANJI_105_WIDTH    = 24*HIRES_X,
		KANJI_120_WIDTH    = (30*160*HIRES_X)/180,
		KANJI_1_5_PITCH    = (1*160*HIRES_X)/5,
		KANJI_1_6_PITCH    = (1*160*HIRES_X)/6,
		KANJI_3_20_PITCH   = (3*160*HIRES_X)/20,
		KANJI_2_15_PITCH   = (2*160*HIRES_X)/15,
		KANJI_1_10_PITCH   = (1*160*HIRES_X)/10,
		NORMAL_HEIGHT      = 24
	};
	// dot count
	enum {
		CXPICA     = 16,
		CXELITE    = 15,
		CXCONDENSE = 14,
		CXKANJI    = 24,
		CXGAIJI16  = 16,
		CYNORMAL   = 24,
		CYGAIJI16  = 16
	};
	// y-position of small kanji
	enum {
		SMALLKANJI_V_HI  = 0,
		SMALLKANJI_V_MID = 1,
		SMALLKANJI_V_LO  = 2
	};
	// using font
	enum {
		USEFONT_DEFAULT = 0,
		USEFONT_ITALIC  = 1,
		USEFONT_COURIER = 2,
		USEFONT_GOTHIC  = 3
	};
	// maximum value
	enum {
		VFU_CH_MAX  = 6,
		VFU_LEN_MAX = 128,
		HORZTAB_MAX = 36,
		SBGAIJI_MAX = 127,
		DBGAIJI_MAX = 256
	};

// typedef
protected:
	// tab position set type
	typedef std::set<int> CTabPosSet;
	// gaiji set type
	typedef std::set<CPrinterGaiji> CGaijiSet;

// attribute
protected:
	// selected paper
	int m_nSelectedPaper;
	// paper centering
	bool m_bPaperCentering;
	// reverse feed
	bool m_bReverseFeed;
	// x-position of printer head in hi-resolution
	int m_nHeadXHR;
	// y-position of printer head in hi-resolution
	int m_nHeadYHR;
	// line feed height in hi-resolution
	int m_nLineFeedHeightHR;
	// line-feed height on carriage-return in hi-resolution
	int m_nLineFeedHeigntOnCRHR;
	// left margin in hi-resolution
	int m_nLeftMarginHR;
	// right margin in hi-resolution
	int m_nRightMarginHR;
	// horizontal-tabs
	CTabPosSet m_setHorzTabs;
	// horizontal-tab skipping
	bool m_bHorzTabSkipping;
	// vertical-tabs in hi-resolution
	CTabPosSet m_asetVertTabsHR[VFU_CH_MAX];
	// VFU head y-position offset
	int m_nVFUOfsYHR;
	// VFU page height in hi-resolution
	int m_nVFUPageHeightHR;
	// VFU page bottom area in hi-resolution
	int m_nVFUPageBottomHR;
	// printing method
	int m_nPrintingMethod;
	// kanji width in hi-resolution
	int m_nKanjiWidthHR;
	// kanji pitch in hi-resolution
	int m_nKanjiPitchHR;
	// left fix dot space
	int m_nFixDotSpaceLeft;
	// right fix dot space
	int m_nFixDotSpaceRight;
	// horizontal zoom rate
	int m_nHorzZoom;
	// vertical zoom rate
	int m_nVertZoom;
	// using font
	int m_nUseFont;
	// strong printing mode
	bool m_bStrongMode;
	// hiragana mode
	bool m_bHiraganaMode;
	// script mode
	int m_nScriptMode;
	// copy mode
	bool m_bCopyMode;
	// half-width kanji vertical mode
	bool m_bHalfKanjiVertMode;
	// half-width kanji combination mode
	bool m_bHalfVertKanjiCombinationMode;
	// half-width kanji combinating
	bool m_bHalfVertKanjiCombinating;
	// y-position of small kanji printing
	int m_nSmallKanjiVertPos;
	// small kanji combination mode
	bool m_bSmallKanjiCombinationMode;
	// small kanji combinating
	bool m_bSmallKanjiCombinating;
	// line draw mode
	bool m_bLineDrawMode;
	// underline
	bool m_bUnderLine;
	// line width
	int m_nLineWidth;
	// character repeat count
	int m_nCharRepeatCount;
	// using download character
	bool m_bDownloadCharUse;
	// single-byte gaijis
	CGaijiSet m_setGaijisSB;
	// double-byte gaijis
	CGaijiSet m_setGaijisDB;
	// current command state
	CPR201CommandState* m_pcstateCurrent;

public:
	// get device id
	virtual std::string GetDeviceID() const;
	// get DPI
	virtual int GetDPI() const {
		return PR201_DPI;
	}
	// is reverse feed
	bool IsReverseFeed() const {
		return m_bReverseFeed;
	}
	// set reverse feed
	void SetReverseFeed(bool bReverseFeedNew) {
		m_bReverseFeed = bReverseFeedNew;
	}
	// get x-position of printer head in hi-resolution
	int GetHeadXHR() const {
		return m_nHeadXHR;
	}
	// set x-position of printer head in hi-resolution
	void SetHeadXHR(int nHeadXHRNew) {
		m_nHeadXHR = nHeadXHRNew;
	}
	// get y-position of printer head in hi-resolution
	int GetHeadYHR() const {
		return m_nHeadYHR;
	}
	// set y-position of printer head in hi-resolution
	void SetHeadYHR(int nHeadYHRNew) {
		m_nHeadYHR = nHeadYHRNew;
	}
	// get line-feed height in hi-resolution
	int GetLineFeedHeightHR() const {
		return m_nLineFeedHeightHR;
	}
	// set line-feed height in hi-resolution
	void SetLineFeedHeightHR(int nLineFeedHeightHRNew) {
		m_nLineFeedHeightHR = nLineFeedHeightHRNew;
	}
	// get line-feed height on carriage-return in hi-resolution
	int GetLineFeedHeigntOnCRHR() const {
		return m_nLineFeedHeigntOnCRHR;
	}
	// set line-feed height on carriage-return in hi-resolution
	void SetLineFeedHeigntOnCRHR(int nLineFeedHeigntOnCRHRNew) {
		m_nLineFeedHeigntOnCRHR = nLineFeedHeigntOnCRHRNew;
	}
	// get left margin in hi-resolution
	int GetLeftMarginHR() const {
		return m_nLeftMarginHR;
	}
	// set left margin in hi-resolution
	void SetLeftMarginHR(int nLeftMarginHRNew) {
		m_nLeftMarginHR = nLeftMarginHRNew;
	}
	// get right margin in hi-resolution
	int GetRightMarginHR() const {
		return m_nRightMarginHR;
	}
	// set right margin in hi-resolution
	void SetRightMarginHR(int nRightMarginHENew) {
		m_nRightMarginHR = nRightMarginHENew;
	}
	// get VFU head y-position offset
	int GetVFUOfsYHR() const {
		return m_nVFUOfsYHR;
	}
	// set VFU head y-position offset
	void SetVFUOfsYHR(int nVFUOfsYHRNew) {
		m_nVFUOfsYHR = nVFUOfsYHRNew;
	}
	// get VFU page height in hi-resolution
	int GetVFUPageHeightHR() const {
		return m_nVFUPageHeightHR;
	}
	// set VFU page height in hi-resolution
	void SetVFUPageHeightHR(int nVFUPageHeightHRNew) {
		m_nVFUPageHeightHR = nVFUPageHeightHRNew;
	}
	// get VFU page bottom area in hi-resolution
	int GetVFUPageBottomHR() const {
		return m_nVFUPageBottomHR;
	}
	// set VFU page bottom area in hi-resolution
	void SetVFUPageBottomHR(int nVFUPageBottomHRNew) {
		m_nVFUPageBottomHR = nVFUPageBottomHRNew;
	}
	// get printing method
	int GetPrintingMethod() const {
		return m_nPrintingMethod;
	}
	// set printing method
	void SetPrintingMethod(int nPrintingMethodNew) {
		m_nPrintingMethod = nPrintingMethodNew;
	}
	// get kanji width in hi-resolution
	int GetKanjiWidthHR() const {
		return m_nKanjiWidthHR;
	}
	// set kanji width in hi-resolution
	void SetKanjiWidthHR(int nKanjiWidthHRNew) {
		m_nKanjiWidthHR = nKanjiWidthHRNew;
	}
	// get kanji pitch in hi-resolution
	int GetKanjiPitchHR() const {
		return m_nKanjiPitchHR;
	}
	// set kanji pitch in hi-resolution
	void SetKanjiPitchHR(int nKanjiPitchHRNew) {
		m_nKanjiPitchHR = nKanjiPitchHRNew;
	}
	// get left fix dot space
	int GetFixDotSpaceLeft() const {
		return m_nFixDotSpaceLeft;
	}
	// set left fix dot space
	void SetFixDotSpaceLeft(int nFixDotSpaceLeftNew) {
		m_nFixDotSpaceLeft = nFixDotSpaceLeftNew;
	}
	// get right fix dot space
	int GetFixDotSpaceRight() const {
		return m_nFixDotSpaceRight;
	}
	// set right fix dot space
	void SetFixDotSpaceRight(int nFixDotSpaceRightNew) {
		m_nFixDotSpaceRight = nFixDotSpaceRightNew;
	}
	// get horizontal zoom rate
	int GetHorzZoom() const {
		return m_nHorzZoom;
	}
	// set horizontal zoom rate
	void SetHorzZoom(int nHorzZoomNew) {
		m_nHorzZoom = nHorzZoomNew;
	}
	// get vertical zoom rate
	int GetVertZoom() const {
		return m_nVertZoom;
	}
	// set vertical zoom rate
	void SetVertZoom(int nVertZoomNew) {
		m_nVertZoom = nVertZoomNew;
	}
	// get using font
	int GetUseFont() const {
		return m_nUseFont;
	}
	// set using font
	void SetUseFont(int nUseFontNew) {
		m_nUseFont = nUseFontNew;
	}
	// is strong printing mode
	bool IsStrongMode() const {
		return m_bStrongMode;
	}
	// set strong printing mode
	void SetStrongMode(bool bStrongModeNew) {
		m_bStrongMode = bStrongModeNew;
	}
	// is hiragana mode
	bool IsHiraganaMode() const {
		return m_bHiraganaMode;
	}
	// set hiragana mode
	void SetHiraganaMode(bool bHiraganaModeNew) {
		m_bHiraganaMode = bHiraganaModeNew;
	}
	// get script mode
	int GetScriptMode() const {
		return m_nScriptMode;
	}
	// set script mode
	void SetScriptMode(int nScriptModeNew) {
		m_nScriptMode = nScriptModeNew;
	}
	// is copy mode
	bool IsCopyMode() const {
		return m_bCopyMode;
	}
	// set copy mode
	void SetCopyMode(bool bCopyModeNew) {
		m_bCopyMode = bCopyModeNew;
	}
	// is half-width kanji vertical mode
	bool IsHalfKanjiVertMode() const {
		return m_bHalfKanjiVertMode;
	}
	// set half-width kanji vertical mode
	void SetHalfKanjiVertMode(bool bHalfKanjiVertModeNew) {
		m_bHalfKanjiVertMode = bHalfKanjiVertModeNew;
	}
	// is half-width kanji combination mode
	bool IsHalfVertKanjiCombinationMode() const {
		return m_bHalfVertKanjiCombinationMode;
	}
	// set half-width kanji combination mode
	void SetHalfVertKanjiCombinationMode(
		bool bHalfVertKanjiCombinationModeNew)
	{
		m_bHalfVertKanjiCombinationMode = bHalfVertKanjiCombinationModeNew;
	}
	// is half-width kanji combinating
	bool IsHalfVertKanjiCombinating() const {
		return m_bHalfVertKanjiCombinating;
	}
	// set half-width kanji combinating
	void SetHalfVertKanjiCombinating(
		bool bHalfVertKanjiCombinatingNew)
	{
		m_bHalfVertKanjiCombinating = bHalfVertKanjiCombinatingNew;
	}
	// get y-position of small kanji printing
	int GetSmallKanjiVertPos() const {
		return m_nSmallKanjiVertPos;
	}
	// set y-position of small kanji printing
	void SetSmallKanjiVertPos(int nSmallKanjiVertPosNew) {
		m_nSmallKanjiVertPos = nSmallKanjiVertPosNew;
	}
	// is small kanji combination mode
	bool IsSmallKanjiCombinationMode() const {
		return m_bSmallKanjiCombinationMode;
	}
	// set small kanji combination mode
	void SetSmallKanjiCombinationMode(
		bool bSmallKanjiCombinationModeNew)
	{
		m_bSmallKanjiCombinationMode = bSmallKanjiCombinationModeNew;
	}
	// is small kanji combinating
	bool IsSmallKanjiCombinating() const {
		return m_bSmallKanjiCombinating;
	}
	// set small kanji combinating
	void SetSmallKanjiCombinating(
		bool bSmallKanjiCombinatingNew)
	{
		m_bSmallKanjiCombinating = bSmallKanjiCombinatingNew;
	}
	// is line draw mode
	bool IsLineDrawMode() const {
		return m_bLineDrawMode;
	}
	// set line draw mode
	void SetLineDrawMode(bool bLineDrawModeNew) {
		m_bLineDrawMode = bLineDrawModeNew;
	}
	// is underline
	bool IsUnderLine() const {
		return m_bUnderLine;
	}
	// set underline
	void SetUnderLine(bool bUnderLineNew) {
		m_bUnderLine  = bUnderLineNew;
	}
	// get line width
	int GetLineWidth() const {
		return m_nLineWidth;
	}
	// set line width
	void SetLineWidth(int nLineWidthNew) {
		m_nLineWidth = nLineWidthNew;
	}
	// get character repeat count
	int GetCharRepeatCount() const {
		return m_nCharRepeatCount;
	}
	// set character repeat count
	void SetCharRepeatCount(int nCharRepeatCountNew) {
		m_nCharRepeatCount = nCharRepeatCountNew;
	}
	// is using download character
	bool IsDownloadCharUse() const {
		return m_bDownloadCharUse;
	}
	// set using download character
	void SetDownloadCharUse(bool bDownloadCharUseNew) {
		m_bDownloadCharUse = bDownloadCharUseNew;
	}

// create & destroy
public:
	// default constructor
	CParallelPR201();
	// destructor
	virtual ~CParallelPR201();

// initialize
public:
	// initialize at first
	virtual void Initialize();
	// reset
	virtual void Reset();

// implementation
protected:
	// process data
	virtual void ProcessData(uint8_t btData);

public:
	// carriage-return
	virtual bool CarriageReturn();
	// line-feed
	virtual bool LineFeed();
	// page-feed
	virtual bool PageFeed();
	// head move
	virtual bool HeadMove(int nMove);
	// horizontal-tab
	virtual bool HorzTab();
	// vertical-tab
	virtual bool VertTab();
	// get selectable paper count
	virtual int GetSelectablePaperCount() const;
	// get selectable paper
	virtual int GetSelectablePaper(int nIndex) const;
	// get selected paper
	virtual int GetSelectedPaper() const;
	// select paper
	virtual bool SelectPaper(int nPaper);
	// is able paper centering
	virtual bool IsAblePaperCentering() const;
	// is paper centering
	virtual bool IsPaperCentering() const;
	// set paper centering
	virtual bool SetPaperCentering(bool bPaperCentering);
	// paper feed from external operation
	virtual bool PaperFeed(bool bPageFeed, int nFeed);

// operation
protected:
	// move head in hi-resolution
	virtual bool HeadMoveHR(int nMoveHR);
	// feed dot in hi-resolution
	virtual bool DoDotFeedHR(int nFeedDotHR);
	// feed page
	virtual bool DoPageFeed(int nFeedPage);
	// get current font type
	virtual int GetCurrentFontType(bool bASCII);
	// get current line type
	virtual int GetCurrentLineType();
	// output text
	virtual bool OutputText(
		int nFontType, int nPitchType,
		uint16_t wText,
		int nCharType,
		int nCharWidthHR, int nCharHeight,
		int nLeftGapHR, int nRightGapHR,
		int nLineType,
		int nVOfs,
		int nHorzZoom, int nVertZoom,
		bool bHeadBack,
		const CPrinterGaiji* pGaiji);

public:
	// delete one page
	virtual bool DeletePage(int nPage);
	// change comand state
	virtual void ChangeComandState(CPR201CommandState* pcstateNew);
	// get current character pitch in hi-resolution
	virtual int GetCurrentCharPitchHR();
	// register horizontal-tab in hi-resolution
	virtual bool RegisterHorzTabHR(int nPosHR);
	// remove one horizontal-tab in hi-resolution
	virtual bool RemoveHorzTabHR(int nPosHR);
	// remove all horizontal-tabs in hi-resolution
	virtual bool RemoveAllHorzTab();
	// set VFU
	virtual bool SetVFU(const std::vector<uint8_t>& vectVFUParams);
	// execute VFU
	virtual bool ExecVFU(int nChannel);
	// output text(single-byte)
	virtual bool OutputTextSB(uint8_t btText);
	// output text(double-byte)
	virtual bool OutputTextDB(uint16_t wText);
	// output null text
	virtual bool OutputTextNull(int nCharWidthHR, bool bHorzZoom);
	// output dot image graphics
	virtual bool OutputDotImage(
		uint8_t btImageKind,
		int cxDot,
		const std::vector<uint8_t>& vectImageData);
	// output repeated dots
	virtual bool OutputDotRepeat(
		uint8_t btImageKind,
		int cxDot,
		const std::vector<uint8_t>& vectRepeatData);
	// register gaiji
	virtual bool RegisterGaiji(const CPrinterGaiji& gaijiRegist);
	// remove all gaiji(single-byte)
	virtual bool RemoveAllSBGaiji();
	// remove all gaiji(double-byte)
	virtual bool RemoveAllDBGaiji();
};

#endif // ParallelPR201_DEFINED
