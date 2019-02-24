////////////////////////////////////////////////////////////
// GUID Declare
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#if defined(WIN32) && !defined(WIN_GTK)

#define INITGUID
#define DIRECTINPUT_VERSION 0x0300

#include <ddraw.h>
#include <dinput.h>

#endif // WIN32 && !WIN_GTK
