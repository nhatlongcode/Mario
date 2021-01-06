#include "CMushroom.h"
#include "CGame.h"

CMushroom::CMushroom()
{
	IsCollisionEnabled = true;
	SetBoundingBox(48, 48);
	SetAnimationSet(30004);
	SetTag(ObjectTag::Buff);
	nx = DIRECTION_RIGHT;
	isOutOfBrick = false;
	vx = vy = 0.0f;
	this->state = 0;
}

void CMushroom::TriggerReward()
{
	startTime = CGame::Instance()->GetDeltaTime();
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (startTime != -1)
	{
		startTime += dt;
		if (startTime < 1000 && startTime > 450)
		{
			vy = -0.048f;
		}
		else if (startTime > 1500)
		{
			vy = 0.0f;
			vx = nx * 0.15f;
			startTime = -1;
			isOutOfBrick = true;
			IsCollisionEnabled = true;
		}
	}
	if (isOutOfBrick)
	{
		vy += 0.03f;
	}
	CGameObject::Update(dt, coObjects);
}

void CMushroom::SetState(int state)
{
	if (state == -1)
	{
		IsCollisionEnabled = false;
	}
	this->state = state;
}

void CMushroom::Render()
{
	if (state == -1) return;
	if (startTime < 450 && startTime != -1) return;
	animSet->at(this->state)->Render(this->x, this->y);
}

void CMushroom::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	auto input = CLocator<IHandleInput>().Get();
	LPGAMEOBJECT go = other->obj;
	ObjectTag tag = go->GetTag();

	
}
