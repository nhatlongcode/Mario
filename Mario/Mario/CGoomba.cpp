#include "CGoomba.h"
#include "CGame.h"

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == GOOMBA_STATE_WALKING)
	{
		vx = nx * GOOMBA_WALKING_SPEED;
	}

	vy += MARIO_GRAVITY;
	CGameObject::Update(dt, coObjects);
}

void CGoomba::Render()
{
	animSet->at(state)->Render(x, y, nx,1,alpha);
}



CGoomba::CGoomba()
{
	SetBoundingBox(GOOMBA_BBOX_WIDTH, GOOMBA_BBOX_HEIGHT);
	SetAnimationSet(GOOMBA_ANIMSET);
	SetState(GOOMBA_STATE_WALKING);
	IsCollisionEnabled = true;
	nx = DIRECTION_LEFT;
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
		int marionx;
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(marionx);
		SetSpeedX(marionx * 0.3f);
		SetSpeedY(-0.8f);
		IsCollisionEnabled = false;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}
