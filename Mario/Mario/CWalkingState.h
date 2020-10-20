#pragma once
#include "CMarioState.h"
class CWalkingState : public CMarioState
{
public:
	virtual void Init();
	virtual void Render();
	virtual void Update(DWORD dt);
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
};

