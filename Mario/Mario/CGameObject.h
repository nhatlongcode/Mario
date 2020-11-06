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
private:
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT other);

	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

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

	ObjectTag tag;

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

	bool CheckCollision(vector<LPGAMEOBJECT>* coObjects);
	void SetBoundingBox(float width, float height);

	void AddAnimation(int aniId);
	void SetAnimationSet(int animSetID);

	void GetState(int& state) { state = this->state; }

	ObjectTag GetTag();

	void RenderCollisionBox();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void OnCollisionEnter(LPCOLLISIONEVENT other);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state);
};


