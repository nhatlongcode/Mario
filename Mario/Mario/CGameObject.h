#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CAnimationsManager.h"
#include "Utils.h"
#include "CLocator.h"


class CGameObject
{
private:
	float x;
	float y;

	float vx;
	float vy;
	
	int nx;
	int currentState;

	vector<LPANIMATION> animations; 

public:
	void SetPosition(float x, float y);
	void SetState(int state);
	CGameObject();
	void AddAnimation(int aniId);
	void Update(DWORD dt);
	void Render();
	~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;

