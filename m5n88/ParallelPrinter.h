////////////////////////////////////////////////////////////
// Printer Emulator
//
// Written by Manuke

#ifndef ParallelPrinter_DEFINED
#define ParallelPrinter_DEFINED

////////////////////////////////////////////////////////////
// declare

class FPrinterBitmap;

class CPrinterGaiji;

class CPrinterObject;
class CPrinterTextObject;
class CPrinterImageObject;

class CPrinterPage;

class CParallelPrinter;

////////////////////////////////////////////////////////////
// include

#include "ParallelDevice.h"

////////////////////////////////////////////////////////////
// declaration of FPrinterBitmap

class FPrinterBitmap {
// interface(FPrinterBitmap)
public:
	// get x dot count
	virtual int GetDotCX() const = 0;
	// get y dot count
	virtual int GetDotCY() const = 0;
	// get pixel value
	virtual uint32_t GetPixel(int x, int y) const = 0;
	// set pixel value
	virtual void SetPixel(int x, int y, uint32_t dwPixel) = 0;
};

////////////////////////////////////////////////////////////
// declaration of CPrinterGaiji

class CPrinterGaiji :
	virtual public FPrinterBitmap
{
// class
protected:
	// declaration of SPrinterGaijiData
	struct SPrinterGaijiData {
		// reference counter
		int nReference;
		// x dot count
		int cxDot;
		// y dot count
		int cyDot;
		// vert byte count for image
		int nVBytes;
		// image data
		std::vector<uint8_t> vectImageData;
	};

// attribute
protected:
	// code
	uint16_t m_wCode;
	// gaiji data
	SPrinterGaijiData* m_pData;

public:
	// get code
	uint16_t GetCode() const {
		return m_wCode;
	}
	// is valid gaiji data
	bool IsValidData() const {
		return m_pData != NULL;
	}
	// get image data
	const std::vector<uint8_t>& GetImageData() const {
		return m_pData->vectImageData;
	}
	std::vector<uint8_t>& GetImageData() {
		return m_pData->vectImageData;
	}

// create & destroy
public:
	// default constructor
	CPrinterGaiji();
	// standard constructor
	CPrinterGaiji(uint16_t wCode, int cxDot = 0, int cyDot = 0);
	// copy constructor
	CPrinterGaiji(const CPrinterGaiji& gaijiOther);
	// destructor
	virtual ~CPrinterGaiji();

// operator
public:
	// let
	CPrinterGaiji& operator=(const CPrinterGaiji& gaijiOther);
	// compare(less)
	bool operator<(const CPrinterGaiji& gaijiOther) const;

// interface(FPrinterBitmap)
public:
	// get x dot count
	virtual int GetDotCX() const {
		return m_pData->cxDot;
	}
	// get y dot count
	virtual int GetDotCY() const {
		return m_pData->cyDot;
	}
	// get pixel value
	virtual uint32_t GetPixel(int x, int y) const {
		return (((m_pData->vectImageData[x*m_pData->nVBytes+y/8]
				>> (y%8)) & 1) != 0)?
			0: 7;
	}
	// set pixel value
	virtual void SetPixel(int x, int y, uint32_t dwPixel) {
		if (dwPixel != 0) {
			m_pData->vectImageData[x*m_pData->nVBytes+y/8] |=
				(uint8_t)(1 << (y%8));
		} else {
			m_pData->vectImageData[x*m_pData->nVBytes+y/8] &=
				(uint8_t)(~(1 << (y%8)));
		}
	}
};

////////////////////////////////////////////////////////////
// declaration of CPrinterObject

