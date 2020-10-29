#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CAnimationsManager.h"
#include "Utils.h"
#include "CLocator.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

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
	int state;

	LPANIMSET animSet;

public:
	CGameObject();
	~CGameObject();

	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	void SetDirection(int nx);
	void GetDirection(int& nx) { nx = this->nx; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void AddSpeed(float vx, float vy) { this->vx += vx; this->vy += vy; }
	void SetSpeedX(float vx);
	void SetSpeedY(float vy);

	void AddAnimation(int aniId);
	void SetAnimationSet(int animSetID);

	void GetState(int& state) { state = this->state; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state);
};


