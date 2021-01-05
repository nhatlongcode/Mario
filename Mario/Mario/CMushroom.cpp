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
		vy += MARIO_GRAVITY;
	}
	CGameObject::Update(dt, coObjects);
}

void CMushroom::SetState(int state)
{
	this->state = state;
}

void CMushroom::Render()
{
	if (startTime < 450 && startTime != -1) return;
	animSet->at(this->state)->Render(this->x, this->y);
}