class CPrinterObject {
// enum
public:
	// object kind value
	enum {
		POBJ_TEXT  = 1,
		POBJ_IMAGE = 2
	};

// attribute
protected:
	// object kind
	int m_nObjectType;
	// x-position
	int m_x;
	// y-position
	int m_y;
	// width
	int m_nWidth;
	// height
	int m_nHeight;

public:
	// get object type
	int GetObjectType() const {
		return m_nObjectType;
	}
	// get x-position
	int GetX() const {
		return m_x;
	}
	// set x-position
	void SetX(int x) {
		m_x = x;
	}
	// get y-position
	int GetY() const {
		return m_y;
	}
	// set y-position
	void SetY(int y) {
		m_y = y;
	}
	// get width
	int GetWidth() const {
		return m_nWidth;
	}
	// set width
	void SetWidth(int nWidthNew) {
		m_nWidth = nWidthNew;
	}
	// get height
	int GetHeight() const {
		return m_nHeight;
	}
	// set height
	void SetHeight(int nHeightNew) {
		m_nHeight = nHeightNew;
	}

// create & destroy
public:
	// standard constructor
	CPrinterObject(
		int nObjectType,
		int x, int y, int nWidth, int nHeight);
	// copy constructor
	CPrinterObject(const CPrinterObject& objOrg);
	// destructor
	virtual ~CPrinterObject();

// operation
public:
	// clone object
	virtual CPrinterObject* Clone() const = 0;
	// is appendable object
	virtual bool IsAppendable(const CPrinterObject* pobjAppend) const;
	// append
	virtual bool Append(const CPrinterObject* pobjAppend);
};

////////////////////////////////////////////////////////////
// declaration of CPrinterTextObject

class CPrinterTextObject :
	public CPrinterObject
{
// enum
public:
	// font type
	enum {
		FONT_MINCHO  = 0x00000001,
		FONT_GOTHIC  = 0x00000002,
		FONT_COURIER = 0x00000003,
		FONT_KIND    = 0x000000FF,
		FONT_VERT    = 0x00000100,
		FONT_STRONG  = 0x00000200,
		FONT_ITALIC  = 0x00000400
	};
	// pitch type
	enum {
		PITCH_FIXED    = 1,
		PITCH_VARIABLE = 2
	};
	// character type
	enum {
		CHAR_NULL     = 0,
		CHAR_ANK      = 1,
		CHAR_ASCII    = 2,
		CHAR_KATAKANA = 3,
		CHAR_HIRAGANA = 4,
		CHAR_CG       = 5,
		CHAR_KANJI    = 6,
		CHAR_GAIJI    = 7
	};
	// line type
	enum {
		LINE_NONE  = 0x00000000,
		LINE_WIDTH = 0x000000FF,
		LINE_UPPER = 0x00000100,
		LINE_UNDER = 0x00000200,
		LINE_KIND  = 0x0000FF00
	};

// attribute
protected:
	// font type
	int m_nFontType;
	// pitch type
	int m_nPitchType;
	// text
	std::vector<uint16_t> m_vectText;
	// character type
	std::vector<int> m_vectCharType;
	// character width
	std::vector<int> m_vectCharWidth;
	// character height
	int m_nCharHeight;
	// left gap
	std::vector<int> m_vectLeftGap;
	// right gap
	std::vector<int> m_vectRightGap;
	// line type
	int m_nLineType;
	// gaiji list
	std::vector<CPrinterGaiji> m_vectGaijiList;

public:
	// get font type
	int GetFontType() const {
		return m_nFontType;
	}
	// get pitch type
	int GetPitchType() const {
		return m_nPitchType;
	}
	// get text length
	int GetTextLength() const {
		return (int)m_vectText.size();
	}
	// get text string
	const std::vector<uint16_t>& GetText() const {
		return m_vectText;
	}
	// get text
	uint16_t GetText(int nIndex) const {
		return m_vectText[nIndex];
	}
	// get character type
	int GetCharType(int nIndex) const {
		return m_vectCharType[nIndex];
	}
	// get character width
	int GetCharWidth(int nIndex) const {
		return m_vectCharWidth[nIndex];
	}
	// get character height
	int GetCharHeight() const {
		return m_nCharHeight;
	}
	// get left gap
	int GetLeftGap(int nIndex) const {
		return m_vectLeftGap[nIndex];
	}
	// get right gap
	int GetRightGap(int nIndex) const {
		return m_vectRightGap[nIndex];
	}
	// get line type
	int GetLineType() const {
		return m_nLineType;
	}
	// get gaiji count
	int GetGaijiCount() const {
		return (int)m_vectGaijiList.size();
	}
	// get gaiji
	const CPrinterGaiji* GetGaiji(int nIndex) const {
		return &m_vectGaijiList[nIndex];
	}

// create & destroy
public:
	// standard constructor
	CPrinterTextObject(
		int x, int y,
		int nFontType, int nPitchType,
		uint16_t wText,
		int nCharType,
		int nCharWidth, int nCharHeight,
		int nLeftGap, int nRightGap,
		int nLineType,
		const CPrinterGaiji* pGaiji);
	// copy constructor
	CPrinterTextObject(const CPrinterTextObject& objOrg);
	// destructor
	virtual ~CPrinterTextObject();

// operation
public:
	// clone object
	virtual CPrinterObject* Clone() const;
	// is appendable object
	virtual bool IsAppendable(const CPrinterObject* pobjAppend) const;
	// append
	virtual bool Append(const CPrinterObject* pobjAppend);
};

