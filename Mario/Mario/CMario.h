#pragma once
#include "CGameObject.h"
class CMario : public CGameObject
{
private:
	int level;
	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void SetLevel(int level);
	void Reset();
};

