////////////////////////////////////////////////////////////
// X88000 Resource
//
// Written by Manuke

////////////////////////////////////////////////////////////
// include

#include "StdHeader.h"

#include "X88Resource.h"

#include "X88Utility.h"

using namespace NX88Utility;

////////////////////////////////////////////////////////////
// implementation of NX88Resource

////////////////////////////////////////////////////////////
// static

// UI language

static int s_nUILanguage = NX88Resource::X88LANG_AUTO;

// locale language

static int s_nLocaleLanguage = NX88Resource::X88LANG_AUTO;

// resource string map initialized

static bool s_bResStrMapInitialized = false;

////////////////////////////////////////////////////////////
// language

// get UI language

int NX88Resource::GetUILanguage() {
	return s_nUILanguage;
}

// set UI language

void NX88Resource::SetUILanguage(int nUILanguage) {
	if (nUILanguage != s_nUILanguage) {
		s_nUILanguage = nUILanguage;
		s_bResStrMapInitialized = false;
	}
}

// get locale language

int NX88Resource::GetLocaleLanguage() {
	if (s_nLocaleLanguage == X88LANG_AUTO) {
		s_nLocaleLanguage = X88LANG_ENGLISH;

#ifdef X88_PLATFORM_WINDOWS

		LCID lcid = GetThreadLocale();
		if (PRIMARYLANGID(LANGIDFROMLCID(lcid)) == LANG_JAPANESE) {
			s_nLocaleLanguage = X88LANG_JAPANESE;
		}

#elif defined(X88_PLATFORM_UNIX)

		std::string strLocale;
		const char* pszLocale = setlocale(LC_MESSAGES, NULL);
		if (pszLocale != NULL) {
			strLocale = pszLocale;
			StrToLwr(strLocale);
			while ((strLocale.size() > 0) && isspace(strLocale[0])) {
				strLocale.erase(0, 1);
			}
		}
		if ((strLocale.find("ja") == 0) ||
			(strLocale.find("ja_jp") != std::string::npos) ||
			(strLocale.find("japan") != std::string::npos) ||
			(strLocale.find("euc-jp") != std::string::npos) ||
			(strLocale.find("euc_jp") != std::string::npos) ||
			(strLocale.find("eucjp") != std::string::npos))
		{
			s_nLocaleLanguage = X88LANG_JAPANESE;
		}

#endif // X88_PLATFORM

	}
	return s_nLocaleLanguage;
}

// get resource language

int NX88Resource::GetResLanguage() {
	int nResLanguage = GetUILanguage();
	if (nResLanguage == X88LANG_AUTO) {
		nResLanguage = GetLocaleLanguage();
	}
	return nResLanguage;
}

// is resource language japanese mode

bool NX88Resource::IsResJapanese() {
	return GetResLanguage() == X88LANG_JAPANESE;
}

////////////////////////////////////////////////////////////
// string resource

// get version(GUI encoding)

std::string NX88Resource::GetVersion() {
	return "1.5.3";
}

// get resource string(GUI encoding)

