#include "CGameObject.h"

void CGameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CGameObject::SetState(int state)
{
	this->currentState = state;
}


CGameObject::CGameObject()
{
	nx = 1;
	vx = vy = 0;
	x = y = 0;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION anim = CLocator<IAnimsManager>().Get()->Get(aniId);
	animSet->push_back(anim);
}

void CGameObject::SetAnimationSet(LPANIMSET animSet)
{
	this->animSet = animSet;
}

int CGameObject::GetState()
{
	return currentState;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dx = vx * dt;
	dy = vy * dt;

	x += dx;
	y += dy;
}




CGameObject::~CGameObject()
{
}