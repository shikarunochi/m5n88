////////////////////////////////////////////////////////////
// X88000 View Window
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "X88View.h"

////////////////////////////////////////////////////////////
// implementation of CX88View

////////////////////////////////////////////////////////////
// attribute

// X88000 object

CX88000* CX88View::m_pX88k;

// window handle

//CX88WndHandle CX88View::m_hWnd;

// stretch drawing

bool CX88View::m_bStretch;

#ifdef X88_GUI_WINDOWS

// frame clear

bool CX88View::m_bFrameClear;

// timer id

UINT_PTR CX88View::m_nTimerID;

#elif defined(X88_GUI_GTK)

// timeout id

gint CX88View::m_nTimeOutID;

// GC

GdkGC* CX88View::m_pGC;

// color map

GdkRgbCmap CX88View::m_rgbcmap;

#ifdef X88_GUI_GTK_USEIMAGE

// visual for drawing

GdkVisual* CX88View::m_pvisualDraw;

// image for drawing

GdkImage* CX88View::m_pimageDraw;

#endif // X88_GUI_GTK_USEIMAGE

#endif // X88_GUI

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CX88View::CX88View() {
	m_pX88k = NULL;
//	m_hWnd = NULL;
	m_bStretch = false;

#ifdef X88_GUI_WINDOWS

	m_bFrameClear = false;
	m_nTimerID = 0;

#elif defined(X88_GUI_GTK)

	m_nTimeOutID = 0;
	m_pGC = NULL;
	memset(&m_rgbcmap, 0, sizeof(m_rgbcmap));

#ifdef X88_GUI_GTK_USEIMAGE

	m_pvisualDraw = NULL;
	m_pimageDraw = NULL;

#endif // X88_GUI_GTK_USEIMAGE

#endif // X88_GUI

}

// destructor

CX88View::~CX88View() {
//	if (GetWndHandle() != NULL) {
//		Destroy();
//	}
}

// create

//bool CX88View::Create(CX88WndHandle hwndFrame, CX88000& x88k) {
bool CX88View::Create( CX88000& x88k) {
	//if (GetWndHandle() != NULL) {
	//	return false;
	//}
	m_pX88k = &x88k;

#ifdef X88_GUI_WINDOWS

	const char* pszViewName = "X88View";
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = X88k().GetInstanceHandle();
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = pszViewName;
	RegisterClass(&wc);
	CreateWindow(
		pszViewName, pszViewName,
		WS_CHILD | WS_VISIBLE,
		0, 0, 640, 400,
		hwndFrame, (HMENU)CTRL_ID, X88k().GetInstanceHandle(),
		NULL);

#elif defined(X88_GUI_GTK)

	(void)hwndFrame;

	m_hWnd = gtk_drawing_area_new();
	if (GetWndHandle() != NULL) {
		gtk_widget_set_size_request(
			GetWndHandle(),
			640, 400);
		g_signal_connect(
			GetWndHandle(), "destroy",
			G_CALLBACK(OnDestroySignal), NULL);
		g_signal_connect(
			GetWndHandle(), "expose_event",
			G_CALLBACK(OnExposeEvent), NULL);
		gtk_widget_set_events(
			GetWndHandle(),
			gtk_widget_get_events(GetWndHandle()) |
				GDK_EXPOSURE_MASK);
		m_nTimeOutID = g_timeout_add(
			X88k().GetScreenUpdateElapse(),
			TimeOutCallback, NULL);
	}

#endif // X88_GUI

	//return GetWndHandle() != NULL;
	return true;
}

// destroy

bool CX88View::Destroy() {
	//if (GetWndHandle() == NULL) {
	//	return false;
	//}

#ifdef X88_GUI_WINDOWS

	DestroyWindow(GetWndHandle());

#elif defined(X88_GUI_GTK)

	g_object_unref(GetWndHandle());
	m_hWnd = NULL;

#ifdef X88_GUI_GTK_USEIMAGE

	if (m_pvisualDraw != NULL) {
		g_object_unref(m_pvisualDraw);
		m_pvisualDraw = NULL;
	}
	if (m_pimageDraw != NULL) {
		g_object_unref(m_pimageDraw);
		m_pimageDraw = NULL;
	}

#endif // X88_GUI_GTK_USEIMAGE

#endif // X88_GUI

	//return GetWndHandle() == NULL;
	return true;
}

