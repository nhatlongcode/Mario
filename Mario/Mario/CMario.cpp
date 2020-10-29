#include "CMario.h"
#include "IHandleInput.h"
#include "CInput.h"

CMario::CMario()
{
	level = MARIO_TYPE_FIRE;
	state = MARIO_STATE_ATK;
	isGrounded = false;
	isHighJump = false;
	force = 0.0f;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	auto input = CLocator<IHandleInput>().Get();

	if (input->IsKeyDown(DIK_RIGHT))
	{
		nx = DIRECTION_RIGHT;
		SetSpeedX(0.5f);
		if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
	}
	else if (input->IsKeyDown(DIK_LEFT))
	{
		nx = DIRECTION_LEFT;
		SetSpeedX(-0.5f);
		if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
	}
	else
	{
		SetSpeedX(0);
		if (isGrounded && !isJumping && !isFalling) SetState(MARIO_STATE_IDLE);
	}
//-----------------------------------------------------------------------------------------------
	if (input->IsKeyDown(DIK_X) && !isFalling && isGrounded)
	{
		SetSpeedY(-0.8f); //jump short
		isGrounded = false;
		isJumping = true;
		SetState(MARIO_STATE_JUMP);
	}
	else if (input->IsKeyDown(DIK_S) && !isFalling && force > -9.0f && (isGrounded || isHighJump))
	{
		SetSpeedY(-0.5f);
		force += vy;
		isJumping = true;
		isGrounded = false;
		isHighJump = true;
		SetState(MARIO_STATE_JUMP);
	}
// --------------------------------------------------------------------------------------------------
	if (!isGrounded)
	{
		if (vy > 0)
		{
			isFalling = true;
			force = 0;
			SetState(MARIO_STATE_FALL);
		}
	}

	vy += MARIO_GRAVITY;
	
	if (y > 300)
	{
		isGrounded = true;
		isFalling = false;
		isJumping = false;
		vy = 0; y = 300.0f;
	}
	CGameObject::Update(dt);
	DebugOut(L"%d\n", isGrounded);
}


void CMario::Render()
{
	animSet->at(state)->Render(x, y, nx);
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	
}

void CMario::SetLevel(int level)
{
	this->level = level;
}

void CMario::OnKeyDown(int keyCode)
{
	
}

void CMario::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_S)
	{
		force = 0.0f;
		isHighJump = false;
	}
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	//SetPosition(startX, startY);
	SetSpeed(0, 0);
}