const char* NX88Resource::GetResStr(const char* psszOrg) {
	static const char* apsszResStr[][2] = {
		// image file
		"<none>",
			"<なし>",
		// parallel device
		"NULL",
			"なし",
		// printer paper
		"10 inch continuous",
			"10インチ連続紙",
		"15 inch continuous",
			"15インチ連続紙",
		"A5 Portrait",
			"A5縦",
		"A5 Landscape",
			"A5横",
		"A4 Portrait",
			"A4縦",
		"A4 Landscape",
			"A4横",
		"A3 Portrait",
			"A3縦",
		"A3 Landscape",
			"A3横",
		"B5 Portrait",
			"B5縦",
		"B5 Landscape",
			"B5横",
		"B4 Portrait",
			"B4縦",
		"B4 Landscape",
			"B4横",
		"Postcard Portrait",
			"はがき縦",
		"Postcard Landscape",
			"はがき横",
		// message caption
		"Breakpoint : Address",
			"ブレークポイント:アドレス",
		"Disassemble : Address",
			"逆アセンブル:アドレス",
		"Disassemble : Line Count",
			"逆アセンブル:行数",
		"Dump : Address",
			"ダンプ:アドレス",
		"Dump : Byte Count",
			"ダンプ:バイト数",
		"Disk Image",
			"ディスクイメージ",
		"Export Screenshot",
			"画像書き出し",
		"Select Paper",
			"用紙選択",
		"Printing Image",
			"印刷イメージ",
		"Delete Paper",
			"用紙削除",
		"Printer",
			"プリンタ",
		"Tape Image",
			"テープイメージ",
		"Saved Data",
			"セーブデータ",
		// message text
		"Please enter a number between %d-%d",
			"%d以上%d以下の数値を入力してください",
		"Please enter a hexadecimal number between %04XH-%04XH",
			"%04XH以上%04XH以下の16進数を入力してください",
		"This address is already registered.",
			"このアドレスは登録済みです",
		"An error occurred while reading.",
			"読み込みエラー",
		"An error occurred while writing.",
			"書き出しエラー",
		"Delete paper?",
			"用紙を削除してもよろしいですか？",
		"Delete page %d?",
			"ページ %d を削除してもよろしいですか？",
		"Delete all pages?",
			"全ページを削除してもよろしいですか？",
		"Reset Printer?",
			"プリンタをリセットします。よろしいですか？",
		"Erase saved data?",
			"セーブデータを消去してもよろしいですか？",
		// file dialog caption
		"Add Disk Image",
			"ディスクイメージの追加",
		"Open Tape Image",
			"テープイメージを開く",
		"Save Tape Image",
			"テープイメージを保存",
		"Load Memory Image",
			"メモリイメージを読み込む",
		"Export Screenshot(XWD)",
			"画像書き出し(XWD)",
		"Write PostScript",
			"PostScript書き出し",
		"Write PDF",
			"PDF書き出し",
		"Write Text",
			"テキスト書き出し",
		// file dialog filter
		"Disk Image(d88)|*.d88||",
			"ディスクイメージ(d88)|*.d88||",
		"Tape Image(t88, cmt)|*.t88;*.cmt||",
			"テープイメージ(t88, cmt)|*.t88;*.cmt||",
		"Memory Image(n80)|*.n80||",
			"メモリイメージ(n80)|*.n80||",
		"Screenshot(XWD)|*.xwd||",
			"画像(XWD)|*.xwd||",
		"PostScript(ps)|*.ps||",
			"PostScript(ps)|*.ps||",
		"PDF(pdf)|*.pdf||",
			"pdf(pdf)|*.pdf||",
		"Text(txt)|*.txt||",
			"テキスト(txt)|*.txt||",
		// other dialog item
		"Environment Settings",
			"環境設定",
		"General",
			"一般",
		"Display",
			"画面",
		"Input",
			"入力",
		"Sound",
			"サウンド",
		"Auto",
			"自動(auto)",
		"Japanese",
			"日本語(ja)",
		"English",
			"英語(en)",
		"20 FPS",
			"20フレーム/秒",
		"30 FPS",
			"30フレーム/秒",
		"40 FPS",
			"40フレーム/秒",
		"60 FPS",
			"60フレーム/秒",
		"8 bit",
			"8ビット",
		"16 bit",
			"16ビット",
		"Mono",
			"モノラル",
		"Stereo",
			"ステレオ",
		"Same",
			"等倍",

#ifdef X88_GUI_WINDOWS

		// display font
		"Courier New",
			"ＭＳ ゴシック",
		// printer font
		"MS Mincho",
			"ＭＳ 明朝",
		"@MS Mincho",
			"@ＭＳ 明朝",
		"MS Gothic",
			"ＭＳ ゴシック",
		"@MS Gothic",
			"@ＭＳ ゴシック",

#elif defined(X88_GUI_GTK)

		// printer font
		"MS Mincho",
			"ＭＳ 明朝",
		"MS Gothic",
			"ＭＳ ゴシック",
		// dialog template
		"UI Language",
			"UI言語",
		"Boost Limiter",
			"ブーストリミッタ",
		"Disk Drives",
			"ディスク",
		"1 Drive",
			"1ドライブ",
		"2 Drives",
			"2ドライブ",
		"3 Drives",
			"3ドライブ",
		"4 Drives",
			"4ドライブ",
		"Other",
			"その他",
		"Wait",
			"ウェイト",
		"Older Compatibility",
			"旧機種互換",
		"International Mode",
			"海外版モード",
		"Frame Rate",
			"更新レート",
		"Interlace",
			"インタレース",
		"ON",
			"する",
		"OFF",
			"しない",
		"Use",
			"使用する",
		"Don't Use",
			"使用しない",
		"Enable",
			"許可する",
		"Disable",
			"禁止する",
		"Printer Settings",
			"プリンタ設定",
		"Printer Name",
			"プリンタ名",
		"Paper Size",
			"用紙サイズ",
		"Centering",
			"用紙中央",
		"Page Number",
			"ページ",
		"Write",
			"書き出し",
		"Delete Paper",
			"用紙削除",
		"Feed Paper",
			"紙送り",
		"Reset",
			"リセット",
		"Preview",
			"プレビュー",
		"Printer Settings : Write",
			"プリンタ設定:書き出し",
		"Content",
			"内容",
		"Zoom Rate",
			"比率",
		"Border",
			"枠",
		"Sprocket Hole",
			"スプロケット穴",
		"Text Extraction",
			"テキスト抽出",
		"Printer Settings : Delete Paper",
			"プリンタ設定:用紙削除",
		"Target",
			"対象",
		"Specified Page",
			"指定ページ",
		"All Pages",
			"全ページ",
		"Printer Settings : Feed Paper",
			"プリンタ設定:紙送り",
		"Unit",
			"単位",
		"Page",
			"ページ",
		"Line",
			"行",
		"Point",
			"ポイント",
		"Disk Image",
			"ディスクイメージ",
		"Disk Image File",
			"ディスクイメージファイル",
		"File",
			"ファイル",
		"Add",
			"追加",
		"Remove",
			"削除",
		"Remove All",
			"全削除",
		"Disk Drive",
			"ドライブ",
		"Drive 1",
			"ドライブ1",
		"Drive 2",
			"ドライブ2",
		"Drive 3",
			"ドライブ3",
		"Drive 4",
			"ドライブ4",
		"Tape Image",
			"テープイメージ",
		"Image for Loading",
			"ロードイメージ",
		"Open",
			"開く",
		"Image for Saving",
			"セーブイメージ",
		"Save",
			"保存",
		"Erase",
			"消去",
		"Export RAM",
			"RAM書き出し",
		"Main RAM0 : 0000H-7FFFH",
			"メインRAM0 : 0000H-7FFFH",
		"Main RAM1 : 8000H-FFFFH",
			"メインRAM1 : 8000H-FFFFH",
		"Fast Text VRAM",
			"高速テキストVRAM",
		"Slow Text VRAM",
			"低速テキストVRAM",
		"Graphic VRAM0",
			"グラフィックVRAM0",
		"Graphic VRAM1",
			"グラフィックVRAM1",
		"Graphic VRAM2",
			"グラフィックVRAM2",
		"Subsystem RAM",
			"サブシステムRAM",
		"Expansion RAM0",
			"拡張RAM0",
		"Expansion RAM1[VAB]",
			"拡張RAM1[VAB]",
		"Disassemble",
			"逆アセンブル",
		"Range",
			"範囲",
		"Address",
			"アドレス",
		"Lines",
			"行数",
		"Refresh",
			"再表示",
		"Disassembled List",
			"逆アセンブルリスト",
		"Dump",
			"ダンプ",
		"Byte Count",
			"バイト数",
		"Dump List",
			"ダンプリスト",
		"Breakpoint Settings",
			"ブレークポイント設定",
		"Position",
			"位置",
		"Breakpoint",
			"ブレークポイント",
		"Version Information",
			"バージョン情報",

		// menu
		"/_System",
			"/システム(_S)",
		"/System/_Reset",
			"/システム(S)/リセット(_R)",
		"/System/---",
			"/システム(S)/---",
		"/System/B_ASIC Mode",
			"/システム(S)/BASICモード(_A)",
		"/System/BASIC Mode/_N-BASIC Mode",
			"/システム(S)/BASICモード(A)/N-BASICモード(_N)",
		"/System/BASIC Mode/N88-BASIC V_1-S Mode",
			"/システム(S)/BASICモード(A)/N88-BASIC V1-Sモード(_1)",
		"/System/BASIC Mode/N88-BASIC V1-_H Mode",
			"/システム(S)/BASICモード(A)/N88-BASIC V1-Hモード(_H)",
		"/System/BASIC Mode/N88-BASIC V_2 Mode",
			"/システム(S)/BASICモード(A)/N88-BASIC V2モード(_2)",
		"/System/BASIC Mode/---",
			"/システム(S)/BASICモード(A)/---",
		"/System/BASIC Mode/N_80-BASIC V1 Mode",
			"/システム(S)/BASICモード(A)/N80-BASIC V1モード(_8)",
		"/System/BASIC Mode/N8_0-BASIC V2 Mode",
			"/システム(S)/BASICモード(A)/N80-BASIC V2モード(_0)",
		"/System/_Clock",
			"/システム(S)/動作クロック(_C)",
		"/System/Clock/_4MHz Mode",
			"/システム(S)/動作クロック(C)/4MHzモード(_4)",
		"/System/Clock/_8MHz Mode",
			"/システム(S)/動作クロック(C)/8MHzモード(_8)",
		"/System/_Boost Mode",
			"/システム(S)/ブーストモード(_B)",
		"/System/_Fullscreen Mode",
			"/システム(S)/フルスクリーンモード(_F)",
		"/System/---",
			"/システム(S)/---",
		"/System/C_lipboard",
			"/システム(S)/クリップボード(_L)",
		"/System/Clipboard/Export Screenshot : XWD(_C)",
			"/システム(S)/クリップボード(L)/画像書き出し：XWD(_C)",
		"/System/Clipboard/Copy : _Text",
			"/システム(S)/クリップボード(L)/コピー：テキスト(_T)",
		"/System/Clipboard/_Paste : Text",
			"/システム(S)/クリップボード(L)/張り付け：テキスト(_P)",
		"/System/---",
			"/システム(S)/---",
		"/System/_Environment Settings...",
			"/システム(S)/環境設定(_E)...",
		"/System/_Parallel Port",
			"/システム(S)/パラレルポート(_P)",
		"/System/Parallel Port/_Device Settings...",
			"/システム(S)/パラレルポート(P)/デバイスの設定(_D)...",
		"/System/Parallel Port/---",
			"/システム(S)/パラレルポート(P)/---",
		"/System/Parallel Port/%s(_0)",
			"/システム(S)/パラレルポート(P)/%s(_0)",
		"/System/Parallel Port/%s(_1)",
			"/システム(S)/パラレルポート(P)/%s(_1)",
		"/System/Parallel Port/%s(_2)",
			"/システム(S)/パラレルポート(P)/%s(_2)",
		"/System/Parallel Port/%s(_3)",
			"/システム(S)/パラレルポート(P)/%s(_3)",
		"/System/Parallel Port/%s(_4)",
			"/システム(S)/パラレルポート(P)/%s(_4)",
		"/System/Parallel Port/%s(_5)",
			"/システム(S)/パラレルポート(P)/%s(_5)",
		"/System/Parallel Port/%s(_6)",
			"/システム(S)/パラレルポート(P)/%s(_6)",
		"/System/Parallel Port/%s(_7)",
			"/システム(S)/パラレルポート(P)/%s(_7)",
		"/System/Parallel Port/%s(_8)",
			"/システム(S)/パラレルポート(P)/%s(_8)",
		"/System/Parallel Port/%s(_9)",
			"/システム(S)/パラレルポート(P)/%s(_9)",
		"/System/---",
			"/システム(S)/---",
		"/System/E_xit X88000",
			"/システム(S)/X88000の終了(_X)",
		"/_Image",
			"/イメージ(_I)",
		"/Image/_Disk Image...",
			"/イメージ(I)/ディスクイメージ(_D)...",
		"/Image/_Tape Image...",
			"/イメージ(I)/テープイメージ(_T)...",
		"/Image/_Memory Image...",
			"/イメージ(I)/メモリイメージ(_M)...",
		"/Debu_g",
			"/デバッグ(_G)",
		"/Debug/Main CPU Debug(_1)",
			"/デバッグ(G)/メインCPUデバッグ(_1)",
		"/Debug/Sub CPU Debug(_2)",
			"/デバッグ(G)/サブCPUデバッグ(_2)",
		"/Debug/---",
			"/デバッグ(G)/---",
		"/Debug/Execute Debu_g",
			"/デバッグ(G)/デバッグ実行(_G)",
		"/Debug/---",
			"/デバッグ(G)/---",
		"/Debug/Execute _Step",
			"/デバッグ(G)/ステップ実行(_S)",
		"/Debug/Execute _Trace",
			"/デバッグ(G)/トレース実行(_T)",
		"/Debug/Execute Ste_p2",
			"/デバッグ(G)/ステップ実行2(_P)",
		"/Debug/---",
			"/デバッグ(G)/---",
		"/Debug/Record Execution L_og",
			"/デバッグ(G)/実行ログ記録(_O)",
		"/Debug/Export RAM(_W)...",
			"/デバッグ(G)/RAM書き出し(_W)...",
		"/Debug/---",
			"/デバッグ(G)/---",
		"/Debug/Disassemb_le...",
			"/デバッグ(G)/逆アセンブル(_L)...",
		"/Debug/_Dump...",
			"/デバッグ(G)/ダンプ(_D)...",
		"/Debug/_Breakpoint Settings...",
			"/デバッグ(G)/ブレークポイント設定(_B)...",
		"/_Help",
			"/ヘルプ(_H)",
		"/Help/_About...",
			"/ヘルプ(H)/バージョン情報(_A)...",

#endif // X88_GUI

		NULL, NULL
	};
	static std::map<std::string, std::string> mapResStr;
	if (!s_bResStrMapInitialized) {
		s_bResStrMapInitialized = true;
		mapResStr.clear();
		if (IsResJapanese()) {
			for (int i = 0; apsszResStr[i][0] != NULL; i++) {
				mapResStr[apsszResStr[i][0]] =
					ConvSRCtoGUI(apsszResStr[i][1]);
			}
		}
	}
	const char* pgszRes = psszOrg;
	if (psszOrg != NULL) {
		std::map<std::string, std::string>::iterator it =
			mapResStr.find(psszOrg);
		if (it != mapResStr.end()) {
			pgszRes = (*it).second.c_str();
		}
	}
	return pgszRes;
}

