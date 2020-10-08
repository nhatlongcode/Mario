#ifndef CWINDOW_H
#define CWINDOW_H

#include <Windows.h>
#include "CAbstractService.h"

class CWindow : public CAbstractService
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
#endif

