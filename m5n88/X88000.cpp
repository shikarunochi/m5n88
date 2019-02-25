////////////////////////////////////////////////////////////
// X88000 Main Module
//
// Written by Manuke
//
// Assisted by apaslothy
// (PC-8001mkII/SR,PCG-8800,InternationalMode Support)

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "X88000.h"

//#include "X88DirectX.h"
//#include "X88Dialog.h"
#include "X88Utility.h"

using namespace NX88Utility;

////////////////////////////////////////////////////////////
// implementation of CX88000

////////////////////////////////////////////////////////////
// attribute

// instance

CX88000* CX88000::m_pThis;

#ifdef X88_PLATFORM_WINDOWS

// instance handle

HINSTANCE CX88000::m_hinstThis;

#endif // X88_PLATFORM

// PC88 object

CPC88 CX88000::m_pc88;

// screen drawer object

CX88ScreenDrawer CX88000::m_scrdrawer;

// DirectX manager

//CX88DirectX CX88000::m_DX;

// module directory(filesystem encoding)

std::string CX88000::m_fstrModuleDir;

// start directory(filesystem encoding)

std::string CX88000::m_fstrStartDir;

// frame window

//CX88Frame CX88000::m_frame;

// disk image memory manager

std::set<CX88DiskImageMemory> CX88000::m_setX88DiskImageMemory;

// parallel device manager

//CX88ParallelManager CX88000::m_paraman;

// connected parallel device number

int CX88000::m_nConnectedParallelDeviceNo;

// execute time1

uint32_t CX88000::m_dwExecTime1;

// execute time2

uint32_t CX88000::m_dwExecTime2;

// execute pass counter1

uint32_t CX88000::m_dwExecPassCounter1;

// execute pass counter2

uint32_t CX88000::m_dwExecPassCounter2;

// queue of IME character input

std::queue<uint16_t> CX88000::m_queueIMEChar;

// wait for left of IME character input

int CX88000::m_nIMECharWait;

// IME character input table

uint16_t CX88000::m_awIMECharTable[] = {
	// Marks
	0x0096, 0x0161, 0x0162, 0x0163, 0x0164, 0x0165, 0x0166, 0x0167,
	0x0170, 0x0171, 0x0172, 0x0173, 0x0074, 0x0057, 0x0075, 0x0076,
	// Numeric
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0174, 0x0157, 0x0175, 0x0176,
	// Upper Alpha
	0x0020, 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127,
	0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x0135, 0x0136, 0x0137,
	0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x0146, 0x0147,
	0x0150, 0x0151, 0x0152, 0x0053, 0x0054, 0x0055, 0x0056, 0x0177,
	// Lower Alpha
	0x0120, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
	0x0050, 0x0051, 0x0052, 0x0153, 0x0154, 0x0155, 0x0156, 0x0000,
	// Kana
	0x0000, 0x1175, 0x1153, 0x1155, 0x1174, 0x1176, 0x1160, 0x1163,
	0x1125, 0x1164, 0x1165, 0x1166, 0x1167, 0x1170, 0x1171, 0x1152,
	0x1054, 0x1063, 0x1025, 0x1064, 0x1065, 0x1066, 0x1044, 0x1027,
	0x1030, 0x1072, 0x1022, 0x1050, 0x1024, 0x1042, 0x1040, 0x1023,
	0x1041, 0x1021, 0x1052, 0x1047, 0x1043, 0x1045, 0x1031, 0x1061,
	0x1074, 0x1033, 0x1026, 0x1046, 0x1062, 0x1056, 0x1057, 0x1032,
	0x1036, 0x1055, 0x1076, 0x1035, 0x1067, 0x1070, 0x1071, 0x1037,
	0x1034, 0x1075, 0x1073, 0x1077, 0x1060, 0x1051, 0x1020, 0x1053,
	// Return
	0x0017,
	// Tab
	0x00A0
};

// option manager

//CX88OptionManager CX88000::m_optman;

// command line parameter count

int CX88000::m_argc;

// command line parameter value

char** CX88000::m_argv;

// boost mode

bool CX88000::m_bBoostMode;

// boost limiter

int CX88000::m_nBoostLimiter;

// frame-rate

int CX88000::m_nScreenFrameRate;

// screen update elapse

int CX88000::m_nScreenUpdateElapse;

// interlace mode

bool CX88000::m_bInterlace;

// using DirectInput

bool CX88000::m_bDirectInputUse;

// IME disable

bool CX88000::m_bIMEDisable;

// using DirectSound

bool CX88000::m_bDirectSoundUse;

// DirectSound frequency

int CX88000::m_nDirectSoundFrequency;

// DirectSound bit count

int CX88000::m_nDirectSoundBits;

// DirectSound channel count

int CX88000::m_nDirectSoundChannels;

// beep player volume

int CX88000::m_nBeepPlayerVolume;

// beep player muting

bool CX88000::m_bBeepPlayerMute;

// PCG sound player volume

int CX88000::m_nPcgPlayerVolume;

// PCG sound player muting

bool CX88000::m_bPcgPlayerMute;

// is saving environment settings

bool CX88000::m_bSaveEnv;

// full-screen mode booting

bool CX88000::m_bFullScreenBoot;

// floppy read-only attribute

bool CX88000::m_bReadOnlyMode;

// floppy drive selected image

int CX88000::m_anDriveSelect[CPC88Fdc::DRIVE_MAX];

// filename of environment settings(filesystem encoding)

std::string CX88000::m_fstrEnvFileName;

// file name of debug log file(filesystem encoding)

std::string CX88000::m_fstrDebugLogFileName;

// pointer of debug log file

FILE* CX88000::m_pfDebugLog;

// columns of debug log output

int CX88000::m_nDebugLogCol;

// sound paused counter

int CX88000::m_nSoundPauseCount;

// beep player

//CX88BeepPlayer* CX88000::m_pBeepPlayer;

// beep port status

bool CX88000::m_bBeepPortStatus;

// beep update count

int CX88000::m_nBeepUpdateCount;

// queue of beep update count

int CX88000::m_anBeepQueue[BEEP_TIME/EXECUTE_UNIT_TIME];

// pseudo sound port status

bool CX88000::m_bExBeepPortStatus;

// pseudo sound update count

int CX88000::m_nExBeepUpdateCount;

// queue of pseudo sound update count

int CX88000::m_anExBeepQueue[BEEP_TIME/EXECUTE_UNIT_TIME];

// queue pointer of beep / pseudo sound update count

int CX88000::m_nBeepQueuePtr;

// PCG sound player

//CX88BeepPlayer* CX88000::m_apPcgPlayer[3];

// PCG sound frequency

int CX88000::m_anPcgFrequency[3];

CX88View CX88000::m_view;

int CX88000::m_lastKeyCode;
int CX88000::m_keyInputCounter;

bool CX88000::m_suspendScrnThreadFlag;
bool CX88000::m_btnBLongPressFlag;

#ifdef X88_GUI_WINDOWS

// period changed

bool CX88000::m_bChangedPeriod;

// message processor

CX88MessageProcessor* CX88000::m_pMessageProcessor = NULL;

#elif defined(X88_GUI_GTK)

// idle id

gint CX88000::m_nIdleID;

// timer for execution

GTimer* CX88000::m_pExecTimer;

// writing file name(filesystem encoding)

std::string CX88000::m_fstrWriteFileName;

#endif // X88_GUI

////////////////////////////////////////////////////////////
// create & destroy

// default constructor

CX88000::CX88000() {
	m_pThis = this;
}

// destructor

CX88000::~CX88000() {
}

// initialize

