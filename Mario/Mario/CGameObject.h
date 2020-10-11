#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CAnimationsManager.h"
#include "CLocator.h"


class CGameObject
{
private:
	float x;
	float y;
	float vx;
	
	int currentState;

	//static vector<LPANIMATION> animations; 

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetState(int state) { this->currentState = state; }

	CGameObject();

	void Update(DWORD dt);
	void Render();
	~CGameObject();
};

