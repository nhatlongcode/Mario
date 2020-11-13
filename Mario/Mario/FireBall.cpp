#include "FireBall.h"
#include "CGame.h"

FireBall::FireBall(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	this->nx = direction;
	this->state = FIREBALL_STATE_FLY;
	SetBoundingBox(FIREBALL_BBOX_WIDTH, FIREBALL_BBOX_HEIGHT);
	SetAnimationSet(FIREBALL_ANIMSET);
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += MARIO_GRAVITY;
	vx = FIREBALL_SPEED_X * nx;
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


	if (tag == ObjectTag::Goomba)
	{
		go->SetState(GOOMBA_STATE_DIE_INSTANT);
		go->SetSpeedX(nx * 0.3f);
		go->SetSpeedY(-0.8f);

		state = FIREBALL_STATE_EXPLO;
	}

	if (tag == ObjectTag::Koopas)
	{
		go->SetState(KOOPAS_STATE_DIE);
		go->SetSpeedX(nx * 0.3f);
		go->SetSpeedY(-0.8f);

		state = FIREBALL_STATE_EXPLO;
	}
}
