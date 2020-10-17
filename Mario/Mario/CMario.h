#pragma once
#include "CGameObject.h"
class CMario : public CGameObject
{
private:
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

