#pragma once
#include <Windows.h>
class CWindow
{
private:
	HINSTANCE hInstance;
	HWND hWnd;
public:
	CWindow();
	void CreateGameWindow(HINSTANCE hInstance, int nCmdWindow);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

