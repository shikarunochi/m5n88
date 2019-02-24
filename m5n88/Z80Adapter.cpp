////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "Z80Adapter.h"

////////////////////////////////////////////////////////////
// CZ80Adapter

#ifdef Z80CFG_USE_TEMPLATE
#define CZ80 CZ80Adapter

#include "Z80ExecutorBase.h"
#include "Z80DisAssembler.h"

////////////////////////////////////////////////////////////
// construct/destruct

CZ80Adapter::CZ80Adapter() {
}

CZ80Adapter::~CZ80Adapter() {
}

////////////////////////////////////////////////////////////
// dis-assemble

void CZ80Adapter::FormatMnemonic(const char* pszFormat, ...) {
	va_list argList;
	va_start(argList, pszFormat);
	FormatMnemonicV(pszFormat, argList);
	va_end(argList);
}

int CZ80Adapter::DisAssemble() {
	FormatMnemonic("???");
	SetStepExecuteOpCode(false);
	SetStepExecuteOpCode2(false);
	CZ80DisAssembler z80DisAssembler(*this);
	return z80DisAssembler.ExecuteOneOpCode();
}
#endif // Z80CFG_USE_TEMPLATE
