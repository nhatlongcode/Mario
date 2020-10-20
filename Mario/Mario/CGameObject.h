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
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	void AddAnimation(int aniId);
	
	int GetState();

	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	virtual void SetState(int state);
};

typedef CGameObject* LPGAMEOBJECT;

