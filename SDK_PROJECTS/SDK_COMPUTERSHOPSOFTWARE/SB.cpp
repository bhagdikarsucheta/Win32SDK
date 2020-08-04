#include<Windows.h>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<wchar.h>
#include"resource.h"
#include"Thank.h"
#include"Receipt.h"
#define BUFFERSIZE 1000
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcTwo(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcThree(HWND, UINT, WPARAM, LPARAM);

void CreateMyFile(TCHAR[]);
void CreateMyWriteFile(TCHAR[]);

HBITMAP g_hbmBall = NULL;
BOOL bErrorFlag = FALSE;
DWORD dwBytesWritten = 0;
BOOL ReceiptFlag = FALSE;
BOOL TextOutFlag = FALSE;
TCHAR gStr;
int flag =0;
HINSTANCE hInst3 = NULL;					//For ThankYou DialogBoxS

wchar_t fileBuffer[200];
wchar_t fileBuffer2[200];
wchar_t fileBuffer3[200];
wchar_t fileBuffer4[200];
wchar_t fileBuffer5[200];
wchar_t fileBuffer6[200];
wchar_t fileBuffer7[200];
wchar_t fileBuffer8[200];
wchar_t fileBuffer9[200];
wchar_t fileBuffer10[200];
wchar_t fileBuffer11[200];
wchar_t fileBuffer12[200];


size_t i;
char *pMBuffer;
char *str = NULL;
wchar_t * STR1 = NULL;
wchar_t p[255];


FILE *gpFile = NULL;

struct Values
{
	TCHAR * RAMSelected;
	TCHAR * RAM_Subtype;
	TCHAR * RAM_Core;
	TCHAR *	RAM_Price;
	TCHAR *	Motherboard_nm;
	TCHAR *	Motherboard_type;
	TCHAR * Motherboard_type2;
	TCHAR *	MotherboardPrice;
	TCHAR * GraphicsCardnm;
	TCHAR * GraphicsCardType;
	TCHAR * GraphicsCardSize;
	TCHAR * GraphicsCardPrice;
	TCHAR * Cpu_nm;
	TCHAR * CPUType2;
	TCHAR * CPUCore;
	TCHAR * CpuPrice;
	TCHAR * HardDisknm;
	TCHAR * HardDiskSize;
	TCHAR * HardDiskPrice;
	TCHAR * HardDiskType;
	TCHAR *DVD;
	TCHAR *DVD_Type;
	TCHAR *Number_disks;
	TCHAR *DVDPrice;
	TCHAR * SMPS;
	TCHAR * SMPSWatt;
	TCHAR * SMPSCables;
	TCHAR *SMPSPrice;
	TCHAR * Cabinet;
	TCHAR * CabinetType;
	TCHAR * CabinetPrice;
	TCHAR * CabinetType2;
	TCHAR * Keyboard;
	TCHAR  *KeyboardType;
	TCHAR  *KeyboardColor;
	TCHAR * KeyboardPrice;
	TCHAR *Mouse;
	TCHAR *MouseType;
	TCHAR *MouseColor;
	TCHAR *MousePrice;
	TCHAR *Monitor;
	TCHAR *MonitorType;
	TCHAR *MonitorSize;
	TCHAR * MonitorPrice;
	TCHAR * Printer;
	TCHAR * PrinterColor;
	TCHAR * PrinterOutput;
	TCHAR * PrinterPrice;
	TCHAR * Name;
	TCHAR * Batch;
	TCHAR * Astromedicomp;
	TCHAR * Total;
	TCHAR * PrntMsg;
	TCHAR * ThankMsg;
	TCHAR * rupee;
	TCHAR * HitMsg;
}myvalues;


Values userdata;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
HINSTANCE hInst;
HDC hdcInst,hdcBitmap;
PAINTSTRUCT ps;
BITMAP bmap;
RECT r;
HBITMAP hBitmap;
HANDLE hFile;

TCHAR * Headings[] = { TEXT("DEVICE TYPE"),TEXT("DEVICE OPTION COMPANY NAME"),TEXT("MODEL NAME/NO"),TEXT("SIZE"),TEXT("COST") };

TCHAR * ComBox1Items_RAM[6] = { TEXT("****Select Company****"),TEXT("Corsair"),TEXT("Micron") ,0};
TCHAR * ComBox3Items_MotherBoard[6] = { TEXT("****Select Motherboard****"),TEXT("Acer"),TEXT("ACube Systems"),0 };
TCHAR* ComBox4Items_GraphicsCard[6] = { TEXT("****Select Company****"),TEXT("NVIDIA"),TEXT("Zotac") ,0};
TCHAR * ComBox5Items_CPU[6] = { TEXT("****Select Processor****"),TEXT("intel"),TEXT("AMD"),0 };
TCHAR * ComBox6Items_RAMSubtype[6] = { TEXT("****Select Company****"),TEXT("SDR"),TEXT("DDR"),0 };
TCHAR * ComBox13Items_RAMCore[6] = { TEXT("****Select Company****"),TEXT("4GB "),TEXT("8GB "),0 };

TCHAR * ComboBox7Items_HardDisk[6] = { TEXT("****Select HardDisk****"), TEXT("CGate"), TEXT("Western Digital"),0 };
TCHAR * ComboBox8Items_Dvd[6] = { TEXT("****Select Dvd****"), TEXT("Amkette"), TEXT("Frontech"),0 };
TCHAR * ComboBox38Items_Dvd[6] = { TEXT("****Select Type****"), TEXT("Recordable"), TEXT("Rewritable"),0 };
TCHAR * ComboBox49Items_NoDisks[6] = { TEXT("****Select Type****"), TEXT("18"), TEXT("50"),0 };

TCHAR * ComboBox9Items_SMPS[6] = { TEXT("****Select SMPS****"), TEXT("VIP"), TEXT("Circle SMPS "),0 };
TCHAR * ComboBox10Items_Cabinet[6] = { TEXT("****Select Cabinet****"), TEXT("Circle"), TEXT("Zebronics"),0 };
TCHAR * ComboBox11Items_Keyboard[6] = { TEXT("****Select Keyboard****"), TEXT("Microsoft"),TEXT("Logitech"), 0 };
TCHAR * ComboBox12Items_Mouse[6] = { TEXT("****Select Mouse****"), TEXT("Microsoft"), TEXT("Logitech"), 0};
TCHAR * ComboBox13Items_MotherboardType[6] = { TEXT("****Select Type****"),TEXT("ATX"), TEXT("ITX "),0 };
TCHAR * ComboBox32Items_MotherboardSubTypeATX[] = { TEXT("****Select Type****"),TEXT("MiniATX"), TEXT("MicroATX"),0 };
TCHAR * ComboBox33Items_MotherboardSubTypeITX[] = { TEXT("****Select Type****"),TEXT("ITX"), TEXT("MiniITX"),0 };
TCHAR * ComBox14Items_GraphicsCardSubtype1[6] = { TEXT("****Select Subtype****"),TEXT("GTX 1060"),TEXT("GTX 1080"),0 };
TCHAR * ComBox34Items_GraphicsCardSubtype2[6] = { TEXT("****Select Subtype****"),TEXT("Zotac 1050"),TEXT("Zotac 1050 Ti"),0 };
TCHAR * ComBox35Items_GraphicsCardSubtype3[6] = { TEXT("****Select Size****"),TEXT("4 GB"),TEXT("8 GB"),0 };

TCHAR * ComboBox15Items_HardDisk[6] = { TEXT("****Select Size****"), TEXT("4 TB"), TEXT("10 TB"),0 };
TCHAR * ComboBox36Items_HardDiskType[6] = { TEXT("****Select Type****"), TEXT("Portable"), TEXT("Desktop"),0 };

TCHAR * ComboBox16Items_SMPSWatt[6] = { TEXT("****Select Watts****"), TEXT("500 Watts"), TEXT("250 Watts"),0 };
TCHAR * ComboBox37Items_SMPSCable[6] = { TEXT("****Select Cables****"), TEXT("7 Cables"), TEXT("8 Cables"),0 };

TCHAR * ComboBox17Items_Cabinet[6] = { TEXT("****Select Color****"), TEXT("Black"), TEXT("Grey"),0 };
TCHAR * ComboBox38Items_CabinetPanel[6] = { TEXT("****Side Panel Option****"), TEXT("Yes"), TEXT("No"),0 };

TCHAR * ComboBox18Items_KeyboardType[6] = { TEXT("****Select Type****"), TEXT("Wired"), TEXT("Wireless"),0 };
TCHAR * ComboBox19Items_MouseType[6] = { TEXT("****Select Mouse****"), TEXT("Wired"), TEXT("Wireless"),0 };
TCHAR * ComboBox40Items_MouseColor[6] = { TEXT("****Mouse Color****"), TEXT("Black"), TEXT("White"),0 };

TCHAR * ComboBoxRAMPrice[2] = { TEXT("2000.0") };
TCHAR * ComBox20Items_CPU[6] = { TEXT("****Select Processor****"),TEXT("i5 Generation"),TEXT("i7 Generation"),0};
TCHAR * ComBox36Items_CPUA[6] = { TEXT("****Select Processor****"),TEXT("i5 A "),TEXT("i7 A"),0 };
TCHAR * ComBoxItems_AMDOne[6] = { TEXT("****Select Processor****"),TEXT("A8-7600 "),TEXT("A6-6400K"),0 };
TCHAR * ComBoxItems_AMDSubtype[6] = { TEXT("****Select Processor****"),TEXT("3.5GHz"),TEXT("4.0GHz"),0 };

TCHAR * ComboBox39Items_KeyboardColor[6] = { TEXT("****Keyboard Color****"), TEXT("Black"), TEXT("White"),0 };
TCHAR * ComboBox41Items_Monitor[6] = { TEXT("****Select Monitor****"), TEXT("Dell"), TEXT("Samsung"),0 };
TCHAR * ComboBox42Items_MonitorType[6] = { TEXT("****Monitor Type****"), TEXT("Full HD"), TEXT("HD"),0 };
TCHAR * ComboBox43Items_MonitorSize[6] = { TEXT("****Monitor Size****"), TEXT("19-22.9"), TEXT("23-26.9"),0 };

TCHAR * ComboBox45Items_Printer[6] = { TEXT("****Select Printer****"), TEXT("Canon"), TEXT("HP"),0 };
TCHAR * ComboBox46Items_PrinterColor[6] = { TEXT("****Select Color****"), TEXT("Black"), TEXT("Blue"),0 };
TCHAR * ComboBox47Items_PrinterOutput[6] = { TEXT("****Select Color****"), TEXT("Color"), TEXT("Monochrome"),0 };


TCHAR * ComBox21Items_CPU[6] = { TEXT("****Select Company****"),TEXT("i3 "),TEXT("i5"),TEXT("i7") ,0};
TCHAR * ComBox22Items_CPU[6] = { TEXT("1500.0"),TEXT("2500.0"),0 };				//price CPU
TCHAR * ComBox23Items_Motherboard[6] = { TEXT("8000.0"), TEXT("10000.0"),0 };		//price motherboard
TCHAR * ComBox24Items_Graphics[6] = { TEXT("5000.0") ,TEXT("6000.0") ,0};			//price graphics card
TCHAR * ComBox25Items_HDD[6] = { TEXT("4500.0"),TEXT("7000.0"),0 };				//price hard drive
TCHAR * ComBox26Items_DVD[6] = { TEXT("5000.0"),TEXT("4500.0"),0 };						//price DVD
TCHAR * ComBox27Items_SMPS[6] = { TEXT("725.0"),TEXT("900.0"),0 };				//price DVD
TCHAR * ComBox28Items_Cabinet[6] = { TEXT("2000.0"),TEXT("2150.0"),0 };				//price Cabinet
TCHAR * ComBox29Items_Keyboard[6] = { TEXT("700.0"),TEXT("1000"),0 };			//price Keyboard
TCHAR * ComBox30Items_Mouse[6] = { TEXT("500.0"),TEXT("700.0"),0 };			//price Mouse
TCHAR * ComBox44Items_Monitor[6] = { TEXT("11940.0"),TEXT("12500.0"),0 };			//price Monitor
TCHAR * Combo31RAMPric[6] = { TEXT("8000.0"), TEXT("10000.0"),0 };
TCHAR * Combo48PrinterPrice[6] = { TEXT("7950.0"), TEXT("9000.0"),0 };
float  Total =0.0f;
wchar_t **endptr = NULL;
wchar_t * buffer;

wchar_t * tempvar = NULL;
int decimal, sign;
HWND ghwnd;
bool splashScreenActive = true;		
HWND hHDlg;



int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Windows");
	pMBuffer = (char *)malloc(BUFFERSIZE);
	gpFile = fopen("ItemsChoosen.txt", "w");
	if (gpFile == NULL)
	{
		printf("Error opening File");
		exit(0);
	}

	ZeroMemory((wchar_t*)&buffer, sizeof(buffer));
	userdata.Name = L"Name:Sucheta.A.Bhagdikar";
	userdata.Batch = L"Batch:SDK 2017";
	userdata.Astromedicomp = L"ASTROMEDICOMP";
	userdata.Total = L"Total :  Rs. ";
	userdata.PrntMsg = L"Press P to Generate Receipt";
	userdata.ThankMsg = L"Thank You !! Visit Again";
	userdata.rupee = L"U + 20B9";

	userdata.RAM_Price = L"0.0";
	userdata.MotherboardPrice = L"0.0";
	userdata.GraphicsCardPrice = L"0.0";
	userdata.HardDiskPrice = L"0.0";
	userdata.CpuPrice = L"0.0";
	userdata.DVDPrice = L"0.0";
	userdata.SMPSPrice = L"0.0";
	userdata.CabinetPrice = L"0.0";
	userdata.KeyboardPrice = L"0.0";
	userdata.MousePrice = L"0.0";
	userdata.MonitorPrice = L"0.0";
	userdata.PrinterPrice = L"0.0";
	userdata.HitMsg = L"Hit SpaceBar to Continue";

	str = (char *)malloc(sizeof(char)*100);

	STR1 = (wchar_t *)malloc(200 * sizeof(wchar_t));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, TEXT("IDI_ICON"));
	wndclass.hIconSm = LoadIcon(hInstance, TEXT("IDI_ICON"));
	wndclass.hCursor = LoadCursor(hInstance, TEXT("IDI_ICON"));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,
		TEXT("MyFirstWindow"),
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1399,
		790,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (NULL == hwnd)
	{
		MessageBox(hwnd,
			TEXT("Window Not Created"),
			TEXT("ERROR"),
			MB_OK);
		exit(0);
	}

	ghwnd = hwnd;

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}




BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd_RAMPrice,hwnd_MotherboardPrice,hwnd_GraphicsCard,hwnd_HardDisk,hwnd_CPU,hwnd_SMPS,hwnd_Keyboard,hwnd_Mouse,hwnd_Monitor,hwnd_Printer;
		TCHAR itemChosen[255];

	int index;
	hHDlg = hDlg;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		for (int count = 0;ComBox1Items_RAM[count] !=0;count++)
		{
			SendDlgItemMessage(hDlg, ID_RAM, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox1Items_RAM[count]);
			
		}
		SendDlgItemMessage(hDlg, ID_RAM, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComBox3Items_MotherBoard[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_MOTHERBOARD, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox3Items_MotherBoard[count]);
		}
		SendDlgItemMessage(hDlg, ID_MOTHERBOARD, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComBox4Items_GraphicsCard[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_GRAPHICSCARD, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox4Items_GraphicsCard[count]);
		}
		SendDlgItemMessage(hDlg, ID_GRAPHICSCARD, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComBox5Items_CPU[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_CPU, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox5Items_CPU[count]);
		}
		SendDlgItemMessage(hDlg, ID_CPU, CB_SETCURSEL, 0, 0);
		
		for (int count = 0;ComboBox7Items_HardDisk[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_HARDDISKS, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox7Items_HardDisk[count]);
		}
		SendDlgItemMessage(hDlg, ID_HARDDISKS, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComboBox8Items_Dvd[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_DVD, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox8Items_Dvd[count]);
		}
		SendDlgItemMessage(hDlg, ID_DVD, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComboBox9Items_SMPS[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_SMPS, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox9Items_SMPS[count]);
		}
		SendDlgItemMessage(hDlg, ID_SMPS, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComboBox10Items_Cabinet[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_CABINET, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox10Items_Cabinet[count]);
		}
		SendDlgItemMessage(hDlg, ID_CABINET, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComboBox11Items_Keyboard[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_KEYBOARD, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox11Items_Keyboard[count]);
		}
		SendDlgItemMessage(hDlg, ID_KEYBOARD, CB_SETCURSEL, 0, 0);

		for (int count = 0;ComboBox12Items_Mouse[count] != 0;count++)
		{
			SendDlgItemMessage(hDlg, ID_MOUSE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox12Items_Mouse[count]);
		}
		SendDlgItemMessage(hDlg, ID_MOUSE, CB_SETCURSEL, 0, 0);
		
			for (int count = 0;ComboBox41Items_Monitor[count] != 0;count++)
			{
				SendDlgItemMessage(hDlg, ID_MONITOR, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox41Items_Monitor[count]);
			}
			SendDlgItemMessage(hDlg, ID_MONITOR, CB_SETCURSEL, 0, 0);

			for (int count = 0;ComboBox45Items_Printer[count] != 0;count++)
			{
				SendDlgItemMessage(hDlg, ID_PRINTER, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox45Items_Printer[count]);
			}
			SendDlgItemMessage(hDlg, ID_PRINTER, CB_SETCURSEL, 0, 0);

		ShowWindow(GetDlgItem(hDlg, ID_SUBTYPE_RAM), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_RAM_CORE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_PRICE_RAM), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE2), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSUBTYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_GRAPHICSCARD_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_CPU_TYPE2), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_CPU_CORE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_CPU_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_SIZE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_DVD_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_NUMBER_DISKS), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_DVD_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_SMPS_WATTS), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_SMPS_CABLES), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_SMPS_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_CABINET_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_CABINET_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_CABINET_TYPE2), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_COLOR), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MOUSE_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MOUSE_COLOR), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MOUSE_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MONITOR_TYPE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MONITOR_SIZE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_MONITOR_PRICE), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_PRINTER_COLOR), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_PRINTER_OUTPUT), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, ID_PRINTER_PRICE), SW_HIDE);

		break;


	case WM_PAINT:
		hdcInst = BeginPaint(hDlg, &ps);
		hInst = (HINSTANCE)GetWindowLong(hDlg, GWLP_HINSTANCE);
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DLGIMAGE));
		hdcBitmap = CreateCompatibleDC(hdcInst);
		GetClientRect(hDlg, &r);
		SelectObject(hdcBitmap, hBitmap);
		GetObject(hBitmap, sizeof(bmap), &bmap);
		BitBlt(hdcInst, 0, 0, r.right - r.left, r.bottom - r.top, hdcBitmap, 0, 0, SRCCOPY);