////////////////////////////////////////////////////////////
// implementation

#ifdef X88_GUI_WINDOWS

// window procedure

LRESULT CALLBACK CX88View::WndProc(
	HWND hwnd, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;
	bool bDWP = false;
	switch (nMessage) {
	case WM_NCCREATE:
		m_hWnd = hwnd;
		bDWP = TRUE;
		break;
	case WM_NCDESTROY:
		m_hWnd = NULL;
		bDWP = TRUE;
		break;
	case WM_CREATE:
		m_nTimerID = SetTimer(hwnd, TIMER_ID, X88k().GetScreenUpdateElapse(), NULL);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, m_nTimerID);
		break;
	case WM_SIZE:
		m_bStretch = (lParam != MAKELPARAM(CXWINDOWDEFAULT, CYWINDOWDEFAULT));
		break;
	case WM_PALETTECHANGED:
		if ((HWND)wParam == hwnd) {
			break;
		}
		// no break
	case WM_QUERYNEWPALETTE:
		UpdatePalette(true);
		break;
	case WM_TIMER:
		{ // Dummy Block
			bool bUpdate = X88k().GetScreenDrawer().RatchText();
			if (bUpdate) {
				X88k().GetScreenDrawer().DrawScreen();
				if (X88k().GetScreenDrawer().UpdatePalette()) {
					UpdatePalette(false);
				}
			} else {
				bUpdate = X88k().GetScreenDrawer().UpdatePalette();
				if (bUpdate) {
					UpdatePalette(false);
				}
			}
			if (X88k().PC88().Z80Main().IsVABScreenActive()) {
				bUpdate = X88k().GetScreenDrawer().DrawScreenVAB();
			}
			if (X88k().GetDX().IsDirectDrawActive()) {
				bUpdate |= m_bFrameClear;
			}
			if (bUpdate) {
				if (!X88k().GetDX().IsDirectDrawActive()) {
					InvalidateRect(hwnd, NULL, FALSE);
					UpdateWindow(hwnd);
				} else {
					DrawSurface();
				}
			}
		}
		break;
	case WM_PAINT:
		{ // dummy block
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			DrawDC(hdc);
			EndPaint(hwnd, &ps);
		}
		break;
	default:
		bDWP = true;
		break;
	}
	return bDWP? DefWindowProc(hwnd, nMessage, wParam, lParam): lResult;
}

#elif defined(X88_GUI_GTK)

// destroy signal

void CX88View::OnDestroySignal(
	GtkWidget* /*pWidget*/, gpointer /*pData*/)
{
	g_source_remove(m_nTimeOutID);
	m_nTimeOutID = 0;
	if (m_pGC != NULL) {
		g_object_unref(m_pGC);
		m_pGC = NULL;
	}
}

// expose event

gboolean CX88View::OnExposeEvent(
	GtkWidget* /*pWidget*/, GdkEventExpose* /*pEvent*/, gpointer /*pData*/)
{
	DrawWindow();
	return FALSE;
}

// time out callback

gboolean CX88View::TimeOutCallback(gpointer /*pData*/) {
	bool bUpdate = X88k().GetScreenDrawer().RatchText();
	if (bUpdate) {
		X88k().GetScreenDrawer().DrawScreen();
		X88k().GetScreenDrawer().UpdatePalette();
	} else {
		bUpdate = X88k().GetScreenDrawer().UpdatePalette();
	}
	if (X88k().PC88().Z80Main().IsVABScreenActive()) {
		bUpdate = X88k().GetScreenDrawer().DrawScreenVAB();
	}
	if (bUpdate) {
		if (GTK_WIDGET_DRAWABLE(GetWndHandle())) {
			DrawWindow();
		}
	}
	return TRUE;
}

#endif // X88_GUI

////////////////////////////////////////////////////////////
// operation

#ifdef X88_GUI_WINDOWS

// draw to device-context

