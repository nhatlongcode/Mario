#pragma once
#include "CGameObject.h"
class CMario : public CGameObject
{
private:
	int level;
	float startX;			// initial position of Mario at scene
	float startY;
public:
	CMario(float startX, float startY);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetState(int state);
	void SetLevel(int level);
	void Reset();
};