//		stretchBlt
		DeleteObject(hdcBitmap);
		EndPaint(hDlg,&ps);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			//here change the size of window for furthur painting of material list
			GetWindowPlacement(ghwnd, &wpPrev);
			wpPrev.rcNormalPosition.top = wpPrev.rcNormalPosition.top + 0x50;
			wpPrev.rcNormalPosition.bottom = wpPrev.rcNormalPosition.bottom - 0x50;
			wpPrev.rcNormalPosition.left = wpPrev.rcNormalPosition.left + 0x50;
			wpPrev.rcNormalPosition.right = wpPrev.rcNormalPosition.right - 0x50;
			SetWindowPlacement(ghwnd, &wpPrev);
			splashScreenActive = false;
			InvalidateRect(ghwnd, NULL, true);
			EndDialog(hDlg, 0);
			splashScreenActive = false;

		
		Total = wcstof(userdata.RAM_Price, endptr) + wcstof(userdata.MotherboardPrice, endptr) + wcstof(userdata.GraphicsCardPrice, endptr) + wcstof(userdata.CpuPrice, endptr) + wcstof(userdata.HardDiskPrice, endptr) + wcstof(userdata.DVDPrice, endptr) + wcstof(userdata.SMPSPrice, endptr) + wcstof(userdata.CabinetPrice, endptr) + wcstof(userdata.KeyboardPrice, endptr) + wcstof(userdata.MousePrice, endptr) + wcstof(userdata.MonitorPrice, endptr) + wcstof(userdata.PrinterPrice, endptr);

			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;

		case ID_PBCONTINUE:
			break;
		}

		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:

			switch (LOWORD(wParam))
			{
			case ID_RAM:
				index = SendMessage(GetDlgItem(hDlg, ID_RAM), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_RAM), CB_GETLBTEXT, index, (LPARAM)itemChosen);

				GetDlgItemText(hDlg, ID_RAM, (LPWSTR)gStr, 50);
		
				/////////

				if (wcscmp(itemChosen, ComBox1Items_RAM[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_SUBTYPE_RAM, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.RAMSelected = ComBox1Items_RAM[index];
					for (int count = 0;ComBox6Items_RAMSubtype[count] != 0;count++)
					{

						SendDlgItemMessage(hDlg, ID_SUBTYPE_RAM, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox6Items_RAMSubtype[count]);
					}
					SendDlgItemMessage(hDlg, ID_SUBTYPE_RAM, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_SUBTYPE_RAM), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComBox1Items_RAM[0]) == 0)
				{
					userdata.RAMSelected = L"-";
				}
				break;

			case ID_SUBTYPE_RAM:
				index = SendMessage(GetDlgItem(hDlg, ID_SUBTYPE_RAM), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_SUBTYPE_RAM), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				 GetDlgItemText(hDlg, ID_SUBTYPE_RAM, (LPWSTR)gStr, 50);
				 GetDlgItem(hDlg, ID_SUBTYPE_RAM);
				if (wcscmp(itemChosen, ComBox6Items_RAMSubtype[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_RAM_CORE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.RAM_Subtype = ComBox6Items_RAMSubtype[1];
					for (int count = 0;ComBox13Items_RAMCore[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_RAM_CORE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox13Items_RAMCore[count]);
					}
					SendDlgItemMessage(hDlg, ID_RAM_CORE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_RAM_CORE), SW_SHOW);					
				}
				else if (wcscmp(itemChosen, ComBox6Items_RAMSubtype[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_RAM_CORE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.RAM_Subtype = ComBox6Items_RAMSubtype[2];
					for (int count = 0;ComBox13Items_RAMCore[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_RAM_CORE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox13Items_RAMCore[count]);
					}
					SendDlgItemMessage(hDlg, ID_RAM_CORE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_RAM_CORE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComBox6Items_RAMSubtype[0]) == 0)
				{
					userdata.RAM_Subtype = L"-";
				}
				break;

			case ID_RAM_CORE:
				index = SendMessage(GetDlgItem(hDlg, ID_RAM_CORE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_RAM_CORE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_SUBTYPE_RAM, (LPWSTR)gStr, 50);
				if (wcscmp(itemChosen, ComBox13Items_RAMCore[1]) == 0)
				{
					userdata.RAM_Core = ComBox13Items_RAMCore[1];
					for (int count = 0;Combo31RAMPric[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRICE_RAM, CB_ADDSTRING,(WPARAM)0, (LPARAM)Combo31RAMPric[count]);
					}
					hwnd_RAMPrice = GetDlgItem(hDlg, ID_PRICE_RAM);
					EnableWindow(hwnd_RAMPrice, FALSE);
					SendDlgItemMessage(hDlg, ID_PRICE_RAM, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_PRICE_RAM), SW_SHOW);
					GetDlgItemText(hDlg, ID_PRICE_RAM, (LPWSTR)gStr, 50);
					userdata.RAM_Price = Combo31RAMPric[0];
				}
				else if (wcscmp(itemChosen, ComBox13Items_RAMCore[2]) == 0)
					{
					userdata.RAM_Core = ComBox13Items_RAMCore[2];
					for (int count = 0;Combo31RAMPric[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRICE_RAM, CB_ADDSTRING,(WPARAM)0, (LPARAM)Combo31RAMPric[count]);
					}
					hwnd_RAMPrice = GetDlgItem(hDlg, ID_PRICE_RAM);
					EnableWindow(hwnd_RAMPrice,FALSE);
					SendDlgItemMessage(hDlg, ID_PRICE_RAM, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_PRICE_RAM), SW_SHOW);
					GetDlgItemText(hDlg, ID_PRICE_RAM, (LPWSTR)gStr, 50);
					userdata.RAM_Price = Combo31RAMPric[1];
					}
					if (wcscmp(itemChosen, ComBox13Items_RAMCore[0]) == 0)
					{
						userdata.RAM_Core = L"-";
						userdata.RAM_Price = L"0.0";
					}

				break;
			case ID_MOTHERBOARD:

				index = SendMessage(GetDlgItem(hDlg, ID_MOTHERBOARD), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MOTHERBOARD), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MOTHERBOARD, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComBox3Items_MotherBoard[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE, CB_RESETCONTENT, (WPARAM)0,(LPARAM)0);
					GetDlgItemText(hDlg, ID_MOTHERBOARD_TYPE, (LPWSTR)gStr, 50);
					userdata.Motherboard_nm = ComBox3Items_MotherBoard[index];
					for (int count = 0;ComboBox13Items_MotherboardType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox13Items_MotherboardType[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComBox3Items_MotherBoard[0]) == 0)
				{
					userdata.Motherboard_nm = L"-";
				}
				break;
			case ID_MOTHERBOARD_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MOTHERBOARD_TYPE, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox13Items_MotherboardType[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE2, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.Motherboard_type = ComboBox13Items_MotherboardType[1];
					for (int count = 0;ComboBox32Items_MotherboardSubTypeATX[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE2, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox32Items_MotherboardSubTypeATX[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE2, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE2), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox13Items_MotherboardType[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE2, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.Motherboard_type = ComboBox13Items_MotherboardType[2];
					for (int count = 0;ComboBox33Items_MotherboardSubTypeITX[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE2, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox33Items_MotherboardSubTypeITX[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_TYPE2, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE2), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox13Items_MotherboardType[0]) == 0)
				{
					userdata.Motherboard_type = L"-";
				}
				break;

			case ID_MOTHERBOARD_TYPE2:
				index = SendMessage(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE2), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MOTHERBOARD_TYPE2), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				hwnd_MotherboardPrice = GetDlgItem(hDlg, ID_MOTHERBOARD_PRICE);
				if(wcscmp(itemChosen, ComboBox32Items_MotherboardSubTypeATX[1]) == 0)
				{
					userdata.Motherboard_type2 = ComboBox32Items_MotherboardSubTypeATX[1];
					for (int count = 0;ComBox23Items_Motherboard[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox23Items_Motherboard[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_PRICE), SW_SHOW);
					userdata.MotherboardPrice = ComBox23Items_Motherboard[0];
					EnableWindow(hwnd_MotherboardPrice, FALSE);
				}
				else if (wcscmp(itemChosen, ComboBox32Items_MotherboardSubTypeATX[2]) == 0)
				{
					userdata.Motherboard_type2 = ComboBox32Items_MotherboardSubTypeATX[2];
					for (int count = 0;ComBox23Items_Motherboard[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox23Items_Motherboard[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_PRICE), SW_SHOW);
					userdata.MotherboardPrice = ComBox23Items_Motherboard[1];
					EnableWindow(hwnd_MotherboardPrice, FALSE);
				}
				else if (wcscmp(itemChosen, ComboBox33Items_MotherboardSubTypeITX[1]) == 0)
				{
					userdata.Motherboard_type2 = ComboBox33Items_MotherboardSubTypeITX[1];
					for (int count = 0;ComBox23Items_Motherboard[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox23Items_Motherboard[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_PRICE), SW_SHOW);
					userdata.MotherboardPrice = ComBox23Items_Motherboard[0];
					EnableWindow(hwnd_MotherboardPrice, FALSE);
				}
				else if (wcscmp(itemChosen, ComboBox33Items_MotherboardSubTypeITX[2]) == 0)
				{
					userdata.Motherboard_type2 = ComboBox33Items_MotherboardSubTypeITX[2];
					for (int count = 0;ComBox23Items_Motherboard[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox23Items_Motherboard[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOTHERBOARD_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_MOTHERBOARD_PRICE), SW_SHOW);
					userdata.MotherboardPrice = ComBox23Items_Motherboard[1];
					EnableWindow(hwnd_MotherboardPrice, FALSE);
				}
				if ((wcscmp(itemChosen, ComboBox33Items_MotherboardSubTypeITX[0])) == 0 )
				{
					userdata.Motherboard_type2 = L"-";
					userdata.MotherboardPrice = L"0.0";
				}
				else if ((wcscmp(itemChosen, ComboBox32Items_MotherboardSubTypeATX[0])) == 0 )
				{
					userdata.Motherboard_type2 = L"-";
					userdata.MotherboardPrice = L"0.0";
				}
				break;
			
			case ID_GRAPHICSCARD:
				index = SendMessage(GetDlgItem(hDlg, ID_GRAPHICSCARD), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_GRAPHICSCARD), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_GRAPHICSCARD, (LPWSTR)gStr, 50);
				if (wcscmp(itemChosen, ComBox4Items_GraphicsCard[1]) == 0)
				{
					userdata.GraphicsCardnm = ComBox4Items_GraphicsCard[1];
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSUBTYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					for (int count = 0;ComBox14Items_GraphicsCardSubtype1[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSUBTYPE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox14Items_GraphicsCardSubtype1[count]);
					}

					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSUBTYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSUBTYPE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBox4Items_GraphicsCard[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSUBTYPE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.GraphicsCardnm = ComBox4Items_GraphicsCard[2];
					for (int count = 0;ComBox34Items_GraphicsCardSubtype2[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSUBTYPE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox34Items_GraphicsCardSubtype2[count]);
					}
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSUBTYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSUBTYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComBox4Items_GraphicsCard[0]) == 0)
				{
					userdata.GraphicsCardnm = L"-";
				}
				break;

			case ID_GRAPHICS_CARDSUBTYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_GRAPHICS_CARDSUBTYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_GRAPHICS_CARDSUBTYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_GRAPHICS_CARDSUBTYPE, (LPWSTR)gStr, 50);
				if (wcscmp(itemChosen, ComBox14Items_GraphicsCardSubtype1[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.GraphicsCardType = ComBox14Items_GraphicsCardSubtype1[1];
					for (int count = 0;ComBox35Items_GraphicsCardSubtype3[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox35Items_GraphicsCardSubtype3[count]);
					}
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBox14Items_GraphicsCardSubtype1[2]) == 0)
				{
					userdata.GraphicsCardType = ComBox14Items_GraphicsCardSubtype1[2];
					for (int count = 0;ComBox35Items_GraphicsCardSubtype3[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox35Items_GraphicsCardSubtype3[count]);
					}
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBox34Items_GraphicsCardSubtype2[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_RESETCONTENT,(WPARAM)0,(LPARAM)0);

					userdata.GraphicsCardType = ComBox34Items_GraphicsCardSubtype2[1];
					for (int count = 0;ComBox35Items_GraphicsCardSubtype3[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox35Items_GraphicsCardSubtype3[count]);
					}
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBox34Items_GraphicsCardSubtype2[2]) == 0)
				{
					userdata.GraphicsCardType = ComBox34Items_GraphicsCardSubtype2[2];
					for (int count = 0;ComBox35Items_GraphicsCardSubtype3[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox35Items_GraphicsCardSubtype3[count]);
					}
					SendDlgItemMessage(hDlg, ID_GRAPHICS_CARDSIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), SW_SHOW);
				}
				if ((wcscmp(itemChosen, ComBox14Items_GraphicsCardSubtype1[0])) == 0)
				{
					userdata.GraphicsCardType = L"-";
				}
				else if ((wcscmp(itemChosen, ComBox34Items_GraphicsCardSubtype2[0])) == 0)
				{
					userdata.GraphicsCardType = L"-";
				}
				break;

			case ID_GRAPHICS_CARDSIZE:				
					index = SendMessage(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_GRAPHICS_CARDSIZE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_GRAPHICS_CARDSIZE, (LPWSTR)gStr, 50);
				hwnd_GraphicsCard = GetDlgItem(hDlg, ID_GRAPHICSCARD_PRICE);
				if (wcscmp(itemChosen, ComBox35Items_GraphicsCardSubtype3[1]) == 0)
				{
					userdata.GraphicsCardSize = ComBox35Items_GraphicsCardSubtype3[1];
					for (int count = 0;ComBox24Items_Graphics[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICSCARD_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox24Items_Graphics[count]);
					}
					EnableWindow(hwnd_GraphicsCard,FALSE);
					SendDlgItemMessage(hDlg, ID_GRAPHICSCARD_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICSCARD_PRICE), SW_SHOW);
					userdata.GraphicsCardPrice = ComBox24Items_Graphics[0];
				}
				else if (wcscmp(itemChosen, ComBox35Items_GraphicsCardSubtype3[2]) == 0)
				{
					userdata.GraphicsCardSize = ComBox35Items_GraphicsCardSubtype3[2];
					for (int count = 0;ComBox24Items_Graphics[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_GRAPHICSCARD_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox24Items_Graphics[count]);
					}
					SendDlgItemMessage(hDlg, ID_GRAPHICSCARD_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_GRAPHICSCARD_PRICE), SW_SHOW);
					userdata.GraphicsCardPrice = ComBox24Items_Graphics[1];
					EnableWindow(hwnd_GraphicsCard, FALSE);
				}
				if (wcscmp(itemChosen, ComBox35Items_GraphicsCardSubtype3[0]) == 0)
				{
					userdata.GraphicsCardSize = L"-";
					userdata.GraphicsCardPrice = L"0.0";
				}
				break;
				
			case ID_CPU:
				index = SendMessage(GetDlgItem(hDlg, ID_CPU), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_CPU), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_CPU, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComBox5Items_CPU[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CPU_TYPE2, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.Cpu_nm = ComBox5Items_CPU[1];
					for (int count = 0;ComBox20Items_CPU[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_TYPE2, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox20Items_CPU[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_TYPE2, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_TYPE2), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBox5Items_CPU[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CPU_TYPE2, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.Cpu_nm = ComBox5Items_CPU[2];
					for (int count = 0;ComBoxItems_AMDOne[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_TYPE2, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBoxItems_AMDOne[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_TYPE2, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_TYPE2), SW_SHOW);
				}
			
				if (wcscmp(itemChosen, ComBox5Items_CPU[0]) == 0)
				{
					userdata.Cpu_nm = L"-";
				}
				else if (wcscmp(itemChosen, ComBoxItems_AMDOne[0]) == 0)
				{
					userdata.Cpu_nm = L"-";
				}
				break;

			case ID_CPU_TYPE2:
				index = SendMessage(GetDlgItem(hDlg, ID_CPU_TYPE2), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_CPU_TYPE2), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_CPU_TYPE2, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComBox20Items_CPU[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_RESETCONTENT, (WPARAM)0,(LPARAM)0);

					userdata.CPUType2 = ComBox20Items_CPU[1];
					for (int count = 0;ComBox36Items_CPUA[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox36Items_CPUA[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_CORE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBox20Items_CPU[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

					userdata.CPUType2 = ComBox20Items_CPU[2];
					for (int count = 0;ComBox36Items_CPUA[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox36Items_CPUA[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_CORE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBoxItems_AMDOne[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

					userdata.CPUType2 = ComBoxItems_AMDOne[2];
					for (int count = 0;ComBoxItems_AMDSubtype[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBoxItems_AMDSubtype[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_CORE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComBoxItems_AMDOne[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

					userdata.CPUType2 = ComBoxItems_AMDOne[1];
					for (int count = 0;ComBoxItems_AMDSubtype[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBoxItems_AMDSubtype[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_CORE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_CORE), SW_SHOW);
				}

				if (wcscmp(itemChosen, ComBox20Items_CPU[0]) == 0)
				{
					userdata.CPUType2 = L"-";
				}
				break;

			case ID_CPU_CORE:
				index = SendMessage(GetDlgItem(hDlg, ID_CPU_CORE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_CPU_CORE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_CPU_CORE, (LPWSTR)gStr, 50);
				hwnd_CPU = GetDlgItem(hDlg, ID_CPU_PRICE);

				if (wcscmp(itemChosen, ComBox36Items_CPUA[1]) == 0)
				{
					userdata.CPUCore = ComBox36Items_CPUA[1];
					for (int count = 0;ComBox22Items_CPU[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox22Items_CPU[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_PRICE), SW_SHOW);
					userdata.CpuPrice = ComBox22Items_CPU[0];
					EnableWindow(hwnd_CPU, FALSE);
				}
				else if (wcscmp(itemChosen, ComBox36Items_CPUA[2]) == 0)
				{
					userdata.CPUCore = ComBox36Items_CPUA[2];
					for (int count = 0;ComBox22Items_CPU[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox22Items_CPU[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_PRICE), SW_SHOW);
					userdata.CpuPrice = ComBox22Items_CPU[0];
					EnableWindow(hwnd_CPU, FALSE);
				}
				else if (wcscmp(itemChosen, ComBoxItems_AMDSubtype[2]) == 0)			//require else if for bothn 1 and 2
				{
					userdata.CPUCore = ComBoxItems_AMDSubtype[2];
					for (int count = 0;ComBox22Items_CPU[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox22Items_CPU[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_PRICE), SW_SHOW);
					userdata.CpuPrice = ComBox22Items_CPU[1];
					EnableWindow(hwnd_CPU, FALSE);
				}
				else if (wcscmp(itemChosen, ComBoxItems_AMDSubtype[1]) == 0)			//require else if for bothn 1 and 2
				{
					userdata.CPUCore = ComBoxItems_AMDSubtype[2];
					for (int count = 0;ComBox22Items_CPU[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox22Items_CPU[count]);
					}
					SendDlgItemMessage(hDlg, ID_CPU_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CPU_PRICE), SW_SHOW);
					userdata.CpuPrice = ComBox22Items_CPU[1];
					EnableWindow(hwnd_CPU, FALSE);
				}
				if (wcscmp(itemChosen, ComBox36Items_CPUA[0]) == 0)
				{
					userdata.CPUCore = L"-";
					userdata.CpuPrice = L"0.0";
				}
				else if (wcscmp(itemChosen, ComBoxItems_AMDSubtype[0]) == 0)
				{
					userdata.CPUCore = L"-";
					userdata.CpuPrice = L"0.0";
				}
				break;
	
			case ID_HARDDISKS:
				index = SendMessage(GetDlgItem(hDlg, ID_HARDDISKS), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_HARDDISKS), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_HARDDISKS, (LPWSTR)gStr, 50);
				SendDlgItemMessage(hDlg, ID_HARDDISK_SIZE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

				if (wcscmp(itemChosen,ComboBox7Items_HardDisk[index]) == 0)
				{
					userdata.HardDisknm = ComboBox7Items_HardDisk[index];
					for (int count = 0;ComboBox15Items_HardDisk[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_HARDDISK_SIZE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox15Items_HardDisk[count]);
					}
					SendDlgItemMessage(hDlg, ID_HARDDISK_SIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_SIZE), SW_SHOW);

				}
				if (wcscmp(itemChosen, ComboBox7Items_HardDisk[0]) == 0)
				{
					userdata.HardDisknm = L"-";
				}
				break;
			case ID_HARDDISK_SIZE:
				index = SendMessage(GetDlgItem(hDlg, ID_HARDDISK_SIZE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_HARDDISK_SIZE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_HARDDISK_SIZE, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox15Items_HardDisk[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_HARDDISK_TYPE, CB_RESETCONTENT,(WPARAM)0,(LPARAM)0);
					userdata.HardDiskSize = ComboBox15Items_HardDisk[1];
					for (int count = 0;ComboBox36Items_HardDiskType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_HARDDISK_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox36Items_HardDiskType[count]);
					}
					SendDlgItemMessage(hDlg, ID_HARDDISK_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_TYPE), SW_SHOW);
				}
				else if(wcscmp(itemChosen, ComboBox15Items_HardDisk[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_HARDDISK_TYPE, CB_RESETCONTENT, (WPARAM)0,(LPARAM)0);

					userdata.HardDiskSize = ComboBox15Items_HardDisk[2];
					for (int count = 0;ComboBox36Items_HardDiskType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_HARDDISK_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox36Items_HardDiskType[count]);
					}
					SendDlgItemMessage(hDlg, ID_HARDDISK_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox15Items_HardDisk[0]) == 0)
				{
					userdata.HardDiskSize = L"-";
				}
				break;

			case ID_HARDDISK_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_HARDDISK_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_HARDDISK_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_HARDDISK_TYPE, (LPWSTR)gStr, 50);
				hwnd_HardDisk = GetDlgItem(hDlg, ID_HARDDISK_PRICE);
				if (wcscmp(itemChosen, ComboBox36Items_HardDiskType[1]) == 0)
				{
					userdata.HardDiskType = ComboBox36Items_HardDiskType[1];
					for (int count = 0;ComBox25Items_HDD[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_HARDDISK_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox25Items_HDD[count]);
					}
					SendDlgItemMessage(hDlg, ID_HARDDISK_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_PRICE), SW_SHOW);
					EnableWindow(hwnd_HardDisk, FALSE);
					userdata.HardDiskPrice = ComBox25Items_HDD[0];
					GetDlgItemText(hDlg, ID_HARDDISK_PRICE, (LPWSTR)gStr, 50);
				}
				else if (wcscmp(itemChosen, ComboBox36Items_HardDiskType[2]) == 0)
				{
					userdata.HardDiskType = ComboBox36Items_HardDiskType[2];
					for (int count = 0;ComBox25Items_HDD[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_HARDDISK_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox25Items_HDD[count]);
					}
					SendDlgItemMessage(hDlg, ID_HARDDISK_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_HARDDISK_PRICE), SW_SHOW);
					userdata.HardDiskPrice = ComBox25Items_HDD[1];
					GetDlgItemText(hDlg, ID_HARDDISK_PRICE, (LPWSTR)gStr, 50);
					EnableWindow(hwnd_HardDisk, FALSE);
				}
				if (wcscmp(itemChosen, ComboBox36Items_HardDiskType[0]) == 0)
				{
					userdata.HardDiskType = L"-";
					userdata.HardDiskPrice = L"0.0";
				}
				break;

			case ID_DVD:
				index = SendMessage(GetDlgItem(hDlg, ID_DVD), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_DVD), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_DVD, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox8Items_Dvd[index]) == 0)
				{		
					SendDlgItemMessage(hDlg, ID_DVD_TYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

					userdata.DVD = ComboBox8Items_Dvd[index];
					for (int count = 0;ComboBox38Items_Dvd[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_DVD_TYPE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox38Items_Dvd[count]);
					}
					SendDlgItemMessage(hDlg, ID_DVD_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_DVD_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox8Items_Dvd[0]) == 0)
				{
					userdata.DVD = L"-";
				}
				break;
			case ID_DVD_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_DVD_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_DVD_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_DVD_TYPE, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox38Items_Dvd[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_NUMBER_DISKS, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

					userdata.DVD_Type = ComboBox38Items_Dvd[1];
					for (int count = 0;ComboBox49Items_NoDisks[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_NUMBER_DISKS, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox49Items_NoDisks[count]);
					}
					SendDlgItemMessage(hDlg, ID_NUMBER_DISKS, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_NUMBER_DISKS), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox38Items_Dvd[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_NUMBER_DISKS, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.DVD_Type = ComboBox38Items_Dvd[2];
					for (int count = 0;ComboBox49Items_NoDisks[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_NUMBER_DISKS, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox49Items_NoDisks[count]);
					}
					SendDlgItemMessage(hDlg, ID_NUMBER_DISKS, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_NUMBER_DISKS), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox38Items_Dvd[0]) == 0)
				{
					userdata.DVD_Type = L"-";
				}
				break;
			case ID_NUMBER_DISKS:
				index = SendMessage(GetDlgItem(hDlg, ID_NUMBER_DISKS), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_NUMBER_DISKS), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_NUMBER_DISKS, (LPWSTR)gStr, 50);
				hwnd_HardDisk = GetDlgItem(hDlg, ID_DVD_PRICE);
				if (wcscmp(itemChosen, ComboBox49Items_NoDisks[1]) == 0)
				{
					userdata.Number_disks = ComboBox49Items_NoDisks[1];
					for (int count = 0;ComBox26Items_DVD[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_DVD_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox26Items_DVD[count]);
					}
					SendDlgItemMessage(hDlg, ID_DVD_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_DVD_PRICE), SW_SHOW);
					EnableWindow(hwnd_HardDisk, FALSE);
					userdata.DVDPrice = ComBox26Items_DVD[0];
				}
				else if (wcscmp(itemChosen, ComboBox49Items_NoDisks[2]) == 0)
				{
					userdata.Number_disks = ComboBox49Items_NoDisks[2];
					for (int count = 0;ComBox26Items_DVD[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_DVD_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox26Items_DVD[count]);
					}
					SendDlgItemMessage(hDlg, ID_DVD_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_DVD_PRICE), SW_SHOW);
					EnableWindow(hwnd_HardDisk, FALSE);
					userdata.DVDPrice = ComBox26Items_DVD[1];
				}
				if (wcscmp(itemChosen, ComboBox49Items_NoDisks[0]) == 0)
				{
					userdata.Number_disks = L"-";
					userdata.DVDPrice = L"0.0";
				}
				break;
			case ID_SMPS:
				index = SendMessage(GetDlgItem(hDlg, ID_SMPS), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_SMPS), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_SMPS, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox9Items_SMPS[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_SMPS_WATTS, CB_RESETCONTENT, (WPARAM)0,(LPARAM)0);
					userdata.SMPS = ComboBox9Items_SMPS[index];
					for (int count = 0;ComboBox16Items_SMPSWatt[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_SMPS_WATTS, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox16Items_SMPSWatt[count]);
					}
					SendDlgItemMessage(hDlg, ID_SMPS_WATTS, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_SMPS_WATTS), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox9Items_SMPS[0]) == 0)
				{
					userdata.SMPS = L"-";
				}
				break;
			case ID_SMPS_WATTS:
				index = SendMessage(GetDlgItem(hDlg, ID_SMPS_WATTS), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_SMPS_WATTS), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_SMPS_WATTS, (LPWSTR)gStr, 50);
				if (wcscmp(itemChosen, ComboBox16Items_SMPSWatt[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_SMPS_CABLES, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

					userdata.SMPSWatt = ComboBox16Items_SMPSWatt[index];
					for (int count = 0;ComboBox37Items_SMPSCable[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_SMPS_CABLES, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox37Items_SMPSCable[count]);
					}
					SendDlgItemMessage(hDlg, ID_SMPS_CABLES, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_SMPS_CABLES), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox16Items_SMPSWatt[0]) == 0)
				{
					userdata.SMPSWatt = L"-";
				}
				break;
			case ID_SMPS_CABLES:
				index = SendMessage(GetDlgItem(hDlg, ID_SMPS_CABLES), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_SMPS_CABLES), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_SMPS_CABLES, (LPWSTR)gStr, 50);
				hwnd_SMPS = GetDlgItem(hDlg, ID_SMPS_PRICE);
				if (wcscmp(itemChosen, ComboBox37Items_SMPSCable[1]) == 0)
				{
					userdata.SMPSCables = ComboBox37Items_SMPSCable[1];
					for (int count = 0;ComBox27Items_SMPS[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_SMPS_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox27Items_SMPS[count]);
					}
					SendDlgItemMessage(hDlg, ID_SMPS_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_SMPS_PRICE), SW_SHOW);
					userdata.SMPSPrice = ComBox27Items_SMPS[0];
					GetDlgItemText(hDlg, ID_SMPS_PRICE, (LPWSTR)gStr, 50);
					EnableWindow(hwnd_SMPS, FALSE);
				}
				else if (wcscmp(itemChosen, ComboBox37Items_SMPSCable[2]) == 0)
				{
					userdata.SMPSCables = ComboBox37Items_SMPSCable[2];
					for (int count = 0;ComBox27Items_SMPS[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_SMPS_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox27Items_SMPS[count]);
					}
					SendDlgItemMessage(hDlg, ID_SMPS_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_SMPS_PRICE), SW_SHOW);
					userdata.SMPSPrice = ComBox27Items_SMPS[1];
					GetDlgItemText(hDlg, ID_SMPS_PRICE, (LPWSTR)gStr, 50);
					EnableWindow(hwnd_SMPS, FALSE);
				}
				if (wcscmp(itemChosen, ComboBox37Items_SMPSCable[0]) == 0)
				{
					userdata.SMPSCables = L"-";
					userdata.SMPSPrice = L"0.0";
				}
				break;

			case ID_CABINET:
				index = SendMessage(GetDlgItem(hDlg, ID_CABINET), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_CABINET), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_CABINET, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox10Items_Cabinet[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

					userdata.Cabinet = ComboBox10Items_Cabinet[1];
					for (int count = 0;ComboBox17Items_Cabinet[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CABINET_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox17Items_Cabinet[count]);
					}
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CABINET_TYPE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox10Items_Cabinet[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

					userdata.Cabinet = ComboBox10Items_Cabinet[2];
					for (int count = 0;ComboBox17Items_Cabinet[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CABINET_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox17Items_Cabinet[count]);
					}
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CABINET_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox10Items_Cabinet[0]) == 0)
				{
					userdata.Cabinet = L"-";
				}
				break;
			case ID_CABINET_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_CABINET_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_CABINET_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				if (wcscmp(itemChosen, ComboBox17Items_Cabinet[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE2, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

					userdata.CabinetType = ComboBox17Items_Cabinet[1];
					for (int count = 0;ComboBox38Items_CabinetPanel[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CABINET_TYPE2, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox38Items_CabinetPanel[count]);
					}
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE2, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CABINET_TYPE2), SW_SHOW);					
				}
				else if (wcscmp(itemChosen, ComboBox17Items_Cabinet[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE2, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

					userdata.CabinetType = ComboBox17Items_Cabinet[2];
					for (int count = 0;ComboBox38Items_CabinetPanel[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CABINET_TYPE2, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox38Items_CabinetPanel[count]);
					}
					SendDlgItemMessage(hDlg, ID_CABINET_TYPE2, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CABINET_TYPE2), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox17Items_Cabinet[0]) == 0)
				{
					userdata.CabinetType = L"-";
				}
				break;

			case ID_CABINET_TYPE2:
				index = SendMessage(GetDlgItem(hDlg, ID_CABINET_TYPE2), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_CABINET_TYPE2), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				hwnd_SMPS = GetDlgItem(hDlg, ID_CABINET_PRICE);
				if (wcscmp(itemChosen, ComboBox38Items_CabinetPanel[1]) == 0)
				{
					userdata.CabinetType2 = ComboBox38Items_CabinetPanel[1];
					for (int count = 0;ComBox28Items_Cabinet[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CABINET_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox28Items_Cabinet[count]);
					}
					SendDlgItemMessage(hDlg, ID_CABINET_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_CABINET_PRICE), SW_SHOW);
					userdata.CabinetPrice = ComBox28Items_Cabinet[1];
					EnableWindow(hwnd_SMPS, FALSE);
					GetDlgItemText(hDlg, ID_CABINET_PRICE, (LPWSTR)gStr, 50);
				}
				else if (wcscmp(itemChosen, ComboBox38Items_CabinetPanel[2]) == 0)
				{
					userdata.CabinetType2 = ComboBox38Items_CabinetPanel[2];
					for (int count = 0;ComBox28Items_Cabinet[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_CABINET_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox28Items_Cabinet[count]);
					}
					SendDlgItemMessage(hDlg, ID_CABINET_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_CABINET_PRICE), SW_SHOW);
					userdata.CabinetPrice = ComBox28Items_Cabinet[0];
					GetDlgItemText(hDlg, ID_CABINET_PRICE, (LPWSTR)gStr, 50);
					EnableWindow(hwnd_SMPS, FALSE);

				}
				if (wcscmp(itemChosen, ComboBox38Items_CabinetPanel[0]) == 0)
				{
					userdata.CabinetType2 = L"-";
					userdata.CabinetPrice = L"0.0";
				}
				break;
			case ID_KEYBOARD:
				index = SendMessage(GetDlgItem(hDlg, ID_KEYBOARD), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_KEYBOARD), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_KEYBOARD, (LPWSTR)gStr, 50);
				if (wcscmp(itemChosen, ComboBox11Items_Keyboard[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_KEYBOARD_COLOR, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.Keyboard = ComboBox11Items_Keyboard[1];
					for (int count = 0;ComboBox39Items_KeyboardColor[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_KEYBOARD_COLOR, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox39Items_KeyboardColor[count]);
					}
					SendDlgItemMessage(hDlg, ID_KEYBOARD_COLOR, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_COLOR), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox11Items_Keyboard[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_KEYBOARD_COLOR, CB_RESETCONTENT,(WPARAM)0,(LPARAM)0);
					userdata.Keyboard = ComboBox11Items_Keyboard[2];
					for (int count = 0;ComboBox39Items_KeyboardColor[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_KEYBOARD_COLOR, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox39Items_KeyboardColor[count]);
					}
					SendDlgItemMessage(hDlg, ID_KEYBOARD_COLOR, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_COLOR), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox11Items_Keyboard[0]) == 0)
				{
					userdata.Keyboard = L"-";
				}
				break;
			case ID_KEYBOARD_COLOR:
				index = SendMessage(GetDlgItem(hDlg, ID_KEYBOARD_COLOR), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_KEYBOARD_COLOR), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_KEYBOARD_TYPE, (LPWSTR)gStr, 50) ;

				if (wcscmp(itemChosen, ComboBox39Items_KeyboardColor[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_KEYBOARD_TYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.KeyboardColor = ComboBox39Items_KeyboardColor[1];
					for (int count = 0;ComboBox18Items_KeyboardType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_KEYBOARD_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox18Items_KeyboardType[count]);
					}
					SendDlgItemMessage(hDlg, ID_KEYBOARD_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_TYPE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox39Items_KeyboardColor[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_KEYBOARD_TYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.KeyboardColor = ComboBox39Items_KeyboardColor[2];
					for (int count = 0;ComboBox18Items_KeyboardType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_KEYBOARD_TYPE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox18Items_KeyboardType[count]);
					}
					SendDlgItemMessage(hDlg, ID_KEYBOARD_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox39Items_KeyboardColor[0]) == 0)
				{
					userdata.KeyboardColor = L"-";
				}
				break;
			case ID_KEYBOARD_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_KEYBOARD_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_KEYBOARD_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_KEYBOARD_TYPE, (LPWSTR)gStr, 50);
				hwnd_Keyboard = GetDlgItem(hDlg, ID_KEYBOARD_PRICE);
				if (wcscmp(itemChosen, ComboBox18Items_KeyboardType[1]) == 0)
				{
					userdata.KeyboardType = ComboBox18Items_KeyboardType[1];
					for (int count = 0;ComBox29Items_Keyboard[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_KEYBOARD_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox29Items_Keyboard[count]);
					}
					SendDlgItemMessage(hDlg, ID_KEYBOARD_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_PRICE), SW_SHOW);
					EnableWindow(hwnd_Keyboard,FALSE);
					userdata.KeyboardPrice = ComBox29Items_Keyboard[0];
				}
				else if (wcscmp(itemChosen, ComboBox18Items_KeyboardType[2]) == 0)
				{
					userdata.KeyboardType = ComboBox18Items_KeyboardType[2];
					for (int count = 0;ComBox29Items_Keyboard[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_KEYBOARD_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox29Items_Keyboard[count]);
					}
					SendDlgItemMessage(hDlg, ID_KEYBOARD_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_KEYBOARD_PRICE), SW_SHOW);
					userdata.KeyboardPrice = ComBox29Items_Keyboard[1];
					EnableWindow(hwnd_Keyboard, FALSE);
				}
				if (wcscmp(itemChosen, ComboBox18Items_KeyboardType[0]) == 0)
				{
					userdata.KeyboardType = L"-";
					userdata.KeyboardPrice = L"0.0";
				}
				break;
			case ID_MOUSE:
				index = SendMessage(GetDlgItem(hDlg, ID_MOUSE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MOUSE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MOUSE, (LPWSTR)gStr, 50);
				if (wcscmp(itemChosen, ComboBox12Items_Mouse[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MOUSE_COLOR, CB_RESETCONTENT, (WPARAM)0,(LPARAM)0);

					userdata.Mouse = ComboBox12Items_Mouse[index];
					for (int count = 0;ComboBox40Items_MouseColor[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOUSE_COLOR, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox40Items_MouseColor[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOUSE_COLOR, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOUSE_COLOR), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox12Items_Mouse[0]) == 0)
				{
					userdata.Mouse = L"-";
				}
				break;
			case ID_MOUSE_COLOR:
				index = SendMessage(GetDlgItem(hDlg, ID_MOUSE_COLOR), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MOUSE_COLOR), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MOUSE_TYPE, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox40Items_MouseColor[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MOUSE_TYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.MouseColor = ComboBox40Items_MouseColor[1];
					for (int count = 0;ComboBox19Items_MouseType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOUSE_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox19Items_MouseType[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOUSE_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOUSE_TYPE), SW_SHOW);
					//GetDlgItemText(hDlg, ID_MOUSE_PRICE, (LPWSTR)gStr, 50);
				}
				else if (wcscmp(itemChosen, ComboBox40Items_MouseColor[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MOUSE_TYPE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.MouseColor = ComboBox40Items_MouseColor[2];
					for (int count = 0;ComboBox19Items_MouseType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOUSE_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox19Items_MouseType[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOUSE_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOUSE_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox40Items_MouseColor[0]) == 0)
				{
					userdata.MouseColor = L"-";
				}
				break;
			case ID_MOUSE_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_MOUSE_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MOUSE_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MOUSE_TYPE, (LPWSTR)gStr, 50);
				hwnd_Mouse = GetDlgItem(hDlg, ID_MOUSE_PRICE);

				if (wcscmp(itemChosen, ComboBox19Items_MouseType[1]) == 0)
				{
					userdata.MouseType = ComboBox19Items_MouseType[1];
					for (int count = 0;ComBox30Items_Mouse[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOUSE_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox30Items_Mouse[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOUSE_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MOUSE_PRICE), SW_SHOW);
					GetDlgItemText(hDlg, ID_MOUSE_PRICE, (LPWSTR)gStr, 50);
					EnableWindow(hwnd_Mouse, FALSE);
					userdata.MousePrice = ComBox30Items_Mouse[0];
				}
				else if (wcscmp(itemChosen, ComboBox19Items_MouseType[2]) == 0)
				{
					userdata.MouseType = ComboBox19Items_MouseType[2];
					for (int count = 0;ComBox30Items_Mouse[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MOUSE_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox30Items_Mouse[count]);
					}
					SendDlgItemMessage(hDlg, ID_MOUSE_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_MOUSE_PRICE), SW_SHOW);
					GetDlgItemText(hDlg, ID_MOUSE_PRICE, (LPWSTR)gStr, 50);
					userdata.MousePrice = ComBox30Items_Mouse[1];
					EnableWindow(hwnd_Mouse, FALSE);

				}
				if (wcscmp(itemChosen, ComboBox19Items_MouseType[0]) == 0)
				{
					userdata.MouseType = L"-";
					userdata.MousePrice = L"0.0";
				}
				break;

			case ID_MONITOR:				
				index = SendMessage(GetDlgItem(hDlg, ID_MONITOR), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MONITOR), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MONITOR, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox41Items_Monitor[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MONITOR_TYPE, CB_RESETCONTENT,(WPARAM)0,(LPARAM)0);
					userdata.Monitor = ComboBox41Items_Monitor[index];
					for (int count = 0;ComboBox42Items_MonitorType[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MONITOR_TYPE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox42Items_MonitorType[count]);
					}
					SendDlgItemMessage(hDlg, ID_MONITOR_TYPE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MONITOR_TYPE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox41Items_Monitor[0]) == 0)
				{
					userdata.Monitor = L"-";
				}
				break;
			case ID_MONITOR_TYPE:
				index = SendMessage(GetDlgItem(hDlg, ID_MONITOR_TYPE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MONITOR_TYPE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MONITOR_TYPE, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox42Items_MonitorType[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MONITOR_SIZE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);
					userdata.MonitorType = ComboBox42Items_MonitorType[1];
					for (int count = 0;ComboBox43Items_MonitorSize[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MONITOR_SIZE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox43Items_MonitorSize[count]);
					}
					SendDlgItemMessage(hDlg, ID_MONITOR_SIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MONITOR_SIZE), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox42Items_MonitorType[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_MONITOR_SIZE, CB_RESETCONTENT,(WPARAM)0, (LPARAM)0);

					userdata.MonitorType = ComboBox42Items_MonitorType[2];
					for (int count = 0;ComboBox43Items_MonitorSize[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MONITOR_SIZE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComboBox43Items_MonitorSize[count]);
					}
					SendDlgItemMessage(hDlg, ID_MONITOR_SIZE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MONITOR_SIZE), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox42Items_MonitorType[0]) == 0)
				{
					userdata.MonitorType = L"-";
				}
				break;
			case ID_MONITOR_SIZE:
				index = SendMessage(GetDlgItem(hDlg, ID_MONITOR_SIZE), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_MONITOR_SIZE), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_MONITOR_SIZE, (LPWSTR)gStr, 50);
				hwnd_Monitor = GetDlgItem(hDlg, ID_MONITOR_PRICE);
				if (wcscmp(itemChosen, ComboBox43Items_MonitorSize[1]) == 0)
				{
					userdata.MonitorSize = ComboBox43Items_MonitorSize[1];
					for (int count = 0;ComBox44Items_Monitor[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MONITOR_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComBox44Items_Monitor[count]);
					}
					SendDlgItemMessage(hDlg, ID_MONITOR_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_MONITOR_PRICE), SW_SHOW);
					userdata.MonitorPrice = ComBox44Items_Monitor[0];
					EnableWindow(hwnd_Monitor,FALSE);
					GetDlgItemText(hDlg, ID_MONITOR_PRICE, (LPWSTR)gStr, 50);
				}
				else if (wcscmp(itemChosen, ComboBox43Items_MonitorSize[2]) == 0)
				{
					userdata.MonitorSize = ComboBox43Items_MonitorSize[2];
					for (int count = 0;ComBox44Items_Monitor[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_MONITOR_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)ComBox44Items_Monitor[count]);
					}
					SendDlgItemMessage(hDlg, ID_MONITOR_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_MONITOR_PRICE), SW_SHOW);
					userdata.MonitorPrice = ComBox44Items_Monitor[1];
					EnableWindow(hwnd_Monitor, FALSE);
					GetDlgItemText(hDlg, ID_MONITOR_PRICE, (LPWSTR)gStr, 50);
				}
				if (wcscmp(itemChosen, ComboBox43Items_MonitorSize[0]) == 0)
				{
					userdata.MonitorSize = L"-";
					userdata.MonitorPrice = L"0.0";
				}
				break;
			case ID_PRINTER:
				index = SendMessage(GetDlgItem(hDlg, ID_PRINTER), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_PRINTER), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_PRINTER, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox45Items_Printer[index]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_PRINTER_COLOR, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.Printer = ComboBox45Items_Printer[index];
					for (int count = 0;ComboBox46Items_PrinterColor[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRINTER_COLOR, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox46Items_PrinterColor[count]);
					}
					SendDlgItemMessage(hDlg, ID_PRINTER_COLOR, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_PRINTER_COLOR), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox45Items_Printer[0]) == 0)
				{
					userdata.Printer = L"-";
				}
				break;
			case ID_PRINTER_COLOR:
				index = SendMessage(GetDlgItem(hDlg, ID_PRINTER_COLOR), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_PRINTER_COLOR), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_PRINTER_COLOR, (LPWSTR)gStr, 50);

				if (wcscmp(itemChosen, ComboBox46Items_PrinterColor[1]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_PRINTER_OUTPUT, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					userdata.PrinterColor = ComboBox46Items_PrinterColor[1];
					for (int count = 0;ComboBox47Items_PrinterOutput[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRINTER_OUTPUT, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox47Items_PrinterOutput[count]);
					}
					SendDlgItemMessage(hDlg, ID_PRINTER_OUTPUT, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_PRINTER_OUTPUT), SW_SHOW);
				}
				else if (wcscmp(itemChosen, ComboBox46Items_PrinterColor[2]) == 0)
				{
					SendDlgItemMessage(hDlg, ID_PRINTER_OUTPUT, CB_RESETCONTENT,(WPARAM)0,(LPARAM)0);
					userdata.PrinterColor = ComboBox46Items_PrinterColor[2];
					for (int count = 0;ComboBox47Items_PrinterOutput[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRINTER_OUTPUT, CB_ADDSTRING, (WPARAM)0, (LPARAM)ComboBox47Items_PrinterOutput[count]);
					}
					SendDlgItemMessage(hDlg, ID_PRINTER_OUTPUT, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_PRINTER_OUTPUT), SW_SHOW);
				}
				if (wcscmp(itemChosen, ComboBox46Items_PrinterColor[0]) == 0)
				{
					userdata.PrinterColor = L"-";
				}
				break;
			case ID_PRINTER_OUTPUT:
				index = SendMessage(GetDlgItem(hDlg, ID_PRINTER_OUTPUT), CB_GETCURSEL, 0, 0);
				(TCHAR*)SendMessage(GetDlgItem(hDlg, ID_PRINTER_OUTPUT), CB_GETLBTEXT, index, (LPARAM)itemChosen);
				GetDlgItemText(hDlg, ID_PRINTER_COLOR, (LPWSTR)gStr, 50);
				hwnd_Printer = GetDlgItem(hDlg, ID_PRINTER_PRICE);
				if (wcscmp(itemChosen, ComboBox47Items_PrinterOutput[1]) == 0)
				{
					userdata.PrinterOutput = ComboBox47Items_PrinterOutput[1];
					for (int count = 0;Combo48PrinterPrice[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRINTER_PRICE, CB_ADDSTRING,(WPARAM)0, (LPARAM)Combo48PrinterPrice[count]);
					}
					SendDlgItemMessage(hDlg, ID_PRINTER_PRICE, CB_SETCURSEL, 0, 0);
					ShowWindow(GetDlgItem(hDlg, ID_PRINTER_PRICE), SW_SHOW);
					EnableWindow(hwnd_Printer,FALSE);
					GetDlgItemText(hDlg, ID_PRINTER_PRICE, (LPWSTR)gStr, 50);
					userdata.PrinterPrice = Combo48PrinterPrice[0];
				}
				else if (wcscmp(itemChosen, ComboBox47Items_PrinterOutput[2]) == 0)
				{
					userdata.PrinterOutput = ComboBox47Items_PrinterOutput[2];
					for (int count = 0;Combo48PrinterPrice[count] != 0;count++)
					{
						SendDlgItemMessage(hDlg, ID_PRINTER_PRICE, CB_ADDSTRING, (WPARAM)0, (LPARAM)Combo48PrinterPrice[count]);
					}
					SendDlgItemMessage(hDlg, ID_PRINTER_PRICE, CB_SETCURSEL, 1, 1);
					ShowWindow(GetDlgItem(hDlg, ID_PRINTER_PRICE), SW_SHOW);
					EnableWindow(hwnd_Printer, FALSE);
					GetDlgItemText(hDlg, ID_PRINTER_PRICE, (LPWSTR)gStr, 50);
					userdata.PrinterPrice = Combo48PrinterPrice[1];

				}
				if (wcscmp(itemChosen, ComboBox47Items_PrinterOutput[0]) == 0)
				{
					userdata.PrinterOutput = L"-";
					userdata.PrinterPrice = L"0.0";
				}
				break;
			}
			break;		
		}
	}
	return(FALSE);

}	//End of Dialog Procedure



