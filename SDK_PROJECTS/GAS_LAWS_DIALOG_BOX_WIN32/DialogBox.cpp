#include <Windows.h>
#include<stdio.h>
#include"myDialog.h"
//Prototype of WndProc() declared Globally

#define R_CONST  8.3144598
#define FULLSCREEN WM_USER+0x0c

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int numgasmols;
HBITMAP g_hbmBall = NULL,hBitmap = NULL;
HWND ghwnd,ghdlg;
HINSTANCE hInst = NULL;


//For boyles Law
wchar_t w_numGasB[255] = L"0.000000";
wchar_t w_incdecB[255] = L"0.000000";
wchar_t w_tempB[255] = L"0.000000";
wchar_t w_pressrB[255] =L"1.000000";
wchar_t w_volB[255] = L"0.000000";

double numgasB = 0.0f, incdecB = 0.0f, pressrB = 0.0f, tempB = 0.0f,volB=0.0f;


//For charles Law
wchar_t w_numGasC[255] = L"0.000000";
wchar_t w_incdecC[255] = L"0.000000";
wchar_t w_tempC[255]=L"0.000000";
wchar_t w_pressrC[255] = L"0.000000";
wchar_t w_volC[255] = L"1.000000";
double numgasC = 0.0f, incdecC = 0.0f, pressrC = 0.0f, tempC = 0.0f, volC = 0.0f;


BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

FILE *gpFile = NULL;
FILE *gpFile2 = NULL;

struct INPUT2
{
	char name[50], address[50];
	int age, mstatus;
	float sal;
} in;
//main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("SDK Window");
	void uninitialize();

	fopen_s(&gpFile, "LogFile.txt", "w");
	if (gpFile == NULL)
	{
		printf("Error opening file\n");
		exit(0);
	}

	fopen_s(&gpFile2, "Bolyes Law State-2 - Log.txt", "w");
	if (gpFile2 == NULL)
	{
		printf("Error opening file\n");
	}
	//code
	//initializing member of WNDCLASS
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Registering Class
	RegisterClassEx(&wndclass);

	//CreateWindow
	hwnd = CreateWindow(
		szClassName,
		TEXT("Sucheta Splash Screen Window"),
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
		);


	//intitialize()

	ghwnd = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	uninitialize();
	return((int)msg.wParam);

}





