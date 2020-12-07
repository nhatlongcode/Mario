#include "CWindow.h"
#include "MarioDefines.h"

LRESULT CWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}

HWND CWindow::GetHandleWindow()
{
	return hWnd;
}


CWindow::CWindow(HINSTANCE hinstance, int ncmdwindow)
{
	hInstance = hinstance;
	nCmdWindow = ncmdwindow;
	CreateGameWindow();
}


void CWindow::CreateGameWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(181, 235, 242));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClassEx(&wc);

	hWnd = CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			WND_WIDTH ,
			WND_HEIGHT,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (hWnd == nullptr)
	{
		DWORD ErrCode = GetLastError();
		OutputDebugString(L"[ERROR] CreateWindow failed: " + ErrCode);
	}
	else
	{
		ShowWindow(hWnd, nCmdWindow);
		UpdateWindow(hWnd);
		OutputDebugString(L"[INFO] Init window complete\n");
	}

}


