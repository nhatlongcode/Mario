#include "CFireFromPlant.h"

CFireFromPlant::CFireFromPlant(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	nx = direction;
	state = 0;
	IsCollisionEnabled = true;
	SetTag(ObjectTag::Venus);
	SetBoundingBox(24, 24);
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
	if (other->obj->GetTag() == ObjectTag::Player) DebugOut(L"Detect from venus\n");
}

void CFireFromPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vx = 0.07f * nx;
	vy = 0.07f;
}

bool CFireFromPlant::GetThrought(ObjectTag tag, float nx, float ny)
{
	return false;
}
