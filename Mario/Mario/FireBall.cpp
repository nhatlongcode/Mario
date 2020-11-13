#include "FireBall.h"
#include "CGame.h"

FireBall::FireBall(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	this->nx = direction;
	this->state = 0;
	SetBoundingBox(24.0f, 24.0f);
	SetAnimationSet(30000);
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.05f;
	vx = 0.5f * nx;
	CGameObject::Update(dt, coObjects);
}

void FireBall::Render()
{
	animSet->at(state)->Render(x, y);
}

void FireBall::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	CGameObject* go = other->obj;
	ObjectTag tag = go->GetTag();
	if (tag == ObjectTag::Ground)
	{
		if (other->ny == -1.0f)
		{
			this->vy = -0.8f;
		}
	}
	if (tag == ObjectTag::GhostPlatform)
	{
		state = 1;
		//CGame::Instance()->GetCurrentScene()->RemoveGameObject(this);
	}

	if (tag == ObjectTag::Goomba)
	{
		go->SetState(GOOMBA_STATE_DIE_INSTANT);
	}

	if (tag == ObjectTag::Koopas)
	{
		go->SetState(KOOPAS_STATE_DIE);
	}
}