bool CX88000::Initialize() {
	Serial.println("X88000Start!");
	m_nConnectedParallelDeviceNo = 0;
	m_bBoostMode = false;
	m_nBoostLimiter = 0;
	m_nScreenFrameRate = 20;
	m_nScreenUpdateElapse = 50;
	m_bInterlace = false;
	m_bDirectInputUse = true;
	m_bIMEDisable = false;
	m_bDirectSoundUse = true;
	m_nDirectSoundFrequency = 44100;
	m_nDirectSoundBits = 8;
	m_nDirectSoundChannels = 1;
	m_nBeepPlayerVolume = 50;
	m_bBeepPlayerMute = false;
	m_nPcgPlayerVolume = 50;
	m_bPcgPlayerMute = false;
	m_bSaveEnv = true;
	m_bFullScreenBoot = false;
	m_nIMECharWait = 0;
	m_pfDebugLog = NULL;
	m_nSoundPauseCount = 0;
//	m_pBeepPlayer = NULL;
	m_bBeepPortStatus = m_bExBeepPortStatus = false;
	m_nBeepUpdateCount = m_nExBeepUpdateCount = 0;
	memset(m_anBeepQueue, 0, sizeof(m_anBeepQueue));
	memset(m_anExBeepQueue, 0, sizeof(m_anExBeepQueue));
	m_nBeepQueuePtr = 0;

	m_lastKeyCode = 0;
	m_keyInputCounter = 0;
	m_suspendScrnThreadFlag = false;
	m_btnBLongPressFlag = false;
//	for (int nChannel = 0; nChannel < 3; nChannel++) {
//		m_apPcgPlayer[nChannel] = NULL;
//	}
Serial.println("X88000Start!:1");
M5.Lcd.println("PC-8801 emulator for M5Stack FIRE");
M5.Lcd.println("Initialize...");

uint8_t *pbtScreenDataBits = (uint8_t*)ps_malloc(640*400);

#ifdef X88_GUI_WINDOWS

	m_bChangedPeriod = false;

	InitCommonControls();
	if (timeBeginPeriod(1) == TIMERR_NOERROR) {
		m_bChangedPeriod = true;
	}

	AddMessageProcessor(m_frame.MessageProcessor());

#elif defined(X88_GUI_GTK)

	m_nIdleID = 0;
	m_pExecTimer = NULL;

	gtk_set_locale();

#ifdef __CYGWIN__

	_Xsetlocale(LC_ALL, "ja_JP.EUC");

#endif // __CYGWIN__

	gtk_init(&m_argc, &m_argv);
	gtk_rc_parse("./gtkrc");

	m_pExecTimer = g_timer_new();

#endif // X88_GUI

//	if (!m_DX.Initialize()) {
//		return false;
//	}
//	m_paraman.Initialize();

#ifdef X88_PLATFORM_WINDOWS

	char fszPath[_MAX_PATH], fszDrive[_MAX_DRIVE], fszDir[_MAX_DIR];
	fszPath[0] = '\0';
	GetModuleFileName(m_hinstThis, fszPath, sizeof(fszPath));
	_splitpath(fszPath, fszDrive, fszDir, NULL, NULL);
	m_fstrModuleDir = fszDrive;
	m_fstrModuleDir += fszDir;
	if (_getcwd(fszPath, sizeof(fszPath)) != NULL) {
		m_fstrStartDir = fszPath;
		const char* pfszLast;

#ifdef X88_GUI_WINDOWS

		pfszLast = CharPrev(fszPath, fszPath+strlen(fszPath));

#elif defined(X88_GUI_GTK)

		pfszLast = NULL;
		if (fszPath[0] != '\0') {
			pfszLast = fszPath+strlen(fszPath)-1;
		}

#endif // X88_GUI

		if ((pfszLast != NULL) && (*pfszLast != '\\')) {
			m_fstrStartDir += '\\';
		}
	} else {
		m_fstrStartDir = '.';
	}

#elif defined(X88_PLATFORM_UNIX)

	char fszDir[_MAX_PATH+1];
/*	//if (getcwd(fszDir, sizeof(fszDir)) == NULL) {
	//	m_fstrStartDir = '.';
	//} else {
		m_fstrStartDir = fszDir;
	//}
	m_fstrModuleDir = m_fstrStartDir;
	strncpy(fszDir, m_argv[0], sizeof(fszDir));
	fszDir[_MAX_PATH] = '\0';
	char* pfszSep = strrchr(fszDir, '/');
	if (pfszSep != NULL) {
		*pfszSep = '\0';
		//if (chdir(fszDir) != 0) {
			// ignore
		//}
		//if (getcwd(fszDir, sizeof(fszDir)) == NULL) {
		//	m_fstrModuleDir = '.';
		//} else {
			m_fstrModuleDir = fszDir;
		//}
		//if (chdir(m_fstrStartDir.c_str()) != 0) {
			// ignore
		//}
	}
	m_fstrStartDir += '/';
	m_fstrModuleDir += '/';
*/
#endif // X88_PLATFORM
	Serial.println("X88000Start!:2");
	m_fstrEnvFileName = m_fstrModuleDir;
	m_fstrEnvFileName += "X88000.ini";
	m_fstrDebugLogFileName = m_fstrModuleDir;
	m_fstrDebugLogFileName += "Debug.log";
	Serial.println("X88000Start!:3");
//	m_pc88.Z80Main().SetBeepOutputCallback(BeepOutput);
	Serial.println("X88000Start!:4");
//	m_pc88.Pcg().SetPcgSoundOutputCallback(PcgSoundOutput);
	Serial.println("X88000Start!:5");
//	m_pc88.Z80Main().SetParallelDevice(
//		*m_paraman[m_nConnectedParallelDeviceNo].Device());
//	m_pc88.SetOutputDebugLogCallback(OutputDebugLog);
	m_pc88.SetSysFileOpenCallback(SysFileOpen);
	CDiskImageFile::SetDiskImageFileOpenCallback(DiskImageFileOpen);
	CDiskImageFile::SetDiskImageFileCloseCallback(DiskImageFileClose);

	M5.Lcd.println("READ ROM FILE");
	m_pc88.Initialize();
	m_pc88.Reset();

	M5.Lcd.println("READ DISK FILE");
	CDiskImageCollection& dic = m_pc88.GetDiskImageCollection();
	Serial.println("DiskImageSet");
	//std::string fileDirPath = DISK_DIRECTORY;
	dic.AddDiskImageFile("pc8801disk.d88", true);

	Serial.println("SetDiskImage");
	m_pc88.Fdc().SetDiskImage(0,m_pc88.GetDiskImageCollection().GetDiskImage(0));
	Serial.println("SetDiskImageDone");
	//);

//	m_optman.LoadEnvFile(*m_pThis, m_fstrEnvFileName);
	//ParseCommandLine();
	//Serial.println("ParseCommandLine End");
	M5.Lcd.println("SYSTEM STARTING...");
	DoReset();
	Serial.println("DoResetEnd");

	m_scrdrawer.Create(PC88(), false, pbtScreenDataBits);
	
	//if (!)///||
		//!m_frame.Create(*m_pThis))
	//{
	//	return false;
	//}
	return true;
}

// dispose

bool CX88000::Dispose() {
	CDiskImageCollection& dic = m_pc88.GetDiskImageCollection();
	while (dic.size() > 0) {
		CDiskImageCollection::iterator itFile = dic.begin();
		dic.erase(itFile);
	}
	m_scrdrawer.Destroy();
	DestroyBeepPlayer();
	DestroyPcgPlayer();
//	m_DX.Dispose();

#ifdef X88_GUI_WINDOWS

	if (m_bChangedPeriod) {
		timeEndPeriod(1);
	}
	m_pMessageProcessor = NULL;

#elif defined(X88_GUI_GTK)

	if (m_pExecTimer != NULL) {
		g_timer_destroy(m_pExecTimer);
		m_pExecTimer = NULL;
	}

#endif // X88_GUI

	return true;
}

////////////////////////////////////////////////////////////
// option

// parse and execute command line option

void CX88000::ParseCommandLine() {
	m_bReadOnlyMode = false;
	int nDrive;
	for (nDrive = 0; nDrive < CPC88Fdc::DRIVE_MAX; nDrive++) {
		m_anDriveSelect[nDrive] = nDrive+1;
	}
//	m_optman.ParseCommandLine(*m_pThis, m_argc, m_argv);
	for (
		nDrive = m_pc88.Fdc().GetDriveCount();
		nDrive < CPC88Fdc::DRIVE_MAX-1;
		nDrive++)
	{
		m_anDriveSelect[nDrive] = 0;
	}
	for (nDrive = 0; nDrive < CPC88Fdc::DRIVE_MAX-1; nDrive++) {
		if (m_anDriveSelect[nDrive] <= 0) {
			continue;
		}
		for (int nDrive2 = nDrive+1; nDrive2 < CPC88Fdc::DRIVE_MAX; nDrive2++) {
			if (m_anDriveSelect[nDrive2] == m_anDriveSelect[nDrive]) {
				m_anDriveSelect[nDrive2] = 0;
			}
		}
	}
	int nDiskCount = m_pc88.GetDiskImageCollection().GetDiskImageCount();
	for (nDrive = 0; nDrive < CPC88Fdc::DRIVE_MAX; nDrive++) {
		if ((m_anDriveSelect[nDrive] > 0) &&
			(m_anDriveSelect[nDrive] <= nDiskCount))
		{
			m_pc88.Fdc().SetDiskImage(
				nDrive,
				m_pc88.GetDiskImageCollection().GetDiskImage(
					m_anDriveSelect[nDrive]-1));
		}
	}
}

// add image file

void CX88000::AddImageFile(const std::string& fstrFileName) {
	std::string strExt = ConvFStoUTF8(GetFileExt(fstrFileName));
	if (StrCaseCmp(strExt, ".t88") == 0) {
		m_pc88.Usart().GetLoadTapeImage().Load(
			fstrFileName);
	} else if (StrCaseCmp(strExt, ".cmt") == 0) {
		m_pc88.Usart().GetLoadTapeImage().LoadCMT(
			fstrFileName);
	} else {
		m_pc88.GetDiskImageCollection().AddDiskImageFile(
			fstrFileName, m_bReadOnlyMode);
	}
}

// set option to default
//
//     pszOptionName
//         option name for setting defaut

void CX88000::DefaultOption(const std::string& strOptionName) {
	std::vector<std::string> vectOptionNames;
	vectOptionNames.push_back(strOptionName);
	DefaultOptions(&vectOptionNames);
}

