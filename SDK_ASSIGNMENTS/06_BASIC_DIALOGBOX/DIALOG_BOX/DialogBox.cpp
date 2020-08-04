#include <Windows.h>
//#include<gl/GL.h>
//#include<math.h>
#include"myDialog.h"

//#pragma comment(lib,"user32.lib")

//Prototype of WndProc() declared Globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);


struct INPUT2
{
	char name[50], address[50];
	int age, mstatus;
	float sal;
} in;
//main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	//function prototype

	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("SDK Window");


	//code
	//initializing member of WNDCLASS
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
		TEXT("Hello World Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1920,
		1080,
		NULL,
		NULL,
		hInstance,
		NULL
		);


	//intitialize()


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}





BOOL CALLBACK MyDialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	char salrs[6], salps[3];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		//set focus in name Edit Box
		SetFocus(GetDlgItem(hDlg, ID_ETNAME));
		//keep married button checked
		SendDlgItemMessage(hDlg, RB_MARRIED, BM_SETCHECK, 1, 0);
		return(TRUE);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OK:
			GetDlgItemText(hDlg, ID_ETNAME, (LPWSTR)in.name, 50);

			GetDlgItemText(hDlg, ID_ETADDRESS, (LPWSTR)in.address, 50);

			GetDlgItemInt(hDlg, ID_TAGE, NULL,TRUE);

			GetDlgItemText(hDlg, ID_ETSALRS,(LPWSTR) salrs, 6);

			GetDlgItemText(hDlg, ID_ETSALPS, (LPWSTR)salps, 3);

			in.sal = atoi(salrs);
	//		in.sal = (float)atoi(salps / 100);

			EndDialog(hDlg, 0);
			break;

		case ID_CANCEL:
			EndDialog(hDlg, 0);
			break;
		default:
			break;
		}

		break;

	default:
		break;
		return(TRUE);
	}

	return(FALSE);
}






//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rc;
	HDC hdc;
	HINSTANCE hInst;
	TCHAR str[] = TEXT("Hello World");
	BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

	//code
	switch (iMsg)
	{

	case WM_CREATE:
		hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		DialogBox(hInst, TEXT("DATAENTRY"), hwnd, (DLGPROC)MyDialogProc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}


















