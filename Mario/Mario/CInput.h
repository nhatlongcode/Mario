#pragma once
#include "Utils.h"
#include "MarioDefines.h"
#include <dinput.h>

class CInput
{
private:
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	
	void KeyState(BYTE* states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
public:
	CInput(HWND hWnd);
	void ProcessKeyboard();
};

typedef CInput* LPINPUTHANDLER;