void CX88View::DrawDC(HDC hdc) {
	uint8_t* pbtScreenDataBits;
	BITMAPINFO* pbmiScreen;
	if (!X88k().PC88().Z80Main().IsVABScreenActive()) {
		pbtScreenDataBits = X88k().GetScreenDrawer().GetScreenDataBits();
		pbmiScreen = X88k().GetScreenDrawer().GetScreenBitmapInfo();
	} else {
		pbtScreenDataBits = X88k().GetScreenDrawer().GetScreenDataBits2();
		pbmiScreen = X88k().GetScreenDrawer().GetScreenBitmapInfo2();
	}
	if (pbtScreenDataBits == NULL) {
		return;
	}
	if (!m_bStretch || X88k().GetDX().IsDirectDrawActive()) {
		SetDIBitsToDevice(
			hdc,
			0, 0,
			640, 400,
			0, 0,
			0, 400,
			pbtScreenDataBits,
			pbmiScreen,
			DIB_RGB_COLORS);
	} else {
		SetStretchBltMode(hdc, STRETCH_DELETESCANS);
		RECT rectClient;
		GetClientRect(GetWndHandle(), &rectClient);
		StretchDIBits(
			hdc,
			0, 0, rectClient.right, rectClient.bottom,
			0, 0, 640, 400,
			pbtScreenDataBits,
			pbmiScreen,
			DIB_RGB_COLORS,
			SRCCOPY);
	}
}

#elif defined(X88_GUI_GTK)

// draw window