// set options to default
//
//     pvectOptionNames = NULL
//         options name vector for setting default
//         (NULL : all options)

void CX88000::DefaultOptions(std::vector<std::string>* pvectOptionNames) {
//	m_optman.SetDefault(*m_pThis, pvectOptionNames);
}

// save option to environment settings file
//
//     strOptionName
//         option name for saving

void CX88000::SaveOption(const std::string& strOptionName) {
	std::vector<std::string> vectOptionNames;
	vectOptionNames.push_back(strOptionName);
	SaveOptions(&vectOptionNames);
}

// save options to environment settings file
//
//     pvectOptionNames = NULL
//         options name vector for saving
//         (NULL : all options)

void CX88000::SaveOptions(std::vector<std::string>* pvectOptionNames) {
	if (m_bSaveEnv) {
//		m_optman.SaveEnvFile(*m_pThis, m_fstrEnvFileName, pvectOptionNames);
	}
}

////////////////////////////////////////////////////////////
// debug

// start debug log recording

bool CX88000::StartDebugLog() {
	if (IsDebugLogging()) {
		return false;
	}
	m_pfDebugLog = fopen(m_fstrDebugLogFileName.c_str(), "at");
	if (m_pfDebugLog != NULL) {
		m_nDebugLogCol = 0;
		OutputDebugLog(CPC88::DEBUGLOG_START);
	}
	return IsDebugLogging();
}

// stop debug log recording

bool CX88000::EndDebugLog() {
	if (!IsDebugLogging()) {
		return false;
	}
	if (m_pc88.IsDebugMode()) {
		OutputDebugLog(CPC88::DEBUGLOG_END);
	}
	fflush(m_pfDebugLog);
	fclose(m_pfDebugLog);
	m_pfDebugLog = NULL;
	return true;
}

// output debug log

void CX88000::OutputDebugLog(int nLogMode) {
	if (m_pfDebugLog != NULL) {
		if (nLogMode != CPC88::DEBUGLOG_EXECUTE) {
			if (m_nDebugLogCol > 0) {
				fputc('\n', m_pfDebugLog);
				m_nDebugLogCol = 0;
			}
		}
		switch (nLogMode) {
		case CPC88::DEBUGLOG_START:
			fprintf(
				m_pfDebugLog,
				"Log Start(%s)\n",
				m_pc88.IsDebugMain()? "Main": "Sub");
			break;
		case CPC88::DEBUGLOG_END:
			fprintf(m_pfDebugLog, "Log End\n\n");
			break;
		case CPC88::DEBUGLOG_CHANGE_CPU:
			fprintf(
				m_pfDebugLog,
				"Change CPU(%s)\n",
				m_pc88.IsDebugMain()? "Main": "Sub");
			break;
		case CPC88::DEBUGLOG_RESET:
			fprintf(m_pfDebugLog, "Reset\n");
			break;
		case CPC88::DEBUGLOG_READ_MEMIMAGE:
			fprintf(m_pfDebugLog, "Read Memory Image\n");
			break;
		}
		if (nLogMode != CPC88::DEBUGLOG_END) {
			if (m_nDebugLogCol > 0) {
				fputc(' ', m_pfDebugLog);
			}
			fprintf(
				m_pfDebugLog,
				"0%04XH",
				m_pc88.GetDebugAdapter()->RegPC().Get());
			if (++m_nDebugLogCol >= DEBUGLOG_COLMAX) {
				fputc('\n', m_pfDebugLog);
				m_nDebugLogCol = 0;
			}
		}
	}
}

// write RAM

void CX88000::WriteRam(
	bool bWriteMainRam0,
	bool bWriteMainRam1,
	bool bWriteFastTVRam,
	bool bWriteSlowTVRam,
	bool bWriteGVRam0,
	bool bWriteGVRam1,
	bool bWriteGVRam2,
	bool bWriteSubRam,
	bool bWriteExRam0,
	bool bWriteExRam1)
{
	FILE* fpt;
	std::string fstrPath;
	if (bWriteMainRam0) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "main0.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetMainRamPtr(), 0x8000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteMainRam1) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "main1.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			if (PC88().Z80Main().IsFastTVRamUse()) {
				fwrite(PC88().Z80Main().GetMainRamPtr()+0x8000, 0x7000, 1, fpt);
				fwrite(PC88().Z80Main().GetFastTVRamPtr(), 0x1000, 1, fpt);
			} else {
				fwrite(PC88().Z80Main().GetMainRamPtr()+0x8000, 0x8000, 1, fpt);
			}
			fclose(fpt);
		}
	}
	if (bWriteFastTVRam &&
		!PC88().Z80Main().IsFastTVRamUse())
	{
		fstrPath = m_fstrModuleDir;
		fstrPath += "fast_tv.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetFastTVRamPtr(), 0x1000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteSlowTVRam &&
		PC88().Z80Main().IsFastTVRamUse())
	{
		fstrPath = m_fstrModuleDir;
		fstrPath += "slow_tv.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetMainRamPtr()+0xF000, 0x1000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteGVRam0) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "gv0.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetGVRamPtr(0), 0x4000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteGVRam1) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "gv1.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetGVRamPtr(1), 0x4000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteGVRam2) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "gv2.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetGVRamPtr(2), 0x4000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteSubRam &&
		!PC88().IsSubSystemDisableNow())
	{
		fstrPath = m_fstrModuleDir;
		fstrPath += "sub.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Sub().GetSubRamPtr(), 0x4000, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteExRam0) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "ex0.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetExRamPtr(0), 0x8000*4, 1, fpt);
			fclose(fpt);
		}
	}
	if (bWriteExRam1) {
		fstrPath = m_fstrModuleDir;
		fstrPath += "ex1.ram";
		fpt = fopen(fstrPath.c_str(), "wb");
		if (fpt != NULL) {
			fwrite(PC88().Z80Main().GetExRamPtr(1), 0x8000*4, 1, fpt);
			fclose(fpt);
		}
	}
}

////////////////////////////////////////////////////////////
// disk image

// open disk image file

int CX88000::DiskImageFileOpen(
	const std::string& fstrFileName, bool& bReadOnly,
	uint8_t*& pbtData, uint32_t& dwSize)
{
	CX88DiskImageMemory dim;
	int nResult = dim.Create(fstrFileName, bReadOnly);
	if (nResult == CDiskImageFile::ERR_NOERROR) {
		bReadOnly = dim.IsReadOnly();
		pbtData = dim.GetData();
		dwSize = dim.GetSize();
		m_setX88DiskImageMemory.insert(dim);
	}
	return nResult;
}

// close disk image file

int CX88000::DiskImageFileClose(uint8_t* pbtData) {
	int nResult;
	std::set<CX88DiskImageMemory>::iterator itInfo =
		m_setX88DiskImageMemory.find(CX88DiskImageMemory(pbtData));
	if (itInfo != m_setX88DiskImageMemory.end()) {
		nResult = (*itInfo).Flush();
		(*itInfo).Destroy();
		m_setX88DiskImageMemory.erase(itInfo);
	} else {
		nResult = CDiskImageFile::ERR_ERROR;
	}
	return nResult;
}

////////////////////////////////////////////////////////////
// clipboard

// copy bitmap from screen-image to clipboard

