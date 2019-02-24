////////////////////////////////////////////////////////////
// Z80 Emulator Class Library
//
// Written by Manuke

#ifndef Z80Config_DEFINED
#define Z80Config_DEFINED

////////////////////////////////////////////////////////////
// environment settings

// decide in accordance with CPU characteristic

#ifdef X88_BYTEORDER_LITTLE_ENDIAN

#define Z80CFG_LITTLE_ENDIAN

#else // X88_BYTEORDER_BIG_ENDIAN

#define Z80CFG_BIG_ENDIAN

#endif // X88_BYTEORDER

// decide I/O address width

#define Z80CFG_IOADDR_WIDTH_8
// #define Z80CFG_IOADDR_WIDTH_16

// decide whether the table used for flag calculation

// #define Z80CFG_NOUSE_FLAGTBL
#define Z80CFG_USE_FLAGTBL

// decide whether Z80 class library is made template mode

//#define Z80CFG_NOUSE_TEMPLATE
#define Z80CFG_USE_TEMPLATE

// decide whether the compiler is supporting template explicit

#ifdef X88_COMPILER_TEMPLATE_EXPLICIT_SUPPORT

#define Z80CFG_TEMPLATE_EXPLICIT_SUPPORT

#else // X88_COMPILER_TEMPLATE_EXPLICIT_UNSUPPORT

#define Z80CFG_TEMPLATE_EXPLICIT_UNSUPPORT

#endif // X88_COMPILER_TEMPLATE_EXPLICIT

// decide whether the compiler declaring static variable

#ifdef X88_COMPILER_TEMPLATE_STATICVAR_NORMAL

#define Z80CFG_TEMPLATE_STATICVAR_NORMAL

#else // X88_COMPILER_TEMPLATE_STATICVAR_SPECIAL

#define Z80CFG_TEMPLATE_STATICVAR_SPECIAL

#endif // X88_COMPILER_TEMPLATE_STATICVAR

////////////////////////////////////////////////////////////
// others

#ifdef Z80CFG_USE_TEMPLATE

#define Z80STATIC static
#define Z80THIS m_pThis

#ifdef Z80CFG_TEMPLATE_EXPLICIT_SUPPORT

#define Z80TEMPLATE_EXPLICIT_AW template <>
#define Z80TEMPLATE_EXPLICIT_SP template <>

#else // Z80CFG_TEMPLATE_EXPLICIT_UNSUPPORT

#define Z80TEMPLATE_EXPLICIT_AW
#define Z80TEMPLATE_EXPLICIT_SP

#endif // Z80CFG_TEMPLATE_EXPLICIT

#else // Z80CFG_NOUSE_TEMPLATE

#define Z80STATIC
#define Z80THIS this

#ifdef Z80CFG_TEMPLATE_EXPLICIT_SUPPORT

#define Z80TEMPLATE_EXPLICIT_AW template <>
#define Z80TEMPLATE_EXPLICIT_SP

#else // Z80CFG_TEMPLATE_EXPLICIT_UNSUPPORT

#define Z80TEMPLATE_EXPLICIT_AW
#define Z80TEMPLATE_EXPLICIT_SP

#endif // Z80CFG_TEMPLATE_EXPLICIT

#endif // Z80CFG_USE/NOUSE_TEMPLATE

#endif // Z80Config_DEFINED
