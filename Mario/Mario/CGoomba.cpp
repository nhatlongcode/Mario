#include "CGoomba.h"


void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	vy += MARIO_GRAVITY;
	CGameObject::Update(dt, coObjects);
}

void CGoomba::Render()
{
	animSet->at(state)->Render(x, y, nx);
}



CGoomba::CGoomba()
{
	SetBoundingBox(GOOMBA_BBOX_WIDTH, GOOMBA_BBOX_HEIGHT);
	SetAnimationSet(GOOMBA_ANIMSET);
	SetState(GOOMBA_STATE_WALKING);
	IsCollisionEnabled = true;
	tag = ObjectTag::Goomba;
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE - 1.3f;
		vx = 0;
		vy = 0;
		IsCollisionEnabled = false;
		break;
	case GOOMBA_STATE_DIE_INSTANT:
		vy = -0.8f;
		vx = 0;
		IsCollisionEnabled = false;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}