bool CX88000::DoClipboardCopyBitmap() {
	bool bResult = true;

#ifdef X88_GUI_WINDOWS

	int nBmiSize, BitsSize;
	BITMAPINFO* pBmi;
	uint8_t* pbtBits;
	if (!PC88().Z80Main().IsVABScreenActive()) {
		nBmiSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*18;
		BitsSize = 640*400;
		pBmi = m_scrdrawer.GetScreenBitmapInfo();
		pbtBits = m_scrdrawer.GetScreenDataBits();
	} else {
		nBmiSize = sizeof(BITMAPINFOHEADER)+sizeof(uint32_t)*3;
		BitsSize = 640*400*2;
		pBmi = m_scrdrawer.GetScreenBitmapInfo2();
		pbtBits = m_scrdrawer.GetScreenDataBits2();
	}
	if (pbtBits == NULL) {
		return false;
	}
	HGLOBAL hdibClip = GlobalAlloc(GHND, nBmiSize+BitsSize);
	if (hdibClip == NULL) {
		return false;
	}
	uint8_t* pbtClip = (uint8_t*)GlobalLock(hdibClip);
	if (pbtClip == NULL) {
		GlobalUnlock(hdibClip);
		GlobalFree(hdibClip);
		return false;
	}
	uint8_t* pbtTmp = pbtClip;
	memcpy(pbtTmp, pBmi, nBmiSize);
	pbtTmp += nBmiSize;
	memcpy(pbtTmp, pbtBits, BitsSize);
	GlobalUnlock(hdibClip);
	if (OpenClipboard(m_frame.GetWndHandle())) {
		EmptyClipboard();
		SetClipboardData(CF_DIB, hdibClip);
		CloseClipboard();
	} else {
		GlobalFree(hdibClip);
	}

#elif defined(X88_GUI_GTK)

	std::string fstrFileName = GetWriteFileName();
	FILE* pFile = NULL;
	try {
		pFile = fopen(fstrFileName.c_str(), "wb");
		if (pFile == NULL) {
			throw 1;
		}
		int nDepth, nVisualClass,
			nRedMask, nGreenMask, nBlueMask,
			nColorEntries;
		uint8_t* pbtBits;
		if (!PC88().Z80Main().IsVABScreenActive()) {
			nDepth = 8;
			nVisualClass = 3;
			nRedMask = nGreenMask = nBlueMask = 0;
			nColorEntries = 18;
			pbtBits = m_scrdrawer.GetScreenDataBits();
		} else {
			nDepth = 24;
			nVisualClass = 5;
			nRedMask = 0x00FF0000;
			nGreenMask = 0x0000FF00;
			nBlueMask = 0x000000FF;
			nColorEntries = 0;
			pbtBits = m_scrdrawer.GetScreenDataBits2();
		}
		int nScanLine = (640*nDepth+7)/8,
			nBytesPerLine = ((640*nDepth+31)/32)*4;
		{ // dummy block
			uint32_t adwHeader[25];
			// header_size
			adwHeader[0] = sizeof(adwHeader);
			// file_version
			adwHeader[1] = 7;
			// pixmap_format
			adwHeader[2] = 2;
			// pixmap_depth
			adwHeader[3] = nDepth;
			// pixmap_width
			adwHeader[4] = 640;
			// pixmap_height
			adwHeader[5] = 400;
			// xoffset
			adwHeader[6] = 0;
			// byte_order
			adwHeader[7] = 1;
			// bitmap_unit
			adwHeader[8] = 32;
			// bitmap_bit_order
			adwHeader[9] = 1;
			// bitmap_pad
			adwHeader[10] = 32;
			// bits_per_pixel
			adwHeader[11] = nDepth;
			// bytes_per_line
			adwHeader[12] = nBytesPerLine;
			// visual_class
			adwHeader[13] = nVisualClass;
			// red_mask
			adwHeader[14] = nRedMask;
			// green_mask
			adwHeader[15] = nGreenMask;
			// blue_mask
			adwHeader[16] = nBlueMask;
			// bits_per_rgb
			adwHeader[17] = 8;
			// colormap_entries
			adwHeader[18] = nColorEntries;
			// ncolors
			adwHeader[19] = nColorEntries;
			// window_width
			adwHeader[20] = 640;
			// window_height
			adwHeader[21] = 400;
			// window_x
			adwHeader[22] = 64;
			// window_y
			adwHeader[23] = 64;
			// window_bdrwidth
			adwHeader[24] = 0;
			for (int i = 0; i < 25; i++) {
				uint8_t abtTmp[4];
				for (int j = 0; j < 4; j++) {
					abtTmp[j] = (uint8_t)((adwHeader[i] >> (24-j*8)) & 0xFF);
				}
				if (fwrite(abtTmp, 1, 4, pFile) != 4) {
					throw 2;
				}
			}
		}
		if (nColorEntries > 0) {
			GdkColor* pColorTable = m_scrdrawer.GetColorTable();
			uint8_t abtTmp[12];
			memset(abtTmp, 0, sizeof(abtTmp));
			abtTmp[10] = 7;
			for (int nColor = 0; nColor < nColorEntries; nColor++) {
				abtTmp[3] = (uint8_t)nColor;
				abtTmp[4] = (uint8_t)((pColorTable[nColor].red >> 8) & 0xFF);
				abtTmp[5] = (uint8_t)(pColorTable[nColor].red & 0xFF);
				abtTmp[6] = (uint8_t)((pColorTable[nColor].green >> 8) & 0xFF);
				abtTmp[7] = (uint8_t)(pColorTable[nColor].green & 0xFF);
				abtTmp[8] = (uint8_t)((pColorTable[nColor].blue >> 8) & 0xFF);
				abtTmp[9] = (uint8_t)(pColorTable[nColor].blue & 0xFF);
				if (fwrite(abtTmp, 1, 12, pFile) != 12) {
					throw 3;
				}
			}
		}
		for (int y = 0; y < 400; y++) {
			if (fwrite(pbtBits, 1, nScanLine, pFile) != (size_t)nScanLine) {
				throw 4;
			}
			pbtBits += nScanLine;
			if (nBytesPerLine > nScanLine) {
				for (int i = nScanLine; i < nBytesPerLine; i++) {
					if (fputc(0, pFile) == EOF) {
						throw 5;
					}
				}
			}
		}
		if (ferror(pFile) != 0) {
			throw 6;
		}
		if (fflush(pFile) != 0) {
			throw 7;
		}
	} catch (int /*nError*/) {
		bResult = false;
	}
	if (pFile != NULL) {
		fclose(pFile);
	}

#endif // X88_GUI

	return bResult;
}

// copy text from text VRAM to clipboard

bool CX88000::DoClipboardCopyText() {
	bool bResult = true;
	int nWidth = m_pc88.Crtc().IsWidth80()? 80: 40,
		nHeight = m_pc88.Crtc().IsHeight25()? 25: 20;
	std::string jstrText;
	int nOfs = 0;
	for (int y = 0; y < nHeight; y++) {
		int nSpace = 0;
		for (int x = 0; x < nWidth; x++) {
			uint8_t btTextChar = m_scrdrawer.GetTextChar(nOfs),
				btTextAttr = m_scrdrawer.GetTextAttr(nOfs);
			uint16_t wChar;
			if (((btTextAttr & CX88ScreenDrawer::TATTR_GRAPHIC) != 0) ||
				(btTextChar <= 0x20) ||
				((btTextChar > 0x7E) && (btTextChar < 0xA1)) ||
				(btTextChar > 0xDF))
			{
				wChar = 0x20;
			} else if ((btTextChar >= 0xA1) && (btTextChar <= 0xDF)) {

#ifdef X88_PLATFORM_WINDOWS

				wChar = btTextChar;

#elif defined(X88_PLATFORM_UNIX)

				wChar = (uint16_t)JIS2SJIS(JISHan2Zen(btTextChar));

#endif // X88_PLATFORM

			} else {
				wChar = btTextChar;
			}
			if (wChar != 0x20) {
				for (; nSpace > 0; nSpace--) {
					jstrText += ' ';
				}
				if (wChar > 0xFF) {
					jstrText += (char)(wChar >> 8);
				}
				jstrText += (char)(wChar & 0xFF);
			} else {
				nSpace++;
			}
			nOfs += (nWidth <= 40)? 2: 1;
		}
		if ((nSpace > 0) || (y == nHeight-1)) {

#ifdef X88_PLATFORM_WINDOWS

			jstrText += "\r\n";

#elif defined(X88_PLATFORM_UNIX)

			jstrText += '\n';

#endif // X88_PLATFORM

		}
	}

#ifdef X88_GUI_WINDOWS

	HGLOBAL hgText = GlobalAlloc(GHND, jstrText.size()+1);
	if (hgText != NULL) {
		char* pszText = (char*)GlobalLock(hgText);
		if (pszText != NULL) {
			strcpy(pszText, jstrText.c_str());
			GlobalUnlock(hgText);
			if (OpenClipboard(m_frame.GetWndHandle())) {
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hgText);
				CloseClipboard();
				hgText = NULL;
			}
		}
		if (hgText != NULL) {
			GlobalFree(hgText);
		}
	}

#elif defined(X88_GUI_GTK)

	std::string gstrText =
		ConvUTF8toGUI(ConvSJIStoUTF8(jstrText));
	gtk_clipboard_set_text(
		gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),
		gstrText.c_str(),
		gstrText.size());
	gtk_clipboard_store(
		gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));

#endif // X88_GUI

	return bResult;
}

// paste text from clipboard to keyboard-input

bool CX88000::DoClipboardPasteText() {
	bool bResult = true;

#ifdef X88_GUI_WINDOWS

	if (OpenClipboard(m_frame.GetWndHandle())) {
		HGLOBAL hgText = GetClipboardData(CF_TEXT);
		if (hgText != NULL) {
			char* pszText = (char*)GlobalLock(hgText);
			AddIMEChar(pszText);
			GlobalUnlock(hgText);
		}
		CloseClipboard();
	}

#elif defined(X88_GUI_GTK)

	gtk_clipboard_request_text(
		gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),
		OnReceivedClipboardText,
		NULL);

#endif // X88_GUI

	return bResult;
}

#ifdef X88_GUI_GTK

// clipboard text received callback

void CX88000::OnReceivedClipboardText(
	GtkClipboard* /*pClipboard*/,
	const gchar* pgszText,
	gpointer /*pData*/)
{
	if (pgszText != NULL) {
		AddIMEChar(pgszText);
	}
}

#endif // X88_GUI

////////////////////////////////////////////////////////////
// sound

// pause sound

