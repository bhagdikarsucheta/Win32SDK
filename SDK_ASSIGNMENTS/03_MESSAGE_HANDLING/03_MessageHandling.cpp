#include<Windows.h>
#include<windowsx.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");


	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("MyApplication"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);



	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return((int)msg.wParam);
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{


	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("Window Created using WM_CREATE MESSAGE"), TEXT("WM_CREATE"), MB_OK);
		break;

	case WM_MOVE:
		MessageBox(hwnd, TEXT("Window Moved using WM_MOVE MESSAGE"), TEXT("WM_MOVE"), MB_OK);
		break;

	case WM_SIZE:
		MessageBox(hwnd, TEXT("Window Resized using WM_SIZE MESSAGE"), TEXT("WM_SIZE"), MB_OK);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Left Button Down Pressed using WM_LBUTTONDOWN MESSAGE"), TEXT("WM_LBUTTONDOWN"), MB_OK);
		break;

	case WM_DESTROY:
		MessageBox(hwnd, TEXT("Window Closing using  WM_DESTROY MESSAGE"), TEXT("WM_DESTROY"), MB_OK);
		break;

	default:
		break;


	}


	return(DefWindowProc(hwnd, iMsg, wParam, lParam));







}



























