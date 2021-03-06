#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CCollisionEvent.h"
#include "CAnimationsManager.h"
#include "Utils.h"
#include "Enum.h"
#include "CLocator.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CGameObject
{
protected:
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT other);

	void SweptAABBE(float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny);

protected:
	float x;
	float y;

	float vx;
	float vy;


	float dx;
	float dy;
	
	int alpha = 255;
	int nx;
	int state;

	float bboxWidth;
	float bboxHeight;

	ObjectTag tag;

	LPANIMSET animSet;

public:
	CGameObject();
	~CGameObject();

	bool IsCollisionEnabled;

	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	void SetAlpha(int alpha);

	void SetDirection(int nx);
	void GetDirection(int& nx) { nx = this->nx; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void AddSpeed(float vx, float vy) { this->vx += vx; this->vy += vy; }
	void SetSpeedX(float vx);
	void SetSpeedY(float vy);

	bool CheckCollision(vector<LPGAMEOBJECT>* coObjects);
	void SetBoundingBox(float width, float height);

	void AddAnimation(int aniId);
	void SetAnimationSet(int animSetID);

	void GetState(int& state) { state = this->state; }

	ObjectTag GetTag();
	void SetTag(ObjectTag tag);

	virtual void RenderCollisionBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void OnCollisionEnter(LPCOLLISIONEVENT other);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state);

	virtual bool GetThrought(ObjectTag tag, float nx, float ny);
};