//void CX88000::PauseSound() {
//	if (m_nSoundPauseCount++ <= 0) {
//		if (m_pBeepPlayer != NULL) {
//			if (m_pBeepPlayer->IsPlaying()) {
//				m_pBeepPlayer->Play(false);
//			}
//		}
//		for (int nChannel = 0; nChannel < 3; nChannel++) {
//			if (m_apPcgPlayer[nChannel] != NULL) {
//				if (m_apPcgPlayer[nChannel]->IsPlaying()) {
//					m_apPcgPlayer[nChannel]->Play(false);
//				}
//			}
//		}
//	}
//}

// restart sound

//void CX88000::RestartSound() {
//	if (m_nSoundPauseCount > 0) {
//		m_nSoundPauseCount--;
//	}
//}

////////////////////////////////////////////////////////////
// parallel device

// select parallel device

bool CX88000::SelectParallelDevice(int nConnectedParallelDeviceNoNew) {
	if ((nConnectedParallelDeviceNoNew < 0) )//||
//		(nConnectedParallelDeviceNoNew >= (int)m_paraman.size()))
	{
		return false;
	}
	if (nConnectedParallelDeviceNoNew == m_nConnectedParallelDeviceNo) {
		return true;
	}
//	m_paraman[m_nConnectedParallelDeviceNo].Device()->Initialize();
	m_nConnectedParallelDeviceNo = nConnectedParallelDeviceNoNew;
	//m_pc88.Z80Main().SetParallelDevice(
	//	*m_paraman[m_nConnectedParallelDeviceNo].Device());
	//m_paraman[m_nConnectedParallelDeviceNo].Device()->Initialize();
	//m_paraman[m_nConnectedParallelDeviceNo].Device()->Reset();
	return true;
}

////////////////////////////////////////////////////////////
// beep

// create beep player

void CX88000::CreateBeepPlayer() {
//	if (m_pBeepPlayer == NULL) {

#ifdef X88_GUI_WINDOWS

		m_pBeepPlayer = new CX88BeepPlayerDirectSound(GetDX());
		if (!m_pBeepPlayer->Create()) {
			delete m_pBeepPlayer;
			m_pBeepPlayer = NULL;
		}

#endif // X88_GUI

//	}
//	UpdateBeepPlayerVolumeMute();
}

// destroy beep player

void CX88000::DestroyBeepPlayer() {
//	if (m_pBeepPlayer != NULL) {
//		delete m_pBeepPlayer;
//		m_pBeepPlayer = NULL;
//	}
}

// update beep player volume and mute

void CX88000::UpdateBeepPlayerVolumeMute() {
//	if (m_pBeepPlayer != NULL) {
//		m_pBeepPlayer->SetVolume(m_nBeepPlayerVolume);
//		m_pBeepPlayer->SetMute(m_bBeepPlayerMute);
//	}
}

// beep output

void CX88000::BeepOutput(
	bool bBeepPortStatus, bool bExBeepPortStatus)
{
	if (bBeepPortStatus != m_bBeepPortStatus) {
		m_bBeepPortStatus = bBeepPortStatus;
		m_anBeepQueue[m_nBeepQueuePtr]++;
	}
	if (bExBeepPortStatus != m_bExBeepPortStatus) {
		m_bExBeepPortStatus = bExBeepPortStatus;
		m_anExBeepQueue[m_nBeepQueuePtr]++;
	}
}

////////////////////////////////////////////////////////////
// PCG sound

// create PCG sound player

void CX88000::CreatePcgPlayer() {
	for (int nChannel = 0; nChannel < 3; nChannel++) {
//		if (m_apPcgPlayer[nChannel] == NULL) {

#ifdef X88_GUI_WINDOWS

			m_apPcgPlayer[nChannel] = new CX88BeepPlayerDirectSound(GetDX());
			if (!m_apPcgPlayer[nChannel]->Create()) {
				delete m_apPcgPlayer[nChannel];
				m_apPcgPlayer[nChannel] = NULL;
			}

#endif // X88_GUI

//		}
	}
	UpdatePcgPlayerVolumeMute();
}

// destroy PCG sound player

void CX88000::DestroyPcgPlayer() {
	for (int nChannel = 0; nChannel < 3; nChannel++) {
//		if (m_apPcgPlayer[nChannel] != NULL) {
//			delete m_apPcgPlayer[nChannel];
//			m_apPcgPlayer[nChannel] = NULL;
//		}
	}
}

// update PCG sound player volume and mute

void CX88000::UpdatePcgPlayerVolumeMute() {
	for (int nChannel = 0; nChannel < 3; nChannel++) {
//		if (m_apPcgPlayer[nChannel] != NULL) {
//			m_apPcgPlayer[nChannel]->SetVolume(m_nPcgPlayerVolume);
//			m_apPcgPlayer[nChannel]->SetMute(m_bPcgPlayerMute);
//		}
	}
}

// PCG sound output

void CX88000::PcgSoundOutput(int nChannel, int nCounter) {
	if (nCounter == 0) {
		m_anPcgFrequency[nChannel] = 4000000/0x10000;
	} else if (nCounter > 0x100) {
		m_anPcgFrequency[nChannel] = 4000000/nCounter;
	} else {
		m_anPcgFrequency[nChannel] = 0;
	}
}

////////////////////////////////////////////////////////////
// implementation


#ifdef X88_GUI_GTK

// idle callback

gboolean CX88000::IdleCallback(gpointer /*pData*/) {
	OnIdle();
	return TRUE;
}

#endif // X88_GUI

////////////////////////////////////////////////////////////
// operation

// open system file
//     (first: current directory, second: module directory)

File CX88000::SysFileOpen(const std::string& strName) {
	std::string fstrName = ConvUTF8toFS(strName);
	Serial.println("SYSFILE OPEN:");
	Serial.println(fstrName.c_str());
#ifdef X88_PLATFORM_UNIX

	std::string strName2;
	char ch;
	for (
		const char* pszName = strName.c_str();
		(ch = *pszName) != '\0';
		pszName++)
	{
		if ((ch >= 'a') && (ch <= 'z')) {
			ch = toupper(ch);
		}
		strName2 += ch;
	}
	std::string gstrName2 = ConvUTF8toGUI(strName2);

#endif // X88_PLATFORM

	//FILE* fpt;
	File file;
	std::string fstrPath;
	fstrPath = m_fstrStartDir;
	fstrPath += fstrName;
	//fpt = fopen(fstrPath.c_str() , "rb");
	file = SD.open(String("/PC88ROM/") + String(strName.c_str()));


#ifdef X88_PLATFORM_UNIX

	//if (fpt == NULL) {
	//	fstrPath = m_fstrStartDir;
	//	fstrPath += gstrName2;
	//	fpt = fopen(fstrPath.c_str() , "rb");
	//}

#endif // X88_PLATFORM

	//if (fpt == NULL) {
	//	fstrPath = m_fstrModuleDir;
	//	fstrPath += fstrName;
	//	fpt = fopen(fstrPath.c_str(), "rb");
	//}

#ifdef X88_PLATFORM_UNIX

	//if (fpt == NULL) {
	//	fstrPath = m_fstrModuleDir;
	//	fstrPath += gstrName2;
	//	fpt = fopen(fstrPath.c_str(), "rb");
	//}

#endif // X88_PLATFORM

	return file;
}

// add IME input character(GUI encoding)
//     (and used from text-paste)

void CX88000::AddIMEChar(const std::string& gstrIME) {
	std::string jstrIME =
		ConvUTF8toSJIS(ConvGUItoUTF8(gstrIME));
	for (
		const char* pjszIME = jstrIME.c_str();
		*pjszIME != '\0';
		pjszIME++)
	{
		uint8_t btIME = (uint8_t)(*pjszIME);
		bool bDakuten = false, bHandakuten = false;
		if (IsSJISLeadByte(btIME) &&
			(*(pjszIME+1) != '\0'))
		{
			pjszIME++;
			unsigned nIME = SJIS2JIS(
				(btIME << 8) | (uint8_t)(*pjszIME));
			if (nIME <= 0xFF) {
				btIME = (uint8_t)nIME;
			} else {
				btIME = (uint8_t)JISZen2Han(
					nIME, &bDakuten, &bHandakuten);
			}
		}
		if ((btIME >= 0x20) && (btIME <= 0x7E)) {
			m_queueIMEChar.push(m_awIMECharTable[btIME-0x20]);
		} else if ((btIME >= 0xA1) && (btIME <= 0xDF)) {
			m_queueIMEChar.push(m_awIMECharTable[btIME-0x40]);
			if (bDakuten) {
				m_queueIMEChar.push(m_awIMECharTable[0x9E]); // 0xDE-0x40
			} else if (bHandakuten) {
				m_queueIMEChar.push(m_awIMECharTable[0x9F]); // 0xDF-0x40
			}
		} else if (btIME == 0x0A) {
			m_queueIMEChar.push(m_awIMECharTable[0xA0]);
		} else if (btIME == 0x09) {
			m_queueIMEChar.push(m_awIMECharTable[0xA1]);
		}
	}
}

// reset execute counter

