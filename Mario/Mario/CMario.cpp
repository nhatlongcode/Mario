#include "CMario.h"
#include "IHandleInput.h"
#include "CInput.h"

CMario::CMario()
{
	level = MARIO_TYPE_FIRE;
	state = MARIO_STATE_ATK;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	auto input = CLocator<IHandleInput>().Get();

	if (input->IsKeyDown(DIK_X))
	{
		SetSpeed(0, 100.0f);
		SetState(MARIO_STATE_JUMP);
	}

	if (input->IsKeyDown(DIK_RIGHT))
	{
		nx = DIRECTION_RIGHT;
		SetState(MARIO_STATE_WALK);
	}
	else if (input->IsKeyDown(DIK_LEFT))
	{
		nx = DIRECTION_LEFT;
		SetState(MARIO_STATE_WALK);
	}
	else
	{
	//	SetState(MARIO_STATE_IDLE);
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
	//animSet->at(currentState)->Render(x, y);
	//CLocator<IAnimsManager>().Get()->Get(level + state)->Render(300, 300);
	animSet->at(state)->Render(x, y, nx);
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

void CMario::OnKeyDown(int keyCode)
{
	DebugOut(L"MARIO KEY DOWN: %d\n", keyCode);
}

void CMario::OnKeyUp(int keyCode)
{
	DebugOut(L"MARIO KEY UP: %d\n", keyCode);
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	//SetPosition(startX, startY);
	SetSpeed(0, 0);
}

