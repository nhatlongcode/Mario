#pragma once
#include "Utils.h"
#include "MarioDefines.h"
#include "CGameObject.h"
#include "CMario.h"
#include "IHandleInput.h"
#include <dinput.h>

class CInput : public IHandleInput
{
private:
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	
	LPKEYEVENTHANDLER keyHandler;

	CMario* mario;
public:
	CInput(HWND hWnd);
	void SetKeyHandler(LPKEYEVENTHANDLER keyHandler);
	void ProcessKeyboard();
	bool IsKeyDown(int KeyCode);
};

typedef CInput* LPINPUTHANDLER;
