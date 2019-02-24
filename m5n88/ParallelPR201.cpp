////////////////////////////////////////////////////////////
// PC-PC201 Emulator
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "ParallelPR201.h"

////////////////////////////////////////////////////////////
// implementation of CPR201CommandState

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201CommandState::CPR201CommandState() :
	m_pPrinter(NULL),
	m_pPreCommandState(NULL)
{
}

// destructor

CPR201CommandState::~CPR201CommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201CommandState::Initialize() {
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201CommandState::ProcessData(uint8_t btData) {
	switch (btData) {
	case 0x0D: // CR : carriage-return
		GetPrinter()->CarriageReturn();
		break;
	case 0x0A: // LF : line-feed
		GetPrinter()->LineFeed();
		break;
	case 0x09: // HT : horizontal-tab
		GetPrinter()->HorzTab();
		break;
	case 0x0B: // VT : vertical-tab
		GetPrinter()->VertTab();
		break;
	case 0x0C: // FF : form-feed
		GetPrinter()->PageFeed();
		break;
	case 0x0E: // SO : expand mode start
		GetPrinter()->SetHorzZoom(2);
		GetPrinter()->SetVertZoom(1);
		break;
	case 0x0F: // SI : expand mode finish
		GetPrinter()->SetHorzZoom(1);
		GetPrinter()->SetVertZoom(1);
		break;
	case 0x18: // CAN : cancel
	case 0x11: // DC1 : select
	case 0x13: // DC3 : deselect
	case 0x07: // BEL : buzzer
	case 0x04: // EOT : finish of gaiji loading
		// ignore
		break;
	case 0x1D: // GS : set VFU
		{ // dummy block
			CPR201VFUCommandState* pcstateVFU =
				CPR201VFUCommandState::GetInstance();
			pcstateVFU->SetPreCommandState(this);
			GetPrinter()->ChangeComandState(pcstateVFU);
		}
		break;
	case 0x1B: // ESC
		{ // dummy block
			CPR201ESCCommandState* pcstateESC =
				CPR201ESCCommandState::GetInstance();
			pcstateESC->SetPreCommandState(this);
			GetPrinter()->ChangeComandState(pcstateESC);
		}
		break;
	case 0x1C: // FS
		{ // dummy block
			CPR201FSCommandState* pcstateFS =
				CPR201FSCommandState::GetInstance();
			pcstateFS->SetPreCommandState(this);
			GetPrinter()->ChangeComandState(pcstateFS);
		}
		break;
	case 0x1F: // US
		{ // dummy block
			CPR201USCommandState* pcstateUS =
				CPR201USCommandState::GetInstance();
			pcstateUS->SetPreCommandState(this);
			GetPrinter()->ChangeComandState(pcstateUS);
		}
		break;
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201ANKCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201ANKCommandState CPR201ANKCommandState::m_cstateANK;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201ANKCommandState::CPR201ANKCommandState() :
	CPR201CommandState()
{
}

// destructor

CPR201ANKCommandState::~CPR201ANKCommandState() {
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201ANKCommandState::ProcessData(uint8_t btData) {
	if (btData >= 0x20) {
		int nCharRepeatCount = GetPrinter()->GetCharRepeatCount();
		GetPrinter()->SetCharRepeatCount(1);
		for (int i = 0; i < nCharRepeatCount; i++) {
			GetPrinter()->OutputTextSB(btData);
		}
	} else {
		CPR201CommandState::ProcessData(btData);
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201KanjiCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201KanjiCommandState CPR201KanjiCommandState::m_cstateKanji;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201KanjiCommandState::CPR201KanjiCommandState() :
	CPR201CommandState(),
	m_btFirst(0xFF)
{
}

////////////////////////////////////////////////////////////
// destructor

CPR201KanjiCommandState::~CPR201KanjiCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201KanjiCommandState::Initialize() {
	m_btFirst = 0xFF;
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201KanjiCommandState::ProcessData(uint8_t btData) {
	if (m_btFirst != 0xFF) {
		if (((m_btFirst != 0) && (btData >= 0x20) && (btData <= 0x7F)) ||
			((m_btFirst == 0) && (btData >= 0x20)))
		{
			uint16_t wText = (uint16_t)((m_btFirst << 8) | btData);
			int nCharRepeatCount = GetPrinter()->GetCharRepeatCount();
			GetPrinter()->SetCharRepeatCount(1);
			for (int i = 0; i < nCharRepeatCount; i++) {
				GetPrinter()->OutputTextDB(wText);
			}
		}
		m_btFirst = 0xFF;
	} else if (
		(btData == 0x00) ||
		((btData >= 0x21) && (btData <= 0x7E)))
	{
		m_btFirst = btData;
	} else {
		CPR201CommandState::ProcessData(btData);
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201ESCCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201ESCCommandState CPR201ESCCommandState::m_cstateESC;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201ESCCommandState::CPR201ESCCommandState() :
	CPR201CommandState()
{
}

// destructor

CPR201ESCCommandState::~CPR201ESCCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201ESCCommandState::Initialize() {
	m_vectParams.clear();
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201ESCCommandState::ProcessData(uint8_t btData) {
	m_vectParams.push_back(btData);
	bool bAbortCommand = false;
	uint8_t btCommandByte = m_vectParams.front();
	switch (btCommandByte) {
	case 0x4E: // ESC N : HS pica mode
	case 0x48: // ESC H : HD pica mode
	case 0x45: // ESC E : elite mode
	case 0x51: // ESC Q : condense mode
	case 0x50: // ESC P : proportional mode
		{ // dummy block
			int nMethod = CParallelPR201::METHOD_HDPICA;
			switch (btCommandByte) {
			case 0x4E: // ESC N : HS pica mode
				nMethod = CParallelPR201::METHOD_HSPICA;
				break;
			case 0x48: // ESC H : HD pica mode
				nMethod = CParallelPR201::METHOD_HDPICA;
				break;
			case 0x45: // ESC E : elite mode
				nMethod = CParallelPR201::METHOD_ELITE;
				break;
			case 0x51: // ESC Q : condense mode
				nMethod = CParallelPR201::METHOD_CONDENSE;
				break;
			case 0x50: // ESC P : proportional mode
				nMethod = CParallelPR201::METHOD_PROPORTIONAL;
				break;
			}
			GetPrinter()->SetPrintingMethod(nMethod);
			GetPrinter()->ChangeComandState(
				CPR201ANKCommandState::GetInstance());
		}
		break;
	case 0x4B: // ESC K : kanji mode(horizontal glyph)
	case 0x74: // ESC t : kanji mode(vertical glyph)
		{ // dummy block
			int nMethod = CParallelPR201::METHOD_KANJI;
			switch (btCommandByte) {
			case 0x4B: // ESC K : horizontal glyph
				nMethod = CParallelPR201::METHOD_KANJI;
				break;
			case 0x74: // ESC t : vertical glyph
				nMethod = CParallelPR201::METHOD_VKANJI;
				break;
			}
			GetPrinter()->SetPrintingMethod(nMethod);
			GetPrinter()->ChangeComandState(
				CPR201KanjiCommandState::GetInstance());
		}
		break;
	case 0x6E: // ESC n : change NHS/SHS pica mode
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x30: // ESC n0 : NHS pica
				break;
			case 0x31: // ESC n1 : SHS pica
				break;
			}
			bAbortCommand = true;
		}
		break;
	case 0x24: // ESC $ : set katakana mode
		GetPrinter()->SetHiraganaMode(false);
		bAbortCommand = true;
		break;
	case 0x26: // ESC & : set hiragana mode
		GetPrinter()->SetHiraganaMode(true);
		bAbortCommand = true;
		break;
	case 0x73: // ESC s : super/sub-script printing mode
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x30:// ESC s0 : cancel
				GetPrinter()->SetScriptMode(CParallelPR201::SCRIPT_NONE);
				break;
			case 0x31:// ESC s1 : super-script
				GetPrinter()->SetScriptMode(CParallelPR201::SCRIPT_SUPER);
				break;
			case 0x32:// ESC s2 : sub-script
				GetPrinter()->SetScriptMode(CParallelPR201::SCRIPT_SUB);
				break;
			}
			bAbortCommand = true;
		}
		break;
	case 0x2B: // ESC + : load gaiji(24x24)
	case 0x2A: // ESC * : load gaiji(16x16)
		if (m_vectParams.size() >= 3) {
			if ((m_vectParams[1] >= 0x76) &&
				(m_vectParams[1] <= 0x78) &&
				(m_vectParams[2] >= 0x20) &&
				(m_vectParams[2] <= 0x7F) &&
				((m_vectParams[1] != 0x78) ||
					(m_vectParams[2] <= 0x5F)))
			{
				CPR201GaijiCommandState* pcstateGaiji =
					CPR201GaijiCommandState::GetInstance();
				if (pcstateGaiji->SetGaijiInfo(
						(uint16_t)((m_vectParams[1] << 8) | m_vectParams[2]),
						(m_vectParams[0] == 0x2B)?
							CParallelPR201::CXKANJI:
							CParallelPR201::CXGAIJI16,
						(m_vectParams[0] == 0x2B)?
							CParallelPR201::CYNORMAL:
							CParallelPR201::CYGAIJI16,
						0,
						(m_vectParams[0] == 0x2B)?
							0:
							(CParallelPR201::CXKANJI-
								CParallelPR201::CXGAIJI16)))
				{
					pcstateGaiji->SetPreCommandState(GetPreCommandState());
					GetPrinter()->ChangeComandState(pcstateGaiji);
				} else {
					bAbortCommand = true;
				}
			} else {
				bAbortCommand = true;
			}
		}
		break;
	case 0x6C: // ESC l
		if (m_vectParams.size() >= 2) {
			switch (m_vectParams[1]) {
			case 0x2B: // ESC l+ : use download character
				GetPrinter()->SetDownloadCharUse(true);
				bAbortCommand = true;
				break;
			case 0x2D: // ESC l- : use internal character
				GetPrinter()->SetDownloadCharUse(false);
				bAbortCommand = true;
				break;
			case 0x30: // ESC l0 : remove download character
				GetPrinter()->RemoveAllSBGaiji();
				bAbortCommand = true;
				break;
			case 0x31: // ESC l1 : register download character(HD pica, katakana)
			case 0x32: // ESC l2 : register download character(HS pica, katakana)
			case 0x33: // ESC l3 : register download character(elite, katakana)
			case 0x34: // ESC l4 : register download character(condense, katakana)
			case 0x41: // ESC lA : register download character(HD pica, hiragana)
			case 0x42: // ESC lB : register download character(HS pica, hiragana)
			case 0x43: // ESC lC : register download character(elite, hiragana)
			case 0x44: // ESC lD : register download character(condense, hiragana)
				if (m_vectParams.size() >= 3) {
					if ((btData >= 0x21) && (btData <= 0x7F)) {
						uint16_t wCode = 0;
						int nWidth = 0,
							nHeight = CParallelPR201::CYNORMAL,
							nLeftGap = 0,
							nRightGap = 0;
						switch (m_vectParams[1]) {
						case 0x31: // ESC l1 : HD pica, katakana
							wCode = 0x0000;
							nWidth = CParallelPR201::CXPICA+2;
							nRightGap = -2;
							break;
						case 0x32: // ESC l2 : HS pica, katakana
							wCode = 0x0100;
							nWidth = CParallelPR201::CXPICA+2;
							nRightGap = -2;
							break;
						case 0x33: // ESC l3 : elite, katakana
							wCode = 0x0200;
							nWidth = CParallelPR201::CXELITE;
							break;
						case 0x34: // ESC l4 : condense, katakana
							wCode = 0x0300;
							nWidth = CParallelPR201::CXCONDENSE;
							break;
						case 0x41: // ESC lA : HD pica, hiragana
							wCode = 0x0500;
							nWidth = CParallelPR201::CXPICA+2;
							nRightGap = -2;
							break;
						case 0x42: // ESC lB : HS pica, hiragana
							wCode = 0x0600;
							nWidth = CParallelPR201::CXPICA+2;
							nRightGap = -2;
							break;
						case 0x43: // ESC lC : elite, hiragana
							wCode = 0x0700;
							nWidth = CParallelPR201::CXELITE;
							break;
						case 0x44: // ESC lD : condense, hiragana
							wCode = 0x0800;
							nWidth = CParallelPR201::CXCONDENSE;
							break;
						}
						wCode = (uint16_t)(wCode | btData);
						CPR201GaijiCommandState* pcstateGaiji =
							CPR201GaijiCommandState::GetInstance();
						if (pcstateGaiji->SetGaijiInfo(
								wCode,
								nWidth, nHeight,
								nLeftGap, nRightGap))
						{
							pcstateGaiji->SetPreCommandState(GetPreCommandState());
							GetPrinter()->ChangeComandState(pcstateGaiji);
						} else {
							bAbortCommand = true;
						}
					} else {
						bAbortCommand = true;
					}
				}
				break;
			case 0x35: // ESC l5 : register download character(proportional katakana)
			case 0x45: // ESC lE : register download character(proportional hiragana)
				if (m_vectParams.size() >= 7) {
					if ((btData >= 0x21) && (btData <= 0x7F)) {
						uint16_t wCode = 0;
						int nWidth = (m_vectParams[3]-0x30)*10+
								(m_vectParams[4]-0x30),
							nHeight = CParallelPR201::CYNORMAL,
							nLeftGap = m_vectParams[2]-0x30,
							nRightGap = m_vectParams[5]-0x30;
						switch (m_vectParams[1]) {
						case 0x35: // ESC l5 : proportional katakana
							wCode = 0x0400;
							break;
						case 0x45: // ESC lE : proportional hiragana
							wCode = 0x0900;
							break;
						}
						wCode = (uint16_t)(wCode | btData);
						CPR201GaijiCommandState* pcstateGaiji =
							CPR201GaijiCommandState::GetInstance();
						if (pcstateGaiji->SetGaijiInfo(
								wCode,
								nWidth, nHeight,
								nLeftGap, nRightGap))
						{
							pcstateGaiji->SetPreCommandState(GetPreCommandState());
							GetPrinter()->ChangeComandState(pcstateGaiji);
						} else {
							bAbortCommand = true;
						}
					} else {
						bAbortCommand = true;
					}
				} else if (m_vectParams.size() >= 3) {
					if ((btData < 0x30) || (btData > 0x39)) {
						bAbortCommand = true;
					}
				}
				break;
			default:
				bAbortCommand = true;
				break;
			}
		}
		break;
	case 0x65: // ESC e : expand character
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 3) {
				int nHorzZoom = m_vectParams[2]-0x30,
					nVertZoom = m_vectParams[1]-0x30;
				if ((((nHorzZoom >= 1) && (nHorzZoom <= 4)) ||
						(nHorzZoom == 6) ||
						(nHorzZoom == 8)) &&
					(((nVertZoom >= 1) && (nVertZoom <= 4)) ||
						(nVertZoom == 6) ||
						(nVertZoom == 8)))
				{
					GetPrinter()->SetHorzZoom(nHorzZoom);
					GetPrinter()->SetVertZoom(nVertZoom);
				}
				bAbortCommand = true;
			}
		}
		break;
	case 0x52: // ESC R : repeat character
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 4) {
				int nCharRepeatCount =
					(m_vectParams[1]-0x30)*100+
					(m_vectParams[2]-0x30)*10+
					(m_vectParams[3]-0x30);
				if ((nCharRepeatCount >= 0) && (nCharRepeatCount <= 999)) {
					GetPrinter()->SetCharRepeatCount(nCharRepeatCount);
				}
				bAbortCommand = true;
			}
		}
		break;
	case 0x21: // ESC ! : set strong printing mode
		GetPrinter()->SetStrongMode(true);
		bAbortCommand = true;
		break;
	case 0x22: // ESC " : cancel strong printing mode
		GetPrinter()->SetStrongMode(false);
		bAbortCommand = true;
		break;
	case 0x5F: // ESC _ : set underline mode
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x31: // ESC _1 : underline
				GetPrinter()->SetUnderLine(true);
				break;
			case 0x32: // ESC _2 : upperline
				GetPrinter()->SetUnderLine(false);
				break;
			}
			bAbortCommand = true;
		}
		break;
	case 0x58: // ESC X : set line draw mode
		GetPrinter()->SetLineDrawMode(true);
		bAbortCommand = true;
		break;
	case 0x59: // ESC Y : cancel line draw mode
		GetPrinter()->SetLineDrawMode(false);
		bAbortCommand = true;
		break;
	case 0x64: // ESC d : draft/fine mode
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x30: // ESC d0 : set draft mode
				break;
			case 0x31: // ESC d1 : cancel draft/fine mode
				break;
			case 0x32: // ESC d2 : set fine mode
				break;
			}
			bAbortCommand = true;
		}
		break;
	case 0x00: // ESC m(0) : 0 dot space
		bAbortCommand = true;
		break;
	case 0x01: // ESC m(1) : 1 dot space
	case 0x02: // ESC m(2) : 2 dot space
	case 0x03: // ESC m(3) : 3 dot space
	case 0x04: // ESC m(4) : 4 dot space
	case 0x05: // ESC m(5) : 5 dot space
	case 0x06: // ESC m(6) : 6 dot space
	case 0x07: // ESC m(7) : 7 dot space
	case 0x08: // ESC m(8) : 8 dot space
		GetPrinter()->OutputTextNull(
			btData*CParallelPR201::HIRES_X, true);
		bAbortCommand = true;
		break;
	case 0x53: // ESC S : draw 8 bit dot image graphics
	case 0x49: // ESC I : draw 16 bit dot image graphics
	case 0x4A: // ESC J : draw 24 bit dot image graphics
	case 0x56: // ESC V : repeat 8 bit dot
	case 0x57: // ESC W : repeat 16 bit dot
	case 0x55: // ESC U : repeat 24 bit dot
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 5) {
				int cxDot = (m_vectParams[1]-0x30)*1000+
					(m_vectParams[2]-0x30)*100+
					(m_vectParams[3]-0x30)*10+
					(m_vectParams[4]-0x30);
				CPR201ImageCommandState* pcstateImage =
					CPR201ImageCommandState::GetInstance();
				if (pcstateImage->SetImageInfo(
						btCommandByte, cxDot))
				{
					pcstateImage->SetPreCommandState(GetPreCommandState());
					GetPrinter()->ChangeComandState(pcstateImage);
				} else {
					bAbortCommand = true;
				}
			}
		}
		break;
	case 0x46: // ESC F : dot addressing
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 5) {
				int nAddress = (m_vectParams[1]-0x30)*1000+
					(m_vectParams[2]-0x30)*100+
					(m_vectParams[3]-0x30)*10+
					(m_vectParams[4]-0x30);
				int nAddressHR = nAddress*CParallelPR201::HIRES_X+
					GetPrinter()->GetLeftMarginHR();
				if (nAddress > GetPrinter()->GetRightMarginHR()) {
					nAddress = GetPrinter()->GetRightMarginHR();
				}
				if (GetPrinter()->GetHeadXHR() < nAddressHR) {
					GetPrinter()->OutputTextNull(
						nAddressHR-GetPrinter()->GetHeadXHR(), false);
				}
				bAbortCommand = true;
			}
		}
		break;
	case 0x44: // ESC D : copy mode
		GetPrinter()->SetCopyMode(true);
		bAbortCommand = true;
		break;
	case 0x4D: // ESC M : native mode
		GetPrinter()->SetCopyMode(false);
		bAbortCommand = true;
		break;
	case 0x3E: // ESC > : single-direction printing mode
	case 0x5D: // ESC ] : dual-direction printing mode
		bAbortCommand = true;
		break;
	case 0x28: // ESC ( : set horizontal-tab
	case 0x29: // ESC ) : remove a part of horizontal-tab
		if (m_vectParams.size() >= 2) {
			if (m_vectParams.size()%4 == 1) {
				if (btData == 0x2E) {
					if (m_vectParams[0] == 0x28) {
						GetPrinter()->RemoveAllHorzTab();
					}
					int nLeftMarginHR = GetPrinter()->GetLeftMarginHR(),
						nCharPitchHR = GetPrinter()->GetCurrentCharPitchHR(),
						n = 0;
					for (int i = 1; i < (int)m_vectParams.size(); i++) {
						uint8_t btData2 = m_vectParams[i];
						if ((btData2 == 0x2E) || (btData2 == 0x2C)) {
							if (n < 1) {
								break;
							}
							int nPosHR = nLeftMarginHR+nCharPitchHR*(n-1);
							if (m_vectParams[0] == 0x28) {
								GetPrinter()->RegisterHorzTabHR(nPosHR);
							} else {
								GetPrinter()->RemoveHorzTabHR(nPosHR);
							}
							if (btData2 == 0x2E) {
								break;
							}
							n = 0;
						} else if ((btData2 >= 0x30) && (btData2 <= 0x39)) {
							n = n*10+btData2-0x30;
						}
					}
					bAbortCommand = true;
				} else if (btData == 0x2C) {
				} else {
					bAbortCommand = true;
				}
			} else {
				if ((btData < 0x30) || (btData > 0x39)) {
					bAbortCommand = true;
				}
			}
		}
		break;
	case 0x32: // ESC 2 : remove all horizontal-tabs
		GetPrinter()->RemoveAllHorzTab();
		bAbortCommand = true;
		break;
	case 0x76: // ESC v : simple VFU
		if (m_vectParams.size() >= 2) {
			if (btData == 0x2E) {
				std::vector<uint8_t> vectVFUParams;
				int nNumCount = 0,
					nPageLength = 0,
					n = 0;
				for (int i = 1; i < (int)m_vectParams.size(); i++) {
					uint8_t btData2 = m_vectParams[i];
					if ((btData2 == 0x2E) || (btData2 == 0x2C)) {
						if (nNumCount == 0) {
							if (n <= 0) {
								break;
							}
							nPageLength = n;
							vectVFUParams.resize((nPageLength+1)*2, 0);
							vectVFUParams[0] = 0x41;
							for (int j = 1; j < nPageLength; j++) {
								vectVFUParams[j*2] = 0x40;
							}
							vectVFUParams[nPageLength*2] = 0x41;
						} else if (nNumCount == 1) {
							if (n >= nPageLength-2) {
								vectVFUParams.clear();
								break;
							}
							vectVFUParams[(nPageLength-n-1)*2] = 0x43;
						} else {
							if ((n < 1) || (n >= nPageLength)) {
								vectVFUParams.clear();
								break;
							}
							vectVFUParams[(n-1)*2] |= 0x02;
						}
						nNumCount++;
						n = 0;
						if (btData2 == 0x2E) {
							break;
						}
					} else if ((btData2 >= 0x30) && (btData2 <= 0x39)) {
						n = n*10+btData2-0x30;
						if (n > 99) {
							vectVFUParams.clear();
							break;
						}
					}
				}
				if (vectVFUParams.size() > 0) {
					GetPrinter()->SetVFU(vectVFUParams);
				}
				bAbortCommand = true;
			} else if (btData == 0x2C) {
				// nothing
			} else if ((btData >= 0x30) && (btData <= 0x39)) {
				// nothing
			} else {
				bAbortCommand = true;
			}
		}
		break;
	case 0x4C: // ESC L : left margin
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 4) {
				int nMargin = (m_vectParams[1]-0x30)*100+
					(m_vectParams[2]-0x30)*10+
					(m_vectParams[3]-0x30);
				int nMarginHR = nMargin*GetPrinter()->GetCurrentCharPitchHR();
				if ((nMarginHR >= 0) &&
					(nMarginHR <= GetPrinter()->GetMovableAreaWidth()*
						CParallelPR201::HIRES_X) &&
					(nMarginHR < GetPrinter()->GetRightMarginHR()))
				{
					GetPrinter()->SetLeftMarginHR(nMarginHR);
					GetPrinter()->HeadMove(0);
				}
				bAbortCommand = true;
			}
		}
		break;
	case 0x2F: // ESC / : right margin
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 4) {
				int nMargin = (m_vectParams[1]-0x30)*100+
					(m_vectParams[2]-0x30)*10+
					(m_vectParams[3]-0x30);
				int nMarginHR = nMargin*GetPrinter()->GetCurrentCharPitchHR();
				if ((nMarginHR >= 0) &&
					(nMarginHR <= GetPrinter()->GetMovableAreaWidth()*
						CParallelPR201::HIRES_X) &&
					(nMarginHR > GetPrinter()->GetLeftMarginHR()))
				{
					GetPrinter()->SetRightMarginHR(nMarginHR);
					GetPrinter()->HeadMove(0);
				}
				bAbortCommand = true;
			}
		}
		break;
	case 0x68: // ESC h : half-width kanji vertical mode
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x30: // ESC h0 : horizontal mode
				GetPrinter()->SetHalfKanjiVertMode(false);
				break;
			case 0x31: // ESC h1 : vertical mode
				GetPrinter()->SetHalfKanjiVertMode(true);
				break;
			}
			bAbortCommand = true;
		}
		break;
	case 0x71: // ESC q : half-width kanji combination mode
		GetPrinter()->SetHalfVertKanjiCombinationMode(true);
		GetPrinter()->SetHalfVertKanjiCombinating(false);
		bAbortCommand = true;
		break;
	case 0x41: // ESC A : 1/6 inch line-feed mode
		GetPrinter()->SetLineFeedHeightHR(
			(CParallelPR201::PR201_DPI*CParallelPR201::HIRES_Y_NAT)/6);
		bAbortCommand = true;
		break;
	case 0x42: // ESC B : 1/8 inch line-feed mode
		GetPrinter()->SetLineFeedHeightHR(
			(CParallelPR201::PR201_DPI*CParallelPR201::HIRES_Y_NAT)/8);
		bAbortCommand = true;
		break;
	case 0x54: // ESC T : n/120 inch line-feed mode
		if (m_vectParams.size() >= 2) {
			if ((btData < 0x30) || (btData > 0x39)) {
				bAbortCommand = true;
			} else if (m_vectParams.size() >= 3) {
				int nFeed = (m_vectParams[1]-0x30)*10+
						(m_vectParams[2]-0x30),
					nFeedHR;
				if (!GetPrinter()->IsCopyMode()) {
					nFeedHR = nFeed*CParallelPR201::HIRES_Y_COPY;
				} else {
					nFeedHR = nFeed*CParallelPR201::HIRES_Y_NAT;
				}
				GetPrinter()->SetLineFeedHeightHR(nFeedHR);
				bAbortCommand = true;
			}
		}
		break;
	case 0x66: // ESC f : forward feed mode
		if (!GetPrinter()->IsExistSheetFeeder()) {
			GetPrinter()->SetReverseFeed(false);
		}
		bAbortCommand = true;
		break;
	case 0x72: // ESC r : backward feed mode
		if (!GetPrinter()->IsExistSheetFeeder()) {
			GetPrinter()->SetReverseFeed(true);
		}
		bAbortCommand = true;
		break;
	case 0x43: // ESC C : change color
		if (m_vectParams.size() >= 2) {
			if ((btData >= 0x30) && (btData <= 0x37)) {
			}
			bAbortCommand = true;
		}
		break;
	case 0x61: // ESC a : discharge paper and inhalation
		if (GetPrinter()->IsExistSheetFeeder()) {
			if (GetPrinter()->IsExistPaper()) {
				GetPrinter()->PageFeed();
			}
			GetPrinter()->SetExistPaper(true);
		}
		bAbortCommand = true;
		break;
	case 0x62: // ESC b : discharge paper
		if (GetPrinter()->IsExistSheetFeeder()) {
			if (GetPrinter()->IsExistPaper()) {
				GetPrinter()->PageFeed();
			}
			GetPrinter()->SetExistPaper(false);
		}
		bAbortCommand = true;
		break;
	case 0x4F: // ESC O : change ANK font
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x30: // ESC O0 : normal font
				break;
			case 0x31: // ESC O1 : F1 font
				break;
			case 0x32: // ESC O2 : F2 font
				break;
			}
			bAbortCommand = true;
		}
		break;
	case 0x63: // ESC c
		if (m_vectParams.size() >= 2) {
			switch (btData) {
			case 0x31: // ESC c1 : reset
				GetPrinter()->Reset();
				bAbortCommand = true;
				break;
			default:
				bAbortCommand = true;
				break;
			}
		}
		break;
	case 0x6B: // ESC k : ignored command
	case 0x6D: // ESC m : ignored command
		if (m_vectParams.size() >= 2) {
			bAbortCommand = true;
		}
		break;
	default:
		bAbortCommand = true;
		break;
	}
	if (bAbortCommand) {
		GetPrinter()->ChangeComandState(
			GetPreCommandState());
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201FSCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201FSCommandState CPR201FSCommandState::m_cstateFS;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201FSCommandState::CPR201FSCommandState() :
	CPR201CommandState()
{
}

// destructor

CPR201FSCommandState::~CPR201FSCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201FSCommandState::Initialize() {
	m_vectParams.clear();
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201FSCommandState::ProcessData(uint8_t btData) {
	m_vectParams.push_back(btData);
	bool bAbortCommand = false;
	uint8_t btCommandByte = m_vectParams.front();
	switch (btCommandByte) {
	case 0x30: // FS 0
		switch ((m_vectParams.size() > 1)? m_vectParams[1]: -1) {
		case -1:
			break;
		case 0x34: // FS 04
			switch ((m_vectParams.size() >= 3)? m_vectParams[2]: -1) {
			case -1:
				break;
			case 0x4C: // FS 04L : set line type
				if (m_vectParams.size() == 4) {
				} else if (m_vectParams.size() >= 5) {
					if ((btData < 0x30) || (btData > 0x39)) {
						bAbortCommand = true;
					} else if (m_vectParams.size() >= 6) {
						int nWidth = m_vectParams[5]-0x30;
						if ((m_vectParams[3] == 0x53) &&
							(m_vectParams[4] == 0x31) &&
							((nWidth == 2) || (nWidth == 4)))
						{
							GetPrinter()->SetLineWidth(nWidth/2);
						}
						bAbortCommand = true;
					}
				}
				break;
			case 0x53: // FS 04S : set kanji size
				if (m_vectParams.size() >= 4) {
					if ((btData < 0x30) || (btData > 0x39)) {
						bAbortCommand = true;
					} else if (m_vectParams.size() >= 6) {
						int nWidth = (m_vectParams[3]-0x30)*100+
							(m_vectParams[4]-0x30)*10+
							(m_vectParams[5]-0x30);
						switch (nWidth) {
						case 70:
							GetPrinter()->SetKanjiWidthHR(
								CParallelPR201::KANJI_070_WIDTH);
							break;
						case 95:
							GetPrinter()->SetKanjiWidthHR(
								CParallelPR201::KANJI_095_WIDTH);
							break;
						case 105:
							GetPrinter()->SetKanjiWidthHR(
								CParallelPR201::KANJI_105_WIDTH);
							break;
						case 120:
							GetPrinter()->SetKanjiWidthHR(
								CParallelPR201::KANJI_120_WIDTH);
							break;
						}
						bAbortCommand = true;
					}
				}
				break;
			default:
				bAbortCommand = true;
				break;
			}
			break;
		case 0x36: // FS 06
			switch ((m_vectParams.size() >= 3)? m_vectParams[2]: -1) {
			case -1:
				break;
			case 0x46: // FS 06F : select character font
				if (m_vectParams.size() >= 8) {
					if ((m_vectParams[3] == 0x31) &&
						(m_vectParams[4] == 0x2D) &&
						(m_vectParams[5] == 0x30) &&
						(m_vectParams[6] == 0x30) &&
						(m_vectParams[7] >= 0x30) &&
						(m_vectParams[7] <= 0x33))
					{
						switch (m_vectParams[7]) {
						case 0x30: // FS 06F1-0000 : default
							GetPrinter()->SetUseFont(
								CParallelPR201::USEFONT_DEFAULT);
							break;
						case 0x31: // FS 06F1-0001 : italic
							GetPrinter()->SetUseFont(
								CParallelPR201::USEFONT_ITALIC);
							break;
						case 0x32: // FS 06F1-0002 : courier
							GetPrinter()->SetUseFont(
								CParallelPR201::USEFONT_COURIER);
							break;
						case 0x33: // FS 06F1-0003 : gothic
							GetPrinter()->SetUseFont(
								CParallelPR201::USEFONT_GOTHIC);
							break;
						}
					}
					bAbortCommand = true;
				}
				break;
			default:
				bAbortCommand = true;
				break;
			}
			break;
		default:
			bAbortCommand = true;
			break;
		}
		break;
	case 0x77: // FS w : fixed dot space
		if (m_vectParams.size() >= 2) {
			if (btData == 0x2E) {
				bool bComma = false;
				int nLeft = -1, nRight = -1,
					n = 0;
				for (int i = 1; i < (int)m_vectParams.size(); i++) {
					uint8_t btData2 = m_vectParams[i];
					if (btData2 == 0x2E) {
						nRight = n;
						break;
					} else if (btData2 == 0x2C) {
						if (bComma) {
							nLeft = nRight = -1;
							break;
						}
						bComma = true;
						nLeft = n;
						n = 0;
					} else if ((btData2 >= 0x30) && (btData2 <= 0x39)) {
						n = n*10+btData2-0x30;
					}
				}
				if ((nLeft >= 0) && (nLeft <= 31) &&
					(nRight >= 0) && (nRight <= 31))
				{
					GetPrinter()->SetFixDotSpaceLeft(nLeft);
					GetPrinter()->SetFixDotSpaceRight(nRight);
				}
				bAbortCommand = true;
			} else if (btData == 0x2C) {
				// nothing
			} else if ((btData >= 0x30) && (btData <= 0x39)) {
				// nothing
			} else {
				bAbortCommand = true;
			}
		}
		break;
	case 0x6D: // FS m : small kanji
		if (m_vectParams.size() >= 2) {
			if (btData == 0x2E) {
				int nComma = 0;
				bool bSlash = false;
				int nNumeratorV = -1, nDenominatorV = -1,
					nNumeratorH = -1, nDenominatorH = -1,
					nVPos = -1,
					n = 0;
				for (int i = 1; i < (int)m_vectParams.size(); i++) {
					uint8_t btData2 = m_vectParams[i];
					if (btData2 == 0x2E) {
						if ((nComma <= 0) || !bSlash) {
							nNumeratorV = nDenominatorV =
								nNumeratorH = nDenominatorH =
								nVPos = -1;
							break;
						}
						if (nComma <= 1) {
							nDenominatorH = n;
						}
						break;
					} else if (btData2 == 0x2C) {
						if ((nComma >= 2) || !bSlash) {
							nNumeratorV = nDenominatorV =
								nNumeratorH = nDenominatorH =
								nVPos = -1;
							break;
						}
						nComma++;
						if (nComma <= 1) {
							bSlash = false;
							nDenominatorV = n;
						} else {
							nDenominatorH = n;
						}
						n = 0;
					} else if (btData2 == 0x2F) {
						if (bSlash) {
							nNumeratorV = nDenominatorV =
								nNumeratorH = nDenominatorH =
								nVPos = -1;
							break;
						}
						bSlash = true;
						if (nComma <= 0) {
							nNumeratorV = n;
						} else {
							nNumeratorH = n;
						}
						n = 0;
					} else if (
						(btData2 == 0x48) ||
						(btData2 == 0x4D) ||
						(btData2 == 0x4C))
					{
						if ((nComma != 2) || (nVPos >= 0)) {
							nNumeratorV = nDenominatorV =
								nNumeratorH = nDenominatorH =
								nVPos = -1;
							break;
						}
						switch (btData2) {
						case 0x48:
							nVPos = 0;
							break;
						case 0x4D:
							nVPos = 1;
							break;
						case 0x4C:
							nVPos = 2;
							break;
						}
					} else if ((btData2 >= 0x30) && (btData2 <= 0x39)) {
						if (nComma >= 2) {
							nNumeratorV = nDenominatorV =
								nNumeratorH = nDenominatorH =
								nVPos = -1;
							break;
						}
						n = n*10+btData2-0x30;
					}
				}
				int nHorzZoom = 0, nVertZoom = 0;
				if ((nDenominatorH == 2) && (nNumeratorH == 1)) {
					nHorzZoom = -nDenominatorH;
				} else if (
					(nDenominatorH == 1) &&
					(((nNumeratorH >= 1) && (nNumeratorH <= 4)) ||
						(nNumeratorH == 6) ||
						(nNumeratorH == 8)))
				{
					nHorzZoom = nNumeratorH;
				}
				if ((nDenominatorV == 2) && (nNumeratorV == 1)) {
					nVertZoom = -nDenominatorV;
				} else if (
					(nDenominatorV == 1) &&
					(((nNumeratorV >= 1) && (nNumeratorV <= 4)) ||
						(nNumeratorV == 6) ||
						(nNumeratorV == 8)))
				{
					nVertZoom = nNumeratorV;
				}
				int nVertPos = CParallelPR201::SMALLKANJI_V_HI;
				if (nVPos < 0) {
					if (nVertZoom < -1) {
						nVertZoom = 0;
					}
				} else {
					if (nVertZoom < -1) {
						switch (nVPos) {
						case 0:
							nVertPos = CParallelPR201::SMALLKANJI_V_HI;
							break;
						case 1:
							nVertPos = CParallelPR201::SMALLKANJI_V_MID;
							break;
						case 2:
							nVertPos = CParallelPR201::SMALLKANJI_V_LO;
							break;
						}
					} else {
						nVertZoom = 0;
					}
				}
				if ((nHorzZoom != 0) && (nVertZoom != 0)) {
					GetPrinter()->SetHorzZoom(nHorzZoom);
					GetPrinter()->SetVertZoom(nVertZoom);
					GetPrinter()->SetSmallKanjiVertPos(nVertPos);
				}
				bAbortCommand = true;
			} else if (btData == 0x2C) {
				// nothing
			} else if (btData == 0x2F) {
				// nothing
			} else if ((btData >= 0x30) && (btData <= 0x39)) {
				// nothing
			} else if (
				(btData == 0x48) ||
				(btData == 0x4D) ||
				(btData == 0x4C))
			{
				// nothing
			} else {
				bAbortCommand = true;
			}
		}
		break;
	case 0x50: // FS P : small kanji combination print mode
		GetPrinter()->SetSmallKanjiCombinationMode(true);
		GetPrinter()->SetSmallKanjiCombinating(false);
		bAbortCommand = true;
		break;
	case 0x41: // FS A : kanji width 3/20, character size 10.5 point
		GetPrinter()->SetKanjiWidthHR(CParallelPR201::KANJI_105_WIDTH);
		GetPrinter()->SetKanjiPitchHR(CParallelPR201::KANJI_3_20_PITCH);
		bAbortCommand = true;
		break;
	case 0x42: // FS B : kanji width 1/5, character size 10.5 point
		GetPrinter()->SetKanjiWidthHR(CParallelPR201::KANJI_105_WIDTH);
		GetPrinter()->SetKanjiPitchHR(CParallelPR201::KANJI_1_5_PITCH);
		bAbortCommand = true;
		break;
	case 0x43: // FS C : kanji width 1/6, character size 9.5 point
		GetPrinter()->SetKanjiWidthHR(CParallelPR201::KANJI_095_WIDTH);
		GetPrinter()->SetKanjiPitchHR(CParallelPR201::KANJI_1_6_PITCH);
		bAbortCommand = true;
		break;
	case 0x44: // FS D : kanji width 2/15, character size 9.5 point
		GetPrinter()->SetKanjiWidthHR(CParallelPR201::KANJI_095_WIDTH);
		GetPrinter()->SetKanjiPitchHR(CParallelPR201::KANJI_2_15_PITCH);
		bAbortCommand = true;
		break;
	case 0x46: // FS F : kanji width 1/10, character size 7 point
		GetPrinter()->SetKanjiWidthHR(CParallelPR201::KANJI_070_WIDTH);
		GetPrinter()->SetKanjiPitchHR(CParallelPR201::KANJI_1_10_PITCH);
		bAbortCommand = true;
		break;
	case 0x47: // FS G : kanji width 1/6, character size 12 point
		GetPrinter()->SetKanjiWidthHR(CParallelPR201::KANJI_120_WIDTH);
		GetPrinter()->SetKanjiPitchHR(CParallelPR201::KANJI_1_6_PITCH);
		bAbortCommand = true;
		break;
	case 0x70: // FS p : kanji width
		if (m_vectParams.size() >= 2) {
			if (btData == 0x2E) {
				bool bComma = false,
					bSlash = false;
				int nBase = -1, nNumerator = -1, nDenominator = -1,
					n = 0;
				for (int i = 1; i < (int)m_vectParams.size(); i++) {
					uint8_t btData2 = m_vectParams[i];
					if (btData2 == 0x2E) {
						if (!bComma || !bSlash) {
							nBase = nNumerator = nDenominator = -1;
							break;
						}
						nDenominator = n;
						break;
					} else if (btData2 == 0x2C) {
						if (bComma) {
							nBase = nNumerator = nDenominator = -1;
							break;
						}
						bComma = true;
						nBase = n;
						n = 0;
					} else if (btData2 == 0x2F) {
						if (!bComma || bSlash) {
							nBase = nNumerator = nDenominator = -1;
							break;
						}
						bSlash = true;
						nNumerator = n;
						n = 0;
					} else if ((btData2 >= 0x30) && (btData2 <= 0x39)) {
						n = n*10+btData2-0x30;
					}
				}
				if (nBase == 2) {
					if ((nNumerator == 1) && (nDenominator == 5)) {
						GetPrinter()->SetKanjiPitchHR(
							CParallelPR201::KANJI_1_5_PITCH);
					} else if ((nNumerator == 1) && (nDenominator == 6)) {
						GetPrinter()->SetKanjiPitchHR(
							CParallelPR201::KANJI_1_6_PITCH);
					} else if ((nNumerator == 3) && (nDenominator == 20)) {
						GetPrinter()->SetKanjiPitchHR(
							CParallelPR201::KANJI_3_20_PITCH);
					} else if ((nNumerator == 2) && (nDenominator == 15)) {
						GetPrinter()->SetKanjiPitchHR(
							CParallelPR201::KANJI_2_15_PITCH);
					} else if ((nNumerator == 1) && (nDenominator == 10)) {
						GetPrinter()->SetKanjiPitchHR(
							CParallelPR201::KANJI_1_10_PITCH);
					}
				}
				bAbortCommand = true;
			} else if (btData == 0x2C) {
				// nothing
			} else if (btData == 0x2F) {
				// nothing
			} else if ((btData >= 0x30) && (btData <= 0x39)) {
				// nothing
			} else {
				bAbortCommand = true;
			}
		}
		break;
	case 0x63: // FS c : character decoration
		if (m_vectParams.size() >= 2) {
			if (btData == 0x2E) {
				bAbortCommand = true;
			} else if (btData == 0x2C) {
				// nothing
			} else if ((btData >= 0x30) && (btData <= 0x39)) {
				// nothing
			} else {
				bAbortCommand = true;
			}
		}
		break;
	default:
		bAbortCommand = true;
		break;
	}
	if (bAbortCommand) {
		GetPrinter()->ChangeComandState(
			GetPreCommandState());
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201USCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201USCommandState CPR201USCommandState::m_cstateUS;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201USCommandState::CPR201USCommandState() :
	CPR201CommandState()
{
}

// destructor

CPR201USCommandState::~CPR201USCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201USCommandState::Initialize() {
	m_vectParams.clear();
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201USCommandState::ProcessData(uint8_t btData) {
	m_vectParams.push_back(btData);
	bool bAbortCommand;
	uint8_t btCommandByte = m_vectParams.front();
	switch (btCommandByte) {
	case 0x01: // US m(1) : execute VFU1
	case 0x02: // US m(2) : execute VFU2
	case 0x03: // US m(3) : execute VFU3
	case 0x04: // US m(4) : execute VFU4
	case 0x05: // US m(5) : execute VFU5
	case 0x06: // US m(6) : execute VFU6
		GetPrinter()->ExecVFU(btCommandByte-1);
		bAbortCommand = true;
		break;
	default:
		if ((btCommandByte >= 0x10) &&
			(btCommandByte <= 0x58))
		{
			// US m(16-88) : feed n line
			for (int nLine = btCommandByte-16; nLine > 0; nLine--) {
				if (!GetPrinter()->LineFeed()) {
					break;
				}
			}
		}
		bAbortCommand = true;
		break;
	}
	if (bAbortCommand) {
		GetPrinter()->ChangeComandState(
			GetPreCommandState());
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201VFUCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201VFUCommandState CPR201VFUCommandState::m_cstateVFU;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201VFUCommandState::CPR201VFUCommandState() :
	CPR201CommandState()
{
	m_vectVFUParams.reserve(128);
}

// destructor

CPR201VFUCommandState::~CPR201VFUCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201VFUCommandState::Initialize() {
	m_vectVFUParams.clear();
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201VFUCommandState::ProcessData(uint8_t btData) {
	if ((btData == 0x1E) &&
		(m_vectVFUParams.size()%2 == 0))
	{
		GetPrinter()->SetVFU(m_vectVFUParams);
		m_vectVFUParams.clear();
		GetPrinter()->ChangeComandState(
			GetPreCommandState());
	} else {
		m_vectVFUParams.push_back(btData);
	}
}

////////////////////////////////////////////////////////////
// implementation of CPR201ImageCommandState

////////////////////////////////////////////////////////////
// attribute

// singleton

CPR201ImageCommandState CPR201ImageCommandState::m_cstateImage;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201ImageCommandState::CPR201ImageCommandState() :
	CPR201CommandState(),
	m_btImageKind(0),
	m_cxDot(0),
	m_nImageDataCount(0)
{
}

// destructor

CPR201ImageCommandState::~CPR201ImageCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201ImageCommandState::Initialize() {
	m_vectImageData.clear();
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201ImageCommandState::ProcessData(uint8_t btData) {
	m_vectImageData.push_back(btData);
	if ((int)m_vectImageData.size() >= m_nImageDataCount) {
		switch (m_btImageKind) {
		case 0x53: // ESC S : draw 8 bit dot image graphics
		case 0x49: // ESC I : draw 16 bit dot image graphics
		case 0x4A: // ESC J : draw 24 bit dot image graphics
			GetPrinter()->OutputDotImage(
				m_btImageKind, m_cxDot, m_vectImageData);
			break;
		case 0x56: // ESC V : repeat 8 bit dot
		case 0x57: // ESC W : repeat 16 bit dot
		case 0x55: // ESC U : repeat 24 bit dot
			GetPrinter()->OutputDotRepeat(
				m_btImageKind, m_cxDot, m_vectImageData);
			break;
		}
		m_vectImageData.clear();
		GetPrinter()->ChangeComandState(
			GetPreCommandState());
	}
}

////////////////////////////////////////////////////////////
// operation

// set image info

bool CPR201ImageCommandState::SetImageInfo(uint8_t btImageKind, int cxDot) {
	m_btImageKind = btImageKind;
	m_cxDot = cxDot;
	m_nImageDataCount = 0;
	switch (m_btImageKind) {
	case 0x53: // ESC S : draw 8 bit dot image graphics
		m_nImageDataCount = m_cxDot;
		break;
	case 0x49: // ESC I : draw 16 bit dot image graphics
		m_nImageDataCount = m_cxDot*2;
		break;
	case 0x4A: // ESC J : draw 24 bit dot image graphics
		m_nImageDataCount = m_cxDot*3;
		break;
	case 0x56: // ESC V : repeat 8 bit dot
		m_nImageDataCount = 1;
		break;
	case 0x57: // ESC W : repeat 16 bit dot
		m_nImageDataCount = 2;
		break;
	case 0x55: // ESC U : repeat 24 bit dot
		m_nImageDataCount = 3;
		break;
	}
	m_vectImageData.reserve(m_nImageDataCount);
	return m_nImageDataCount > 0;
}

////////////////////////////////////////////////////////////
// implementation of CPR201GaijiCommandState

// singleton

CPR201GaijiCommandState CPR201GaijiCommandState::m_cstateGaiji;

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CPR201GaijiCommandState::CPR201GaijiCommandState() :
	CPR201CommandState(),
	m_wCode(0),
	m_cxDot(0), m_cyDot(0),
	m_nLeftGap(0), m_nRightGap(0),
	m_nGaijiDataCount(0)
{
}

// destructor

CPR201GaijiCommandState::~CPR201GaijiCommandState() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CPR201GaijiCommandState::Initialize() {
	m_vectGaijiData.clear();
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CPR201GaijiCommandState::ProcessData(uint8_t btData) {
	m_vectGaijiData.push_back(btData);
	if ((int)m_vectGaijiData.size() >= m_nGaijiDataCount) {
		CPrinterGaiji gaiji(
			m_wCode,
			m_cxDot+m_nLeftGap+m_nRightGap,
			CParallelPR201::CYNORMAL);
		int nSrcVBytes = (m_cyDot+7)/8,
			nDstVBytes = (CParallelPR201::CYNORMAL+7)/8,
			cx = min_value(m_cxDot, gaiji.GetDotCX());
		for (int x = 0; x < cx; x++) {
			for (int y = 0; y < nSrcVBytes; y++) {
				gaiji.GetImageData()[(x+m_nLeftGap)*nDstVBytes+y] =
					m_vectGaijiData[x*nSrcVBytes+y];
			}
		}
		GetPrinter()->RegisterGaiji(gaiji);
		m_vectGaijiData.clear();
		GetPrinter()->ChangeComandState(
			GetPreCommandState());
	}
}

////////////////////////////////////////////////////////////
// operation

// set gaiji info

bool CPR201GaijiCommandState::SetGaijiInfo(
	uint16_t wCode,
	int cxDot, int cyDot,
	int nLeftGap, int nRightGap)
{
	m_wCode = wCode;
	m_cxDot = cxDot;
	m_cyDot = cyDot;
	m_nLeftGap = nLeftGap;
	m_nRightGap = nRightGap;
	m_nGaijiDataCount = ((m_cyDot+7)/8)*m_cxDot;
	m_vectGaijiData.reserve(m_nGaijiDataCount);
	return m_nGaijiDataCount > 0;
}

////////////////////////////////////////////////////////////
// implementation of CParallelPR201

////////////////////////////////////////////////////////////
// attribute

// get device id

std::string CParallelPR201::GetDeviceID() const {
	return "pr201";
}

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CParallelPR201::CParallelPR201() :
	CParallelPrinter(),
	m_nSelectedPaper(PAPER_C15),
	m_bPaperCentering(true),
	m_bReverseFeed(false),
	m_nHeadXHR(0), m_nHeadYHR(0),
	m_nLineFeedHeightHR(0),
	m_nLineFeedHeigntOnCRHR(0),
	m_nLeftMarginHR(0), m_nRightMarginHR(0),
	m_bHorzTabSkipping(false),
	m_nVFUOfsYHR(0),
	m_nVFUPageHeightHR(1),
	m_nVFUPageBottomHR(-1),
	m_nPrintingMethod(METHOD_HDPICA),
	m_nKanjiWidthHR(KANJI_105_WIDTH),
	m_nKanjiPitchHR(KANJI_3_20_PITCH),
	m_nFixDotSpaceLeft(0), m_nFixDotSpaceRight(0),
	m_nHorzZoom(1), m_nVertZoom(1),
	m_nUseFont(USEFONT_DEFAULT),
	m_bStrongMode(false),
	m_bHiraganaMode(false),
	m_nScriptMode(SCRIPT_NONE),
	m_bCopyMode(false),
	m_bHalfKanjiVertMode(false),
	m_bHalfVertKanjiCombinationMode(false),
	m_bHalfVertKanjiCombinating(false),
	m_nSmallKanjiVertPos(SMALLKANJI_V_HI),
	m_bSmallKanjiCombinationMode(false),
	m_bSmallKanjiCombinating(false),
	m_bLineDrawMode(false),
	m_bUnderLine(true),
	m_nLineWidth(1),
	m_nCharRepeatCount(1),
	m_bDownloadCharUse(false),
	m_pcstateCurrent(NULL)
{
}

// destructor

CParallelPR201::~CParallelPR201() {
}

////////////////////////////////////////////////////////////
// initialize

// initialize at first

void CParallelPR201::Initialize() {
	CParallelPrinter::Initialize();
	SetHeadHeight(PR201_HEAD);
	SetHeadXHR(0);
	SetHeadYHR(0);
	SetMovableAreaWidth((136*GetDPI())/10);
	SelectPaper(GetSelectablePaper(0));
}

// reset

void CParallelPR201::Reset() {
	CParallelPrinter::Reset();
	SetHeadXHR(0);
	SetHeadX(0);
	SetReverseFeed(false);
	SetLineFeedHeightHR((GetDPI()*HIRES_Y_NAT)/6);
	SetLineFeedHeigntOnCRHR(0);
	SetLeftMarginHR(0);
	SetRightMarginHR(GetMovableAreaWidth()*HIRES_X);
	m_setHorzTabs.clear();
	m_bHorzTabSkipping = false;
	for (int nChannel = 0; nChannel < VFU_CH_MAX; nChannel++) {
		m_asetVertTabsHR[nChannel].clear();
	}
	m_asetVertTabsHR[0].insert(0);
	for (int nVTab = 6; nVTab < 66; nVTab += 6) {
		m_asetVertTabsHR[1].insert((nVTab*GetDPI()*HIRES_Y_NAT)/6);
	}
	SetVFUPageHeightHR((11*GetDPI())*HIRES_Y_NAT);
	SetVFUPageBottomHR(-1);
	SetPrintingMethod(METHOD_HDPICA);
	SetKanjiWidthHR(KANJI_105_WIDTH);
	SetKanjiPitchHR(KANJI_3_20_PITCH);
	SetFixDotSpaceLeft(0);
	SetFixDotSpaceRight(0);
	SetHorzZoom(1);
	SetVertZoom(1);
	SetUseFont(USEFONT_DEFAULT);
	SetStrongMode(false);
	SetHiraganaMode(false);
	SetScriptMode(SCRIPT_NONE);
	SetCopyMode(false);
	SetHalfKanjiVertMode(false);
	SetHalfVertKanjiCombinationMode(false);
	SetHalfVertKanjiCombinating(false);
	SetSmallKanjiVertPos(SMALLKANJI_V_HI);
	SetSmallKanjiCombinationMode(false);
	SetSmallKanjiCombinating(false);
	SetLineDrawMode(false);
	SetUnderLine(true);
	SetLineWidth(1);
	SetCharRepeatCount(1);
	SetDownloadCharUse(false);
	m_setGaijisSB.clear();
	m_setGaijisDB.clear();
	ChangeComandState(CPR201ANKCommandState::GetInstance());
	if (IsExistSheetFeeder()) {
		if (IsExistPaper()) {
			DoPageFeed(1);
		}
	} else {
		SetVFUOfsYHR(0);
	}
}

////////////////////////////////////////////////////////////
// implementation

// process data

void CParallelPR201::ProcessData(uint8_t btData) {
	m_pcstateCurrent->ProcessData(btData);
}

// carriage-return

bool CParallelPR201::CarriageReturn() {
	SetDirty(true);
	bool bResult = true;
	if (GetLineFeedHeigntOnCRHR() != 0) {
		int nFeedHR = GetLineFeedHeigntOnCRHR();
		SetLineFeedHeigntOnCRHR(0);
		bResult = DoDotFeedHR(nFeedHR);
	}
	HeadMoveHR(GetLeftMarginHR()-GetHeadXHR());
	return bResult;
}

// line-feed

bool CParallelPR201::LineFeed() {
	SetDirty(true);
	int nFeedHR = IsReverseFeed()?
		-GetLineFeedHeightHR(): GetLineFeedHeightHR();
	if (GetLineFeedHeigntOnCRHR() != 0) {
		nFeedHR += GetLineFeedHeigntOnCRHR();
		SetLineFeedHeigntOnCRHR(0);
	}
	return DoDotFeedHR(nFeedHR);
}

// page-feed

bool CParallelPR201::PageFeed() {
	SetDirty(true);
	if (GetLineFeedHeigntOnCRHR() != 0) {
		int nFeedHR = GetLineFeedHeigntOnCRHR();
		SetLineFeedHeigntOnCRHR(0);
		if (!DoDotFeedHR(nFeedHR)) {
			return false;
		}
	}
	return DoPageFeed(
		IsReverseFeed()? -1: 1);
}

// head move

bool CParallelPR201::HeadMove(int nMove) {
	SetDirty(true);
	return HeadMoveHR(nMove*HIRES_X);
}

// horizontal-tab

bool CParallelPR201::HorzTab() {
	SetDirty(true);
	CTabPosSet::const_iterator itHorzTab =
		m_setHorzTabs.lower_bound(GetHeadXHR());
	if (itHorzTab == m_setHorzTabs.end()) {
		return false;
	}
	if (*itHorzTab == GetHeadXHR()) {
		if (!m_bHorzTabSkipping) {
			m_bHorzTabSkipping = true;
			return true;
		} else {
			m_bHorzTabSkipping = false;
			if (++itHorzTab == m_setHorzTabs.end()) {
				return false;
			}
		}
	}
	if ((*itHorzTab < GetLeftMarginHR()) ||
		(*itHorzTab > GetRightMarginHR()))
	{
		return false;
	}
	return HeadMoveHR(*itHorzTab-GetHeadXHR());
}

// vertical-tab

bool CParallelPR201::VertTab() {
	return ExecVFU(1);
}

// get selectable paper count

int CParallelPR201::GetSelectablePaperCount() const {
	return 12;
}

// get selectable paper

int CParallelPR201::GetSelectablePaper(int nIndex) const {
	int nPaper = PAPER_NONE;
	switch (nIndex) {
	case 0:
		nPaper = PAPER_C15;
		break;
	case 1:
		nPaper = PAPER_C10;
		break;
	case 2:
		nPaper = PAPER_A4V;
		break;
	case 3:
		nPaper = PAPER_A4H;
		break;
	case 4:
		nPaper = PAPER_A5V;
		break;
	case 5:
		nPaper = PAPER_A5H;
		break;
	case 6:
		nPaper = PAPER_B4V;
		break;
	case 7:
		nPaper = PAPER_B4H;
		break;
	case 8:
		nPaper = PAPER_B5V;
		break;
	case 9:
		nPaper = PAPER_B5H;
		break;
	case 10:
		nPaper = PAPER_HAGAKIV;
		break;
	case 11:
		nPaper = PAPER_HAGAKIH;
		break;
	}
	return nPaper;
}

// get selected paper

int CParallelPR201::GetSelectedPaper() const {
	return m_nSelectedPaper;
}

// select paper

bool CParallelPR201::SelectPaper(int nPaper) {
	SetDirty(true);
	int nPaperWidth = 0, nPaperHeight = 0;
	switch (nPaper) {
	case PAPER_C15:
		nPaperWidth = 15*GetDPI();
		nPaperHeight = 11*GetDPI();
		break;
	case PAPER_C10:
		nPaperWidth = 10*GetDPI();
		nPaperHeight = 11*GetDPI();
		break;
	case PAPER_A4V:
	case PAPER_A4H:
		nPaperWidth = (2100*GetDPI())/254;
		nPaperHeight = (2970*GetDPI())/254;
		break;
	case PAPER_A5V:
	case PAPER_A5H:
		nPaperWidth = (1485*GetDPI())/254;
		nPaperHeight = (2100*GetDPI())/254;
		break;
	case PAPER_B4V:
	case PAPER_B4H:
		nPaperWidth = (2570*GetDPI())/254;
		nPaperHeight = (3640*GetDPI())/254;
		break;
	case PAPER_B5V:
	case PAPER_B5H:
		nPaperWidth = (1820*GetDPI())/254;
		nPaperHeight = (2570*GetDPI())/254;
		break;
	case PAPER_HAGAKIV:
	case PAPER_HAGAKIH:
		nPaperWidth = (1000*GetDPI())/254;
		nPaperHeight = (1480*GetDPI())/254;
		break;
	}
	if ((nPaperWidth <= 0) || (nPaperHeight <= 0)) {
		return false;
	}
	m_nSelectedPaper = nPaper;
	switch (nPaper) {
	case PAPER_A4H:
	case PAPER_A5H:
	case PAPER_B4H:
	case PAPER_B5H:
	case PAPER_HAGAKIH:
		std::swap(nPaperWidth, nPaperHeight);
		break;
	}
	int nPaperLeft = 0,
		nPaperTop = 0, nPaperBottom = 0;
	switch (nPaper) {
	case PAPER_C15:
	case PAPER_C10:
		if (nPaperWidth > GetMovableAreaWidth()) {
			nPaperLeft = (GetMovableAreaWidth()-nPaperWidth)/2;
		} else {
			nPaperLeft = -1*GetDPI();
		}
		SetExistSheetFeeder(false);
		break;
	case PAPER_A4V:
	case PAPER_A4H:
	case PAPER_A5V:
	case PAPER_A5H:
	case PAPER_B4V:
	case PAPER_B4H:
	case PAPER_B5V:
	case PAPER_B5H:
		nPaperTop = nPaperBottom = -(80*GetDPI())/254+NORMAL_HEIGHT/2;
		if (IsPaperCentering() ||
			(nPaperWidth > GetMovableAreaWidth()))
		{
			nPaperLeft = (GetMovableAreaWidth()-nPaperWidth)/2;
		}
		SetExistSheetFeeder(true);
		break;
	case PAPER_HAGAKIV:
	case PAPER_HAGAKIH:
		nPaperTop = -(115*GetDPI())/254+NORMAL_HEIGHT/2;
		nPaperBottom = -(140*GetDPI())/254+NORMAL_HEIGHT/2;
		if (IsPaperCentering() ||
			(nPaperWidth > GetMovableAreaWidth()))
		{
			nPaperLeft = (GetMovableAreaWidth()-nPaperWidth)/2;
		}
		SetExistSheetFeeder(true);
		break;
	}
	SetMovableAreaHeight(
		nPaperHeight+nPaperTop+nPaperBottom);
	SetPaperArea(
		nPaperLeft, nPaperTop,
		nPaperWidth, nPaperHeight);
	SetHeadYHR(0);
	SetHeadY(0);
	SetVFUOfsYHR(0);
	SetCurrentPage(0);
	DeleteAllPages();
	if (IsExistSheetFeeder()) {
		SetHeadXHR(GetLeftMarginHR());
		SetHeadX(GetHeadXHR()/HIRES_X);
		SetReverseFeed(false);
		SetExistPaper(false);
	} else {
		SetExistPaper(true);
	}
	return true;
}

// is able paper centering

bool CParallelPR201::IsAblePaperCentering() const {
	bool bAble = true;
	switch (GetSelectedPaper()) {
	case PAPER_C15:
	case PAPER_C10:
		bAble = false;
		break;
	}
	return bAble;
}

// is paper centering

bool CParallelPR201::IsPaperCentering() const {
	return m_bPaperCentering;
}

// set paper centering

bool CParallelPR201::SetPaperCentering(bool bPaperCentering) {
	SetDirty(true);
	m_bPaperCentering = bPaperCentering;
	if (!IsAblePaperCentering()) {
		return false;
	}
	int nPaperLeft = 0;
	if (IsPaperCentering() ||
		(GetPaperWidth() > GetMovableAreaWidth()))
	{
		nPaperLeft = (GetMovableAreaWidth()-GetPaperWidth())/2;
	}
	SetPaperLeft(nPaperLeft);
	return true;
}

// paper feed from external operation
//
//     bPageFeed
//         feed in page-unit
//     nFeed
//         bPageFeed = false : feed value in points
//         bPageFeed = true  : feed value in pages

bool CParallelPR201::PaperFeed(bool bPageFeed, int nFeed) {
	if (nFeed < 0) {
		return false;
	} else if (nFeed == 0) {
		return true;
	}
	SetDirty(true);
	bool bResult;
	if (!bPageFeed) {
		bResult = DoDotFeedHR((nFeed*GetDPI()*HIRES_Y_NAT+71)/72);
	} else {
		bResult = DoPageFeed(nFeed);
	}
	return bResult;
}

////////////////////////////////////////////////////////////
// operation

// move head in hi-resolution

bool CParallelPR201::HeadMoveHR(int nMoveHR) {
	bool bResult = true;
	int nHeadXHR = GetHeadXHR()+nMoveHR;
	if (nHeadXHR < GetLeftMarginHR()) {
		nHeadXHR = GetLeftMarginHR();
		bResult = false;
	} else if (nHeadXHR > GetRightMarginHR()) {
		nHeadXHR = GetRightMarginHR();
		bResult = false;
	}
	SetHeadXHR(nHeadXHR);
	SetHeadX(nHeadXHR/HIRES_X);
	m_bHorzTabSkipping = false;
	return bResult;
}

// feed dot in hi-resolution

bool CParallelPR201::DoDotFeedHR(int nFeedDotHR) {
	if (nFeedDotHR == 0) {
		return true;
	}
	int nMoveableAreaHeightHR = GetMovableAreaHeight()*HIRES_Y_NAT,
		nFeed = nFeedDotHR;
	if (IsExistSheetFeeder()) {
		if (nFeedDotHR < 0) {
			return false;
		}
		while (nFeed > 0) {
			int nHeadYHRNew = GetHeadYHR()+nFeed;
			if (GetVFUPageBottomHR() >= 0) {
				if (nHeadYHRNew >= GetVFUPageBottomHR()) {
					nHeadYHRNew = nMoveableAreaHeightHR;
				}
			}
			if (nHeadYHRNew >= nMoveableAreaHeightHR) {
				nFeed = nMoveableAreaHeightHR-nHeadYHRNew;
				if (!DoPageFeed(1)) {
					return false;
				}
			} else {
				nFeed = 0;
				SetVFUOfsYHR(nHeadYHRNew);
				SetHeadYHR(nHeadYHRNew);
				SetHeadY(nHeadYHRNew/HIRES_Y_NAT);
				SetExistPaper(true);
			}
		}
	} else {
		int nFeed = nFeedDotHR;
		int nVFUOfsYHRNew = GetVFUOfsYHR()+nFeed;
		int nVFUPage = (nFeedDotHR >= 0)?
			(nVFUOfsYHRNew/GetVFUPageHeightHR()):
			(-(GetVFUPageHeightHR()-nVFUOfsYHRNew-1)/GetVFUPageHeightHR());
		if (GetVFUPageBottomHR() >= 0) {
			if (nVFUOfsYHRNew-nVFUPage*GetVFUPageHeightHR() >
					GetVFUPageBottomHR())
			{
				if (nFeedDotHR >= 0) {
					nVFUPage++;
					nVFUOfsYHRNew = nVFUPage*GetVFUPageHeightHR();
				} else {
					nVFUOfsYHRNew = nVFUPage*GetVFUPageHeightHR()+
						GetVFUPageBottomHR();
				}
				nFeed = nVFUOfsYHRNew-GetVFUOfsYHR();
			}
		}
		if (nVFUPage != 0) {
			nVFUOfsYHRNew -= nVFUPage*GetVFUPageHeightHR();
		}
		SetVFUOfsYHR(nVFUOfsYHRNew);
		int nHeadYHRNew = GetHeadYHR()+nFeed;
		int nPage = (nFeedDotHR >= 0)?
			(nHeadYHRNew/nMoveableAreaHeightHR):
			(-(nMoveableAreaHeightHR-nHeadYHRNew-1)/nMoveableAreaHeightHR);
		if (nPage != 0) {
			int nCurrntPageNew = GetCurrentPage()+nPage;
			if (nCurrntPageNew >= 0) {
				SetCurrentPage(nCurrntPageNew);
				nHeadYHRNew -= nPage*nMoveableAreaHeightHR;
			} else {
				SetCurrentPage(0);
				nHeadYHRNew = 0;
			}
		}
		SetHeadYHR(nHeadYHRNew);
		SetHeadY(nHeadYHRNew/HIRES_Y_NAT);
	}
	return true;
}

// feed page

bool CParallelPR201::DoPageFeed(int nFeedPage) {
	if (nFeedPage == 0) {
		return true;
	}
	if (IsExistSheetFeeder()) {
		if (nFeedPage > 0) {
			SetCurrentPage(GetCurrentPage()+nFeedPage);
			SetHeadY(0);
			SetHeadYHR(0);
			SetVFUOfsYHR(0);
			SetExistPaper(false);
		} else {
			return false;
		}
	} else {
		if (nFeedPage > 0) {
			for (int i = 0; i < nFeedPage; i++) {
				int nFeedDotHR;
				if (GetVFUPageBottomHR() < 0) {
					nFeedDotHR = GetVFUPageHeightHR()-GetVFUOfsYHR();
				} else {
					nFeedDotHR = GetVFUPageBottomHR()-GetVFUOfsYHR()+1;
				}
				if (!DoDotFeedHR(nFeedDotHR)) {
					return false;
				}
			}
		} else {
			for (int i = 0; i > nFeedPage; i--) {
				int nFeedDotHR;
				if (GetVFUPageBottomHR() < 0) {
					nFeedDotHR = -GetVFUOfsYHR()-GetHeadHeight();
				} else {
					nFeedDotHR = -GetVFUOfsYHR()-
						(GetVFUPageHeightHR()-GetVFUPageBottomHR());
				}
				if (!DoDotFeedHR(nFeedDotHR)) {
					return false;
				}
			}
		}
	}
	return true;
}

// get current font type

int CParallelPR201::GetCurrentFontType(bool bASCII) {
	int nFontType = CPrinterTextObject::FONT_MINCHO;
	switch (GetUseFont()) {
	case USEFONT_DEFAULT:
		nFontType = CPrinterTextObject::FONT_MINCHO;
		break;
	case USEFONT_ITALIC:
		nFontType |= CPrinterTextObject::FONT_ITALIC;
		break;
	case USEFONT_COURIER:
		if (bASCII) {
			nFontType = CPrinterTextObject::FONT_COURIER;
		} else {
			nFontType = CPrinterTextObject::FONT_MINCHO;
		}
		break;
	case USEFONT_GOTHIC:
		nFontType = CPrinterTextObject::FONT_GOTHIC;
		break;
	}
	if (IsStrongMode()) {
		nFontType |= CPrinterTextObject::FONT_STRONG;
	}
	return nFontType;
}

// get current line type

int CParallelPR201::GetCurrentLineType() {
	return IsLineDrawMode()?
		(GetLineWidth() |
			(IsUnderLine()?
				CPrinterTextObject::LINE_UNDER:
				CPrinterTextObject::LINE_UPPER)):
		CPrinterTextObject::LINE_NONE;
}

// output text

bool CParallelPR201::OutputText(
	int nFontType, int nPitchType,
	uint16_t wText,
	int nCharType,
	int nCharWidthHR, int nCharHeight,
	int nLeftGapHR, int nRightGapHR,
	int nLineType,
	int nVOfs,
	int nHorzZoom, int nVertZoom,
	bool bHeadBack,
	const CPrinterGaiji* pGaiji)
{
	int nCharWidthHR2 = nCharWidthHR,
		nCharHeight2 = nCharHeight,
		nLeftGapHR2 = nLeftGapHR,
		nRightGapHR2 = nRightGapHR,
		nVOfs2 = nVOfs;
	if (nHorzZoom > 1) {
		nCharWidthHR2 *= nHorzZoom;
		nLeftGapHR2 *= nHorzZoom;
		nRightGapHR2 *= nHorzZoom;
	} else if (nHorzZoom < -1) {
		nCharWidthHR2 /= -nHorzZoom;
		nLeftGapHR2 /= -nHorzZoom;
		nRightGapHR2 /= -nHorzZoom;
	}
	if (nVertZoom > 1) {
		nCharHeight2 *= nVertZoom;
		nVOfs2 *= nVertZoom;
	} else if (nVertZoom < -1) {
		nCharHeight2 /= -nVertZoom;
		nVOfs2 /= -nVertZoom;
	}
	int nCharPitchHR = nLeftGapHR2+nCharWidthHR2+nRightGapHR2;
	if (GetHeadXHR()+nCharPitchHR > GetRightMarginHR()) {
		CarriageReturn();
		LineFeed();
	}
	if (nVertZoom > 1) {
		int nFeedOnCRHR = PR201_HEAD*(nVertZoom-1)*HIRES_Y_NAT;
		if ((GetVFUPageBottomHR() >= 0) &&
			(GetHeadYHR()+nFeedOnCRHR > GetVFUPageBottomHR()))
		{
			PageFeed();
		}
		if (GetLineFeedHeigntOnCRHR() < nFeedOnCRHR) {
			SetLineFeedHeigntOnCRHR(nFeedOnCRHR);
		}
	}
	if (bHeadBack &&
		(GetHeadXHR()-nCharPitchHR >= GetLeftMarginHR()))
	{
		HeadMoveHR(-nCharPitchHR);
	}
	int nHeadXOld = GetHeadX();
	HeadMoveHR(nCharPitchHR);
	int nCharPitch = GetHeadX()-nHeadXOld,
		nCharWidth = nCharWidthHR2/HIRES_X,
		nLeftGap = nLeftGapHR2/HIRES_X,
		nRightGap = nRightGapHR2/HIRES_X,
		nExcess = nCharPitch-(nLeftGap+nCharWidth+nRightGap);
	nLeftGap += (nExcess+1)/2;
	nRightGap += nExcess/2;
	AddPrinterObject(
		new CPrinterTextObject(
			nHeadXOld,
			GetHeadY()+nVOfs2,
			nFontType,
			nPitchType,
			wText,
			nCharType,
			nCharWidth, nCharHeight2,
			nLeftGap, nRightGap,
			nLineType,
			pGaiji));
	SetExistPaper(true);
	return true;
}

// delete one page

bool CParallelPR201::DeletePage(int nPage) {
	if (nPage == GetCurrentPage()) {
		SetHeadXHR(GetLeftMarginHR());
		SetHeadX(GetHeadXHR()/HIRES_X);
		SetHeadYHR(0);
		SetHeadY(0);
		if (IsExistSheetFeeder()) {
			SetVFUOfsYHR(0);
			SetExistPaper(false);
		}
	}
	return CParallelPrinter::DeletePage(nPage);
}

// change comand state

void CParallelPR201::ChangeComandState(CPR201CommandState* pcstateNew) {
	m_pcstateCurrent = pcstateNew;
	m_pcstateCurrent->SetPrinter(this);
	m_pcstateCurrent->Initialize();
}

// get current character pitch in hi-resolution

int CParallelPR201::GetCurrentCharPitchHR() {
	int nPitchHR = 0;
	switch (GetPrintingMethod()) {
	case METHOD_HDPICA:
	case METHOD_HSPICA:
	case METHOD_PROPORTIONAL:
	case METHOD_KANJI:
	case METHOD_VKANJI:
		nPitchHR = PICA_WIDTH;
		break;
	case METHOD_ELITE:
		nPitchHR = ELITE_WIDTH;
		break;
	case METHOD_CONDENSE:
		nPitchHR = CONDENSE_WIDTH;
		break;
	}
	return nPitchHR;
}

// register horizontal-tab in hi-resolution

bool CParallelPR201::RegisterHorzTabHR(int nPosHR) {
	if (m_setHorzTabs.size() >= HORZTAB_MAX) {
		return false;
	}
	m_setHorzTabs.insert(nPosHR);
	return true;
}

// remove one horizontal-tab in hi-resolution

bool CParallelPR201::RemoveHorzTabHR(int nPosHR) {
	return m_setHorzTabs.erase(nPosHR) > 0;
}

// remove all horizontal-tabs

bool CParallelPR201::RemoveAllHorzTab() {
	m_setHorzTabs.clear();
	return true;
}

// set VFU

bool CParallelPR201::SetVFU(const std::vector<uint8_t>& vectVFUParams) {
	int nChannel;
	for (nChannel = 0; nChannel < VFU_CH_MAX; nChannel++) {
		m_asetVertTabsHR[nChannel].clear();
	}
	int i;
	for (i = 0; i < (int)vectVFUParams.size()-1; i += 2) {
		if ((vectVFUParams[i] & 0x41) == 0x41) {
			i += 2;
			break;
		}
	}
	m_asetVertTabsHR[0].insert(0);
	int nLineCount = 1;
	if (!IsExistSheetFeeder()) {
		SetVFUOfsYHR(0);
	}
	SetVFUPageHeightHR((11*GetDPI())*HIRES_Y_NAT);
	SetVFUPageBottomHR(-1);
	for (; i < (int)vectVFUParams.size()-1; i += 2) {
		if ((vectVFUParams[i] & 0x40) != 0) {
			int nPosHR = (nLineCount*GetDPI()*HIRES_Y_NAT)/6;
			for (nChannel = 0; nChannel < VFU_CH_MAX; nChannel++) {
				if ((vectVFUParams[i] & (0x01 << nChannel)) != 0) {
					m_asetVertTabsHR[nChannel].insert(nPosHR);
				}
			}
			if ((vectVFUParams[i] & 0x01) != 0) {
				if ((GetVFUPageBottomHR() < 0) &&
					((vectVFUParams[i] & 0x02) != 0))
				{
					SetVFUPageBottomHR(nPosHR);
				} else {
					SetVFUPageHeightHR(nPosHR);
					break;
				}
			}
			if (++nLineCount >= VFU_LEN_MAX) {
				SetVFUPageHeightHR(nPosHR);
				break;
			}
		}
	}
	return true;
}

// execute VFU
//
//     nChannel
//         VFU channel number(0-5)

bool CParallelPR201::ExecVFU(int nChannel) {
	if ((nChannel < 0) || (nChannel >= VFU_CH_MAX)) {
		return false;
	}
	SetDirty(true);
	int nFeedDotHR = 0,
		nFeedPage = 0;
	CTabPosSet::const_iterator itVertTab;
	if (!IsReverseFeed()) {
		itVertTab =
			m_asetVertTabsHR[nChannel].upper_bound(GetVFUOfsYHR());
		if ((itVertTab != m_asetVertTabsHR[nChannel].end()) &&
			((GetVFUPageBottomHR() < 0) ||
				(*itVertTab < GetVFUPageBottomHR())))
		{
			nFeedDotHR = *itVertTab-GetVFUOfsYHR();
		} else if (
			(GetVFUPageBottomHR() >= 0) &&
			(GetVFUOfsYHR() < GetVFUPageBottomHR()))
		{
			nFeedDotHR = GetVFUPageBottomHR()-GetVFUOfsYHR();
		} else {
			nFeedPage = 1;
		}
		if (IsExistSheetFeeder() &&
			(nFeedDotHR != 0) &&
			(GetHeadYHR()+nFeedDotHR > GetMovableAreaHeight()))
		{
			nFeedDotHR = 0;
			nFeedPage = 1;
		}
	} else {
		itVertTab =
			m_asetVertTabsHR[nChannel].lower_bound(GetVFUOfsYHR()-1);
		if ((itVertTab != m_asetVertTabsHR[nChannel].begin()) &&
			(m_asetVertTabsHR[nChannel].size() > 0))
		{
			itVertTab--;
			nFeedDotHR = *itVertTab-GetVFUOfsYHR();
		} else if (GetVFUOfsYHR() > 0) {
			nFeedDotHR = -GetVFUOfsYHR();
		} else {
			nFeedDotHR = -GetVFUPageHeightHR();
			if (GetVFUPageBottomHR() >= 0) {
				nFeedDotHR += GetVFUPageBottomHR();
			} else if (m_asetVertTabsHR[nChannel].size() > 0) {
				itVertTab = m_asetVertTabsHR[nChannel].end();
				itVertTab--;
				nFeedDotHR += *itVertTab;
			}
		}
	}
	bool bResult = true;
	if (nFeedPage != 0) {
		bResult = DoPageFeed(nFeedPage);
	} else if (nFeedDotHR != 0) {
		bResult = DoDotFeedHR(nFeedDotHR);
	}
	return bResult;
}

// output text(single-byte)

bool CParallelPR201::OutputTextSB(uint8_t btText) {
	int nFontType = GetCurrentFontType(false),
		nPitchType = CPrinterTextObject::PITCH_FIXED,
		nCharWidthHR = PICA_WIDTH,
		nCharHeight = NORMAL_HEIGHT,
		nVOfs = 0,
		nLeftGapHR = GetFixDotSpaceLeft()*HIRES_X,
		nRightGapHR = GetFixDotSpaceRight()*HIRES_X,
		nLineType = GetCurrentLineType();
	const CPrinterGaiji* pGaiji = NULL;
	bool bHeadBack = false,
		bDrawLine = false;
	int nCharType = CPrinterTextObject::CHAR_ANK;
	uint16_t wText = btText;
	switch (GetPrintingMethod()) {
	case METHOD_HDPICA:
	case METHOD_HSPICA:
		nCharWidthHR = PICA_WIDTH;
		break;
	case METHOD_ELITE:
		nCharWidthHR = ELITE_WIDTH;
		break;
	case METHOD_CONDENSE:
		nCharWidthHR = CONDENSE_WIDTH;
		break;
	case METHOD_PROPORTIONAL:
		nPitchType = CPrinterTextObject::PITCH_VARIABLE;
		nCharWidthHR = PROPORTIONAL_WIDTH;
		switch (btText) {
		case 0x20: // (space)
		case 0x22: // "
		case 0x27: // '
		case 0x2C: // ,
		case 0x2E: // .
		case 0x3A: // :
		case 0x3B: // ;
		case 0x5E: // ^
		case 0x60: // `
		case 0x7C: // |
			nCharWidthHR /= 2;
			break;
		case 0x21: // !
		case 0x28: // (
		case 0x29: // )
		case 0x2A: // *
		case 0x2B: // +
		case 0x2D: // -
		case 0x2F: // /
		case 0x30: // 0
		case 0x31: // 1
		case 0x32: // 2
		case 0x33: // 3
		case 0x34: // 4
		case 0x35: // 5
		case 0x36: // 6
		case 0x37: // 7
		case 0x38: // 8
		case 0x39: // 9
		case 0x3C: // <
		case 0x3D: // =
		case 0x3E: // >
		case 0x3F: // ?
		case 0x49: // I
		case 0x5B: // [
		case 0x5D: // ]
		case 0x5F: // _
		case 0x69: // i
		case 0x7B: // {
		case 0x7D: // }
		case 0x7E: // ~
			nCharWidthHR = (nCharWidthHR*3)/4;
			break;
		}
		break;
	}
	if (IsDownloadCharUse()) {
		uint16_t wCode = 0;
		switch (GetPrintingMethod()) {
		case METHOD_HDPICA:
			wCode = 0x0000;
			break;
		case METHOD_HSPICA:
			wCode = 0x0100;
			break;
		case METHOD_ELITE:
			wCode = 0x0200;
			break;
		case METHOD_CONDENSE:
			wCode = 0x0300;
			break;
		case METHOD_PROPORTIONAL:
			wCode = 0x0400;
			break;
		}
		if (IsHiraganaMode()) {
			wCode = (uint16_t)(wCode+0x0500);
		}
		wCode = (uint16_t)(wCode+btText);
		CGaijiSet::iterator itGaiji = m_setGaijisSB.find(wCode);
		if (itGaiji != m_setGaijisSB.end()) {
			nCharType = CPrinterTextObject::CHAR_GAIJI;
			pGaiji = &(*itGaiji);
			if (GetPrintingMethod() == METHOD_PROPORTIONAL) {
				nCharWidthHR = pGaiji->GetDotCX()*HIRES_X;
			}
		}
	}
	if (nCharType != CPrinterTextObject::CHAR_GAIJI) {
		if (((btText >= 0x80) && (btText <= 0x9F)) ||
			(btText >= 0xE0))
		{
			nCharType = CPrinterTextObject::CHAR_CG;
			if (btText < 0xE0) {
				wText = (uint16_t)(wText-0x60);
			} else {
				wText = (uint16_t)(wText-0xA0);
			}
		} else if (
			IsHiraganaMode() &&
			(btText >= 0xA0) && (btText <= 0xDF))
		{
			nCharType = CPrinterTextObject::CHAR_HIRAGANA;
			wText = (uint16_t)(wText-0x80);
		}
	}
	if (((nCharType == CPrinterTextObject::CHAR_ASCII) ||
			(nCharType == CPrinterTextObject::CHAR_ANK) ||
			(nCharType == CPrinterTextObject::CHAR_GAIJI)) &&
		(wText >= 0x20) && (wText <= 0x7E))
	{
		nFontType = GetCurrentFontType(true);
	}
	switch (GetScriptMode()) {
	case SCRIPT_SUPER:
		nCharHeight /= 2;
		if (nLineType != CPrinterTextObject::LINE_NONE) {
			bDrawLine = true;
		}
		break;
	case SCRIPT_SUB:
		nCharHeight /= 2;
		nVOfs = nCharHeight;
		if (nLineType != CPrinterTextObject::LINE_NONE) {
			bDrawLine = true;
		}
		break;
	}
	SetHalfVertKanjiCombinationMode(false);
	SetSmallKanjiCombinationMode(false);
	if (bDrawLine) {
		if (!OutputText(
				nFontType,
				nPitchType,
				0,
				CPrinterTextObject::CHAR_NULL,
				nCharWidthHR, NORMAL_HEIGHT,
				nLeftGapHR, nRightGapHR,
				nLineType,
				0,
				max_value(GetHorzZoom(), 1),
				max_value(GetVertZoom(), 1),
				false,
				NULL))
		{
			return false;
		}
		nLineType = CPrinterTextObject::LINE_NONE;
		bHeadBack = true;
	}
	return OutputText(
		nFontType, nPitchType,
		wText,
		nCharType,
		nCharWidthHR, nCharHeight,
		nLeftGapHR, nRightGapHR,
		nLineType,
		nVOfs,
		max_value(GetHorzZoom(), 1),
		max_value(GetVertZoom(), 1),
		bHeadBack,
		pGaiji);
}

// output text(double-byte)

bool CParallelPR201::OutputTextDB(uint16_t wText) {
	uint8_t btTextHi = (uint8_t)(wText >> 8),
		btTextLo = (uint8_t)wText;
	bool bHalf = (btTextHi == 0);
	bool bVKanji = (GetPrintingMethod() == METHOD_VKANJI);
	if (bVKanji && bHalf &&
		!IsHalfKanjiVertMode())
	{
		bVKanji = false;
	}
	int nFontType = GetCurrentFontType(false) |
			(bVKanji? CPrinterTextObject::FONT_VERT: 0),
		nPitchType = CPrinterTextObject::PITCH_FIXED,
		nCharWidthHR = GetKanjiWidthHR(),
		nCharPitchHR = max_value(GetKanjiPitchHR(), GetKanjiWidthHR()),
		nCharHeight = NORMAL_HEIGHT,
		nVOfs = 0,
		nLineType = GetCurrentLineType(),
		nHorzZoom = GetHorzZoom(),
		nVertZoom = GetVertZoom();
	const CPrinterGaiji* pGaiji = NULL;
	int nCharType;
	bool bHeadBack = false,
		bDrawLine = false;
	if (!bHalf) {
		nCharType = CPrinterTextObject::CHAR_KANJI;
		if (((btTextHi >= 0x76) && (btTextHi <= 0x77) &&
				(btTextLo >= 0x20) && (btTextLo <= 0x7F)) ||
			((btTextHi == 0x78) &&
				(btTextLo >= 0x20) && (btTextLo <= 0x5F)))
		{
			CGaijiSet::iterator itGaiji = m_setGaijisDB.find(wText);
			if (itGaiji != m_setGaijisDB.end()) {
				nCharType = CPrinterTextObject::CHAR_GAIJI;
				pGaiji = &(*itGaiji);
			} else {
				wText = 0x2121;
			}
		}
		if (nHorzZoom < 1) {
			if ((btTextHi >= 0x30) && (btTextHi <= 0x7F)) {
				if (bVKanji) {
					nHorzZoom = 1;
				}
			} else if ((btTextHi < 0x21) || (btTextHi > 0x27)) {
				nHorzZoom = 1;
			}
		}
		if (nVertZoom < 1) {
			if ((btTextHi >= 0x30) && (btTextHi <= 0x7F)) {
				if (!bVKanji) {
					nVertZoom = 1;
				}
			} else if ((btTextHi < 0x21) || (btTextHi > 0x27)) {
				nVertZoom = 1;
			}
		}
		if (nVertZoom < 1) {
			if (!IsSmallKanjiCombinationMode()) {
				switch (GetSmallKanjiVertPos()) {
				case SMALLKANJI_V_HI:
					break;
				case SMALLKANJI_V_MID:
					nVOfs += nCharHeight/2;
					break;
				case SMALLKANJI_V_LO:
					nVOfs += nCharHeight;
					break;
				}
				if (nLineType != CPrinterTextObject::LINE_NONE) {
					bDrawLine = true;
				}
			} else if (!IsSmallKanjiCombinating()) {
				SetSmallKanjiCombinating(true);
				nVOfs += nCharHeight;
				if (nLineType != CPrinterTextObject::LINE_NONE) {
					bDrawLine = true;
				}
			} else {
				SetSmallKanjiCombinationMode(false);
				bHeadBack = true;
				nLineType = CPrinterTextObject::LINE_NONE;
			}
		} else {
			SetSmallKanjiCombinationMode(false);
		}
		SetHalfVertKanjiCombinationMode(false);
	} else {
		if (wText < 0x80) {
			nCharType = CPrinterTextObject::CHAR_ASCII;
		} else if (wText < 0xA0) {
			wText = (uint16_t)(wText-0x60);
			nCharType = CPrinterTextObject::CHAR_HIRAGANA;
		} else if (wText < 0xE0) {
			wText = (uint16_t)(wText-0x80);
			nCharType = CPrinterTextObject::CHAR_KATAKANA;
		} else {
			wText = (uint16_t)(wText-0xA0);
			nCharType = CPrinterTextObject::CHAR_HIRAGANA;
		}
		if (!bVKanji) {
			nCharWidthHR /= 2;
			nCharPitchHR /= 2;
			SetHalfVertKanjiCombinationMode(false);
		} else {
			if (!IsHalfVertKanjiCombinationMode()) {
				nVOfs += nCharHeight/4;
				if (nLineType != CPrinterTextObject::LINE_NONE) {
					bDrawLine = true;
				}
			} else if (!IsHalfVertKanjiCombinating()) {
				SetHalfVertKanjiCombinating(true);
				nVOfs += nCharHeight/2;
				if (nLineType != CPrinterTextObject::LINE_NONE) {
					bDrawLine = true;
				}
			} else {
				SetHalfVertKanjiCombinationMode(false);
				bHeadBack = true;
				nLineType = CPrinterTextObject::LINE_NONE;
			}
			nCharHeight /= 2;
		}
		if (nHorzZoom < 1) {
			nHorzZoom = 1;
		}
		if (nVertZoom < 1) {
			nVertZoom = 1;
		}
		SetSmallKanjiCombinationMode(false);
	}
	int nGapHR = nCharPitchHR-nCharWidthHR,
		nLeftGapHR = (nGapHR+1)/2+GetFixDotSpaceLeft()*HIRES_X,
		nRightGapHR = nGapHR/2+GetFixDotSpaceRight()*HIRES_X;
	if (bDrawLine) {
		if (!OutputText(
				nFontType,
				nPitchType,
				0,
				CPrinterTextObject::CHAR_NULL,
				nCharWidthHR, NORMAL_HEIGHT,
				nLeftGapHR, nRightGapHR,
				nLineType,
				0,
				nHorzZoom,
				max_value(nVertZoom, 1),
				false,
				NULL))
		{
			return false;
		}
		nLineType = CPrinterTextObject::LINE_NONE;
		bHeadBack = true;
	}
	return OutputText(
		nFontType, nPitchType,
		wText,
		nCharType,
		nCharWidthHR, nCharHeight,
		nLeftGapHR, nRightGapHR,
		nLineType,
		nVOfs,
		nHorzZoom,
		nVertZoom,
		bHeadBack,
		pGaiji);
}

// output null text

bool CParallelPR201::OutputTextNull(int nCharWidthHR, bool bHorzZoom) {
	return OutputText(
		GetCurrentFontType(true),
		CPrinterTextObject::PITCH_FIXED,
		0,
		CPrinterTextObject::CHAR_NULL,
		nCharWidthHR, NORMAL_HEIGHT,
		0, 0,
		GetCurrentLineType(),
		0,
		bHorzZoom? max_value(GetHorzZoom(), 1): 1,
		max_value(GetVertZoom(), 1),
		false,
		NULL);
}

// output dot image graphics

bool CParallelPR201::OutputDotImage(
	uint8_t btImageKind,
	int cxDot,
	const std::vector<uint8_t>& vectImageData)
{
	int cyDot = 0, nVBytes = 0;
	switch (btImageKind) {
	case 0x53: // ESC S : draw 8 bit dot image graphics
		cyDot = 16;
		nVBytes = 1;
		break;
	case 0x49: // ESC I : draw 16 bit dot image graphics
		cyDot = 16;
		nVBytes = 2;
		break;
	case 0x4A: // ESC J : draw 24 bit dot image graphics
		cyDot = 24;
		nVBytes = 3;
		break;
	}
	int nDotGap = 1;
	if ((btImageKind == 0x53) &&
		IsCopyMode())
	{
		nDotGap = 2;
	}
	if (GetHorzZoom() > 1) {
		nDotGap *= GetHorzZoom();
	}
	int xDot = 0;
	while (xDot < cxDot) {
		int nPrintDot = cxDot-xDot;
		bool bCRLF = false;
		if (GetHeadXHR()+nPrintDot*nDotGap*HIRES_X >
				GetRightMarginHR())
		{
			nPrintDot = (GetRightMarginHR()-GetHeadXHR())/
				(nDotGap*HIRES_X);
			bCRLF = true;
		}
		if (nPrintDot > 0) {
			CPrinterImageObject* pobjImage = new CPrinterImageObject(
				GetHeadX(), GetHeadY(),
				GetDPI(),
				GetDPI(), GetDPI(),
				nPrintDot*nDotGap,
				cyDot);
			for (int nDot = 0; nDot < nPrintDot; nDot++, xDot++) {
				for (int yDot = 0; yDot < cyDot; yDot += 8) {
					uint8_t btData = 0;
					switch (btImageKind) {
					case 0x53: // ESC S : draw 8 bit dot image graphics
						btData = vectImageData[xDot*nVBytes];
						if (yDot > 0) {
							btData >>= 4;
						}
						btData = (uint8_t)(
							(btData & 0x01) |
							((btData & 0x02) << 1) |
							((btData & 0x04) << 2) |
							((btData & 0x08) << 3));
						if (IsCopyMode()) {
							btData |= (uint8_t)(btData << 1);
						}
						break;
					case 0x49: // ESC I : draw 16 bit dot image graphics
					case 0x4A: // ESC J : draw 24 bit dot image graphics
						btData = vectImageData[xDot*nVBytes+yDot/8];
						break;
					}
					pobjImage->GetImageData()[
							xDot*nDotGap*((cyDot+7)/8)+yDot/8] = btData;
				}
			}
			AddPrinterObject(pobjImage);
			HeadMove(nPrintDot*nDotGap);
		} else if (GetHeadXHR() <= GetLeftMarginHR()) {
			return false;
		}
		if (bCRLF) {
			CarriageReturn();
			LineFeed();
		}
		xDot += nPrintDot;
	}
	return true;
}

// output repeated dots

bool CParallelPR201::OutputDotRepeat(
	uint8_t btImageKind,
	int cxDot,
	const std::vector<uint8_t>& vectRepeatData)
{
	int cyDot = 0;
	switch (btImageKind) {
	case 0x56: // ESC V : repeat 8 bit dot
		cyDot = 16;
		break;
	case 0x57: // ESC W : repeat 16 bit dot
		cyDot = 16;
		break;
	case 0x55: // ESC U : repeat 24 bit dot
		cyDot = 24;
		break;
	}
	int nDotGap = 1;
	if (GetHorzZoom() > 1) {
		nDotGap *= GetHorzZoom();
	}
	int xDot = 0;
	while (xDot < cxDot) {
		int nPrintDot = cxDot-xDot;
		bool bCRLF = false;
		if (GetHeadXHR()+nPrintDot*nDotGap*HIRES_X >
			GetRightMarginHR())
		{
			nPrintDot = (GetRightMarginHR()-GetHeadXHR())/
				(nDotGap*HIRES_X);
			bCRLF = true;
		}
		if (nPrintDot > 0) {
			CPrinterImageObject* pobjImage = new CPrinterImageObject(
				GetHeadX(), GetHeadY(),
				GetDPI(),
				GetDPI(), GetDPI(),
				nPrintDot*nDotGap,
				cyDot);
			for (int nDot = 0; nDot < nPrintDot; nDot++, xDot++) {
				for (int yDot = 0; yDot < cyDot; yDot += 8) {
					uint8_t btData = 0;
					switch (btImageKind) {
					case 0x56: // ESC V : repeat 8 bit dot
						btData = vectRepeatData[0];
						if (yDot > 0) {
							btData >>= 4;
						}
						btData = (uint8_t)(
							(btData & 0x01) |
							((btData & 0x02) << 1) |
							((btData & 0x04) << 2) |
							((btData & 0x08) << 3));
						if (IsCopyMode()) {
							btData |= (uint8_t)(btData << 1);
						}
						break;
					case 0x57: // ESC W : repeat 16 bit dot
					case 0x55: // ESC U : repeat 24 bit dot
						btData = vectRepeatData[yDot/8];
						break;
					}
					pobjImage->GetImageData()[
							xDot*nDotGap*((cyDot+7)/8)+yDot/8] = btData;
				}
			}
			AddPrinterObject(pobjImage);
			HeadMove(nPrintDot*nDotGap);
		} else if (GetHeadXHR() <= GetLeftMarginHR()) {
			return false;
		}
		if (bCRLF) {
			CarriageReturn();
			LineFeed();
		}
		xDot += nPrintDot;
	}
	return true;
}

// register gaiji

bool CParallelPR201::RegisterGaiji(const CPrinterGaiji& gaijiRegist) {
	if (gaijiRegist.GetCode() < 0x7600) {
		m_setGaijisSB.erase(gaijiRegist);
		if (m_setGaijisSB.size() >= SBGAIJI_MAX) {
			return false;
		}
		m_setGaijisSB.insert(gaijiRegist);
	} else {
		m_setGaijisDB.erase(gaijiRegist);
		if (m_setGaijisDB.size() >= DBGAIJI_MAX) {
			return false;
		}
		m_setGaijisDB.insert(gaijiRegist);
	}
	return true;
}

// remove all gaiji(single-byte)

bool CParallelPR201::RemoveAllSBGaiji() {
	m_setGaijisSB.clear();
	return true;
}

// remove all gaiji(double-byte)

bool CParallelPR201::RemoveAllDBGaiji() {
	m_setGaijisDB.clear();
	return true;
}
