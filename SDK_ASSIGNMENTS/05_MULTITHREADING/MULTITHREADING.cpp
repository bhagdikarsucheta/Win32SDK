#define UNICODE 
#include <Windows.h>

//#include<gl/GL.h>
//Prototype of WndProc() declared Globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD CALLBACK MyThreadProcOne(LPVOID);
DWORD CALLBACK MyThreadProcTwo(LPVOID);

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
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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


//WndProc()
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThread1, hThread2;
	
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcOne,(LPVOID)hwnd, 0, NULL);
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("This is Third Thread"), TEXT("Message from Thread"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}


DWORD  WINAPI MyThreadProcOne(LPVOID lParam)
{
	HWND hwnd = HWND(lParam);
	HDC hdc = GetDC(hwnd);
	TCHAR str[255];

	for (int i = 0;i < 32768;i++)
	{
		wsprintf(str, TEXT("Increamenting: %d"), i);
		TextOut(hdc, 5,5, str, (int)wcslen(str));
	}
	ReleaseDC(hwnd, hdc);
	return 0;
}





DWORD WINAPI MyThreadProcTwo(LPVOID lParam)
{
	HWND hwnd = HWND(lParam);
	HDC hdc = GetDC(hwnd);
	TCHAR str[255];

	for (int i= 32768;i >= 0; i--)
	{
		wsprintf(str, TEXT("Decrementing: %d"), i);
		Sleep(0.1);
		TextOut(hdc, 5,25, str, (int)wcslen(str));
	}
	ReleaseDC(hwnd, hdc);
	return 0;
}




















