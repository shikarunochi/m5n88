////////////////////////////////////////////////////////////
// X88000 Main Module
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

#ifndef X88000_DEFINED
#define X88000_DEFINED

////////////////////////////////////////////////////////////
// declare

class CX88000;

////////////////////////////////////////////////////////////
// include

#include "PC88.h"
#include "X88View.h"
#include "X88ScreenDrawer.h"
#include "X88DiskImageMemory.h"
//#include "X88ParallelManager.h"
//#include "X88Option.h"
//#include "X88Frame.h"
//#include "X88Dialog.h"
//#include "X88DirectX.h"
//#include "X88BeepPlayer.h"
#include<set>
#include<queue>

////////////////////////////////////////////////////////////
// declaration of CX88000

class CX88000 {
// enum
protected:
	// execution unit
	enum {
		EXECUTE_UNIT_TIME = 2
	};
	// beep / pseudo sound port watching time
	enum {
		BEEP_TIME = 10
	};
	// PCG sound port watching time
	enum {
		PCG_TIME = 10
	};
	// IME input
	enum {
		IME_WAIT = 200
	};
	// debug log output format
	enum {
		DEBUGLOG_COLMAX = 8
	};

// attribute
protected:
	// instance
	static CX88000* m_pThis;

#ifdef X88_PLATFORM_WINDOWS

	// instance handle
	static HINSTANCE m_hinstThis;

#endif // X88_PLATFORM

	// PC88 object
	static CPC88 m_pc88;

	// screen drawer object
	static CX88ScreenDrawer m_scrdrawer;

	// DirectX manager
	//static CX88DirectX m_DX;

	// module directory(filesystem encoding)
	static std::string m_fstrModuleDir;
	// start directory(filesystem encoding)
	static std::string m_fstrStartDir;
	// frame window
	//static CX88Frame m_frame;

	// disk image memory manager
	static std::set<CX88DiskImageMemory> m_setX88DiskImageMemory;

	// parallel device manager
	//static CX88ParallelManager m_paraman;
	// connected parallel device number
	static int m_nConnectedParallelDeviceNo;

	// execute time1
	static uint32_t m_dwExecTime1;
	// execute time2
	static uint32_t m_dwExecTime2;
	// execute pass counter1
	static uint32_t m_dwExecPassCounter1;
	// execute pass counter2
	static uint32_t m_dwExecPassCounter2;

	// queue of IME character input
	static std::queue<uint16_t> m_queueIMEChar;
	// wait for left of IME character input
	static int m_nIMECharWait;
	// IME character input table
	static uint16_t m_awIMECharTable[];

	// option manager
	//static CX88OptionManager m_optman;
	// command line paremeter count
	static int m_argc;
	// command line paremeter value
	static char** m_argv;
	// boost mode
	static bool m_bBoostMode;
	// boost limiter
	static int m_nBoostLimiter;
	// frame-rate
	static int m_nScreenFrameRate;
	// screen update elapse
	static int m_nScreenUpdateElapse;
	// interlace mode
	static bool m_bInterlace;
	// using DirectInput
	static bool m_bDirectInputUse;
	// IME disable
	static bool m_bIMEDisable;
	// using DirectSound
	static bool m_bDirectSoundUse;
	// DirectSound frequency
	static int m_nDirectSoundFrequency;
	// DirectSound bit count
	static int m_nDirectSoundBits;
	// DirectSound channel count
	static int m_nDirectSoundChannels;
	// beep player volume
	static int m_nBeepPlayerVolume;
	// beep player muting
	static bool m_bBeepPlayerMute;
	// PCG sound player volume
	static int m_nPcgPlayerVolume;
	// PCG sound player muting
	static bool m_bPcgPlayerMute;
	// is saving environment settings
	static bool m_bSaveEnv;
	// full-screen mode booting
	static bool m_bFullScreenBoot;
	// floppy read-only attribute
	static bool m_bReadOnlyMode;
	// floppy drive selected image
	static int m_anDriveSelect[CPC88Fdc::DRIVE_MAX];
	// filename of environment settings(filesystem encoding)
	static std::string m_fstrEnvFileName;