////////////////////////////////////////////////////////////
// declaration of CPrinterImageObject

class CPrinterImageObject :
	public CPrinterObject,
	virtual public FPrinterBitmap
{
// attribute
protected:
	// horizontal DPI
	int m_nHorzDPI;
	// vertical DPI
	int m_nVertDPI;
	// x dot count
	int m_cxDot;
	// y dot count
	int m_cyDot;
	// vert byte count for image
	int m_nVBytes;
	// image data
	std::vector<uint8_t> m_vectImageData;

	// get vert byte count for image
	int GetVBytes() const {
		return m_nVBytes;
	}

public:
	// get horizontal DPI
	int GetHorzDPI() const {
		return m_nHorzDPI;
	}
	// get vertical DPI
	int GetVertDPI() const {
		return m_nVertDPI;
	}
	// get image data
	const std::vector<uint8_t>& GetImageData() const {
		return m_vectImageData;
	}
	std::vector<uint8_t>& GetImageData() {
		return m_vectImageData;
	}

// create & destroy
public:
	// standard constructor
	CPrinterImageObject(
		int x, int y,
		int nHorzDPI, int nVertDPI,
		int nBaseDPI,
		int cxDot, int cyDot);
	// copy constructor
	CPrinterImageObject(const CPrinterImageObject& objOrg);
	// destructor
	virtual ~CPrinterImageObject();

// operation
public:
	// clone object
	virtual CPrinterObject* Clone() const;
	// is appendable object
	virtual bool IsAppendable(const CPrinterObject* pobjAppend) const;
	// append
	virtual bool Append(const CPrinterObject* pobjAppend);

// interface(FPrinterBitmap)
public:
	// get x dot count
	virtual int GetDotCX() const {
		return m_cxDot;
	}
	// get y dot count
	virtual int GetDotCY() const {
		return m_cyDot;
	}
	// get pixel value
	virtual uint32_t GetPixel(int x, int y) const {
		return (((m_vectImageData[x*m_nVBytes+y/8] >> (y%8)) & 1) != 0)?
			0: 7;
	}
	// set pixel value
	virtual void SetPixel(int x, int y, uint32_t dwPixel) {
		if (dwPixel != 0) {
			m_vectImageData[x*m_nVBytes+y/8] |= (uint8_t)(1 << (y%8));
		} else {
			m_vectImageData[x*m_nVBytes+y/8] &= (uint8_t)(~(1 << (y%8)));
		}
	}
};

////////////////////////////////////////////////////////////
// declaration of CPrinterPage

class CPrinterPage :
	public std::list<CPrinterObject*>
{
// create & destroy
public:
	// default constructor
	CPrinterPage();
	// destructor
	virtual ~CPrinterPage();

// operation
public:
	// add printer object
	virtual bool AddPrinterObject(CPrinterObject* pPrtObj);
};

////////////////////////////////////////////////////////////
// declaration of CParallelPrinter

