#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CAnimationsManager.h"
#include "Utils.h"
#include "CLocator.h"


class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	float vy;

	float dx;
	float dy;
	
	int nx;
	int currentState;

	vector<LPANIMATION> animations;

public:
	CGameObject();
	~CGameObject();

	void SetPosition(float x, float y);
	void SetSpeed(Vector2 vel);

	void AddAnimation(int aniId);
	
	int GetState();

	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	virtual void SetState(int state);
};

typedef CGameObject* LPGAMEOBJECT;