	// file name of debug log file(filesystem encoding)
	static std::string m_fstrDebugLogFileName;
	// pointer of debug log file
	static FILE* m_pfDebugLog;
	// columns of debug log output
	static int m_nDebugLogCol;

	// sound paused counter
	static int m_nSoundPauseCount;

	// beep player
	//static CX88BeepPlayer* m_pBeepPlayer;
	// beep port status
	static bool m_bBeepPortStatus;
	// beep update count
	static int m_nBeepUpdateCount;
	// queue of beep update count
	static int m_anBeepQueue[BEEP_TIME/EXECUTE_UNIT_TIME];
	// pseudo sound port status
	static bool m_bExBeepPortStatus;
	// pseudo sound update count
	static int m_nExBeepUpdateCount;
	// queue of pseudo sound update count
	static int m_anExBeepQueue[BEEP_TIME/EXECUTE_UNIT_TIME];
	// queue pointer of beep / pseudo sound update count
	static int m_nBeepQueuePtr;

	// PCG sound player
	//static CX88BeepPlayer* m_apPcgPlayer[3];
	// PCG sound frequency
	static int m_anPcgFrequency[3];

	static CX88View m_view;

#ifdef X88_GUI_WINDOWS

	// period changed
	static bool m_bChangedPeriod;

	// message processor
	static CX88MessageProcessor* m_pMessageProcessor;

#elif defined(X88_GUI_GTK)

	// idle id
	static gint m_nIdleID;
	// timer for execution
	static GTimer* m_pExecTimer;

	// writing file name(filesystem encoding)
	static std::string m_fstrWriteFileName;

#endif // X88_GUI

public:

#ifdef X88_PLATFORM_WINDOWS

	// get instance handle
	static HINSTANCE GetInstanceHandle() {
		return m_hinstThis;
	}
	// set instance handle
	static void SetInstanceHandle(HINSTANCE hinstThis) {
		m_hinstThis = hinstThis;
	}

#endif // X88_PLATFORM

	// get PC88 object
	static CPC88& PC88() {
		return m_pc88;
	}
	// get screen drawer object
	static CX88ScreenDrawer& GetScreenDrawer() {
		return m_scrdrawer;
	}
	// get DirectX manager
	//static CX88DirectX& GetDX() {
	//	return m_DX;
	//}

	// get parallel device manager
	//static CX88ParallelManager& ParallelManager() {
	//	return m_paraman;
	//}
	// get connected parallel device number
	static int GetConnectedParallelDeviceNo() {
		return m_nConnectedParallelDeviceNo;
	}

	// get beep player
	//static CX88BeepPlayer* GetBeepPlayer() {
	//	return m_pBeepPlayer;
	//}
	// set beep player
	//static void SetBeepPlayer(CX88BeepPlayer* pBeepPlayerNew) {
	//	m_pBeepPlayer = pBeepPlayerNew;
	//}

	// get PCG sound player
	//static CX88BeepPlayer* GetPcgPlayer(int nChannel) {
	//	return m_apPcgPlayer[nChannel];
	//}
	// set PCG sound player
	//static void SetPcgPlayer(int nChannel, CX88BeepPlayer* pPcgPlayerNew) {
	//	m_apPcgPlayer[nChannel] = pPcgPlayerNew;
	//}

#ifdef X88_GUI_WINDOWS

	// add message processor
	static void AddMessageProcessor(CX88MessageProcessor* pProcessor) {
		m_pMessageProcessor = (m_pMessageProcessor == NULL)?
			pProcessor:
			m_pMessageProcessor->Add(pProcessor);
	}
	// remove message processor
	static void RemoveMessageProcessor(CX88MessageProcessor* pProcessor) {
		m_pMessageProcessor = m_pMessageProcessor->Remove(pProcessor);
	}

#elif defined(X88_GUI_GTK)

	// get writing file name(filesystem encoding)
	static std::string GetWriteFileName() {
		return m_fstrWriteFileName;
	}
	// set writing file name(filesystem encoding)
	static void SetWriteFileName(
		const std::string& fstrWriteFileName)
	{
		m_fstrWriteFileName = fstrWriteFileName;
	}

#endif // X88_GUI

// create & destroy
public:
	// default constructor
	CX88000();
	// destructor
	~CX88000();

