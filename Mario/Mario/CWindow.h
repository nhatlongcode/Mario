#pragma once
#include <Windows.h>

class CWindow
{
private:
	HINSTANCE hInstance;
	HWND hWnd;
	int nCmdWindow;
	void CreateGameWindow();
public:
	CWindow(HINSTANCE hinstance, int nCmdWindow);
	void Init();
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HWND GetHandleWindow();
};

