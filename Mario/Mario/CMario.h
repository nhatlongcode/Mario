#pragma once
#include "CGameObject.h"
class CMario : public CGameObject
{
protected:
	int level;
	float startX;			// initial position of Mario at scene
	float startY;
public:
	CMario();
	void SetState(int state);
	void SetLevel(int level);

	virtual void Init();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);

	void Reset();
};

