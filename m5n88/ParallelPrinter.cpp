////////////////////////////////////////////////////////////
// Printer Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "ParallelPrinter.h"

////////////////////////////////////////////////////////////
// implementation of CPrinterGaiji

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPrinterGaiji::CPrinterGaiji() :
	m_wCode(0),
	m_pData(NULL)
{
}

// standard constructor

CPrinterGaiji::CPrinterGaiji(uint16_t wCode, int cxDot, int cyDot) :
	m_wCode(wCode),
	m_pData(NULL)
{
	m_pData = new SPrinterGaijiData;
	m_pData->nReference = 1;
	m_pData->cxDot = cxDot;
	m_pData->cyDot = cyDot;
	m_pData->nVBytes = (cyDot+7)/8;
	m_pData->vectImageData.resize(m_pData->nVBytes*cxDot, 0);
}

// copy constructor

CPrinterGaiji::CPrinterGaiji(const CPrinterGaiji& gaijiOther) :
	m_wCode(gaijiOther.m_wCode),
	m_pData(gaijiOther.m_pData)
{
	if (m_pData != NULL) {
		m_pData->nReference++;
	}
}

// destructor

CPrinterGaiji::~CPrinterGaiji() {
	if ((m_pData != NULL) &&
		(--m_pData->nReference <= 0))
	{
		delete m_pData;
	}
}

////////////////////////////////////////////////////////////
// operator

// let

CPrinterGaiji& CPrinterGaiji::operator=(const CPrinterGaiji& gaijiOther) {
	m_wCode = gaijiOther.m_wCode;
	SPrinterGaijiData* pDataOld = m_pData;
	m_pData = gaijiOther.m_pData;
	if (m_pData != NULL) {
		m_pData->nReference++;
	}
	if (pDataOld != NULL) {
		if (--pDataOld->nReference <= 0) {
			delete pDataOld;
		}
	}
	return *this;
}

// compare(less)

bool CPrinterGaiji::operator<(const CPrinterGaiji& gaijiOther) const {
	return m_wCode < gaijiOther.m_wCode;
}

////////////////////////////////////////////////////////////
// implementation of CPrinterObject

////////////////////////////////////////////////////////////
// create & destroy

// standard constructor

CPrinterObject::CPrinterObject(
		int nObjectType,
		int x, int y, int nWidth, int nHeight) :
	m_nObjectType(nObjectType),
	m_x(x), m_y(y),
	m_nWidth(nWidth), m_nHeight(nHeight)
{
}

// copy constructor

CPrinterObject::CPrinterObject(
		const CPrinterObject& objOrg) :
	m_nObjectType(objOrg.m_nObjectType),
	m_x(objOrg.m_x), m_y(objOrg.m_y),
	m_nWidth(objOrg.m_nWidth), m_nHeight(objOrg.m_nHeight)
{
}

// destructor

CPrinterObject::~CPrinterObject() {
}

////////////////////////////////////////////////////////////
// operation

// is appendable object

bool CPrinterObject::IsAppendable(
	const CPrinterObject* /*pobjAppend*/) const
{
	return false;
}

// append

bool CPrinterObject::Append(
	const CPrinterObject* /*pobjAppend*/)
{
	return false;
}

////////////////////////////////////////////////////////////
// implementation of CPrinterTextObject

////////////////////////////////////////////////////////////
// create & destroy

// standard constructor

CPrinterTextObject::CPrinterTextObject(
		int x, int y,
		int nFontType, int nPitchType,
		uint16_t wText,
		int nCharType,
		int nCharWidth, int nCharHeight,
		int nLeftGap, int nRightGap,
		int nLineType,
		const CPrinterGaiji* pGaiji) :
	CPrinterObject(POBJ_TEXT, x, y, 0, 0),
	m_nFontType(nFontType),
	m_nPitchType(nPitchType),
	m_nCharHeight(nCharHeight),
	m_nLineType(nLineType)
{
	m_vectText.push_back(wText);
	m_vectCharType.push_back(nCharType);
	m_vectCharWidth.push_back(nCharWidth);
	m_vectLeftGap.push_back(nLeftGap);
	m_vectRightGap.push_back(nRightGap);
	SetWidth(nLeftGap+nCharWidth+nRightGap);
	SetHeight(nCharHeight);
	if (pGaiji != NULL) {
		m_vectGaijiList.push_back(*pGaiji);
	}
}

// copy constructor