	// initialize
	static bool Initialize();
	// dispose
	static bool Dispose();

// option
protected:
	// parse and execute command line option
	static void ParseCommandLine();

public:
	// get BASIC mode
	static int GetBasicMode() {
		return m_pc88.GetBasicMode();
	}
	// is hi-speed mode
	static bool IsHighSpeedMode() {
		return m_pc88.IsHighSpeedMode();
	}
	// set BASIC mode
	static void SetBasicMode(int nBasicMode, bool bHighSpeedMode) {
		m_pc88.SetBasicMode(nBasicMode);
		m_pc88.SetHighSpeedMode(bHighSpeedMode);
	}
	// get base clock
	static int GetBaseClock() {
		return m_pc88.GetBaseClock();
	}
	// set base clock
	static void SetBaseClock(int nClock) {
		m_pc88.SetBaseClock(nClock);
	}
	// is hi-resolution mode
	static bool IsHiresolution() {
		return m_pc88.IsHiresolution();
	}
	// set hi-resolution mode
	static void SetHiresolution(bool bHiresolution) {
		m_pc88.SetHiresolution(bHiresolution);
	}
	// is wait emulation
	static bool IsWaitEmulation() {
		return m_pc88.IsWaitEmulation();
	}
	// set wait emulation
	static void SetWaitEmulation(bool bWaitEmulation) {
		m_pc88.SetWaitEmulation(bWaitEmulation);
	}
	// is old-machine compatible mode
	static bool IsOldCompatible() {
		return m_pc88.IsOldCompatible();
	}
	// set old-machine compatible mode
	static void SetOldCompatible(bool bOldCompatible) {
		m_pc88.SetOldCompatible(bOldCompatible);
	}
	// is PCG enable
	static bool IsPcgEnable() {
		return m_pc88.IsPcgEnable();
	}
	// set PCG enable
	static void SetPcgEnable(bool bPcgEnable) {
		m_pc88.SetPcgEnable(bPcgEnable);
	}
	// is international display mode
	static bool IsOptionFont() {
		return m_pc88.IsOptionFont();
	}
	// set international display mode
	static void SetOptionFont(bool bOptionFont) {
		m_pc88.SetOptionFont(bOptionFont);
	}
	// is boost mode
	static bool IsBoostMode() {
		return m_bBoostMode;
	}
	// set boost mode
	static void SetBoostMode(bool bBoostMode) {
		m_bBoostMode = bBoostMode;
	}
	// get boost limiter
	static int GetBoostLimiter() {
		return m_nBoostLimiter;
	}
	// set boost limiter
	static void SetBoostLimiter(int nBoostLimiter) {
		if ((nBoostLimiter == 0) ||
			((nBoostLimiter >= 25) && (nBoostLimiter <= 400)))
		{
			m_nBoostLimiter = nBoostLimiter;
		}
	}
	// get frame-rate
	static int GetScreenFrameRate() {
		return m_nScreenFrameRate;
	}
	// get screen update elapse
	static int GetScreenUpdateElapse() {
		return m_nScreenUpdateElapse;
	}
	// set frame-rate
	static void SetScreenFrameRate(int nScreenFrameRate) {
		switch (nScreenFrameRate) {
		case 20:
		case 30:
		case 40:
		case 60:
			m_nScreenFrameRate = nScreenFrameRate;
			m_nScreenUpdateElapse = 1000/m_nScreenFrameRate;
			break;
		}
	}
	// is interlace mode
	static bool IsInterlace() {
		return m_bInterlace;
	}
	// set interlace mode
	static void SetInterlace(bool bInterlace) {
		m_bInterlace = bInterlace;
	}
	// is using DirectInput
	static bool IsDirectInputUse() {
		return m_bDirectInputUse;
	}
	// set using DirectInput
	static void SetDirectInputUse(bool bDirectInputUse) {
		m_bDirectInputUse = bDirectInputUse;
	}
	// is IME disable
	static bool IsIMEDisable() {
		return m_bIMEDisable;
	}
	// set IME disable
	static void SetIMEDisable(bool bIMEDisable) {
		m_bIMEDisable = bIMEDisable;
	}
	// is using DirectSound
	static bool IsDirectSoundUse() {
		return m_bDirectSoundUse;
	}
	// set using DirectSound
	static void SetDirectSoundUse(bool bDirectSoundUse) {
		m_bDirectSoundUse = bDirectSoundUse;
	}
	// get DirectSound frequency
	static int GetDirectSoundFrequency() {
		return m_nDirectSoundFrequency;
	}
	// set DirectSound frequency
	static void SetDirectSoundFrequency(int nDirectSoundFrequency) {
		switch (nDirectSoundFrequency) {
		case 11025:
		case 22050:
		case 44100:
		case 48000:
			m_nDirectSoundFrequency = nDirectSoundFrequency;
			break;
		}
	}
	// get DirectSound bit count
	static int GetDirectSoundBits() {
		return m_nDirectSoundBits;
	}
	// set DirectSound bit count
	static void SetDirectSoundBits(int nDirectSoundBits) {
		switch (nDirectSoundBits) {
		case 8:
		case 16:
			m_nDirectSoundBits = nDirectSoundBits;
			break;
		}
	}
	// get DirectSound channel count
	static int GetDirectSoundChannels() {
		return m_nDirectSoundChannels;
	}
	// set DirectSound channel count
	static void SetDirectSoundChannels(int nDirectSoundChannels) {
		switch (nDirectSoundChannels) {
		case 1:
		case 2:
			m_nDirectSoundChannels = nDirectSoundChannels;
			break;
		}
	}
	// get beep player volume
	static int GetBeepPlayerVolume() {
		return m_nBeepPlayerVolume;
	}
	// set beep player volume
	static void SetBeepPlayerVolume(int nBeepPlayerVolume) {
		if ((nBeepPlayerVolume >= 0) && (nBeepPlayerVolume <= 100)) {
			m_nBeepPlayerVolume = nBeepPlayerVolume;
		}
	}
	// is beep player muting
	static bool IsBeepPlayerMute() {
		return m_bBeepPlayerMute;
	}
	// set beep player muting
	static void SetBeepPlayerMute(bool bBeepPlayerMute) {
		m_bBeepPlayerMute = bBeepPlayerMute;
	}
	// get PCG sound player volume
	static int GetPcgPlayerVolume() {
		return m_nPcgPlayerVolume;
	}
	// set PCG sound player volume
	static void SetPcgPlayerVolume(int nPcgPlayerVolume) {
		if ((nPcgPlayerVolume >= 0) && (nPcgPlayerVolume <= 100)) {
			m_nPcgPlayerVolume = nPcgPlayerVolume;
		}
	}
	// is PCG sound player muting
	static bool IsPcgPlayerMute() {
		return m_bPcgPlayerMute;
	}
	// set PCG sound player muting
	static void SetPcgPlayerMute(bool bPcgPlayerMute) {
		m_bPcgPlayerMute = bPcgPlayerMute;
	}
	// is saving environment settings
	static bool IsSaveEnv() {
		return m_bSaveEnv;
	}
	// set saving environment settings
	static void SetSaveEnv(bool bSaveEnv) {
		m_bSaveEnv = bSaveEnv;
	}
	// is full-screen mode booting
	static bool IsFullScreenBoot() {
		return m_bFullScreenBoot;
	}
	// is full-screen mode booting
	static void SetFullScreenBoot(bool bFullScreenBoot) {
		m_bFullScreenBoot = bFullScreenBoot;
	}
	// get floppy drive count
	static int GetDriveCount() {
		return m_pc88.Fdc().GetDriveCount();
	}
	// set floppy drive count
	static void SetDriveCount(int nDriveCount) {
		if ((nDriveCount >= 1) && (nDriveCount <= 4)) {
			m_pc88.Fdc().SetDriveCount(nDriveCount);
		}
	}
	// set selected image of floppy drive
	static void SetDriveSelect(int nDrive, int nSelect) {
		m_anDriveSelect[nDrive] = nSelect;
	}
	// floppy read-only attribute
	static void SetReadOnlyMode(bool bReadOnlyMode) {
		m_bReadOnlyMode = bReadOnlyMode;
	}
	// set command line paremeter
	static void SetCmdLine(int argc, char** argv) {
		m_argc = argc;
		m_argv = argv;
	}
	// add image file
	static void AddImageFile(const std::string& fstrFileName);
	// set option to default
	static void DefaultOption(
		const std::string& strOptionName);
	// set options to default
	static void DefaultOptions(
		std::vector<std::string>* pvectOptionNames = NULL);
	// save option to environment settings file
	static void SaveOption(const std::string& strOptionName);
	// save options to environment settings file
	static void SaveOptions(
		std::vector<std::string>* pvectOptionNames = NULL);

// debug
public:
	// is recording debug log
	static bool IsDebugLogging() {
		return m_pfDebugLog != NULL;
	}
	// start debug log recording
	static bool StartDebugLog();
	// end debug log recording
	static bool EndDebugLog();
	// output debug log
	static void OutputDebugLog(int nLogMode);
	// write RAM
	static void WriteRam(
		bool bWriteMainRam0,
		bool bWriteMainRam1,
		bool bWriteFastTVRam,
		bool bWriteSlowTVRam,
		bool bWriteGVRam0,
		bool bWriteGVRam1,
		bool bWriteGVRam2,
		bool bWriteSubRam,
		bool bWriteExRam0,
		bool bWriteExRam1);

// disk image
public:
	// open disk image file
	static int DiskImageFileOpen(
		const std::string& fstrFileName, bool& bReadOnly,
		uint8_t*& pbtData, uint32_t& dwSize);
	// close disk image file
	static int DiskImageFileClose(uint8_t* pbtData);

// clipboard
public:
	// copy bitmap from screen-image to clipboard
	static bool DoClipboardCopyBitmap();
	// copy text from text VRAM to clipboard
	static bool DoClipboardCopyText();
	// paste text from clipboard to keyboard-input
	static bool DoClipboardPasteText();

#ifdef X88_GUI_GTK