void CX88View::DrawWindow() {
	GdkColor* pColorTable = X88k().GetScreenDrawer().GetColorTable();
	gboolean abSuccesses[CX88ScreenDrawer::COLOR_COUNT];
	GdkColormap* pSysColormap = gdk_colormap_get_system();
	gdk_colormap_alloc_colors(
		pSysColormap,
		pColorTable,
		CX88ScreenDrawer::COLOR_COUNT,
		FALSE, FALSE,
		abSuccesses);
	for (int i = 0; i < CX88ScreenDrawer::COLOR_COUNT; i++) {
		m_rgbcmap.colors[i] = (guint32)(
			(((guint32)pColorTable[i].red & 0xFF00) << 8) |
			((guint32)pColorTable[i].green & 0xFF00) |
			((guint32)pColorTable[i].blue >> 8));
	}
	if (m_pGC == NULL) {
		m_pGC = gdk_gc_new(GetWndHandle()->window);

#ifdef X88_GUI_GTK_USEIMAGE

		if (m_pvisualDraw == NULL) {
			GList* pVisuals = gdk_list_visuals();
			GList* pTmpVisuals = pVisuals;
			int nBestScore = 0;
			while (pTmpVisuals != NULL) {
				GdkVisual* pVisual = (GdkVisual*)pTmpVisuals->data;
				pTmpVisuals = pTmpVisuals->next;
				int nScore = 0;
				switch (pVisual->type) {
				case GDK_VISUAL_TRUE_COLOR:
				case GDK_VISUAL_DIRECT_COLOR:
					switch (pVisual->depth) {
					case 32:
						nScore = 90;
						break;
					case 24:
						nScore = 80;
						break;
					case 16:
						nScore = 70;
						break;
					case 15:
						nScore = 60;
						break;
					}
					break;
				case GDK_VISUAL_PSEUDO_COLOR:
					switch (pVisual->depth) {
					case 8:
						nScore = 100;
						break;
					}
					break;
				}
				if (nScore > nBestScore) {
					nBestScore = nScore;
					m_pvisualDraw = pVisual;
				}
			}
			if (m_pvisualDraw != NULL) {
				g_object_ref(m_pvisualDraw);
				m_pimageDraw = gdk_image_new(
					GDK_IMAGE_FASTEST,
					m_pvisualDraw,
					640, 400);
			}
		}

#endif // X88_GUI_GTK_USEIMAGE

	}
	int nGdkRGBBits = 8;
	if (X88k().PC88().Z80Main().IsVABScreenActive()) {
		nGdkRGBBits = 24;
	}

#ifdef X88_GUI_GTK_USEIMAGE

	if ((nGdkRGBBits == 8) && (m_pimageDraw != NULL)) {
		static uint32_t adwPixels[256];
		static uint16_t awPixels[256];
		static uint8_t abtPixels[256];

#ifdef X88_BYTEORDER_LITTLE_ENDIAN

		bool bReverse = (m_pimageDraw->byte_order == GDK_MSB_FIRST);

#else // X88_BYTEORDER_BIG_ENDIAN

		bool bReverse = (m_pimageDraw->byte_order == GDK_LSB_FIRST);

#endif // X88_BYTEORDER_LITTLE/BIG_ENDIAN

		uint8_t* pbtSrc = X88k().GetScreenDrawer().GetScreenDataBits();
		uint8_t* pbtDst = (uint8_t*)m_pimageDraw->mem;
		int i, x, y;
		switch (m_pimageDraw->bpp) {
		case 4:
			for (i = 0; i < CX88ScreenDrawer::COLOR_COUNT; i++) {
				adwPixels[i] = pColorTable[i].pixel;
				if (bReverse) {
					adwPixels[i] =
						((adwPixels[i] & 0x000000FF) << 24) |
						((adwPixels[i] & 0x0000FF00) << 8) |
						((adwPixels[i] & 0x00FF0000) >> 8) |
						((adwPixels[i] & 0xFF000000) >> 24);
				}
			}
			y = 400;
			do {
				uint8_t* pbtSrc2 = pbtSrc;
				uint32_t* pdwDst2 = (uint32_t*)pbtDst;
				x = 640;
				do {
					*(pdwDst2++) = adwPixels[*(pbtSrc2++)];
				} while (--x != 0);
				pbtSrc += 640;
				pbtDst += m_pimageDraw->bpl;
			} while (--y != 0);
			break;
		case 3:
			for (i = 0; i < CX88ScreenDrawer::COLOR_COUNT; i++) {
				adwPixels[i] = pColorTable[i].pixel;
				if (bReverse) {
					adwPixels[i] =
						((adwPixels[i] & 0x000000FF) << 16) |
						(adwPixels[i] & 0x0000FF00) |
						((adwPixels[i] & 0x00FF0000) >> 16);
				}
			}
			y = 400;
			do {
				uint8_t* pbtSrc2 = pbtSrc;
				uint8_t* pbtDst2 = pbtDst;
				x = 640;
				do {
					uint32_t dwPixel = adwPixels[*(pbtSrc2++)];
					*(pbtDst2++) = (uint8_t)dwPixel;
					*(pbtDst2++) = (uint8_t)(dwPixel >> 8);
					*(pbtDst2++) = (uint8_t)(dwPixel >> 16);
				} while (--x != 0);
				pbtSrc += 640;
				pbtDst += m_pimageDraw->bpl;
			} while (--y != 0);
			break;
		case 2:
			for (i = 0; i < CX88ScreenDrawer::COLOR_COUNT; i++) {
				awPixels[i] = (uint16_t)pColorTable[i].pixel;
				if (bReverse) {
					awPixels[i] = (uint16_t)(
						((awPixels[i] & 0x00FF) << 8) |
						((awPixels[i] & 0xFF00) >> 8));
				}
			}
			y = 400;
			do {
				uint8_t* pbtSrc2 = pbtSrc;
				uint16_t* pwDst2 = (uint16_t*)pbtDst;
				x = 640;
				do {
					*(pwDst2++) = awPixels[*(pbtSrc2++)];
				} while (--x != 0);
				pbtSrc += 640;
				pbtDst += m_pimageDraw->bpl;
			} while (--y != 0);
			break;
		case 1:
			for (i = 0; i < CX88ScreenDrawer::COLOR_COUNT; i++) {
				abtPixels[i] = (uint8_t)pColorTable[i].pixel;
			}
			y = 400;
			do {
				uint8_t* pbtSrc2 = pbtSrc;
				uint8_t* pbtDst2 = pbtDst;
				x = 640;
				do {
					*(pbtDst2++) = abtPixels[*(pbtSrc2++)];
				} while (--x != 0);
				pbtSrc += 640;
				pbtDst += m_pimageDraw->bpl;
			} while (--y != 0);
			break;
		}
		gdk_draw_image(
			GetWndHandle()->window, m_pGC,
			m_pimageDraw,
			0, 0, 0, 0, 640, 400);
		nGdkRGBBits = 0;
	}

#endif // X88_GUI_GTK_USEIMAGE

	if (nGdkRGBBits != 0) {
		if (nGdkRGBBits == 8) {
			uint8_t* pbtBits = X88k().GetScreenDrawer().GetScreenDataBits();
			if (pbtBits != NULL) {
				gdk_draw_indexed_image(
					GetWndHandle()->window, m_pGC,
					0, 0, 640, 400,
					GDK_RGB_DITHER_NONE,
					pbtBits,
					640,
					&m_rgbcmap);
			}
		} else if (nGdkRGBBits == 24) {
			uint8_t* pbtBits = X88k().GetScreenDrawer().GetScreenDataBits2();
			if (pbtBits != NULL) {
				gdk_draw_rgb_image(
					GetWndHandle()->window, m_pGC,
					0, 0, 640, 400,
					GDK_RGB_DITHER_NONE,
					pbtBits,
					1920);
			}
		}
	}
}