CPrinterTextObject::CPrinterTextObject(
		const CPrinterTextObject& objOrg) :
	CPrinterObject(objOrg),
	m_nFontType(objOrg.m_nFontType),
	m_nPitchType(objOrg.m_nPitchType),
	m_vectText(objOrg.m_vectText),
	m_vectCharType(objOrg.m_vectCharType),
	m_vectCharWidth(objOrg.m_vectCharWidth),
	m_nCharHeight(objOrg.m_nCharHeight),
	m_vectLeftGap(objOrg.m_vectLeftGap),
	m_vectRightGap(objOrg.m_vectRightGap),
	m_nLineType(objOrg.m_nLineType),
	m_vectGaijiList(objOrg.m_vectGaijiList)
{
}

// destructor

CPrinterTextObject::~CPrinterTextObject() {
}

////////////////////////////////////////////////////////////
// operation

// clone object

CPrinterObject* CPrinterTextObject::Clone() const {
	return new CPrinterTextObject(*this);
}

// is appendable object

bool CPrinterTextObject::IsAppendable(
	const CPrinterObject* pobjAppend) const
{
	if (pobjAppend->GetObjectType() != POBJ_TEXT) {
		return false;
	}
	const CPrinterTextObject* pobjAppend2 =
		(const CPrinterTextObject*)pobjAppend;
	return (pobjAppend2->GetFontType() == GetFontType()) &&
		(pobjAppend2->GetPitchType() == GetPitchType()) &&
		(pobjAppend2->GetCharHeight() == GetCharHeight()) &&
		(pobjAppend2->GetLineType() == GetLineType()) &&
		(pobjAppend2->GetX() == GetX()+GetWidth()) &&
		(pobjAppend2->GetY() == GetY());
}

// append

bool CPrinterTextObject::Append(
	const CPrinterObject* pobjAppend)
{
	const CPrinterTextObject* pobjAppend2 =
		(const CPrinterTextObject*)pobjAppend;
	int nLength1 = GetTextLength(),
		nLength2 = pobjAppend2->GetTextLength(),
		nLengthNew = nLength1+nLength2;
	m_vectText.reserve(nLengthNew);
	m_vectCharType.reserve(nLengthNew);
	m_vectCharWidth.reserve(nLengthNew);
	m_vectLeftGap.reserve(nLengthNew);
	m_vectRightGap.reserve(nLengthNew);
	for (int nIndex = 0; nIndex < nLength2; nIndex++) {
		m_vectText.push_back(pobjAppend2->GetText(nIndex));
		m_vectCharType.push_back(pobjAppend2->GetCharType(nIndex));
		m_vectCharWidth.push_back(pobjAppend2->GetCharWidth(nIndex));
		m_vectLeftGap.push_back(pobjAppend2->GetLeftGap(nIndex));
		m_vectRightGap.push_back(pobjAppend2->GetRightGap(nIndex));
	}
	m_vectGaijiList.reserve(
		GetGaijiCount()+
		pobjAppend2->GetGaijiCount());
	for (int nGaiji = 0; nGaiji < pobjAppend2->GetGaijiCount(); nGaiji++) {
		m_vectGaijiList.push_back(*pobjAppend2->GetGaiji(nGaiji));
	}
	SetWidth(GetWidth()+pobjAppend2->GetWidth());
	return true;
}

////////////////////////////////////////////////////////////
// implementation of CPrinterImageObject

////////////////////////////////////////////////////////////
// create & destroy

// standard constructor

CPrinterImageObject::CPrinterImageObject(
		int x, int y,
		int nHorzDPI, int nVertDPI,
		int nBaseDPI,
		int cxDot, int cyDot) :
	CPrinterObject(POBJ_IMAGE, x, y, 0, 0),
	m_nHorzDPI(nHorzDPI), m_nVertDPI(nVertDPI),
	m_cxDot(cxDot), m_cyDot(cyDot),
	m_nVBytes((m_cyDot+7)/8)
{
	SetWidth((GetDotCX()*GetHorzDPI())/nBaseDPI);
	SetHeight((GetDotCY()*GetVertDPI())/nBaseDPI);
	GetImageData().resize(GetVBytes()*GetDotCX(), 0);
}

// copy constructor

CPrinterImageObject::CPrinterImageObject(
		const CPrinterImageObject& objOrg) :
	CPrinterObject(objOrg),
	m_nHorzDPI(objOrg.m_nHorzDPI),
	m_nVertDPI(objOrg.m_nVertDPI),
	m_cxDot(objOrg.m_cxDot),
	m_cyDot(objOrg.m_cyDot),
	m_nVBytes(objOrg.m_nVBytes),
	m_vectImageData(objOrg.m_vectImageData)
{
}

// destructor

CPrinterImageObject::~CPrinterImageObject() {
}

////////////////////////////////////////////////////////////
// operation

// clone object

CPrinterObject* CPrinterImageObject::Clone() const {
	return new CPrinterImageObject(*this);
}