LRESULT CALLBACK WndProc(HWND hwnd,
	UINT iMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	HINSTANCE hInst=NULL;
	HINSTANCE hInst2 = NULL;					//For Receipt
	BOOL CALLBACK DlgProcTwo(HWND, UINT, WPARAM, LPARAM);
	BOOL CALLBACK DlgProcThree(HWND, UINT, WPARAM, LPARAM);
	switch (iMsg)
	{

		bool paintMainWindow(void);

	case WM_CREATE:
		g_hbmBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_SPLASHID));
		if (g_hbmBall == NULL)
		{
			MessageBox(NULL,TEXT("Could Not load Bitmap"),TEXT("ERROR"),MB_OK);
		}

		break;
	
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_SPACE:
			hInst = (HINSTANCE)GetWindowLong(ghwnd,-6);
			DialogBox(hInst, TEXT("DATAENTRY"), ghwnd, (DLGPROC)MyDlgProc);
		break;

		case VK_ESCAPE:
//			DestroyWindow(ghwnd);
			hInst3 = (HINSTANCE)GetWindowLong(ghwnd, GWLP_HINSTANCE);
			DialogBox(hInst3, TEXT("ThankYou"), ghwnd, (DLGPROC)DlgProcThree);
			break;

		case 'P':
		case 'p':
			if (flag == 0)
			{
				hInst2 = (HINSTANCE)GetWindowLong(ghwnd, GWL_HINSTANCE);
				DialogBox(hInst2, TEXT("RECEIPT"), ghwnd, (DLGPROC)DlgProcTwo);
			}
			flag = 1;
			break;
		}
	break;
		
	case WM_PAINT:
		paintMainWindow();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