BOOL CALLBACK MyDialogProc(HWND hDlg, UINT DlgiMsg, WPARAM DlgwParam, LPARAM DlglParam)
{
	HWND rbHwnd,rbHwnd2;
	int valB = 0;
	ghdlg = hDlg;

	static int boylesLawSelected = 0;
	static int charlesLawSelected = 0;
	static double resPressure = 0.0f;
	static double resVol = 0.0f;


	wchar_t szstr[255];
	HWND hIncDecB= NULL,hPressure= NULL,hVol= NULL,hTempB = NULL;
	HWND hIncDecC= NULL, hPressureC= NULL, hVolC = NULL, hTempC=NULL;

	
	switch (DlgiMsg)
	{

		
	case WM_INITDIALOG:


		rbHwnd = GetDlgItem(hDlg, RB_BOYLES);
		SendDlgItemMessage(hDlg, RB_BOYLES, BM_SETCHECK, 1, 0);					
					rbHwnd = GetDlgItem(hDlg, ID_GROUPBOX2);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_NUMGASMOLESC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_TEMPC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_INCDECC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_VOLUMEC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_TPLUSC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_TMINUSC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_VPLUSC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_VMINUSC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_PRESSUREC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_PLUSC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_MINUSC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_TEMPC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_FILEC);
					EnableWindow(rbHwnd, FALSE);
					rbHwnd = GetDlgItem(hDlg, ID_RESETC);
					EnableWindow(rbHwnd, FALSE);



					rbHwnd = GetDlgItem(hDlg, ID_GROUPBOX1);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_NUMGASMOLESB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_INCDECB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_TEMPB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_PRESSUREB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_PRESSUREPLUSB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_PLUSC);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_PRESSUREMINUSB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_VOLUMEB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_VPLUSB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_VMINUSB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_FILEB);
					EnableWindow(rbHwnd, TRUE);
					rbHwnd = GetDlgItem(hDlg, ID_RESETB);
					EnableWindow(rbHwnd, TRUE);
					

		break;

	case WM_COMMAND:
		rbHwnd = GetDlgItem(hDlg, RB_BOYLES);
		rbHwnd2 = GetDlgItem(hDlg, RB_CHARLES);
		boylesLawSelected = SendMessage(rbHwnd, BM_GETCHECK, 0, 0);
		charlesLawSelected = SendMessage(rbHwnd2, BM_GETCHECK, 0, 0);


		if (boylesLawSelected > 0)
		{
			switch (LOWORD(DlgwParam))
			{

			
			case VK_ESCAPE:
				EndDialog(hDlg, FALSE);
				return FALSE;
				break;

			case 2:
				EndDialog(hDlg, FALSE);
				break;

			case ID_PRESSUREPLUSB:
		
				//////// Pressure Increment in TextBox
				GetDlgItemText(hDlg, ID_INCDECB, (LPWSTR)w_incdecB, 255);
				swprintf(szstr, 255, L"%s", w_incdecB);
				if (incdecB == NULL)
				{
					swprintf(szstr, 255, L"%f", pressrB);
					hPressure = GetDlgItem(hDlg, ID_PRESSUREB);
					SetWindowText(hPressure, szstr);
					swprintf(szstr, 255, L"%f", volB);
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					SetWindowText(hVol, szstr);
				}
				else
				{
					incdecB = _wtof(w_incdecB);
					pressrB = pressrB + incdecB;
					hPressure = GetDlgItem(hDlg, ID_PRESSUREB);
					swprintf(szstr, 255, L"%f", pressrB);
					SetWindowText(hPressure, szstr);


					///////Volume Update (Decrement)
					volB = (float)(numgasB * R_CONST *tempB / pressrB);
					volB = volB - incdecB;
					swprintf(szstr, 255, L"%f", volB);
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					SetWindowText(hVol, szstr);
				}
				break;


			case ID_PRESSUREMINUSB:
				//////// Pressure Decrement in TextBox
				GetDlgItemText(hDlg, ID_INCDECB, (LPWSTR)w_incdecB, 255);
				if (incdecB == NULL)
				{
					swprintf(szstr, 255, L"%f", pressrB);
					hPressure = GetDlgItem(hDlg, ID_PRESSUREB);
					SetWindowText(hPressure, szstr);
					swprintf(szstr, 255, L"%f", volB);
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					SetWindowText(hVol, szstr);
				}
				else
				{
					incdecB = _wtof(w_incdecB);
					pressrB = pressrB - incdecB;
					hPressure = GetDlgItem(hDlg, ID_PRESSUREB);
					swprintf(szstr, 255, L"%f", pressrB);
					SetWindowText(hPressure, szstr);

					///////Volume Update (Increment)
					volB = (numgasB * R_CONST *tempB / pressrB);
					volB = volB + incdecB;
					swprintf(szstr, 255, L"%f", volB);
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					SetWindowText(hVol, szstr);
				}
				break;

			case ID_VMINUSB :
				//////// Volume Decrement in TextBox
				GetDlgItemText(hDlg, ID_INCDECB, (LPWSTR)w_incdecB, 255);
				swprintf(szstr, 255, L"%s", w_incdecB);

				if (incdecB == NULL)
				{
					swprintf(szstr, 255, L"%f", pressrB);
					hPressure = GetDlgItem(hDlg, ID_PRESSUREB);
					SetWindowText(hPressure, szstr);
					swprintf(szstr, 255, L"%f", volB);
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					SetWindowText(hVol, szstr);
				}
				else
				{

					incdecB = _wtof(w_incdecB);
					volB = volB - incdecB;
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					swprintf(szstr, 255, L"%f", volB);
					SetWindowText(hVol, szstr);


					/////////Pressure Update (Increment)
					pressrB = pressrB - incdecB;
					pressrB = (numgasB * R_CONST *tempB / volB);
					swprintf(szstr, 255, L"%f", pressrB);
					hVol = GetDlgItem(hDlg, ID_PRESSUREB);
					SetWindowText(hVol, szstr);
				}
				break;
	
			case ID_VPLUSB:
				//////// Volume Increment in TextBox
				GetDlgItemText(hDlg, ID_INCDECB, (LPWSTR)w_incdecB, 255);
			//	swprintf(szstr, 255, L"%s", w_incdecB);
				incdecB =_wtof(w_incdecB);
				volB = volB + incdecB;
				hVol = GetDlgItem(hDlg, ID_VOLUMEB);
				swprintf(szstr, 255, L"%f", volB);
				SetWindowText(hVol, szstr);

				/////////Pressure Update (Increment)
				pressrB = pressrB - incdecB;
				pressrB =(numgasB * R_CONST *tempB / volB);
				swprintf(szstr, 255, L"%f", pressrB);
				hVol = GetDlgItem(hDlg, ID_PRESSUREB);
				SetWindowText(hVol, szstr);
				break;


			case ID_FILEB:

			

				if (pressrB && volB && tempB && numgasB != NULL)
				{
					
					fprintf(gpFile2, "Value of the Pressure(P) of state 2 = %f\n", pressrB);
					fprintf(gpFile2, "Value of the Volume(V) of state 2 = %f\n", volB);
					fprintf(gpFile2, "Value of the Temprature(T) of state 2 = %f\n", tempB);
					fprintf(gpFile2, "Value of the Number of Gas Moles of state 2 = %f\n", numgasB);

					MessageBox(NULL, TEXT("Values successfully saved to Boyles law state - 2 Log.txt"), TEXT("MESSAGE "), MB_OK);
				}
				else
				{
					MessageBox(NULL, TEXT("Fill The Values All Values Are Zero"), TEXT("ERROR"), MB_ICONERROR);
				}
				break;

	
			case ID_NUMGASMOLESB:
			 GetDlgItemText(hDlg, ID_NUMGASMOLESB, (LPWSTR)w_numGasB, 255);
				numgasB = _wtof(w_numGasB);
				break;
				
			case ID_TEMPB:
				GetDlgItemText(hDlg, ID_TEMPB, (LPWSTR)w_tempB, 255);
				tempB = _wtof(w_tempB);

				pressrB =_wtof(w_pressrB);
				volB = (numgasB * R_CONST * tempB)/ pressrB;
			
				swprintf(szstr, 255, L"%f", volB);
				hVol = GetDlgItem(hDlg, ID_VOLUMEB);
				SetWindowText(hVol, szstr);
				break;


			case ID_INCDECB:
				GetDlgItemText(hDlg, ID_INCDECB, (LPWSTR)w_incdecB, 255);
					incdecB =  _wtof(w_incdecB);				

					// After entering in incdecB textbox cursor immediately default pressure and volume should get display
					hVol = GetDlgItem(hDlg, ID_VOLUMEB);
					SetWindowText(hVol, w_volB);

					hPressure = GetDlgItem(hDlg, ID_PRESSUREB);
					SetWindowText(hPressure, w_pressrB);
				break;

			case ID_PRESSUREB:
	
				break;

			case ID_VOLUMEB:
				GetDlgItemText(hDlg, ID_VOLUMEB, (LPWSTR)w_volB, 255);
				volB =_wtof(w_volB);
				resVol =numgasB * R_CONST * tempB / pressrB;
				
				break;


			case ID_VPLUSC:
				wsprintf(szstr, TEXT("%s "), w_numGasC);
		
				break;


			case RB_BOYLES:
				rbHwnd = GetDlgItem(hDlg, ID_GROUPBOX2);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_NUMGASMOLESC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_TEMPC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_INCDECC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_VOLUMEC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_TPLUSC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_TMINUSC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_VPLUSC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_VMINUSC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_PRESSUREC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_PLUSC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_MINUSC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_TEMPC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_FILEC);
				EnableWindow(rbHwnd, FALSE);
				rbHwnd = GetDlgItem(hDlg, ID_RESETC);
				EnableWindow(rbHwnd, FALSE);



				rbHwnd = GetDlgItem(hDlg, ID_GROUPBOX1);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_NUMGASMOLESB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_INCDECB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_TEMPB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_PRESSUREB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_PRESSUREPLUSB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_PLUSC);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_PRESSUREMINUSB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_VOLUMEB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_VPLUSB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_VMINUSB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_FILEB);
				EnableWindow(rbHwnd, TRUE);
				rbHwnd = GetDlgItem(hDlg, ID_RESETB);
				EnableWindow(rbHwnd, TRUE);
				break;

			case ID_RESETB:

				SendDlgItemMessage(hDlg, ID_NUMGASMOLESB, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_INCDECB, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_TEMPB, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_VOLUMEB, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_PRESSUREB, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_VOLUMEB, CB_RESETCONTENT, 0, 0);
				pressrB = volB = tempB = numgasB = NULL;
				break;
		

			

			default:
				break;
			}
		}






		///////////////////////////////////////////////////////// Charles Law  ////////////////////////////////////////////////////////////////
		if (charlesLawSelected > 0)
		{
			switch (LOWORD(DlgwParam))
			{

			case VK_ESCAPE:
				EndDialog(hDlg, FALSE);
				return FALSE;
				break;

			case 2:
				EndDialog(hDlg, FALSE);
				break;

			case RB_CHARLES:

				rbHwnd2 = GetDlgItem(hDlg, ID_GROUPBOX2);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_NUMGASMOLESC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_TEMPC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_INCDECC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_VOLUMEC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_TPLUSC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_TMINUSC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_VPLUSC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_VMINUSC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_PRESSUREC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_PLUSC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_MINUSC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_TEMPC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_FILEC);
				EnableWindow(rbHwnd2, TRUE);
				rbHwnd2 = GetDlgItem(hDlg, ID_RESETC);
				EnableWindow(rbHwnd2, TRUE);


				rbHwnd2 = GetDlgItem(hDlg, ID_GROUPBOX1);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_NUMGASMOLESB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_INCDECB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_TEMPB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_PRESSUREB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_PRESSUREPLUSB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_PLUSC);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_PRESSUREMINUSB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_VOLUMEB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_VPLUSB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_VMINUSB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_FILEB);
				EnableWindow(rbHwnd2, FALSE);
				rbHwnd2 = GetDlgItem(hDlg, ID_RESETB);
				EnableWindow(rbHwnd2, FALSE);

				break;
				case ID_CANCEL:
					EndDialog(hDlg, 0);
					break;

			case ID_RESETC:
				SendDlgItemMessage(hDlg, ID_NUMGASMOLESC, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_INCDECC, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_PRESSUREC, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_VOLUMEC, CB_RESETCONTENT, 0, 0);

				SendDlgItemMessage(hDlg, ID_TEMPC, CB_RESETCONTENT, 0, 0);

				incdecC = numgasC = volC = pressrC= tempC = NULL;
				break;

			case ID_NUMGASMOLESC:
				GetDlgItemText(hDlg, ID_NUMGASMOLESC, (LPWSTR)w_numGasC, 255);
				numgasC =(float) _wtof(w_numGasC);
				break;

			case ID_INCDECC:
				GetDlgItemText(hDlg, ID_INCDECC, (LPWSTR)w_incdecC, 255);
				incdecC = _wtof(w_incdecC);

				hVolC = GetDlgItem(hDlg, ID_VOLUMEC); 
				SetWindowText(hVolC, w_volC);

				hTempC = GetDlgItem(hDlg, ID_TEMPC);
				SetWindowText(hTempC, w_tempC);
				break;

			case ID_PRESSUREC:
				GetDlgItemText(hDlg, ID_PRESSUREC, (LPWSTR)w_pressrC, 255);
				pressrC = _wtof(w_pressrC);
				volC = _wtof(w_volC);
				tempC = _wtof(w_tempC);
				tempC =(pressrC * volC / numgasC * R_CONST);


				swprintf(szstr, 255, L"%f", tempC);
				hTempC = GetDlgItem(hDlg, ID_TEMPC);
				SetWindowText(hTempC, szstr);

				break;

			case ID_TEMPC:
				GetDlgItemText(hDlg, ID_TEMPC, (LPWSTR)w_tempC, 255);
				tempC = _wtof(w_tempC);
				break;


			case ID_VOLUMEC:
				GetDlgItemText(hDlg, ID_VOLUMEC, (LPWSTR)w_volC, 255);
				volC = _wtof(w_volC);
				break;

			case ID_VPLUSC:
				GetDlgItemText(hDlg, ID_INCDECC, (LPWSTR)w_incdecC, 255);
				if (incdecC == NULL)
				{
					swprintf(szstr, 255, L"%f", tempC);
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					SetWindowText(hTempC, szstr);
					swprintf(szstr, 255, L"%f", volC);
					hVolC = GetDlgItem(hDlg, ID_VOLUMEC);
					SetWindowText(hVolC, szstr);
				}
				else
				{
					incdecC = _wtof(w_incdecC);
					volC = volC + incdecC;
					hVol = GetDlgItem(hDlg, ID_VOLUMEC);
					swprintf(szstr, 255, L"%f", volC);
					SetWindowText(hVol, szstr);

					////Temprature (increment when volume increment)
					tempC = tempC + incdecC;
					tempC =(pressrC * volC / numgasC * R_CONST);
					swprintf(szstr, 255, L"%f", tempC);
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					SetWindowText(hTempC, szstr);
				}
				break;

			case ID_VMINUSC:
				GetDlgItemText(hDlg, ID_INCDECC, (LPWSTR)w_incdecC, 255);

				if (incdecC == NULL)
				{
					swprintf(szstr, 255, L"%f", tempC);
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					SetWindowText(hTempC, szstr);
					swprintf(szstr, 255, L"%f", volC);
					hVolC = GetDlgItem(hDlg, ID_VOLUMEC);
					SetWindowText(hVolC, szstr);
				}
				else
				{

					//For update Volume textBox (decrement)
					incdecC = _wtof(w_incdecC);
					volC = volC - incdecC;
					hVol = GetDlgItem(hDlg, ID_VOLUMEC);
					swprintf(szstr, 255, L"%f", volC);
					SetWindowText(hVol, szstr);

					////Temprature (decrement when volume decrement)
					tempC = tempC - incdecC;
					tempC = (pressrC * volC / numgasC * R_CONST);
					swprintf(szstr, 255, L"%f", tempC);
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					SetWindowText(hTempC, szstr);
				}
				break;


			case ID_TPLUSC:
				GetDlgItemText(hDlg, ID_INCDECC, (LPWSTR)w_incdecC, 255);
				if (incdecC == NULL)
				{
					swprintf(szstr, 255, L"%f", tempC);
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					SetWindowText(hTempC, szstr);
					swprintf(szstr, 255, L"%f", volC);
					hVolC = GetDlgItem(hDlg, ID_VOLUMEC);
					SetWindowText(hVolC, szstr);
				}
				else
				{
					incdecC = _wtof(w_incdecC);
					tempC = tempC + incdecC;
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					swprintf(szstr, 255, L"%f", tempC);
					SetWindowText(hTempC, szstr);

					volC = volC + incdecC;
					volC = (numgasC * R_CONST *tempC) / pressrC;
					swprintf(szstr, 255, TEXT("%f"), volC);
					hVolC = GetDlgItem(hDlg, ID_VOLUMEC);
					SetWindowText(hVolC, szstr);
				}
				break;


			case ID_TMINUSC:
				GetDlgItemText(hDlg, ID_INCDECC, (LPWSTR)w_incdecC, 255);
				if (incdecC == NULL)
				{
					swprintf(szstr, 255, L"%f", tempC);
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					SetWindowText(hTempC, szstr);
					swprintf(szstr, 255, L"%f", volC);
					hVolC = GetDlgItem(hDlg, ID_VOLUMEC);
					SetWindowText(hVolC, szstr);
				}
				else
				{
					incdecC = _wtof(w_incdecC);
					tempC = tempC - incdecC;
					hTempC = GetDlgItem(hDlg, ID_TEMPC);
					swprintf(szstr, 255, TEXT("%f"), tempC);
					SetWindowText(hTempC, szstr);

					volC = volC - incdecC;
					volC = (numgasC * R_CONST *tempC) / pressrC;
					swprintf(szstr, 255, L"%f", volC);
					hVolC = GetDlgItem(hDlg, ID_VOLUMEC);
					SetWindowText(hVolC, szstr);
				}
				break;

			case ID_FILEC:
				

				if (pressrC && volC && tempC && numgasC != NULL)
				{
					fprintf(gpFile2, "Value of the Pressure(P) of state 2 = %f\n", pressrC);
					fprintf(gpFile2, "Value of the Volume(V) of state 2 = %f\n", volC);
					fprintf(gpFile2, "Value of the Temprature(T) of state 2 = %f\n", tempC);
					fprintf(gpFile2, "Value of the Number of Gas Moles of state 2 = %f\n", numgasC);

					MessageBox(NULL, TEXT("Values successfully saved to Boyles law state - 2 Log.txt"), TEXT("MESSAGE "), MB_OK);
				}
				else
				{
					MessageBox(NULL, TEXT("Fill The Values All Values Are Zero"), TEXT("ERROR"), MB_ICONERROR);
				}
				break;

				break;
			}
		}
		break;
	}

	return(FALSE);
}






