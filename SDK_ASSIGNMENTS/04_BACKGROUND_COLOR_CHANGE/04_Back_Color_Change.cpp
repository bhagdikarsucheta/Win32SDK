















//Headers
#include<windows.h>

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Variable declararions
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Assignment 04");

	//code
	//initialization of  WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//Creat window
	hwnd = CreateWindow(szAppName,
		TEXT("Assignment 04"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush;
	static HDC hdc;
	static RECT rc;
	PAINTSTRUCT ps;
	HGDIOBJ hdgiobject;

	//code
	switch (iMsg)
	{
	case  WM_CREATE:
		//When window gets created its colour will be gray 
		hBrush = CreateSolidBrush(RGB(128, 128, 128));
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'R':
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'G':
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'B':
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'Y':
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'K':
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'C':
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'W':
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			InvalidateRect(hwnd, &rc, TRUE);
			break;

		case 'M':
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		default:
			hBrush = CreateSolidBrush(RGB(165, 42, 42));
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hdgiobject =  SelectObject(hdc,(HBRUSH) hBrush);
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hdgiobject);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
