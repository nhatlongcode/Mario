#include "CGameObject.h"
#include "CLocator.h"
#include "IAnimSetsManager.h"


void CGameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CGameObject::SetDirection(int nx)
{
	this->nx = nx;
}

void CGameObject::SetState(int state)
{
	this->state = state;
}


CGameObject::CGameObject()
{
	nx = 1;
	vx = vy = 0;
	x = y = 0;
}

void CGameObject::SetSpeedX(float vx)
{
	this->vx = vx;
}

void CGameObject::SetSpeedY(float vy)
{
	this->vy = vy;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION anim = CLocator<IAnimsManager>().Get()->Get(aniId);
	animSet->push_back(anim);
}

void CGameObject::SetAnimationSet(int animSetID)
{
	this->animSet = CLocator<IAnimSetsManager>().Get()->Get(animSetID);
}


void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dx = vx * dt;
	dy = vy * dt;
	//DebugOut(L"%f")
	x += dx;
	y += dy;
}




CGameObject::~CGameObject()
{
}