void CX88000::ResetExecuteCounter() {

#ifdef X88_GUI_WINDOWS

	m_dwExecTime1 = timeGetTime();
	do {
		m_dwExecTime2 = timeGetTime();
	} while (m_dwExecTime2 == m_dwExecTime1);

#elif defined(X88_GUI_GTK)

	m_dwExecTime1 = (uint32_t)(g_timer_elapsed(m_pExecTimer, NULL)*1000);
	do {
		m_dwExecTime2 = (uint32_t)(g_timer_elapsed(m_pExecTimer, NULL)*1000);
	} while (m_dwExecTime2 == m_dwExecTime1);

#endif // X88_GUI

	m_dwExecTime1 = m_dwExecTime2;
	m_dwExecPassCounter1 = m_dwExecPassCounter2 = 0;
}

// execute reset

void CX88000::DoReset() {

#ifdef X88_PLATFORM_WINDOWS

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	m_pc88.Calendar().SetSecond(systime.wSecond);
	m_pc88.Calendar().SetMinute(systime.wMinute);
	m_pc88.Calendar().SetHour(systime.wHour);
	m_pc88.Calendar().SetDay(systime.wDay);
	m_pc88.Calendar().SetWDay(systime.wDayOfWeek);
	m_pc88.Calendar().SetMonth(systime.wMonth);
	m_pc88.Calendar().SetYear(systime.wYear%100);

#elif defined(X88_PLATFORM_UNIX)

	time_t timeNow;
	time(&timeNow);
	struct tm* ptmNow = localtime(&timeNow);

	m_pc88.Calendar().SetSecond(ptmNow->tm_sec);
	m_pc88.Calendar().SetMinute(ptmNow->tm_min);
	m_pc88.Calendar().SetHour(ptmNow->tm_hour);
	m_pc88.Calendar().SetDay(ptmNow->tm_mday);
	m_pc88.Calendar().SetWDay(ptmNow->tm_wday);
	m_pc88.Calendar().SetMonth(ptmNow->tm_mon+1);
	m_pc88.Calendar().SetYear(ptmNow->tm_year);

#endif // X88_PLATFORM

	m_pc88.Reset();
	//if (PC88().IsDebugMode()) {
	//	m_frame.UpdateDebugWnd();
	//}
	OutputDebugLog(CPC88::DEBUGLOG_RESET);
}

// execute X88000

int CX88000::Execute() {
	if (!Initialize()) {
		Dispose();
		return 0;
	}
	Serial.println("Initialize Done!");
	ResetExecuteCounter();
	int nResult;

	//画面描画スレッド起動
	xTaskCreatePinnedToCore(
        scrn_thread,     /* Function to implement the task */
        "scrn_thread",   /* Name of the task */
        4096,      /* Stack size in words */
        NULL,      /* Task input parameter */
        1,         /* Priority of the task */
        NULL,      /* Task handle. */
        1);        /* Core where the task should run */

	//Emulator loop
	bool bQuit = false;

	while(bQuit == false){
		OnIdle();
		//キー入力
		CheckKeyInput();
	}


#ifdef X88_GUI_WINDOWS

	MSG msg;
	bool bQuit = false;
	do {
		OnIdle();
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (GetMessage(&msg, NULL, 0, 0)) {
				if (!m_pMessageProcessor->ProcessMessage(&msg)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			} else {
				bQuit = true;
				break;
			}
		}
	} while (!bQuit);
	nResult = int(msg.wParam);

#elif defined(X88_GUI_GTK)

	m_nIdleID = g_idle_add(IdleCallback, NULL);

	gtk_main();

	g_source_remove(m_nIdleID);
	m_nIdleID = 0;
	nResult = 0;

#endif // X88_GUI

	Dispose();
	return nResult;
}

// idle process

void CX88000::OnIdle() {

	m_dwExecTime2 = millis();

#ifdef X88_GUI_WINDOWS

	m_dwExecTime2 = timeGetTime();

#elif defined(X88_GUI_GTK)

	if (CX88Dialog::GetModalCounter() > 0) {
		DoSleep(1);
		return;
	}
	m_dwExecTime2 = (uint32_t)(g_timer_elapsed(m_pExecTimer, NULL)*1000);

#endif // X88_GUI

	//if (m_pc88.IsDebugMode() && m_pc88.IsDebugStopped()) {
		//if ((m_pBeepPlayer != NULL) &&
		//	m_pBeepPlayer->IsPlaying())
		//{
		//	m_pBeepPlayer->Play(false);
		//}
		//for (int nChannel = 0; nChannel < 3; nChannel++) {
		//	if ((m_apPcgPlayer[nChannel] != NULL) &&
		//		m_apPcgPlayer[nChannel]->IsPlaying())
		//	{
		//		m_apPcgPlayer[nChannel]->Play(false);
		//	}
		//}
		//m_pc88.Z80Main().ParallelDevice().OnIdle(EXECUTE_UNIT_TIME);
	//	DoSleep(1);
	//	return;
	//} else 
/*
	if (m_bBoostMode) {
		if ((m_nBoostLimiter > 0) &&
			(uint32_t(m_dwExecTime2-m_dwExecTime1)+10)*m_nBoostLimiter <
				(m_dwExecPassCounter2-m_dwExecPassCounter1)*100)
		{
			DoSleep(1);
			return;
		}
	} else {
		if (uint32_t(m_dwExecTime2-m_dwExecTime1)+10 <
				(m_dwExecPassCounter2-m_dwExecPassCounter1))
		{
			DoSleep(1);
			return;
		}
	}
	if (uint32_t(m_dwExecTime2-m_dwExecTime1) >= 1000) {
		//m_frame.ShowFrequency(
		//	double(uint32_t(m_dwExecPassCounter2-m_dwExecPassCounter1)*
		//			m_pc88.Z80Main().GetBaseClock())/
		//		uint32_t(m_dwExecTime2-m_dwExecTime1));
		m_dwExecTime1 = m_dwExecTime2;
		m_dwExecPassCounter1 = m_dwExecPassCounter2;
	}
*/
	//Serial.println("OnIdle 1");
	int nExecClock = m_pc88.Z80Main().GetBaseClock()*1000*EXECUTE_UNIT_TIME;
	if (!m_pc88.IsDebugMode()) {
		//Serial.println("OnIdle 2");
		m_pc88.Execute(nExecClock);


		//Serial.println("OnIdle 3");
	} else {
		m_pc88.DebugExecute(nExecClock);
		if (m_pc88.IsDebugStopped()) {
		//	m_frame.UpdateDebugWnd();
			ResetExecuteCounter();
		}
		PC88().SetMnemonicUpdated(true);
	}
	//m_pc88.Z80Main().ParallelDevice().OnIdle(EXECUTE_UNIT_TIME);
	//if (m_pc88.IsDebugMode() && m_pc88.IsDebugStopped()) {
	//	if ((m_pBeepPlayer != NULL) &&
	//		m_pBeepPlayer->IsPlaying())
	//	{
	//		m_pBeepPlayer->Play(false);
	//	}
	//	for (int nChannel = 0; nChannel < 3; nChannel++) {
	//		if ((m_apPcgPlayer[nChannel] != NULL) &&
	//			m_apPcgPlayer[nChannel]->IsPlaying())
	//		{
	//			m_apPcgPlayer[nChannel]->Play(false);
	//		}
	//	}
	//	return;
	//}
	//Serial.println("OnIdle 4");
	/*
	m_dwExecPassCounter2 += EXECUTE_UNIT_TIME;
	if (m_queueIMEChar.size() > 0) {
		// key input from IME
		bool bPressedESC = false;//m_frame.IsPressedESC();
		m_pc88.Z80Main().ClearKeyMatrics();
		uint16_t wIMEChar = m_queueIMEChar.front();
		if (wIMEChar != 0xFFFF) {
			if (!bPressedESC) {
				m_pc88.Z80Main().SetKeyMatrics(
					0x08, 6,
					(wIMEChar & 0x0100) != 0);
				m_pc88.Z80Main().SetKeyMatrics(
					0x08, 5,
					(wIMEChar & 0x1000) != 0);
				if ((m_nIMECharWait >= IME_WAIT/4) &&
					(m_nIMECharWait >= (IME_WAIT*3)/4))
				{
					m_pc88.Z80Main().SetKeyMatrics(
						(wIMEChar >> 4) & 0x000F, wIMEChar & 0x0007,
						true);
				}
				m_nIMECharWait += EXECUTE_UNIT_TIME;
				if (m_nIMECharWait >= IME_WAIT) {
					m_nIMECharWait = 0;
					m_queueIMEChar.pop();
				}
			} else {
				while (m_queueIMEChar.size() > 0) {
					m_queueIMEChar.pop();
				}
				m_queueIMEChar.push((uint16_t)0xFFFF);
			}
		} else {
			if (!bPressedESC) {
				m_queueIMEChar.pop();
				m_nIMECharWait = 0;
			}
		}
	} else {
		// key input from keyboard(like a redundancy :-)
		//m_frame.UpdateAllKeyMatrics();
	}
	*/
	m_nBeepUpdateCount += m_anBeepQueue[m_nBeepQueuePtr];
	m_nExBeepUpdateCount += m_anExBeepQueue[m_nBeepQueuePtr];
	if (++m_nBeepQueuePtr >= BEEP_TIME/EXECUTE_UNIT_TIME) {
		m_nBeepQueuePtr = 0;
	}
	if (m_nSoundPauseCount <= 0) {
		//if (m_pBeepPlayer != NULL) {
		//	int nFrequency = 0;
		//	if (m_nExBeepUpdateCount > 0) {
		//		nFrequency = (m_nExBeepUpdateCount*(1000/BEEP_TIME))/2;
		//	} else if (m_nBeepUpdateCount > 1) {
		//		nFrequency = (m_nBeepUpdateCount*(1000/BEEP_TIME))/2;
		//	} else if (m_bBeepPortStatus) {
		//		nFrequency = CX88BeepPlayer::BEEP_FREQUENCY;
		//	}
		//	if (nFrequency > 0) {
		//		if (nFrequency != m_pBeepPlayer->GetFrequency()) {
		//			m_pBeepPlayer->SetFrequency(nFrequency);
		//		}
		//		if (!m_pBeepPlayer->IsPlaying()) {
		//			m_pBeepPlayer->Play(true);
		//		}
		//	} else {
		//		if (m_pBeepPlayer->IsPlaying()) {
		//			m_pBeepPlayer->Play(false);
		//		}
		//	}
		//}
		//for (int nChannel = 0; nChannel < 3; nChannel++) {
		//	if (m_apPcgPlayer[nChannel] != NULL) {
		//		if (m_anPcgFrequency[nChannel] > 0) {
		//			if (m_anPcgFrequency[nChannel] !=
		//					m_apPcgPlayer[nChannel]->GetFrequency())
		//			{
		//				m_apPcgPlayer[nChannel]->SetFrequency(
		//					m_anPcgFrequency[nChannel]);
		//			}
		//			if (!m_apPcgPlayer[nChannel]->IsPlaying()) {
		//				m_apPcgPlayer[nChannel]->Play(true);
		//			}
		//		} else {
		//			if (m_apPcgPlayer[nChannel]->IsPlaying()) {
		//				m_apPcgPlayer[nChannel]->Play(false);
		//			}
		//		}
		//	}
		//}
	}
	m_nBeepUpdateCount -= m_anBeepQueue[m_nBeepQueuePtr];
	m_anBeepQueue[m_nBeepQueuePtr] = 0;
	m_nExBeepUpdateCount -= m_anExBeepQueue[m_nBeepQueuePtr];
	m_anExBeepQueue[m_nBeepQueuePtr] = 0;
	
    M5.update();
	if(M5.BtnB.wasReleased()){
		m_btnBLongPressFlag = false;
	}
    if(M5.BtnB.pressedFor(2000)){
      if(m_btnBLongPressFlag != true){
        m_btnBLongPressFlag = true;
        //B長押しで、テープ選択画面
        //選択時は画面描画止める
        m_suspendScrnThreadFlag = true;
        selectD88();
        delay(100);
        m_suspendScrnThreadFlag = false;
      }
    } 

	//erial.println("OnIdle End");
	delay(1);
}

