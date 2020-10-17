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

void CGameObject::SetSpeed(Vector2 vel)
{
	vx = vel.x;
	vy = vel.y;
}

CGameObject::CGameObject()
{
	nx = 1;
	vx = vy = 0;
	x = y = 0;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION anim = CLocator<CAnimationsManager>().Get()->Get(aniId);
	animations.push_back(anim);
}

int CGameObject::GetState()
{
	return currentState;
}

void CGameObject::Update(DWORD dt)
{
	dx = vx * dt;
	dy = vy * dt;

}


CGameObject::~CGameObject()
{
}