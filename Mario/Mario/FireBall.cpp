#include "FireBall.h"
#include "CGame.h"

FireBall::FireBall(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	this->nx = direction;
	explodeStart = 0;
	SetAnimationSet(FIREBALL_ANIMSET);
	this->state = FIREBALL_STATE_FLY;
	SetBoundingBox(FIREBALL_BBOX_WIDTH, FIREBALL_BBOX_HEIGHT);
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += MARIO_GRAVITY;
	vx = FIREBALL_SPEED_X * nx;

	if (state == FIREBALL_STATE_EXPLO || state == -1) vx = vy = 0;

	if (GetTickCount() - explodeStart > 400.0f && state == FIREBALL_STATE_EXPLO) // done explod
	{
		state = -1;
		explodeStart = 0;
		IsCollisionEnabled = false;
	}
	CGameObject::Update(dt, coObjects);
}

void FireBall::Render()
{
	if (state == -1) return;
	animSet->at(state)->Render(x, y);
}

void FireBall::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	CGameObject* go = other->obj;
	ObjectTag tag = go->GetTag();
	if ((tag == ObjectTag::Ground || tag == ObjectTag::GhostPlatform));
	{
		if (other->ny == -1.0f)
		{
			this->vy = -0.8f;
		}
	}

	if (tag == ObjectTag::Solid && nx != 0)
	{
		StartExplode();
	}

	if (tag == ObjectTag::Goomba)
	{
		go->SetState(GOOMBA_STATE_DIE_INSTANT);
		go->SetSpeedX(nx * 0.3f);
		go->SetSpeedY(-0.8f);
		StartExplode();
	}

	if (tag == ObjectTag::Koopas)
	{
		go->SetState(KOOPAS_STATE_DIE);
		StartExplode();
	}
}

void FireBall::StartExplode()
{
	explodeStart = GetTickCount();
	SetBoundingBox(0, 0);
	state = FIREBALL_STATE_EXPLO;
}