// is appendable object

bool CPrinterImageObject::IsAppendable(
	const CPrinterObject* pobjAppend) const
{
	if (pobjAppend->GetObjectType() != POBJ_IMAGE) {
		return false;
	}
	const CPrinterImageObject* pobjAppend2 =
		(const CPrinterImageObject*)pobjAppend;
	bool bAppendable = false;
	if ((pobjAppend2->GetHorzDPI() == GetHorzDPI()) &&
		(pobjAppend2->GetVertDPI() == GetVertDPI()))
	{
		if (((pobjAppend2->GetY() == GetY()) &&
				(pobjAppend2->GetX() == GetX()+GetWidth()) &&
				(pobjAppend2->GetDotCY() == GetDotCY())) ||
			((pobjAppend2->GetX() == GetX()) &&
				(pobjAppend2->GetY() == GetY()+GetHeight()) &&
				(pobjAppend2->GetDotCX() == GetDotCX()) &&
				(GetDotCY()%8 == 0)))
		{
			bAppendable = true;
		}
	}
	return bAppendable;
}

// append

bool CPrinterImageObject::Append(
	const CPrinterObject* pobjAppend)
{
	const CPrinterImageObject* pobjAppend2 =
		(const CPrinterImageObject*)pobjAppend;
	if (pobjAppend2->GetY() == GetY()) {
		// horizontal connect
		int cxDotNew = GetDotCX()+pobjAppend2->GetDotCX();
		GetImageData().resize(GetVBytes()*cxDotNew);
		std::copy(
			pobjAppend2->GetImageData().begin(),
			pobjAppend2->GetImageData().end(),
			GetImageData().begin()+GetVBytes()*GetDotCX());
		SetWidth(GetWidth()+pobjAppend2->GetWidth());
		m_cxDot = cxDotNew;
	} else {
		// vertical connect
		int cyDotNew = GetDotCY()+pobjAppend2->GetDotCY(),
			nVBytesNew = (cyDotNew+7)/8;
		GetImageData().resize(nVBytesNew*GetDotCX());
		std::vector<uint8_t>::iterator itNew = GetImageData().end();
		std::vector<uint8_t>::const_iterator
			itOld = GetImageData().begin()+GetVBytes()*GetDotCX(),
			itAppend = pobjAppend2->GetImageData().end();
		do {
			int i;
			for (i = 0; i < pobjAppend2->GetVBytes(); i++) {
				*(--itNew) = *(--itAppend);
			}
			for (i = 0; i < GetVBytes(); i++) {
				*(--itNew) = *(--itOld);
			}
		} while (itNew != GetImageData().begin());
		SetHeight(GetHeight()+pobjAppend2->GetHeight());
		m_cyDot = cyDotNew;
		m_nVBytes = nVBytesNew;
	}
	return true;
}

////////////////////////////////////////////////////////////
// implementation of CPrinterPage

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPrinterPage::CPrinterPage() :
	std::list<CPrinterObject*>()
{
}

// destructor

CPrinterPage::~CPrinterPage() {
	for (iterator itObject = begin(); itObject != end(); itObject++) {
		delete *itObject;
	}
}

////////////////////////////////////////////////////////////
// operation

// add printer object

bool CPrinterPage::AddPrinterObject(CPrinterObject* pPrtObj) {
	if ((size() > 0) &&
		back()->IsAppendable(pPrtObj))
	{
		back()->Append(pPrtObj);
		delete pPrtObj;
	} else {
		push_back(pPrtObj);
	}
	return true;
}

////////////////////////////////////////////////////////////
// implementation of CParallelPrinter

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CParallelPrinter::CParallelPrinter() :
	m_bPause(false),
	m_bPending(false),
	m_bNStrobe(true),
	m_btData(0),
	m_nCurrentPage(0),
	m_nMovableAreaWidth(0), m_nMovableAreaHeight(0),
	m_nPaperLeft(0), m_nPaperTop(0), m_nPaperWidth(0), m_nPaperHeight(0),
	m_nHeadX(0), m_nHeadY(0),
	m_nHeadHeight(0),
	m_bExistSheetFeeder(false),
	m_bExistPaper(true),
	m_bDirty(true)
{
}

// destructor