	// clipboard text received callback
	static void OnReceivedClipboardText(
		GtkClipboard* pClipboard,
		const gchar* pgszText,
		gpointer pData);

#endif // X88_GUI

// sound
public:
	// pause sound
	static void PauseSound();
	// restart sound
	static void RestartSound();

// parallel device
public:
	// select parallel device
	static bool SelectParallelDevice(int nConnectedParallelDeviceNoNew);

// beep
public:
	// create beep player
	static void CreateBeepPlayer();
	// destroy beep player
	static void DestroyBeepPlayer();
	// update beep player volume and mute
	static void UpdateBeepPlayerVolumeMute();
	// beep output
	static void BeepOutput(
		bool bBeepPortStatus, bool bExBeepPortStatus);

// PCG sound
public:
	// create PCG sound player
	static void CreatePcgPlayer();
	// destroy PCG sound player
	static void DestroyPcgPlayer();
	// update PCG sound player volume and mute
	static void UpdatePcgPlayerVolumeMute();
	// PCG sound output
	static void PcgSoundOutput(int nChannel, int nCounter);

// implementation
protected:

#ifdef X88_GUI_GTK

	// idle callback
	static gboolean IdleCallback(gpointer pData);

#endif // X88_GUI

// operation
public:
	// clear key matrics
	static void ClearKeyMatrics() {
		m_pc88.Z80Main().ClearKeyMatrics();
	}
	// set key matrics
	static void SetKeyMatrics(
		int nAddress, int nBit, bool bPressed)
	{
		m_pc88.Z80Main().SetKeyMatrics(nAddress, nBit, bPressed);
	}
	// open system file
	static File SysFileOpen(const std::string& strName);
	// add IME input character(GUI encoding)
	static void AddIMEChar(const std::string& gstrIME);
	// reset execute counter
	static void ResetExecuteCounter();
	// execute reset
	static void DoReset();
	// execute X88000
	static int Execute();
	// idle process
	static void OnIdle();
	// sleep process
	static void DoSleep(int nMilliSec);
	
	// key input from CardKB
	static int m_lastKeyCode;
	static int m_keyInputCounter;
	static void CheckKeyInput();
	static void ChangeKeyMatricsStatus(int charCode, bool keyOnFlag);
	
	static void scrn_thread(void *arg);
};

#endif // X88000_DEFINED
