#pragma once
#include <Windows.h>
class IWindow
{
public:
	virtual	HWND GetHandleWindow() = 0;
};