#pragma once
#include "CKeyEventHandler.h"
#include "ICommand.h"

class IHandleInput
{
public:
	virtual void SetKeyHandler(LPKEYEVENTHANDLER keyHandler) = 0;
	virtual void ProcessKeyboard() = 0;
	virtual ICommand* HandleInput() = 0;
	virtual bool IsKeyDown(int KeyCode) = 0;
};