class CParallelPrinter :
	public CParallelDevice
{
// enum
protected:
	// processing constant value
	enum {
		DATAQUEUE_MAX = 1024,
		PROCESS_IDLE  = 128
	};

public:
	// paper type
	enum {
		PAPER_NONE    = 0,
		PAPER_C10     = 1,
		PAPER_C15     = 2,
		PAPER_A5V     = 3,
		PAPER_A5H     = 4,
		PAPER_A4V     = 5,
		PAPER_A4H     = 6,
		PAPER_A3V     = 7,
		PAPER_A3H     = 8,
		PAPER_B5V     = 9,
		PAPER_B5H     = 10,
		PAPER_B4V     = 11,
		PAPER_B4H     = 12,
		PAPER_HAGAKIV = 13,
		PAPER_HAGAKIH = 14
	};

// typedef
protected:
	// page container type
	typedef std::vector<CPrinterPage*> CPageContainer;

public:
	// STL
	typedef CPageContainer::const_iterator const_iterator;
	typedef CPageContainer::iterator iterator;
	typedef CPageContainer::value_type value_type;
	typedef CPageContainer::size_type size_type;

// attribute
protected:
	// pause mode
	bool m_bPause;
	// pending mode
	bool m_bPending;
	// inactive strobe
	bool m_bNStrobe;
	// inputed data
	uint8_t m_btData;
	// data queue
	std::queue<uint8_t> m_queueData;
	// current page
	int m_nCurrentPage;
	// page container
	CPageContainer m_conPages;
	// movable area width
	int m_nMovableAreaWidth;
	// movable area height
	int m_nMovableAreaHeight;
	// paper left position
	int m_nPaperLeft;
	// paper top position
	int m_nPaperTop;
	// paper width
	int m_nPaperWidth;
	// paper height
	int m_nPaperHeight;
	// x-position of printer head
	int m_nHeadX;
	// y-position of printer head
	int m_nHeadY;
	// printer head height
	int m_nHeadHeight;
	// exist sheet feeder
	bool m_bExistSheetFeeder;
	// exist paper
	bool m_bExistPaper;
	// dirty
	bool m_bDirty;

public:
	// get current page
	int GetCurrentPage() const {
		return m_nCurrentPage;
	}
	// get movable area
	void GetMovableArea(
		int& nMovableAreaWidth, int& nMovableAreaHeight) const
	{
		nMovableAreaWidth = m_nMovableAreaWidth;
		nMovableAreaHeight = m_nMovableAreaHeight;
	}
	// set movable area
	void SetMovableArea(
		int nMovableAreaWidth, int nMovableAreaHeight)
	{
		m_nMovableAreaWidth = nMovableAreaWidth;
		m_nMovableAreaHeight = nMovableAreaHeight;
	}
	// get movable area width
	int GetMovableAreaWidth() const {
		return m_nMovableAreaWidth;
	}
	// set movable area width
	void SetMovableAreaWidth(int nMovableAreaWidth) {
		m_nMovableAreaWidth = nMovableAreaWidth;
	}
	// get movable area height
	int GetMovableAreaHeight() const {
		return m_nMovableAreaHeight;
	}
	// set movable area height
	void SetMovableAreaHeight(int nMovableAreaHeight) {
		m_nMovableAreaHeight = nMovableAreaHeight;
	}
	// get paper left position
	int GetPaperLeft() const {
		return m_nPaperLeft;
	}
	// set paper left position
	void SetPaperLeft(int nPaperLeft) {
		m_nPaperLeft = nPaperLeft;
	}
	// get paper top position
	int GetPaperTop() const {
		return m_nPaperTop;
	}
	// set paper top position
	void SetPaperTop(int nPaperTop) {
		m_nPaperTop = nPaperTop;
	}
	// get paper width
	int GetPaperWidth() const {
		return m_nPaperWidth;
	}
	// set paper width
	void SetPaperWidth(int nPaperWidth) {
		m_nPaperWidth = nPaperWidth;
	}
	// get paper height
	int GetPaperHeight() const {
		return m_nPaperHeight;
	}
	// set paper height
	void SetPaperHeight(int nPaperHeight) {
		m_nPaperHeight = nPaperHeight;
	}
	// get paper area
	void GetPaperArea(
		int& nPaperLeft, int& nPaperTop,
		int& nPaperWidth, int& nPaperHeight) const
	{
		nPaperLeft = m_nPaperLeft;
		nPaperTop = m_nPaperTop;
		nPaperWidth = m_nPaperWidth;
		nPaperHeight = m_nPaperHeight;
	}
	// set paper area
	void SetPaperArea(
		int nPaperLeft, int nPaperTop,
		int nPaperWidth, int nPaperHeight)
	{
		m_nPaperLeft = nPaperLeft;
		m_nPaperTop = nPaperTop;
		m_nPaperWidth = nPaperWidth;
		m_nPaperHeight = nPaperHeight;
	}
	// get x-position of printer head
	int GetHeadX() const {
		return m_nHeadX;
	}
	// set x-position of printer head
	void SetHeadX(int nHeadXNew) {
		m_nHeadX = nHeadXNew;
	}
	// get y-position of printer head
	int GetHeadY() const {
		return m_nHeadY;
	}
	// set y-position of printer head
	void SetHeadY(int nHeadYNew) {
		m_nHeadY = nHeadYNew;
	}
	// get printer head height
	int GetHeadHeight() const {
		return m_nHeadHeight;
	}
	// get printer head height
	void SetHeadHeight(int nHeadHeightNew) {
		m_nHeadHeight = nHeadHeightNew;
	}
	// is exist sheet feeder
	bool IsExistSheetFeeder() const {
		return m_bExistSheetFeeder;
	}
	// set exist sheet feeder
	void SetExistSheetFeeder(bool bExistSheetFeederNew) {
		m_bExistSheetFeeder = bExistSheetFeederNew;
	}
	// is exist paper
	bool IsExistPaper() const {
		return m_bExistPaper;
	}
	// set exist paper
	void SetExistPaper(bool bExistPaperNew) {
		m_bExistPaper = bExistPaperNew;
	}
	// is dirty
	bool IsDirty() const {
		return m_bDirty;
	}
	// set dirty
	void SetDirty(bool bDirtyNew) {
		m_bDirty = bDirtyNew;
	}
	// get DPI
	virtual int GetDPI() const = 0;

// create & destroy
public:
	// default constructor
	CParallelPrinter();
	// destructor
	virtual ~CParallelPrinter();

// initialize
public:
	// initialize at first
	virtual void Initialize();
	// reset
	virtual void Reset();

// communication
public:
	// is busy
	virtual bool IsBusy();
	// set strobe(negative logic)
	virtual void SetStrobe(bool bNStrobe);
	// output data
	virtual void SetData(uint8_t btData);

// STL
public:
	const_iterator begin() const {
		return m_conPages.begin();
	}
	iterator begin() {
		return m_conPages.begin();
	}
	const_iterator end() const {
		return m_conPages.end();
	}
	iterator end() {
		return m_conPages.end();
	}
	size_type size() const {
		return m_conPages.size();
	}

// implementation
protected:
	// process data
	virtual void ProcessData(uint8_t btData) = 0;

public:
	// is pause mode
	virtual bool IsPause();
	// set pause mode
	virtual void SetPause(bool bPause);
	// is pending mode
	virtual bool IsPending();
	// set pending mode
	virtual void SetPending(bool bPending);
	// flush data
	virtual void Flush();
	// idle process
	virtual void OnIdle(int nMilliSecond);
	// carriage-return
	virtual bool CarriageReturn() = 0;
	// line-feed
	virtual bool LineFeed() = 0;
	// page-feed
	virtual bool PageFeed() = 0;
	// head move
	virtual bool HeadMove(int nMove) = 0;
	// horizontal-tab
	virtual bool HorzTab() = 0;
	// vertical-tab
	virtual bool VertTab() = 0;
	// get selectable paper count
	virtual int GetSelectablePaperCount() const = 0;
	// get selectable paper
	virtual int GetSelectablePaper(int nIndex) const = 0;
	// get selected paper
	virtual int GetSelectedPaper() const = 0;
	// select paper
	virtual bool SelectPaper(int nPaper) = 0;
	// is able paper centering
	virtual bool IsAblePaperCentering() const = 0;
	// is paper centering
	virtual bool IsPaperCentering() const = 0;
	// set paper centering
	virtual bool SetPaperCentering(bool bPaperCentering) = 0;
	// paper feed from external operation
	virtual bool PaperFeed(bool bPageFeed, int nFeed) = 0;

// operation
public:
	// add printer object
	virtual bool AddPrinterObject(CPrinterObject* pPrtObj);
	// set current page
	virtual void SetCurrentPage(int nCurrentPageNew);
	// delete one page
	virtual bool DeletePage(int nPage);
	// delete all pages
	virtual bool DeleteAllPages();
};

#endif // ParallelPrinter_DEFINED
