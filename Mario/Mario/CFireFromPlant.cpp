#include "CFireFromPlant.h"

CFireFromPlant::CFireFromPlant(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	nx = direction;
	SetAnimationSet(FIREBALL_ANIMSET);
}

void CFireFromPlant::Render()
{
	if (state == -1) return;
	animSet->at(state)->Render(this->x, this->y);
}

void CFireFromPlant::SetState(int state)
{
	this->state = state;
}

void CFireFromPlant::OnCollisionEnter(LPCOLLISIONEVENT other)
{
}

void CFireFromPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vx = 0.2f * nx;
	vy = 0.2f;
}
