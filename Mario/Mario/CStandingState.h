#pragma once
#include "CMarioState.h"
class CStandingState : public CMarioState
{
public:
	virtual void Init();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
};

