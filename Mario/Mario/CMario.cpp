#include "CMario.h"
#include "IHandleInput.h"
#include "CInput.h"

CMario::CMario(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;
	SetState(0);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_RIGHT))
	{
		SetState(MARIO_ANI_WALK);
	}

	vy += MARIO_GRAVITY;
	
	if (y > 300)
	{
		vy = 0; y = 300.0f;
	}
	CGameObject::Update(dt);
}


void CMario::Render()
{
	/*//
	int ani = -1;
	if (vx == 0)
	{
		if (nx > 0) ani = MARIO_ANI_IDLE_RIGHT;
		else ani = MARIO_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = MARIO_ANI_WALKING_RIGHT;
	else ani = MARIO_ANI_WALKING_LEFT;

	//*/
	animSet->at(currentState)->Render(x, y);
	//CLocator<IAnimsManager>().Get()->Get(MARIO_TYPE_FIRE + MARIO_ANI_CLIMB)->Render(300, 300);
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	
	
	/*
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
	*/
}

void CMario::SetLevel(int level)
{
	this->level = level;
}

void CMario::Reset()
{
	SetState(MARIO_ANI_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(startX, startY);
	SetSpeed(0, 0);
}

