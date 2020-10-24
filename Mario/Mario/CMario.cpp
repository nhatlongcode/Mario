#include "CMario.h"

CMario::CMario(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;
}

void CMario::Update(DWORD dt)
{
	vy += MARIO_GRAVITY;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}
	CGameObject::Update(dt);

}

void CMario::Render()
{
	int ani = -1;
	if (vx == 0)
	{
		if (nx > 0) ani = MARIO_ANI_IDLE_RIGHT;
		else ani = MARIO_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = MARIO_ANI_WALKING_RIGHT;
	else ani = MARIO_ANI_WALKING_LEFT;

	animSet->at(ani)->Render(x, y);
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMPING:
		vy += -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CMario::SetLevel(int level)
{
	this->level = level;
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(startX, startY);
	SetSpeed(0, 0);
}