CParallelPrinter::~CParallelPrinter() {
	for (iterator itPage = begin(); itPage != end(); itPage++) {
		delete *itPage;
	}
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CParallelPrinter::Initialize() {
	m_bPause = false;
	m_bPending = false;
	m_bNStrobe = true;
	m_btData = 0;
	while (m_queueData.size() > 0) {
		m_queueData.pop();
	}
	m_nCurrentPage = 0;
	for (iterator itPage = begin(); itPage != end(); itPage++) {
		delete *itPage;
	}
	m_conPages.clear();
	m_nMovableAreaWidth = m_nMovableAreaHeight = 0;
	m_nPaperLeft = m_nPaperTop = m_nPaperWidth = m_nPaperHeight = 0;
	m_nHeadX = m_nHeadY = 0;
	m_nHeadHeight = 0;
	m_bExistSheetFeeder = false;
	m_bExistPaper = true;
	m_bDirty = true;
}

// reset

void CParallelPrinter::Reset() {
	while (m_queueData.size() > 0) {
		m_queueData.pop();
	}
}

////////////////////////////////////////////////////////////
// communication

// is busy

bool CParallelPrinter::IsBusy() {
	return m_bPause ||
		!m_bNStrobe ||
		(m_queueData.size() >= DATAQUEUE_MAX);
}

// set strobe(negative logic)

void CParallelPrinter::SetStrobe(bool bNStrobe) {
	if (!m_bPause) {
		if (bNStrobe && !m_bNStrobe) {
			if (m_queueData.size() < DATAQUEUE_MAX) {
				m_queueData.push(m_btData);
			}
		}
		m_bNStrobe = bNStrobe;
	}
}

// output data

void CParallelPrinter::SetData(uint8_t btData) {
	if (!m_bPause) {
		m_btData = btData;
	}
}

////////////////////////////////////////////////////////////
// implementation

// is pause mode

bool CParallelPrinter::IsPause() {
	return m_bPause;
}

// set pause mode

void CParallelPrinter::SetPause(bool bPause) {
	m_bPause = bPause;
}

// is pending mode

bool CParallelPrinter::IsPending() {
	return m_bPending;
}

// set pending mode

void CParallelPrinter::SetPending(bool bPending) {
	m_bPending = bPending;
}

// flush data

void CParallelPrinter::Flush() {
	while (m_queueData.size() > 0) {
		uint8_t btData = m_queueData.front();
		m_queueData.pop();
		ProcessData(btData);
	}
}

// idle process

void CParallelPrinter::OnIdle(int nMilliSecond) {
	if (!m_bPause && !m_bPending) {
		int nProcessDataCount = (int)m_queueData.size();
		if (nProcessDataCount > PROCESS_IDLE*nMilliSecond) {
			nProcessDataCount = PROCESS_IDLE*nMilliSecond;
		}
		for (; nProcessDataCount > 0; nProcessDataCount--) {
			uint8_t btData = m_queueData.front();
			m_queueData.pop();
			ProcessData(btData);
		}
	}
}

////////////////////////////////////////////////////////////
// operation

// add printer object

bool CParallelPrinter::AddPrinterObject(CPrinterObject* pPrtObj) {
	SetDirty(true);
	CPrinterObject* pPrtObjClone = NULL;
	int nMaxPage = m_nCurrentPage;
	if (!IsExistSheetFeeder() &&
		(pPrtObj->GetY()+pPrtObj->GetHeight() > GetPaperHeight()))
	{
		// page across object in continuous paper
		pPrtObjClone = pPrtObj->Clone();
		pPrtObjClone->SetY(
			pPrtObjClone->GetY()-GetPaperHeight());
		nMaxPage++;
	}
	while (nMaxPage >= (int)size()) {
		m_conPages.push_back(new CPrinterPage);
	}
	iterator itPage = begin();
	std::advance(itPage, m_nCurrentPage);
	bool bResult = (*itPage)->AddPrinterObject(pPrtObj);
	if (pPrtObjClone != NULL) {
		itPage++;
		(*itPage)->AddPrinterObject(pPrtObjClone);
	}
	return bResult;
}

// set current page

void CParallelPrinter::SetCurrentPage(int nCurrentPageNew) {
	SetDirty(true);
	m_nCurrentPage = nCurrentPageNew;
}

// delete one page

bool CParallelPrinter::DeletePage(int nPage) {
	if (nPage < 0) {
		return false;
	}
	if (nPage >= (int)size()) {
		return true;
	}
	SetDirty(true);
	iterator itPage = begin();
	std::advance(itPage, nPage);
	delete *itPage;
	m_conPages.erase(itPage);
	if (GetCurrentPage() > nPage) {
		SetCurrentPage(GetCurrentPage()-1);
	}
	return true;
}

// delete all pages

bool CParallelPrinter::DeleteAllPages() {
	while (size() > 0) {
		if (!DeletePage((int)size()-1)) {
			return false;
		}
	}
	if (!DeletePage(GetCurrentPage())) {
		return false;
	}
	SetCurrentPage(0);
	return true;
}
