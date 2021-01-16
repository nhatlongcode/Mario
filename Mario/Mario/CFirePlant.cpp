#include "CFirePlant.h"
#include "CGame.h"

CFirePlant::CFirePlant()
{
	nx = DIRECTION_LEFT;
	SetAnimationSet(22000);
	SetBoundingBox(48, 96);
	this->state = 0;
}

void CFirePlant::Render()
{
	animSet->at(state)->Render(x,y,nx);
}

void CFirePlant::SetState(int state)
{
	//0: look down 1: look up 2: goDown
	this->state = state;
}

void CFirePlant::OnCollisionEnter(LPCOLLISIONEVENT other)
{
}

bool CFirePlant::GetThrought(ObjectTag tag, float nx, float ny)
{
	return true;
}

void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float pX, pY;
	CGame::Instance()->GetCurrentScene()->GetPlayer()->GetPosition(pX, pY);
	if ((this->x - pX) > 0) nx = DIRECTION_RIGHT;
	else nx = DIRECTION_LEFT;

	if (this->y - pY < 0) SetState(0);
	else SetState(1);
}