#endif // X88_GUI


#ifdef X88_GUI_WINDOWS

// draw surface

void CX88View::DrawSurface() {
	if (X88k().GetDX().IsDirectDrawActive()) {
		if (m_bFrameClear) {
			HWND hwndParent = GetParent(GetWndHandle());
			HDC hdc = GetWindowDC(hwndParent);
			if (hdc != NULL) {
				RECT rectView;
				GetWindowRect(GetWndHandle(), &rectView);
				ExcludeClipRect(
					hdc,
					rectView.left, rectView.top,
					rectView.right, rectView.bottom);
				RECT rectClear;
				SetRect(
					&rectClear,
					0, 0, 640, GetSystemMetrics(SM_CYMENU));
				SetBkColor(hdc, RGB(0, 0, 0));
				ExtTextOut(
					hdc,
					0, 0, ETO_OPAQUE, &rectClear,
					"", 0, NULL);
				ReleaseDC(hwndParent, hdc);
			}
			m_bFrameClear = false;
		}
		HDC hdc = GetDC(GetWndHandle());
		if (hdc != NULL) {
			DrawDC(hdc);
			ReleaseDC(GetWndHandle(), hdc);
		}
	}
}

// update palette

void CX88View::UpdatePalette(bool bUpdateAll) {
	if (bUpdateAll) {
		HDC hdc = GetDC(GetWndHandle());
		if (hdc != NULL) {
			SelectPalette(
				hdc, X88k().GetScreenDrawer().GetScreenPalette(), FALSE);
			RealizePalette(hdc);
			ReleaseDC(GetWndHandle(), hdc);
		}
	} else {
		AnimatePalette(
			X88k().GetScreenDrawer().GetScreenPalette(),
			0, 17,
			X88k().GetScreenDrawer().GetScreenPalEntry());
	}
}

#endif // X88_GUI

// restart timer

void CX88View::RestartTimer() {

#ifdef X88_GUI_WINDOWS

	KillTimer(
		GetWndHandle(), m_nTimerID);
	m_nTimerID = SetTimer(
		GetWndHandle(), TIMER_ID,
		X88k().GetScreenUpdateElapse(), NULL);

#elif defined(X88_GUI_GTK)

	g_source_remove(m_nTimeOutID);
	m_nTimeOutID = g_timeout_add(
		X88k().GetScreenUpdateElapse(),
		TimeOutCallback, NULL);

#endif // X88_GUI

}



bool CX88View::TimeOutCallback() {
	//Serial.println("M_VIEW CALLBACK!!!");
	bool bUpdate = X88k().GetScreenDrawer().RatchText();
	//Serial.println("M_VIEW CALLBACK 1");
	if (bUpdate) {
		//Serial.println("M_VIEW CALLBACK 2");
		X88k().GetScreenDrawer().DrawScreen();
		//Serial.println("M_VIEW CALLBACK 3");
		X88k().GetScreenDrawer().UpdatePalette();
		//Serial.println("M_VIEW CALLBACK 4");
	} else {
		//Serial.println("M_VIEW CALLBACK 5");
		bUpdate = X88k().GetScreenDrawer().UpdatePalette();
	}
	//Serial.println("M_VIEW CALLBACK 6");
	if (X88k().PC88().Z80Main().IsVABScreenActive()) {
		//Serial.println("M_VIEW CALLBACK 7");
		bUpdate = X88k().GetScreenDrawer().DrawScreenVAB();
		//Serial.println("M_VIEW CALLBACK 8");
	}
	if (bUpdate) {
		//Serial.println("M_VIEW CALLBACK 9");
		DrawWindow();
	}
	return TRUE;
}
void CX88View::DrawWindow() {


	//Window 描画
}
