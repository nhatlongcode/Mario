#pragma once
#include "CInput.h"
class CMario;
class CMarioState
{

protected:
	CMario* mario;
	BYTE* keyStates;
	bool IsKeyDown(int keyCode);
public:
	virtual void Init();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	void SetMario(CMario* mario);
};