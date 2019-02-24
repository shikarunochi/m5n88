////////////////////////////////////////////////////////////
// X88000 View Window
//
// Written by Manuke

#ifndef X88View_DEFINED
#define X88View_DEFINED

////////////////////////////////////////////////////////////
// declare

class CX88View;

////////////////////////////////////////////////////////////
// include

#include "X88000.h"

////////////////////////////////////////////////////////////
// declaration of CX88View

class CX88View {
// enum
protected:
	// timer
	enum {
		TIMER_ID = 1
	};

public:
	// window size
	enum {
		CTRL_ID         = 1,
		CXWINDOWDEFAULT = 640,
		CYWINDOWDEFAULT = 400,
		CXWINDOWMIN     = 64,
		CYWINDOWMIN     = 8
	};

// attribute
protected:
	// X88000 object
	static CX88000* m_pX88k;

	// window handle
	//static CX88WndHandle m_hWnd;

	// stretch drawing
	static bool m_bStretch;

#ifdef X88_GUI_WINDOWS

	// frame clear
	static bool m_bFrameClear;
	// timer id
	static UINT_PTR m_nTimerID;

#elif defined(X88_GUI_GTK)

	// timeout id
	static gint m_nTimeOutID;
	// GC
	static GdkGC* m_pGC;
	// color map
	static GdkRgbCmap m_rgbcmap;

#ifdef X88_GUI_GTK_USEIMAGE

	// visual for drawing
	static GdkVisual* m_pvisualDraw;
	// image for drawing
	static GdkImage* m_pimageDraw;

#endif // X88_GUI_GTK_USEIMAGE

#endif // X88_GUI

public:
	// X88000 object
	static CX88000& X88k() {
		return *m_pX88k;
	}
	// get window handle
	//static CX88WndHandle GetWndHandle() {
	//	return m_hWnd;
	//}

#ifdef X88_GUI_WINDOWS

	// set frame clear
	static void SetFrameClear(bool bFrameClearNew) {
		m_bFrameClear = bFrameClearNew;
	}

#endif // X88_GUI

// create & destroy
public:
	// default constructor
	CX88View();
	// destructor
	~CX88View();

	// create
	//static bool Create(CX88WndHandle hwndFrame, CX88000& x88k);
	static bool Create(CX88000& x88k);
	// destroy
	static bool Destroy();

// implementation
protected:

#ifdef X88_GUI_WINDOWS

	// window procedure
	static LRESULT CALLBACK WndProc(
		HWND hwnd, UINT nMessage, WPARAM wParam, LPARAM lParam);

#elif defined(X88_GUI_GTK)

	// destroy signal
	static void OnDestroySignal(
		GtkWidget* pWidget, gpointer pData);
	// expose event
	static gboolean OnExposeEvent(
		GtkWidget* pWidget,
		GdkEventExpose* pEvent,
		gpointer pData);
	// time out callback
	static gboolean TimeOutCallback(gpointer pData);

#endif // X88_GUI

// operation
protected:

#ifdef X88_GUI_WINDOWS

	// draw to device-context
	static void DrawDC(HDC hdc);

#elif defined(X88_GUI_GTK)

	// draw window
	static void DrawWindow();

#endif // X88_GUI

	static void DrawWindow();
public:

#ifdef X88_GUI_WINDOWS

	// draw surface
	static void DrawSurface();
	// update palette
	static void UpdatePalette(bool bUpdateAll);

#endif // X88_GUI

	// restart timer
	static void RestartTimer();
	static bool TimeOutCallback();
};

#endif // X88View_DEFINED