// get formatted resource string(GUI encoding)

std::string NX88Resource::FormatResStr(const char* psszOrg, ...) {
	std::string gstrRes;
	const char* pgszOrg = GetResStr(psszOrg);
	if (pgszOrg != NULL) {
		va_list ap;
		va_start(ap, psszOrg);
		gstrRes = FormatStrV(pgszOrg, ap);
		va_end(ap);
	}
	return gstrRes;
}

// get parallel device name from id(GUI encoding)

std::string NX88Resource::GetParallelDeviceNameFromID(
	const std::string& strDeviceID)
{
	static const char* apszDeviceNames[][2] = {
		"null", "NULL",
		"pr201", "PC-PR201"
	};
	static const int nDeviceCount =
		sizeof(apszDeviceNames)/sizeof(apszDeviceNames[0]);
	std::string gstrDeviceName;
	for (int i = 0; i < nDeviceCount; i++) {
		if (StrCaseCmp(strDeviceID, apszDeviceNames[i][0]) == 0) {
			gstrDeviceName = RSTR(apszDeviceNames[i][1]);
			break;
		}
	}
	return gstrDeviceName;
}

////////////////////////////////////////////////////////////
// dialog resource

#ifdef X88_GUI_GTK

// get dialog entries

NX88Resource::SDialogEntry*
	NX88Resource::GetDialogEntries(int nID, int& nItemCount)
{
	// message-box
	static SDialogEntry adeMessageBox[] = {
		{	// ActionArea
			" Button", "OK",
			1, IDOK, NULL, "fd"
		}, {
			" Button", "Yes",
			4, IDYES, NULL, "f"
		}, {
			" Button", "No",
			8, IDNO, NULL, "f"
		}, {
			" Button", "Cancel",
			2, IDCANCEL, NULL, "f"
		}, {	// MainVBox
			"VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Label", NULL,
			0, 0, "s50,1", NULL
		}, {	// Message
			" Label", "",
			0, IDC_MESSAGE, NULL, NULL
		}, {
			" Label", NULL,
			0, 0, "s50,1", NULL
		}
	};
	// environment settings dialog
	static SDialogEntry adeEnvSet[] = {
		{
			"Caption", "Environment Settings",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {
			" Button", "Cancel",
			0, IDCANCEL, NULL, "f"
		}, {	// MainVBox
			"+*NoteBook", NULL,
			0, 0, "b1", NULL
		}, {	// General Page
			"NoteTag", "General",
			0, 0, NULL, NULL
		}, {
			" HBox", NULL,
			0, IDC_ENV_GENERAL, "b1", NULL
		}, {	// Display Page
			"NoteTag", "Display",
			0, 0, NULL, NULL
		}, {
			" HBox", NULL,
			0, IDC_ENV_DISPLAY, "b1", NULL
		}, {	// Input Page
			"NoteTag", "Input",
			0, 0, NULL, NULL
		}, {
			" HBox", NULL,
			0, IDC_ENV_INPUT, "b1", NULL
		}
	};
	// environment settings: general notebook
	static SDialogEntry adeEnvGeneral[] = {
		{
			"HBox", NULL,
			0, 0, NULL, NULL
		}, {
			" VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "UI Language",
			0, 0, NULL, NULL
		}, {
			"  Combo", NULL,
			0, IDC_UI_LANGUAGE, NULL, "e0"
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "Boost Limiter",
			0, 0, NULL, NULL
		}, {
			"  Combo", NULL,
			0, IDC_BOOST_LIMITER, NULL, "e0"
		}, {
			"  Frame", "Disk Drives",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    RadioButton", "1 Drive",
			0, IDC_DISK_DRIVE1, NULL, NULL
		}, {
			"    RadioButton", "2 Drives",
			0, IDC_DISK_DRIVE2, NULL, NULL
		}, {
			"    RadioButton", "3 Drives",
			0, IDC_DISK_DRIVE3, NULL, NULL
		}, {
			"    RadioButton", "4 Drives",
			0, IDC_DISK_DRIVE4, NULL, NULL
		}, {
			" VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  Frame", "CRT",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    RadioButton", "24KHz",
			0, IDC_VSYNC_24KHZ, NULL, NULL
		}, {
			"    RadioButton", "15KHz",
			0, IDC_VSYNC_15KHZ, NULL, NULL
		}, {
			"  Frame", "Other",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    CheckButton", "Wait",
			0, IDC_WAIT_EMULATION, NULL, NULL
		}, {
			"    CheckButton", "Older Compatibility",
			0, IDC_OLD_COMPATIBLE, NULL, NULL
		}, {
			"    CheckButton", "PCG-8800",
			0, IDC_PCG_ENABLE, NULL, NULL
		}, {
			"    CheckButton", "International Mode",
			0, IDC_OPTION_FONT, NULL, NULL
		}
	};
	// environment settings: display notebook
	static SDialogEntry adeEnvDisplay[] = {
		{
			"HBox", NULL,
			0, 0, NULL, NULL
		}, {
			" VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "Frame Rate",
			0, 0, NULL, NULL
		}, {
			"  Combo", NULL,
			0, IDC_FRAME_RATE, NULL, "e0"
		}, {
			"  Frame", "Interlace",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    RadioButton", "ON",
			0, IDC_INTERLACE_DO, NULL, NULL
		}, {
			"    RadioButton", "OFF",
			0, IDC_INTERLACE_NODO, NULL, NULL
		}
	};
	// environment settings: input notebook
	static SDialogEntry adeEnvInput[] = {
		{
			"HBox", NULL,
			0, 0, NULL, NULL
		}, {
			" VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  Frame", "XQueryKeymap",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    RadioButton", "Use",
			0, IDC_DIRECT_INPUT_USE, NULL, NULL
		}, {
			"    RadioButton", "Don't Use",
			0, IDC_DIRECT_INPUT_NOUSE, NULL, NULL
		}, {
			"  Frame", "IM",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    RadioButton", "Enable",
			0, IDC_IME_ENABLE, NULL, NULL
		}, {
			"    RadioButton", "Disable",
			0, IDC_IME_DISABLE, NULL, NULL
		}
	};
	// printer settings dialog
	static SDialogEntry adePrinter[] = {
		{
			"Caption", "Printer Settings",
			0, 0, NULL, NULL
		}, {	// MainHBox
			"+*HBox", NULL,
			0, 0, "b1", NULL
		}, {
			" VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "Printer Name",
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "",
			0, IDC_PRINTER_NAME, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "Paper Size",
			0, 0, NULL, NULL
		}, {
			"  Combo", NULL,
			0, IDC_PRINTER_PAPER, NULL, "e0"
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   CheckButton", "Centering",
			0, IDC_PRINTER_PAPER_CENTER, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "Page Number",
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   +*SpinButton", NULL,
			0, IDC_PRINTER_PAGE_SPIN, NULL, NULL
		}, {
			"   +*HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    Label", "/1",
			0, IDC_PRINTER_PAGE_MAX, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    Button", "Write",
			0, IDC_PRINTER_COPY, NULL, NULL
		}, {
			"    Button", "Delete Paper",
			0, IDC_PRINTER_PAPER_DELETE, NULL, NULL
		}, {
			"    Button", "Feed Paper",
			0, IDC_PRINTER_PAPER_FEED, NULL, NULL
		}, {
			"    Button", "Reset",
			0, IDC_PRINTER_RESET, NULL, NULL
		}, {
			" +*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"  HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Label", "Preview",
			0, 0, NULL, NULL
		}, {
			"  +*ScrolledWindow", NULL,
			0, IDC_PRINTER_PREVIEW, "s64,64", NULL
		}, {
			"   Alignment", NULL,
			0, IDC_PRINTER_PREVIEW_ALIGN, NULL, NULL
		}
	};
	// printer settings: write dialog
	static SDialogEntry adePrinterCopy[] = {
		{
			"Caption", "Printer Settings : Write",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {
			" Button", "Cancel",
			0, IDCANCEL, NULL, "f"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "Page Number",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   HBox", NULL,
			0, 0, NULL, "h1"
		}, {
			"    +*SpinButton", NULL,
			0, IDC_PRINTER_COPY_PAGENO_SPIN, NULL, NULL
		}, {
			"    +*Label", "  ",
			0, 0, NULL, NULL
		}, {
			" Frame", "Content",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, "b1", NULL
		}, {

#ifdef X88_PRINTER_DRAW_POSTSCRIPT

			"   RadioButton", "PostScript",
			0, IDC_PRINTER_COPY_METAFILE, NULL, "l"

#elif defined(X88_PRINTER_DRAW_CAIRO)

			"   RadioButton", "PDF",
			0, IDC_PRINTER_COPY_METAFILE, NULL, "l"

#endif // X88_PRINTER_DRAW

		}, {
			"   HBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    Label", "  ",
			0, 0, NULL, NULL
		}, {
			"    VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      Label", "Zoom Rate",
			0, 0, NULL, NULL
		}, {
			"     HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      Combo", NULL,
			0, IDC_PRINTER_COPY_ZOOM, NULL, "e0"
		}, {
			"     CheckButton", "Border",
			0, IDC_PRINTER_COPY_BORDER, NULL, NULL
		}, {
			"     CheckButton", "Sprocket Hole",
			0, IDC_PRINTER_COPY_HOLE, NULL, NULL
		}, {
			"   RadioButton", "Text Extraction",
			0, IDC_PRINTER_COPY_TEXT, NULL, "t"
		}
	};
	// printer settings: paper delete dialog
	static SDialogEntry adePrinterPaperDel[] = {
		{
			"Caption", "Printer Settings : Delete Paper",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {
			" Button", "Cancel",
			0, IDCANCEL, NULL, "f"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "Target",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   HBox", NULL,
			0, 0, NULL, "h1"
		}, {
			"    +*RadioButton", "Specified Page",
			0, IDC_PRINTER_PAPERDEL_ONEPAGE, NULL, "l"
		}, {
			"    -+*SpinButton", NULL,
			0, IDC_PRINTER_PAPERDEL_PAGENO_SPIN, NULL, NULL
		}, {
			"   HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    +*RadioButton", "All Pages",
			0, IDC_PRINTER_PAPERDEL_ALLPAGES, NULL, "t"
		}
	};
	// printer settings: paper feed dialog
	static SDialogEntry adePrinterPaperFeed[] = {
		{
			"Caption", "Printer Settings : Feed Paper",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {
			" Button", "Cancel",
			0, IDCANCEL, NULL, "f"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "Unit",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    +*RadioButton", "Page",
			0, IDC_PRINTER_PAPERFEED_PAGE, NULL, "l"
		}, {
			"   HBox", NULL,
			0, 0, NULL, "h1"
		}, {
			"    +*RadioButton", "Line",
			0, IDC_PRINTER_PAPERFEED_LINE, NULL, "t"
		}, {
			"    -+*SpinButton", NULL,
			0, IDC_PRINTER_PAPERFEED_LINE_COUNT_SPIN, NULL, NULL
		}, {
			"   HBox", NULL,
			0, 0, NULL, "h1"
		}, {
			"    +*RadioButton", "Point",
			0, IDC_PRINTER_PAPERFEED_POINT, NULL, "t"
		}, {
			"    -+*SpinButton", NULL,
			0, IDC_PRINTER_PAPERFEED_POINT_COUNT_SPIN, NULL, NULL
		}
	};
	// disk image dialog
	static SDialogEntry adeDiskImage[] = {
		{
			"Caption", "Disk Image",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {	// Images
			" +*Frame", "Disk Image File",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    Label", "File",
			0, 0, NULL, NULL
		}, {
			"   +*HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    +*ScrolledWindow", NULL,
			0, 0, "s64,1", "p0,1"
		}, {
			"     List", NULL,
			0, IDC_IMAGES, NULL, "m"
		}, {
			"    VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Button", "Add",
			0, IDC_IMAGE_ADD, NULL, NULL
		}, {
			"     Button", "Remove",
			0, IDC_IMAGE_REMOVE, NULL, NULL
		}, {
			"     Button", "Remove All",
			0, IDC_IMAGE_ERASE, NULL, NULL
		}, {	// Drives
			" Frame", "Disk Drive",
			0, 0, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"    +*HBox", NULL,
			0, 0, NULL, "h1"
		}, {	// Drive1
			"     +*VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"       Label", "Drive 1",
			0, 0, NULL, NULL
		}, {
			"       -CheckButton", "P",
			0, IDC_DISK_DRIVE1_PROTECT, NULL, NULL
		}, {
			"      +*Combo", NULL,
			0, IDC_DISK_DRIVE1, NULL, "e0"
		}, {	// Drive2
			"     +*VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      HBox", NULL,
			1, 0, NULL, NULL
		}, {
			"       Label", "Drive 2",
			1, 0, NULL, NULL
		}, {
			"       -CheckButton", "P",
			1, IDC_DISK_DRIVE2_PROTECT, NULL, NULL
		}, {
			"      +*Combo", NULL,
			1, IDC_DISK_DRIVE2, NULL, "e0"
		}, {
			"    +*HBox", NULL,
			0, 0, NULL, "h1"
		}, {	// Drive3
			"     +*VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      HBox", NULL,
			2, 0, NULL, NULL
		}, {
			"       Label", "Drive 3",
			2, 0, NULL, NULL
		}, {
			"       -CheckButton", "P",
			2, IDC_DISK_DRIVE3_PROTECT, NULL, NULL
		}, {
			"      +*Combo", NULL,
			2, IDC_DISK_DRIVE3, NULL, "e0"
		}, {	// Drive4
			"     +*VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      HBox", NULL,
			4, 0, NULL, NULL
		}, {
			"       Label", "Drive 4",
			4, 0, NULL, NULL
		}, {
			"       -CheckButton", "P",
			4, IDC_DISK_DRIVE4_PROTECT, NULL, NULL
		}, {
			"      +*Combo", NULL,
			4, IDC_DISK_DRIVE4, NULL, "e0"
		}
	};
	// tape image dialog
	static SDialogEntry adeTapeImage[] = {
		{
			"Caption", "Tape Image",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {	// MainVBox
			"VBox", NULL,
			0, 0, "b1", NULL
		}, {	// Load Image
			" +*Frame", "Image for Loading",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   +*Frame", NULL,
			0, 0, NULL, NULL
		}, {
			"    Label", "",
			0, IDC_LIMAGE_NAME, NULL, NULL
		}, {
			"   Label", NULL,
			0, 0, "s60,0", NULL
		}, {
			"   +*HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    +*VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     +*Label", "",
			0, IDC_LIMAGE_INFO, NULL, NULL
		}, {
			"     +*Label", "",
			0, IDC_LIMAGE_COUNTER, NULL, NULL
		}, {
			"    -VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Button", "Open",
			0, IDC_LIMAGE_OPEN, NULL, NULL
		}, {
			"     HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"      +*Button", "<<",
			0, IDC_LIMAGE_REW, NULL, NULL
		}, {
			"      +*Button", ">>",
			0, IDC_LIMAGE_FWD, NULL, NULL
		}, {
			"     Label", NULL,
			0, 0, "s15,0", NULL
		}, {	// Save Image
			" +*Frame", "Image for Saving",
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   +*VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    +*Label", "",
			0, IDC_SIMAGE_INFO, NULL, NULL
		}, {
			"    +*Label", "",
			0, IDC_SIMAGE_COUNTER, NULL, NULL
		}, {
			"   -VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    Button", "Save",
			0, IDC_SIMAGE_SAVE, NULL, NULL
		}, {
			"    Button", "Erase",
			0, IDC_SIMAGE_ERASE, NULL, NULL
		}, {
			"    Label", NULL,
			0, 0, "s15,0", NULL
		}
	};
	// RAM writing dialog
	static SDialogEntry adeDebugWriteRam[] = {
		{
			"Caption", "Export RAM",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {
			" Button", "Cancel",
			0, IDCANCEL, NULL, "f"
		}, {	// MainVBox
			"VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "RAM",
			0, 0, NULL, NULL
		}, {
			"  VBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   CheckButton", "Main RAM0 : 0000H-7FFFH",
			0, IDC_WRITE_MAIN_RAM0, NULL, NULL
		}, {
			"   CheckButton", "Main RAM1 : 8000H-FFFFH",
			0, IDC_WRITE_MAIN_RAM1, NULL, NULL
		}, {
			"   CheckButton", "Fast Text VRAM",
			1, IDC_WRITE_FAST_TVRAM, NULL, NULL
		}, {
			"   CheckButton", "Slow Text VRAM",
			2, IDC_WRITE_SLOW_TVRAM, NULL, NULL
		}, {
			"   CheckButton", "Graphic VRAM0",
			0, IDC_WRITE_GVRAM0, NULL, NULL
		}, {
			"   CheckButton", "Graphic VRAM1",
			0, IDC_WRITE_GVRAM1, NULL, NULL
		}, {
			"   CheckButton", "Graphic VRAM2",
			0, IDC_WRITE_GVRAM2, NULL, NULL
		}, {
			"   CheckButton", "Subsystem RAM",
			0, IDC_WRITE_SUB_RAM, NULL, NULL
		}, {
			"   CheckButton", "Expansion RAM0",
			0, IDC_WRITE_EX_RAM0, NULL, NULL
		}, {
			"   CheckButton", "Expansion RAM1[VAB]",
			0, IDC_WRITE_EX_RAM1, NULL, NULL
		}
	};
	// dis-assemble dialog
	static SDialogEntry adeDisAssemble[] = {
		{
			"Caption", "Disassemble",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "Range",
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Label", "Address",
			0, 0, NULL, NULL
		}, {
			"    Entry", NULL,
			0, IDC_ADDRESS, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Label", "Lines",
			0, 0, NULL, NULL
		}, {
			"    Entry", NULL,
			0, IDC_LINE_COUNT, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    -Button", "Refresh",
			0, IDC_DIS_ASSEMBLE, NULL, NULL
		}, {
			"   Label", NULL,
			0, 0, "s10,1", NULL
		}, {
			" HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  Label", "Disassembled List",
			0, 0, NULL, NULL
		}, {
			" +*HBox", NULL,
			0, 0, NULL, "s0"
		}, {
			"  +*Text", NULL,
			0, IDC_DIS_ASSEMBLE_LIST, "s40,40", "ve1"
		}, {
			"  VScrollBar", NULL,
			0, 0, NULL, "a"
		}
	};
	// dump dialog
	static SDialogEntry adeDump[] = {
		{
			"Caption", "Dump",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "Range",
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Label", "Address",
			0, 0, NULL, NULL
		}, {
			"    Entry", NULL,
			0, IDC_ADDRESS, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Label", "Byte Count",
			0, 0, NULL, NULL
		}, {
			"    Entry", NULL,
			0, IDC_BYTE_COUNT, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    -Button", "Refresh",
			0, IDC_DUMP, NULL, NULL
		}, {
			"   Label", NULL,
			0, 0, "s10,1", NULL
		}, {
			" HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  Label", "Dump List",
			0, 0, NULL, NULL
		}, {
			" +*HBox", NULL,
			0, 0, NULL, "s0"
		}, {
			"  +*Text", NULL,
			0, IDC_DUMP_LIST, "s40,40", "ve1"
		}, {
			"  VScrollBar", NULL,
			0, 0, NULL, "a"
		}
	};
	// breakpoint dialog
	static SDialogEntry adeBreakPoint[] = {
		{
			"Caption", "Breakpoint Settings",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Frame", "Position",
			0, 0, NULL, NULL
		}, {
			"  HBox", NULL,
			0, 0, "b1", NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"     Label", "Address",
			0, 0, NULL, NULL
		}, {
			"    Entry", NULL,
			0, IDC_ADDRESS, NULL, NULL
		}, {
			"   VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"    -Button", "Add",
			0, IDC_ADDRESS_ADD, NULL, NULL
		}, {
			" HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  Label", "Breakpoint",
			0, 0, NULL, NULL
		}, {
			" +*HBox", NULL,
			0, 0, NULL, NULL
		}, {
			"  +*ScrolledWindow", NULL,
			0, 0, "s1,20", "p0,1"
		}, {
			"   List", NULL,
			0, IDC_BREAK_POINT, NULL, "m"
		}, {
			"  VBox", NULL,
			0, 0, NULL, NULL
		}, {
			"   Button", "Remove",
			0, IDC_BREAK_POINT_REMOVE, NULL, NULL
		}, {
			"   Button", "Remove All",
			0, IDC_BREAK_POINT_ERASE, NULL, NULL
		}
	};
	// version dialog
	static SDialogEntry adeVersion[] = {
		{
			"Caption", "Version Information",
			0, 0, NULL, NULL
		}, {	// ActionArea
			" Button", "OK",
			0, IDOK, NULL, "fd"
		}, {	// MainVBox
			"+*VBox", NULL,
			0, 0, "b1", NULL
		}, {
			" Label", NULL,
			0, 0, "s50,1", NULL
		}, {
			" Label", "X88000 Ver. ",
			0, IDC_VERSION, NULL, NULL
		}, {
			" Label", "by Manuke",
			0, 0, NULL, NULL
		}, {
			" Label", NULL,
			0, 0, "s50,1", NULL
		}
	};

	SDialogEntry* pdeTemplate = NULL;
	nItemCount = 0;

#define SET_DIALOG_ENTRY(ade) \
	pdeTemplate = ade; \
	nItemCount = sizeof(ade)/sizeof(ade[0]);

	switch (nID) {
	case IDD_MESSAGEBOX:
		SET_DIALOG_ENTRY(adeMessageBox);
		break;
	case IDD_ENV_SET:
		SET_DIALOG_ENTRY(adeEnvSet);
		break;
	case IDD_ENV_GENERAL:
		SET_DIALOG_ENTRY(adeEnvGeneral);
		break;
	case IDD_ENV_DISPLAY:
		SET_DIALOG_ENTRY(adeEnvDisplay);
		break;
	case IDD_ENV_INPUT:
		SET_DIALOG_ENTRY(adeEnvInput);
		break;
	case IDD_PRINTER:
		SET_DIALOG_ENTRY(adePrinter);
		break;
	case IDD_PRINTER_COPY:
		SET_DIALOG_ENTRY(adePrinterCopy);
		break;
	case IDD_PRINTER_PAPERDEL:
		SET_DIALOG_ENTRY(adePrinterPaperDel);
		break;
	case IDD_PRINTER_PAPERFEED:
		SET_DIALOG_ENTRY(adePrinterPaperFeed);
		break;
	case IDD_DISK_IMAGE:
		SET_DIALOG_ENTRY(adeDiskImage);
		break;
	case IDD_TAPE_IMAGE:
		SET_DIALOG_ENTRY(adeTapeImage);
		break;
	case IDD_DEBUG_WRITE_RAM:
		SET_DIALOG_ENTRY(adeDebugWriteRam);
		break;
	case IDD_DEBUG_DIS_ASSEMBLE:
		SET_DIALOG_ENTRY(adeDisAssemble);
		break;
	case IDD_DEBUG_DUMP:
		SET_DIALOG_ENTRY(adeDump);
		break;
	case IDD_DEBUG_BREAK_POINT:
		SET_DIALOG_ENTRY(adeBreakPoint);
		break;
	case IDD_VERSION:
		SET_DIALOG_ENTRY(adeVersion);
		break;
	}

#undef SET_DIALOG_ENTRY

	return pdeTemplate;
}

#endif // X88_GUI

////////////////////////////////////////////////////////////
// menu resource

#ifdef X88_GUI_GTK

// get menu entries

GtkItemFactoryEntry* NX88Resource::GetMenuEntries(int& nItemCount) {
	// main menu
	static GtkItemFactoryEntry aifeMenu[] = {
		{
			(char*)"/_System",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/System/_Reset",
			NULL,
			NULL,
			IDM_RESET,
			NULL
		}, {
			(char*)"/System/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/System/B_ASIC Mode",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/System/BASIC Mode/_N-BASIC Mode",
			NULL,
			NULL,
			IDM_BASICMODE_N,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/BASIC Mode/N88-BASIC V_1-S Mode",
			NULL,
			NULL,
			IDM_BASICMODE_V1_S,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/BASIC Mode/N88-BASIC V1-_H Mode",
			NULL,
			NULL,
			IDM_BASICMODE_V1_H,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/BASIC Mode/N88-BASIC V_2 Mode",
			NULL,
			NULL,
			IDM_BASICMODE_V2,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/BASIC Mode/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/System/BASIC Mode/N_80-BASIC V1 Mode",
			NULL,
			NULL,
			IDM_BASICMODE_N80_V1,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/BASIC Mode/N8_0-BASIC V2 Mode",
			NULL,
			NULL,
			IDM_BASICMODE_N80_V2,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/_Clock",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/System/Clock/_4MHz Mode",
			NULL,
			NULL,
			IDM_BASE_CLOCK_4,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Clock/_8MHz Mode",
			NULL,
			NULL,
			IDM_BASE_CLOCK_8,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/_Boost Mode",
			(char*)"<Alt>B",
			NULL,
			IDM_BOOST_MODE,
			(char*)"<CheckItem>"
		/* unsupport
		}, {
			(char*)"/System/_Fullscreen Mode",
			(char*)"<Alt>Return",
			NULL,
			IDM_FULL_SCREEN_MODE,
			(char*)"<CheckItem>"
		*/
		}, {
			(char*)"/System/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/System/C_lipboard",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/System/Clipboard/Export Screenshot : XWD(_C)",
			NULL,
			NULL,
			IDM_CLIPBOARD_COPY_BITMAP,
			NULL
		}, {
			(char*)"/System/Clipboard/Copy : _Text",
			NULL,
			NULL,
			IDM_CLIPBOARD_COPY_TEXT,
			NULL
		}, {
			(char*)"/System/Clipboard/_Paste : Text",
			NULL,
			NULL,
			IDM_CLIPBOARD_PASTE_TEXT,
			NULL
		}, {
			(char*)"/System/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/System/_Environment Settings...",
			NULL,
			NULL,
			IDM_ENV_SET,
			NULL
		}, {
			(char*)"/System/_Parallel Port",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/System/Parallel Port/_Device Settings...",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE_SETTING,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/System/Parallel Port/%s(_0)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE0,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_1)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE1,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_2)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE2,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_3)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE3,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_4)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE4,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_5)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE5,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_6)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE6,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_7)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE7,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_8)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE8,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/Parallel Port/%s(_9)",
			NULL,
			NULL,
			IDM_PARALLEL_DEVICE9,
			(char*)"<CheckItem>"
		}, {
			(char*)"/System/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/System/E_xit X88000",
			NULL,
			NULL,
			IDM_EXIT,
			NULL
		}, {
			(char*)"/_Image",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/Image/_Disk Image...",
			(char*)"<Alt>D",
			NULL,
			IDM_DISK_IMAGE,
			NULL
		}, {
			(char*)"/Image/_Tape Image...",
			(char*)"<Alt>T",
			NULL,
			IDM_TAPE_IMAGE,
			NULL
		}, {
			(char*)"/Image/_Memory Image...",
			(char*)"<Alt>M",
			NULL,
			IDM_MEMORY_IMAGE,
			NULL
		}, {
			(char*)"/Debu_g",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/Debug/Main CPU Debug(_1)",
			NULL,
			NULL,
			IDM_DEBUG_MAIN,
			(char*)"<CheckItem>"
		}, {
			(char*)"/Debug/Sub CPU Debug(_2)",
			NULL,
			NULL,
			IDM_DEBUG_SUB,
			(char*)"<CheckItem>"
		}, {
			(char*)"/Debug/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/Debug/Execute Debu_g",
			(char*)"<Alt>F5",
			NULL,
			IDM_DEBUG_EXECUTE,
			(char*)"<CheckItem>"
		}, {
			(char*)"/Debug/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/Debug/Execute _Step",
			(char*)"<Alt>F10",
			NULL,
			IDM_DEBUG_EXECUTE_STEP,
			NULL
		}, {
			(char*)"/Debug/Execute _Trace",
			(char*)"<Alt>F11",
			NULL,
			IDM_DEBUG_EXECUTE_TRACE,
			NULL
		}, {
			(char*)"/Debug/Execute Ste_p2",
			(char*)"<Alt>F12",
			NULL,
			IDM_DEBUG_EXECUTE_STEP2,
			NULL
		}, {
			(char*)"/Debug/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/Debug/Record Execution L_og",
			NULL,
			NULL,
			IDM_DEBUG_LOG,
			(char*)"<CheckItem>"
		}, {
			(char*)"/Debug/Export RAM(_W)...",
			NULL,
			NULL,
			IDM_DEBUG_WRITE_RAM,
			NULL
		}, {
			(char*)"/Debug/---",
			NULL,
			NULL,
			0,
			(char*)"<Separator>"
		}, {
			(char*)"/Debug/Disassemb_le...",
			NULL,
			NULL,
			IDM_DEBUG_DIS_ASSEMBLE,
			NULL
		}, {
			(char*)"/Debug/_Dump...",
			NULL,
			NULL,
			IDM_DEBUG_DUMP,
			NULL
		}, {
			(char*)"/Debug/_Breakpoint Settings...",
			NULL,
			NULL,
			IDM_DEBUG_BREAK_POINT,
			NULL
		}, {
			(char*)"/_Help",
			NULL,
			NULL,
			0,
			(char*)"<Branch>"
		}, {
			(char*)"/Help/_About...",
			NULL,
			NULL,
			IDM_VERSION,
			NULL
		}
	};

	nItemCount = sizeof(aifeMenu)/sizeof(aifeMenu[0]);
	return aifeMenu;
}

#endif // X88_GUI