bool paintMainWindow()
{
	HDC hdcInst, hdcBitmap;
	PAINTSTRUCT ps;
	BITMAP bmp;
	RECT rc;
	HBRUSH hBrush;
	HPEN hPen;
	HBITMAP  hBitmapOld;


	hdcInst = BeginPaint(ghwnd, &ps);
	if (splashScreenActive)
	{
		hInst = (HINSTANCE)GetWindowLong(ghwnd, GWLP_HINSTANCE);
		hdcBitmap = CreateCompatibleDC(hdcInst);
		 hBitmapOld = (HBITMAP)SelectObject(hdcBitmap,g_hbmBall);
		 GetClientRect(ghwnd, &rc);
		 GetObject(g_hbmBall, sizeof(bmp), &bmp);
		 BitBlt(hdcInst,0,0,bmp.bmWidth,bmp.bmHeight,hdcBitmap,0,0,SRCCOPY);
		 StretchBlt(hdcInst, rc.left, rc.right, rc.right - rc.left, rc.bottom - rc.top, hdcInst, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		//Select here new bitmap
		SelectObject(hdcBitmap, hBitmapOld);
		///Title to be Displayed on main page
		SelectObject(hdcInst, CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman")));
		SetTextColor(hdcInst, RGB(255, 255, 255));
		SetBkColor(hdcInst, TRANSPARENT);
		SetBkMode(hdcInst, TRANSPARENT);
		TextOut(hdcInst, 100, 600, userdata.HitMsg,wcslen(userdata.HitMsg));
		TextOut(hdcInst, 550, 20, userdata.Astromedicomp, wcslen(userdata.Astromedicomp));
		TextOut(hdcInst, 100, 200, userdata.Name, wcslen(userdata.Name));
		TextOut(hdcInst, 100, 240, userdata.Batch, wcslen(userdata.Batch));
		
		//cleanup
		DeleteDC(hdcBitmap);

	}
	else
	{
		GetClientRect(ghwnd, &rc);
		hBrush = CreateSolidBrush((COLORREF)RGB(0, 0, 0));
		FillRect(hdcInst, &ps.rcPaint, hBrush);
		hPen = CreatePen(PS_SOLID, 3, (COLORREF)RGB(255, 255, 0));
		SelectObject(hdcInst, hPen);

		//Tile Selection
		MoveToEx(hdcInst, 0,ps.rcPaint.top + 0x50,NULL);
		LineTo(hdcInst, ps.rcPaint.right, ps.rcPaint.top + 0x50);
		MoveToEx(hdcInst, 0, ps.rcPaint.top + 0x75, NULL);
		LineTo(hdcInst, ps.rcPaint.right, ps.rcPaint.top + 0x75);
	
		//total selection
		MoveToEx(hdcInst, 0, ps.rcPaint.top + 0x200, NULL);
		LineTo(hdcInst, ps.rcPaint.right, ps.rcPaint.top + 0x200);
	
		//COLUMN 1 DEVICE
		MoveToEx(hdcInst, ps.rcPaint.top+ 230,ps.rcPaint.top + 0x50,NULL);
		LineTo(hdcInst, ps.rcPaint.top + 230,ps.rcPaint.top + 0x200);

		//COLUMN 2 TYPE
		MoveToEx(hdcInst, ps.rcPaint.top + 540, ps.rcPaint.top + 0x50, NULL);
		LineTo(hdcInst, ps.rcPaint.top + 540, ps.rcPaint.top + 0x200);

		////COLUMN 3 SUBTYPE
		MoveToEx(hdcInst, ps.rcPaint.top + 920, ps.rcPaint.top + 0x50, NULL);
		LineTo(hdcInst, ps.rcPaint.top + 920, ps.rcPaint.top + 0x200);

		////COLUMN 4 SIZE
		MoveToEx(hdcInst, ps.rcPaint.top + 780, ps.rcPaint.top + 0x50, NULL);
		LineTo(hdcInst, ps.rcPaint.top + 780, ps.rcPaint.top + 0x200);

			//Tile on material page
		SelectObject(hdcInst, CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Cambria")));
		SetTextColor(hdcInst, RGB(0, 255, 100));
		SetBkColor(hdcInst, TRANSPARENT);
		SetBkMode(hdcInst, TRANSPARENT);

		 //Add columns
		TextOut(hdcInst, ps.rcPaint.top +  50 , ps.rcPaint.top + 91, Headings[0], wcslen(Headings[0]));
		TextOut(hdcInst, ps.rcPaint.top + 250, ps.rcPaint.top + 0x5b, Headings[1], wcslen(Headings[1]));
		TextOut(hdcInst, ps.rcPaint.top + 580, ps.rcPaint.top + 0x5b, Headings[2], wcslen(Headings[2]));
		TextOut(hdcInst, ps.rcPaint.top + 830, ps.rcPaint.top + 0x5b, Headings[3], wcslen(Headings[3]));
		TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 0x5b, Headings[4], wcslen(Headings[4]));
		
	
		//RAM SELECTED
		if (userdata.RAMSelected != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 0x80, userdata.RAMSelected, wcslen(userdata.RAMSelected));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 0x80, TEXT("-"), 1);
		
		//RAM SUBTYPE
		if (userdata.RAM_Subtype != NULL)
			//GetDlgItemText(hHDlg, ID_SUBTYPE_RAM, str, 50);
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 0x80, userdata.RAM_Subtype, wcslen(userdata.RAM_Subtype));
		else		
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 0x80, TEXT("-"), 1);
		
			TextOut(hdcInst, ps.rcPaint.top + 630, ps.rcPaint.top + 0x80, TEXT("-"), 1);

		//RAM PRICE
		if (userdata.RAM_Core != NULL)
		{
			TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 0x80, userdata.RAM_Core, wcslen(userdata.RAM_Core));
		}
		else
			TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 0x80, TEXT("-"), 1);

		if(userdata.RAM_Price!= NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 0x80, userdata.RAM_Price, wcslen(userdata.RAM_Price));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 0x80, TEXT("-"), 1);
		
		//MOTHERBOARD
		if(userdata.Motherboard_nm != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 150, userdata.Motherboard_nm, wcslen(userdata.Motherboard_nm));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 150, TEXT("-"), 1);

		if(userdata.Motherboard_type != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 150, userdata.Motherboard_type, wcslen(userdata.Motherboard_type));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 150, TEXT("-"), 1);

		//Motherboard Type2
		if(userdata.Motherboard_type2 != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 150, userdata.Motherboard_type2, wcslen(userdata.Motherboard_type2));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 150, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 150, TEXT("-"), 1);


		if(userdata.MotherboardPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 150, userdata.MotherboardPrice, wcslen(userdata.MotherboardPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 150, TEXT("-"), 1);

		//GRAPHICS CARD
		if(userdata.GraphicsCardnm != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 172, userdata.GraphicsCardnm, wcslen(userdata.GraphicsCardnm));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 172, TEXT("-"), 1);

		if(userdata.GraphicsCardType != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 172, userdata.GraphicsCardType, wcslen(userdata.GraphicsCardType));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 172, TEXT("-"), 1);

		//graphics card size
		TextOut(hdcInst, ps.rcPaint.top + 630, ps.rcPaint.top + 172, TEXT("-"), 1);

		if (userdata.GraphicsCardSize != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 172, userdata.GraphicsCardSize, wcslen(userdata.GraphicsCardSize));
		else
			TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 172, TEXT("-"), 1);

		if(userdata.GraphicsCardPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 172, userdata.GraphicsCardPrice, wcslen(userdata.GraphicsCardPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 172, TEXT("-"), 1);
					
		//CPU
		if(userdata.Cpu_nm != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 194, userdata.Cpu_nm, wcslen(userdata.Cpu_nm));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 194, TEXT("-"), 1);

		if(userdata.CPUType2 != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 194, userdata.CPUType2, wcslen(userdata.CPUType2));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 194, TEXT("-"), 1);

		if(userdata.CPUCore != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 194, userdata.CPUCore, wcslen(userdata.CPUCore));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 194, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 194, TEXT("-"), 1);

		if(userdata.CpuPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 194, userdata.CpuPrice, wcslen(userdata.CpuPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 194, TEXT("-"), 1);

		//HARDDISK
		if(userdata.HardDisknm != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 216, userdata.HardDisknm, wcslen(userdata.HardDisknm));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 216, TEXT("-"), 1);

		//harddisk type
		if(userdata.HardDiskType != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 216, userdata.HardDisknm, wcslen(userdata.HardDiskType));
		else 
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 216, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 630, ps.rcPaint.top + 216, TEXT("-"), 1);

		if (userdata.HardDiskSize != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 216, userdata.HardDiskSize, wcslen(userdata.HardDiskSize));
		else
			TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 216, TEXT("-"), 1);

		if (userdata.HardDiskPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 216, userdata.HardDiskPrice, wcslen(userdata.HardDiskPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 216, TEXT("-"), 1);

		//CD/DVD
		if(userdata.DVD != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 238, userdata.DVD, wcslen(userdata.DVD));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 238, TEXT("-"), 1);

		if(userdata.DVD_Type != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 238, userdata.DVD_Type, wcslen(userdata.DVD_Type));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 238, TEXT("-"), 1);

		if (userdata.Number_disks != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 238, userdata.Number_disks, wcslen(userdata.Number_disks));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 238, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 238, TEXT("-"), 1);

		if(userdata.DVDPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 238, userdata.DVDPrice, wcslen(userdata.DVDPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 238, TEXT("-"), 1);

		//SMPS
		if(userdata.SMPS != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 260, userdata.SMPS, wcslen(userdata.SMPS));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 260, TEXT("-"), 1);

		if(userdata.SMPSWatt != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 260, userdata.SMPSWatt, wcslen(userdata.SMPSWatt));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 260, TEXT("-"), 1);

		if(userdata.SMPSCables != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 260, userdata.SMPSCables, wcslen(userdata.SMPSCables));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 260, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 260, TEXT("-"), 1);

		if(userdata.SMPSPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 260, userdata.SMPSPrice, wcslen(userdata.SMPSPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 260, TEXT("-"), 1);
		
		//CABINET
		if(userdata.Cabinet != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 282, userdata.Cabinet, wcslen(userdata.Cabinet));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 282, TEXT("-"), 1);

		if(userdata.CabinetType != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 282, userdata.CabinetType, wcslen(userdata.CabinetType));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 282, TEXT("-"), 1);

		if(userdata.CabinetType2 != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 282, userdata.CabinetType2, wcslen(userdata.CabinetType2));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 282, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 282, TEXT("-"), 1);

		if(userdata.CabinetPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 282, userdata.CabinetPrice, wcslen(userdata.CabinetPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 282, TEXT("-"), 1);
		
		//KEYBOARD
		if(userdata.Keyboard != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 304, userdata.Keyboard, wcslen(userdata.Keyboard));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 304, TEXT("-"), 1);

		if(userdata.KeyboardColor != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 304, userdata.KeyboardColor, wcslen(userdata.KeyboardColor));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 304, TEXT("-"), 1);

		if (userdata.KeyboardType != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 304, userdata.KeyboardType, wcslen(userdata.KeyboardType));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 304, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 304, TEXT("-"), 1);

		if(userdata.KeyboardPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 304, userdata.KeyboardPrice, wcslen(userdata.KeyboardPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 304, TEXT("-"), 1);

		//MOUSE
		if (userdata.Mouse != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 326, userdata.Mouse, wcslen(userdata.Mouse));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 326, TEXT("-"), 1);

		if(userdata.MouseType != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 326, userdata.MouseType, wcslen(userdata.MouseType));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 326, TEXT("-"), 1);

		if(userdata.MouseColor!= NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 326, userdata.MouseColor, wcslen(userdata.MouseColor));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 326, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 326, TEXT("-"), 1);

		if(userdata.MousePrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 326, userdata.MousePrice, wcslen(userdata.MousePrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 326, TEXT("-"), 1);

		//MONITOR
		if(userdata.Monitor != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 348, userdata.Monitor, wcslen(userdata.Monitor));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 348, TEXT("-"), 1);

		if(userdata.MonitorType!= NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 348, userdata.MonitorType, wcslen(userdata.MonitorType));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 348, TEXT("-"), 1);

		if(userdata.MonitorSize!= NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 348, userdata.MonitorSize, wcslen(userdata.MonitorSize));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 348, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 348, TEXT("-"), 1);

		if(userdata.MonitorPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 348, userdata.MonitorPrice, wcslen(userdata.MonitorPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 348, TEXT("-"), 1);

		//PRINTER
		if (userdata.Printer != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 366, userdata.Printer, wcslen(userdata.Printer));
		else
			TextOut(hdcInst, ps.rcPaint.top + 85, ps.rcPaint.top + 366, TEXT("-"), 1);

		if (userdata.PrinterColor != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 366, userdata.PrinterColor, wcslen(userdata.PrinterColor));
		else
			TextOut(hdcInst, ps.rcPaint.top + 300, ps.rcPaint.top + 366, TEXT("-"), 1);

		if (userdata.PrinterOutput != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 366, userdata.PrinterOutput, wcslen(userdata.PrinterOutput));
		else
			TextOut(hdcInst, ps.rcPaint.top + 620, ps.rcPaint.top + 366, TEXT("-"), 1);

		TextOut(hdcInst, ps.rcPaint.top + 850, ps.rcPaint.top + 366, TEXT("-"), 1);

		if (userdata.PrinterPrice != NULL)
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 366, userdata.PrinterPrice, wcslen(userdata.PrinterPrice));
		else
			TextOut(hdcInst, ps.rcPaint.top + 1020, ps.rcPaint.top + 366, TEXT("-"), 1);
		swprintf(p,100,TEXT("%.2f"), Total);

		TextOut(hdcInst, ps.rcPaint.top + 1000, ps.rcPaint.top + 550, (LPWSTR)p, wcslen(p));
		TextOut(hdcInst, ps.rcPaint.top + 920, ps.rcPaint.top + 550, userdata.Total, wcslen(userdata.Total));
		TextOut(hdcInst, ps.rcPaint.top + 600, ps.rcPaint.top + 550, userdata.PrntMsg, wcslen(userdata.PrntMsg));
		flag = 0;
	}

	EndPaint(ghwnd, &ps);
	return 0;
	
}

