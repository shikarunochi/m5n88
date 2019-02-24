////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Template_DEFINED
#define Z80Template_DEFINED

////////////////////////////////////////////////////////////
// include

#include "Z80Config.h"

////////////////////////////////////////////////////////////
// declare

#ifdef Z80CFG_USE_TEMPLATE
#define CZ80_1	TZ80<1, 4096, 1>
#define CZ80_2	TZ80<2, 4096, 1>
#endif // Z80CFG_USE_TEMPLATE

#endif // Z80Template_DEFINED
