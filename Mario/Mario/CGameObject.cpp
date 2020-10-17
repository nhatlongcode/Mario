#include "CGameObject.h"


void CGameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CGameObject::SetState(int state)
{
	this->currentState = state;
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
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		vy = -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	}
}

CGameObject::CGameObject()
{
	currentState = MARIO_ANI_IDLE_RIGHT;
	x = y = 0;
	vx = 0.07f;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION anim = CLocator<CAnimationsManager>().Get()->Get(aniId);
	animations.push_back(anim);
}

void CGameObject::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	vy += MARIO_GRAVITY * dt;

	if (y > 100) y = 100;
	//if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) vx = -vx;
}

void CGameObject::Render()
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

	animations.at(ani)->Render(x, y);
}

CGameObject::~CGameObject()
{
}