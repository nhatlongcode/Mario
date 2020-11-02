#include "CMario.h"
#include "IHandleInput.h"
#include "CInput.h"

CMario::CMario()
{
	level = MARIO_TYPE_FIRE;
	state = MARIO_STATE_ATK;
	isGrounded = false;
	isHighJump = false;
	isJumping = false;
	isFinishHighJump = true;
	force = 0.0f;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{

	auto input = CLocator<IHandleInput>().Get();
	ICommand* command = input->HandleInput();



	if (y > 300) // fall down to ground
	{

		isGrounded = true;
		isFalling = false;
		isJumping = false;
		force = 0.0f;
		isHighJump = false;
		vy = 0;
		y = 300.0f;
	}
	
	if (command != NULL)
	{
		command->Execute(this);
	}
	else
	{
		if (!isGrounded)
		{
			if (vy > 0)
			{
				isFalling = true;
				isJumping = false;
				force = 0;
				SetState(MARIO_STATE_FALL);
			}
		}
		else
		{
			SetState(MARIO_STATE_IDLE);
			SetSpeed(0.0f, 0.0f);
			if (!input->IsKeyDown(DIK_S)) isFinishHighJump = true;
		}
	}


	vy += MARIO_GRAVITY;
	

	CGameObject::Update(dt);
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
		isFinishHighJump = true;
	}
}

void CMario::HandleMovement()
{
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_RIGHT))
	{
		nx = DIRECTION_RIGHT;
		SetSpeedX(0.19f);
		if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
	}
	else if (input->IsKeyDown(DIK_LEFT))
	{
		nx = DIRECTION_LEFT;
		SetSpeedX(-0.19f);
		if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
	}
	else
	{
		SetSpeedX(0);
		if (isGrounded && !isJumping && !isFalling) SetState(MARIO_STATE_IDLE);
	}
}

void CMario::HandleJump()
{
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_X) && !isFalling && isGrounded)
	{
		SetSpeedY(-0.8f); //jump short
		isGrounded = false;
		isJumping = true;
		SetState(MARIO_STATE_JUMP);
	}
	else if (input->IsKeyDown(DIK_S) && !isFalling && force > -9.0f && (isGrounded || isHighJump) && (isFinishHighJump ^ isHighJump))
	{
		SetSpeedY(-0.5f);
		force += vy;
		isJumping = true;
		isGrounded = false;
		isFinishHighJump = false;
		isHighJump = true;
		SetState(MARIO_STATE_JUMP);
		DebugOut(L"LOLOLOLOL");
	}
}

void CMario::ShortJump()
{
	if (!isFalling && isGrounded)
	SetSpeedY(-0.8f); //jump short
	isGrounded = false;
	isJumping = true;
	SetState(MARIO_STATE_JUMP);
}

void CMario::Idle()
{
	SetState(MARIO_STATE_IDLE);
}

void CMario::Walk(int direction)
{
	nx = direction;
	SetSpeedX(0.19f * (float)direction);
	if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	//SetPosition(startX, startY);
	SetSpeed(0, 0);
}

