#pragma once
#include "CGameObject.h"
#include "CMarioState.h"
class CMario : public CGameObject
{
private:
	CMarioState* state;
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void SetMarioState(CMarioState* state);
	CMarioState* GetMarioState();
};