// sleep process

void CX88000::DoSleep(int nMilliSec) {

#ifdef X88_GUI_WINDOWS

	Sleep(nMilliSec);

#elif defined(X88_GUI_GTK)

	g_usleep(1000L*nMilliSec);

#endif // X88_GUI
	delay(nMilliSec);
}

#define CARDKB_ADDR 0x5F

void CX88000::CheckKeyInput() {
	//Serial.println("CheckInput");
	if(m_lastKeyCode != 0){
		m_keyInputCounter++;
		if(m_keyInputCounter <= 20){
			return;
		}
		m_keyInputCounter = 0;
		ChangeKeyMatricsStatus(m_lastKeyCode, false);
		m_lastKeyCode = 0;
	}
	int i2cKeyCode = 0;  
  	if(Wire.requestFrom(CARDKB_ADDR, 1)){  // request 1 byte from keyboard
    	while (Wire.available()) {
    	  i2cKeyCode = Wire.read();                  // receive a byte as 
      		break;
    	}
	}
	if(i2cKeyCode == 0){
		return;
	}

	ChangeKeyMatricsStatus(i2cKeyCode, true);
	m_lastKeyCode = i2cKeyCode;
}

void CX88000::ChangeKeyMatricsStatus(int charCode, bool bPressed){
	int nAddress = 0;
	int nBit = 0;
	bool bShift = false;
	switch(charCode){
	//http://www.maroon.dti.ne.jp/youkan/pc88/iomap.html
		case '@': nAddress = 0x02;nBit = 0;break;
		case 'a': nAddress = 0x02;nBit = 1;break;
		case 'b': nAddress = 0x02;nBit = 2;break;
		case 'c': nAddress = 0x02;nBit = 3;break;
		case 'd': nAddress = 0x02;nBit = 4;break;
		case 'e': nAddress = 0x02;nBit = 5;break;
		case 'f': nAddress = 0x02;nBit = 6;break;
		case 'g': nAddress = 0x02;nBit = 7;break;
		case 'h': nAddress = 0x03;nBit = 0;break;
		case 'i': nAddress = 0x03;nBit = 1;break;
		case 'j': nAddress = 0x03;nBit = 2;break;
		case 'k': nAddress = 0x03;nBit = 3;break;
		case 'l': nAddress = 0x03;nBit = 4;break;
		case 'm': nAddress = 0x03;nBit = 5;break;
		case 'n': nAddress = 0x03;nBit = 6;break;
		case 'o': nAddress = 0x03;nBit = 7;break;
		case 'p': nAddress = 0x04;nBit = 0;break;
		case 'q': nAddress = 0x04;nBit = 1;break;
		case 'r': nAddress = 0x04;nBit = 2;break;
		case 's': nAddress = 0x04;nBit = 3;break;
		case 't': nAddress = 0x04;nBit = 4;break;
		case 'u': nAddress = 0x04;nBit = 5;break;
		case 'v': nAddress = 0x04;nBit = 6;break;
		case 'w': nAddress = 0x04;nBit = 7;break;
		case 'x': nAddress = 0x05;nBit = 0;break;
		case 'y': nAddress = 0x05;nBit = 1;break;
		case 'z': nAddress = 0x05;nBit = 2;break;

		case 'A': nAddress = 0x02;nBit = 1;bShift = true;break;
		case 'B': nAddress = 0x02;nBit = 2;bShift = true;break;
		case 'C': nAddress = 0x02;nBit = 3;bShift = true;break;
		case 'D': nAddress = 0x02;nBit = 4;bShift = true;break;
		case 'E': nAddress = 0x02;nBit = 5;bShift = true;break;
		case 'F': nAddress = 0x02;nBit = 6;bShift = true;break;
		case 'G': nAddress = 0x02;nBit = 7;bShift = true;break;
		case 'H': nAddress = 0x03;nBit = 0;bShift = true;break;
		case 'I': nAddress = 0x03;nBit = 1;bShift = true;break;
		case 'J': nAddress = 0x03;nBit = 2;bShift = true;break;
		case 'K': nAddress = 0x03;nBit = 3;bShift = true;break;
		case 'L': nAddress = 0x03;nBit = 4;bShift = true;break;
		case 'M': nAddress = 0x03;nBit = 5;bShift = true;break;
		case 'N': nAddress = 0x03;nBit = 6;bShift = true;break;
		case 'O': nAddress = 0x03;nBit = 7;bShift = true;break;
		case 'P': nAddress = 0x04;nBit = 0;bShift = true;break;
		case 'Q': nAddress = 0x04;nBit = 1;bShift = true;break;
		case 'R': nAddress = 0x04;nBit = 2;bShift = true;break;
		case 'S': nAddress = 0x04;nBit = 3;bShift = true;break;
		case 'T': nAddress = 0x04;nBit = 4;bShift = true;break;
		case 'U': nAddress = 0x04;nBit = 5;bShift = true;break;
		case 'V': nAddress = 0x04;nBit = 6;bShift = true;break;
		case 'W': nAddress = 0x04;nBit = 7;bShift = true;break;
		case 'X': nAddress = 0x05;nBit = 0;bShift = true;break;
		case 'Y': nAddress = 0x05;nBit = 1;bShift = true;break;
		case 'Z': nAddress = 0x05;nBit = 2;bShift = true;break;

		case '^': nAddress = 0x05;nBit = 6;break;
		case '-': nAddress = 0x05;nBit = 7;break;
		case '=': nAddress = 0x05;nBit = 7;bShift = true;break;

		case '[': nAddress = 0x05;nBit = 3;break;
		case '\\': nAddress = 0x05;nBit = 4;break;
		case ']': nAddress = 0x05;nBit = 5;break;

		case ';': nAddress = 0x07;nBit = 2;break;
		case ':': nAddress = 0x07;nBit = 3;break;
		case ',': nAddress = 0x07;nBit = 4;break;
		case '.': nAddress = 0x07;nBit = 5;break;
		case '/': nAddress = 0x07;nBit = 6;break;
		case '_': nAddress = 0x07;nBit = 7;break;

		case '+': nAddress = 0x07;nBit = 2;bShift = true;break;
		case '*': nAddress = 0x07;nBit = 3;bShift = true;break;
		case '<': nAddress = 0x07;nBit = 4;break;
		case '>': nAddress = 0x07;nBit = 5;break;
		case '?': nAddress = 0x07;nBit = 6;break;

		case '0': nAddress = 0x06;nBit = 0;break;
		case '1': nAddress = 0x06;nBit = 1;break;
		case '2': nAddress = 0x06;nBit = 2;break;
		case '3': nAddress = 0x06;nBit = 3;break;
		case '4': nAddress = 0x06;nBit = 4;break;
		case '5': nAddress = 0x06;nBit = 5;break;
		case '6': nAddress = 0x06;nBit = 6;break;
		case '7': nAddress = 0x06;nBit = 7;break;
		case '8': nAddress = 0x07;nBit = 0;break;
		case '9': nAddress = 0x07;nBit = 1;break;

		case '!': nAddress = 0x06;nBit = 1;bShift = true;break;
		case '"': nAddress = 0x06;nBit = 2;bShift = true;break;
		case '#': nAddress = 0x06;nBit = 3;bShift = true;break;
		case '$': nAddress = 0x06;nBit = 4;bShift = true;break;
		case '%': nAddress = 0x06;nBit = 5;bShift = true;break;
		case '&': nAddress = 0x06;nBit = 6;bShift = true;break;
		case '\'': nAddress = 0x06;nBit = 7;bShift = true;break;
		case '(': nAddress = 0x07;nBit = 0;bShift = true;break;
		case ')': nAddress = 0x07;nBit = 1;bShift = true;break;
		
		case 0x20: nAddress = 0x09;nBit = 6;break;//SPACE

		case 0xB5: nAddress = 0x08;nBit = 1;break; //↑
		case 0xB6: nAddress = 0x08;nBit = 1;bShift = true;break; //↓
		case 0xB7: nAddress = 0x08;nBit = 2;break; //→
		case 0xB4: nAddress = 0x08;nBit = 2;bShift = true;break; //←
		case 0x08: nAddress = 0x08;nBit = 3;break; //DELETE
		case 0x7F: nAddress = 0x08;nBit = 3;bShift = true;break; //INSERT
		case 0x0d: nAddress = 0x01;nBit = 7;break; //ENTER

		case 0x09: nAddress = 0x0A;nBit = 0;break; //TAB
		case 0x1B: nAddress = 0x09;nBit = 7;break; //ESC
		case 0x80: nAddress = 0x01;nBit = 7;break; //Fn+ESC -> STOP
	}

	if(nAddress != 0){
		if(bShift == true){
			m_pc88.Z80Main().SetKeyMatrics(0x08, 6, bPressed);	
		}else{
			m_pc88.Z80Main().SetKeyMatrics(0x08, 6, false);	
		}
		m_pc88.Z80Main().SetKeyMatrics(nAddress, nBit, bPressed);
	}
}

