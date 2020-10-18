#pragma once
#include <Windows.h>
#include "IWindow.h"
class CWindow : public IWindow
{
private:
	HINSTANCE hInstance;
	HWND hWnd;
	int nCmdWindow;
	void CreateGameWindow();
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	CWindow(HINSTANCE hinstance, int nCmdWindow);
	HWND GetHandleWindow();
};