//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	
	HINSTANCE hInst;
	TCHAR str[] = TEXT("Hello World");
	TCHAR spaceStr[255] = TEXT("HIT SPACE BAR TO CONTINUE....");
	TCHAR Astromedicomp[255] = TEXT("ASTROMEDICOMP");
	BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
	void FullScreen(HWND);

	PAINTSTRUCT ps;
	RECT rc;
	HFONT hFont = NULL;
	HDC hdcInst= NULL,hdcInst2 = NULL;


	HBITMAP hBitmapOld = NULL;

	static HBITMAP hBitmap = NULL;
	static HDC hdc = NULL;
	static BITMAP bmp;
	//code
	switch (iMsg)
	{

	case WM_CREATE:
	
		hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SPLASH), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

		GetObject(hBitmap, sizeof(bmp), &bmp);
		hdc = CreateCompatibleDC(GetDC(0));
		SelectObject(hdc, hBitmap);
		SendMessage(hwnd, FULLSCREEN, 0, 0);
		break;
		

	case WM_PAINT:

		hdcInst = BeginPaint(ghwnd, &ps);
		rc = ps.rcPaint;
		BitBlt(hdcInst, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hdc, 0, 0, SRCCOPY);
		StretchBlt(hdcInst, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);


		SelectObject(hdc, hBitmap);
		///Title to be Displayed on main page
		SelectObject(hdcInst, CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman")));
		SetTextColor(hdcInst, RGB(255, 0, 0));
		SetBkColor(hdcInst, TRANSPARENT);
		SetBkMode(hdcInst, TRANSPARENT);

		TextOut(hdcInst, 100, 600, spaceStr, wcslen(spaceStr));
		TextOut(hdcInst, 600, 50, Astromedicomp, wcslen(Astromedicomp));

		EndPaint(ghwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_SPACE:
			hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
			DialogBox(hInst, TEXT("DATAENTRY"), hwnd, (DLGPROC)MyDialogProc);
		
			break;

		case VK_ESCAPE:
			EndDialog(ghwnd, 0);
			exit(0);
			break;

		default:
			break;
		}

	case WM_DESTROY:
		DeleteObject(hBitmap);
		DeleteDC(hdc);
		PostQuitMessage(0);
		break;

	case FULLSCREEN:
		FullScreen(hwnd);
		break;
	case WM_CLOSE:

		break;
	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}





void FullScreen(HWND hwnd)
{
	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	MONITORINFO mi = { sizeof(mi) };

	if (dwStyle & WS_OVERLAPPEDWINDOW)
	{
		if (GetMonitorInfo(MonitorFromWindow(hwnd, MONITORINFOF_PRIMARY), &mi) == TRUE)
		{
			SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_EX_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}
}


void uninitialize()
{

	if(gpFile)
		fprintf(gpFile, "Log File Is Successfully Closed.\n");
	fclose(gpFile);
	gpFile = NULL;

	if(gpFile2)
		fprintf(gpFile2, "Log File2 Is Successfully Closed.\n");
	fclose(gpFile2);
	gpFile2 = NULL;
}







