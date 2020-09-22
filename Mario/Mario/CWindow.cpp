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

CWindow::CWindow()
{
}

void CWindow::CreateGameWindow(HINSTANCE hInstance, int nCmdWindow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
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
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
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
		OutputDebugString(L"[INFO] Init window complete");
	}

}


