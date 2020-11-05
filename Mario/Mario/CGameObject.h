#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CCollisionEvent.h"
#include "CAnimationsManager.h"
#include "Utils.h"
#include "CLocator.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CGameObject
{
private:
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT other);
protected:
	float x;
	float y;

	float vx;
	float vy;

	float dx;
	float dy;
	
	int nx;
	int state;

	float bboxWidth;
	float bboxHeight;

	LPANIMSET animSet;

public:
	CGameObject();
	~CGameObject();

	bool IsCollisionEnabled;

	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	void SetDirection(int nx);
	void GetDirection(int& nx) { nx = this->nx; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void AddSpeed(float vx, float vy) { this->vx += vx; this->vy += vy; }
	void SetSpeedX(float vx);
	void SetSpeedY(float vy);

	void CheckCollision(vector<LPGAMEOBJECT>* coObjects);
	void SetBoundingBox(float width, float height);

	void AddAnimation(int aniId);
	void SetAnimationSet(int animSetID);

	void GetState(int& state) { state = this->state; }

	void RenderCollisionBox();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void OnCollisionEnter(LPCOLLISIONEVENT other);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state);
};