BOOL CALLBACK DlgProcThree(HWND hDlg2, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
//	TextOut(hdcInst, ps.rcPaint.top + 70, ps.rcPaint.top + 70, userdata.ThankMsg, wcslen(userdata.ThankMsg));
//	MessageBox(NULL, TEXT("Inside DLG3"), TEXT("Msg"), MB_OK);

	switch (iMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OK3:
			DestroyWindow(ghwnd);
			break;
		}
	}
	return(FALSE);
}

BOOL CALLBACK DlgProcTwo(HWND hDlg1, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		TCHAR str[50];
		CreateMyFile(str);             
	case WM_INITDIALOG:
		return(TRUE);
		break;
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			//			DestroyWindow(ghwnd);
			hInst3 = (HINSTANCE)GetWindowLong(ghwnd, GWLP_HINSTANCE);
			DialogBox(hInst3, TEXT("ThankYou"), ghwnd, (DLGPROC)DlgProcThree);
			break;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{ 
		case ID_CANCEL1:
			EndDialog(hDlg1, 0);

			break;
		case ID_OK1:
			GetDlgItemText(hDlg1, ID_ETNAME, str, 50);
		/*	swprintf(fileBuffer, 200, TEXT("\n%-30s\t\t %-30s \t %-30s \t%-30s"), userdata.RAMSelected, userdata.RAM_Subtype, userdata.RAM_Core, userdata.RAM_Price);
			swprintf(fileBuffer2, 200, TEXT("\n%-30s \t\t%-30s \t\t %-30s \t%-30s"), userdata.Motherboard_nm, userdata.Motherboard_type, userdata.Motherboard_type2, userdata.MotherboardPrice);
			swprintf(fileBuffer3, 200, TEXT("\n%-30s %30s \t\t %-20s \t\t%-30s"), userdata.GraphicsCardnm, userdata.GraphicsCardType, userdata.GraphicsCardSize, userdata.GraphicsCardPrice);
			swprintf(fileBuffer4, 200, TEXT("\n%-30s %30s \t\t %-20s \t\t%-30s"), userdata.Cpu_nm, userdata.CPUType2, userdata.CPUCore, userdata.CpuPrice);
			swprintf(fileBuffer5, 200, TEXT("\n%-30s %30s \t\t %-30s \t%-30s"), userdata.HardDisknm, userdata.HardDiskType, userdata.HardDiskSize, userdata.HardDiskPrice);
			swprintf(fileBuffer6, 200, TEXT("\n%-30s %30s \t\t %-30s \t\t%-30s"), userdata.DVD, userdata.DVD_Type, userdata.Number_disks, userdata.DVDPrice);
			swprintf(fileBuffer7, 200, TEXT("\n%-30s %30s \t\t %-30s \t%-30s"), userdata.SMPS, userdata.SMPSWatt, userdata.SMPSCables, userdata.SMPSPrice);
			swprintf(fileBuffer8, 200, TEXT("\n%-30s %30s \t\t\t %-30s \t\t%-30s"), userdata.Cabinet, userdata.CabinetType, userdata.CabinetType2, userdata.CabinetPrice);
			swprintf(fileBuffer9, 200, TEXT("\n%-30s %30s \t\t %-30s \t%-30s"), userdata.Keyboard, userdata.KeyboardType, userdata.KeyboardColor, userdata.KeyboardPrice);
			swprintf(fileBuffer10, 200, TEXT("\n%-30s %30s \t\t %-30s \t%-30s"), userdata.Mouse, userdata.MouseType, userdata.MouseColor, userdata.MousePrice);
			swprintf(fileBuffer11, 200, TEXT("\n%-30s %30s \t\t\t %-30s \t%-30s"), userdata.Monitor, userdata.MonitorType, userdata.MonitorSize, userdata.MonitorPrice);
			swprintf(fileBuffer12, 200, TEXT("\n%-30s %30s \t\t %-30s \t%-30s"), userdata.Printer, userdata.PrinterColor, userdata.PrinterOutput, userdata.PrinterPrice);
*/

			swprintf(fileBuffer, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.RAMSelected, userdata.RAM_Subtype, userdata.RAM_Core, userdata.RAM_Price);
			swprintf(fileBuffer2, 200, TEXT("\n%-30s %30s \t\t%-30s %-30s"), userdata.Motherboard_nm, userdata.Motherboard_type, userdata.Motherboard_type2, userdata.MotherboardPrice);
			swprintf(fileBuffer3, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.GraphicsCardnm, userdata.GraphicsCardType, userdata.GraphicsCardSize, userdata.GraphicsCardPrice);
			swprintf(fileBuffer4, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.Cpu_nm, userdata.CPUType2, userdata.CPUCore, userdata.CpuPrice);
			swprintf(fileBuffer5, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.HardDisknm, userdata.HardDiskType, userdata.HardDiskSize, userdata.HardDiskPrice);
			swprintf(fileBuffer6, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.DVD, userdata.DVD_Type, userdata.Number_disks, userdata.DVDPrice);
			swprintf(fileBuffer7, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.SMPS, userdata.SMPSWatt, userdata.SMPSCables, userdata.SMPSPrice);
			swprintf(fileBuffer8, 200, TEXT("\n%-30s %30s \t\t%-30s %-30s"), userdata.Cabinet, userdata.CabinetType, userdata.CabinetType2, userdata.CabinetPrice);
			swprintf(fileBuffer9, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.Keyboard, userdata.KeyboardType, userdata.KeyboardColor, userdata.KeyboardPrice);
			swprintf(fileBuffer10, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.Mouse, userdata.MouseType, userdata.MouseColor, userdata.MousePrice);
			swprintf(fileBuffer11, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.Monitor, userdata.MonitorType, userdata.MonitorSize, userdata.MonitorPrice);
			swprintf(fileBuffer12, 200, TEXT("\n%-30s %30s \t%-30s %-30s"), userdata.Printer, userdata.PrinterColor, userdata.PrinterOutput, userdata.PrinterPrice);

			wofstream myFile;
			
			myFile.open(str);
			myFile << fileBuffer;
			myFile << fileBuffer2;
			myFile << fileBuffer3;
			myFile << fileBuffer4;
			myFile << fileBuffer5;
			myFile << fileBuffer6;
			myFile << fileBuffer7;
			myFile << fileBuffer8;
			myFile << fileBuffer9;
			myFile << fileBuffer10;
			myFile << fileBuffer11;
			myFile << fileBuffer12;

			myFile << "\nTotal:\t" << Total;

			myFile.close();
			if (flag == 0)
			{
				userdata.PrntMsg = L"Thank you visit again!!";
				TextOut(hdcInst, ps.rcPaint.top + 600, ps.rcPaint.top + 550, userdata.PrntMsg, wcslen(userdata.PrntMsg));

			}
			EndDialog(hDlg1, 0);
			break;
		}

		return(TRUE);
		break;
	}

	return(FALSE);
}


void CreateMyFile(TCHAR filename[])
{
	hFile = CreateFile(filename, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile)
	{
		MessageBox(NULL,
			TEXT("Created"),
			TEXT("Data"),
			MB_OK);
	}

}

