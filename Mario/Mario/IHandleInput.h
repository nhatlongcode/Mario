#pragma once
#include "CKeyEventHandler.h"

class IHandleInput
{
public:
	virtual void SetKeyHandler(LPKEYEVENTHANDLER keyHandler) = 0;
	virtual void ProcessKeyboard() = 0;
	virtual bool IsKeyDown(int KeyCode) = 0;
};