//画面更新スレッド
//--------------------------------------------------------------
// 画面描画スレッド 
//--------------------------------------------------------------
void CX88000::scrn_thread(void *arg){
	long synctime = 500;// 2fps
    long timeTmp;
    long vsyncTmp;
	while(true){
		if(m_suspendScrnThreadFlag == false){
			timeTmp = millis();
			m_view.TimeOutCallback();
			vsyncTmp = millis();
			if(synctime - (vsyncTmp - timeTmp) > 0){
				delay(synctime - (vsyncTmp - timeTmp));
			}else{
				delay(1);
			}
		}else{
       		delay(synctime);
    	}
	}
}

void CX88000::selectD88(){
	File d88FileRoot;
	String fileList[MAX_FILES];

  	delay(100);
  	d88FileRoot = SD.open(DISK_DIRECTORY);
	int fileListCount = 0;
  	
	while(1){
    	File entry =  d88FileRoot.openNextFile();
    	if(!entry){// no more files
	        break;
	    }
	    //ファイルのみ取得
	    if (!entry.isDirectory()) {
        	String fullFileName = entry.name();
        	String fileName = fullFileName.substring(fullFileName.lastIndexOf("/") + 1);
        	fileList[fileListCount] = fileName;
        	fileListCount++;
			Serial.println(fileName);
    	}
    	entry.close();
  	}
  	d88FileRoot.close();


  	delay(10);
  	M5.Lcd.fillScreen(TFT_BLACK);
  	delay(10);
  	M5.Lcd.setTextSize(2);


  
  int startIndex = 0;
  int endIndex = startIndex + 10;
  if(endIndex > fileListCount){
    endIndex = fileListCount;
  }
  Serial.print("start:");
  Serial.println(startIndex);
  Serial.println("end:");
  Serial.println(endIndex);
  boolean needRedraw = true;
  int selectIndex = 0;
  while(true){

    if(needRedraw == true){
      M5.Lcd.fillScreen(0);
      M5.Lcd.setCursor(0,0);
      startIndex = selectIndex - 5;
      if(startIndex < 0){
        startIndex = 0;
      }

      endIndex = startIndex + 13;
      if(endIndex > fileListCount){
        endIndex = fileListCount;
      }

      for(int index = startIndex;index <= endIndex;index++){
          if(index == selectIndex){
             M5.Lcd.setTextColor(TFT_GREEN);
          }else{
            M5.Lcd.setTextColor(TFT_WHITE);
          }
		  if(index == 0){
			M5.Lcd.println("[NO DISK]");
		  }else{
          	M5.Lcd.println(fileList[index - 1]);
		  }
      }
      M5.Lcd.setTextColor(TFT_WHITE);

      M5.Lcd.drawRect(0, 240 - 19, 100 , 18, TFT_WHITE);
      M5.Lcd.setCursor(35, 240 - 17);
      M5.Lcd.print("U P");
      M5.Lcd.drawRect(110, 240 - 19, 100 , 18, TFT_WHITE);
      M5.Lcd.setCursor(125, 240 - 17);
      M5.Lcd.print("SELECT");
      M5.Lcd.drawRect(220, 240 - 19, 100 , 18, TFT_WHITE);
      M5.Lcd.setCursor(245, 240 - 17);
      M5.Lcd.print("DOWN");
      needRedraw = false;
    }
    M5.update();
    if(M5.BtnA.wasPressed()){
      selectIndex--;
      if(selectIndex < 0){
        selectIndex = 0;
      }
      needRedraw = true;
    }

    if(M5.BtnC.wasPressed()){
      selectIndex++;
      if(selectIndex > fileListCount){
        selectIndex = fileListCount;
      }
      needRedraw = true;
    }
    
    if(M5.BtnB.wasPressed()){
		CDiskImageCollection& dic = m_pc88.GetDiskImageCollection();
		if(m_pc88.Fdc().IsDriveReady(0)==true){
			m_pc88.Fdc().SetDiskImage(0, NULL);
			CDiskImage* curDiskImage = m_pc88.Fdc().GetDiskImage(0);
			dic.clear();
		}
		if(selectIndex == 0){
			M5.Lcd.fillScreen(TFT_BLACK);
			M5.Lcd.setCursor(0,0);			
			M5.Lcd.println("Disk Eject");
		}else{
			Serial.print("select:");
			Serial.println(fileList[selectIndex-1]);
			delay(10);
			//Set Disk
			Serial.println("DiskImageSet");
			const char* cFileName = (fileList[selectIndex-1]).c_str();
			std::string fileName(cFileName);
			dic.AddDiskImageFile(fileName, true);

			Serial.println("SetDiskImage");
			m_pc88.Fdc().SetDiskImage(0,m_pc88.GetDiskImageCollection().GetDiskImage(0));

			M5.Lcd.fillScreen(TFT_BLACK);
			M5.Lcd.setCursor(0,0);			
			M5.Lcd.print("Set Disk:");
			M5.Lcd.println(fileList[selectIndex-1]);
		}
		M5.Lcd.println("System Reset...");		
		delay(1000);
		DoReset();
      	M5.Lcd.fillScreen(TFT_BLACK);
      	delay(10);
      	return;
    }    
    delay(100);
  }
}


////////////////////////////////////////////////////////////
// Main

CX88000 x88000;

#ifdef X88_GUI_WINDOWS

int WINAPI WinMain(
	HINSTANCE hinstThis, HINSTANCE /*hinstPrev*/,
	LPSTR /*pszCmdLine*/, int /*nCmdShow*/)
{
	x88000.SetInstanceHandle(hinstThis);
	x88000.SetCmdLine(__argc, __argv);
	return x88000.Execute();
}

#else // !X88_GUI_WINDOWS

int main(int argc, char* argv[]) {

#ifdef X88_PLATFORM_WINDOWS

	x88000.SetInstanceHandle(GetModuleHandle(NULL));

#endif // X88_PLATFORM

	x88000.SetCmdLine(argc, argv);
	return x88000.Execute();
}

#endif // X88_GUI
