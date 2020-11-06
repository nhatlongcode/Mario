#include "CMario.h"
#include "IHandleInput.h"
#include "CGoomba.h"
#include "CInput.h"
#include "CGame.h"
#include "CBrick.h"

void CMario::StandingOnGround()
{
	isGrounded = true;
	isFalling = false;
	isJumping = false;
	isFlying = false;
	force = 0.0f;
	isHighJump = false;

}

CMario::CMario()
{
	level = MARIO_TYPE_FIRE;
	state = MARIO_STATE_ATK;
	isGrounded = false;
	isMaxSpeed = false;
	isFlying = true;
	isHighJump = false;
	isFinishHighJump = true;
	force = 0.0f;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	auto input = CLocator<IHandleInput>().Get();

	if (!isGrounded)
	{
		if (vy > 0)
		{
			HandleFall();
		}
	}

	HandleMovement();
	if (!isMaxSpeed) HandleJump();

	else
	{
		if (!input->IsKeyDown(DIK_S)) isFinishHighJump = true;
	}



	vy += MARIO_GRAVITY;
	



	CGameObject::Update(dt, coObjects);
	//DebugOut(L"isFinishHighJump %d\n", isFinishHighJump);
	//DebugOut(L"isHighJump %d\n", isHighJump);
	//DebugOut(L"isGrounded %d\n", isGrounded);
	//DebugOut(L"force %.2f\n", force);
}


void CMario::Render()
{
	animSet->at(state)->Render(x, y, nx);
	CGameObject::RenderCollisionBox();
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
	DWORD dt = CGame::Instance()->GetDeltaTime();
	if (keyCode == DIK_S)
	{
		isFinishHighJump = true;
	}
}

void CMario::HandleMovement()
{
	DWORD dt = CGame::Instance()->GetDeltaTime();
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_RIGHT) || input->IsKeyDown(DIK_LEFT))
	{
		if (input->IsKeyDown(DIK_RIGHT)) nx = DIRECTION_RIGHT;
		else nx = DIRECTION_LEFT;
		
		if (isGrounded && !isJumping)
		{
			if (input->IsKeyDown((DIK_A)))
			{
				SetState(MARIO_STATE_WALK);
				a.x = MARIO_ACCELERATION * nx;
				isRunning = true;
				DebugOut(L"RUNNNN\n");

				if (abs(vx) > MARIO_RUNNING_SPEED)
				{
					isMaxSpeed = true;
					HandleRun();
				}
			}
			else
			{
				SetState(MARIO_STATE_WALK);
				SetSpeedX(MARIO_WALKING_SPEED * nx);
				isMaxSpeed = false;
				isRunning = false;
			}
		}
	}
	else
	{
		SetSpeedX(MARIO_IDLE_SPEED);
		a.x = 0;
		if (isGrounded && !isJumping && !isFalling) SetState(MARIO_STATE_IDLE);
	}
}

void CMario::HandleJump()
{
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_X) && !isFalling && isGrounded)
	{
		SetSpeedY(MARIO_JUMP_SHORT_SPEED); //jump short
		isGrounded = false;
		isJumping = true;
		SetState(MARIO_STATE_JUMP);
	}
	else if (input->IsKeyDown(DIK_S) && !isFalling && force > -MARIO_MAX_JUMP && (isGrounded || isHighJump) && (isFinishHighJump ^ isHighJump))
	{
		SetSpeedY(MARIO_JUMP_HIGH_SPEED);
		force += vy;
		isJumping = true;
		isGrounded = false;
		isFinishHighJump = false;
		isHighJump = true;
		SetState(MARIO_STATE_JUMP);
		//DebugOut(L"LOLOLOLOL");
	}
}

void CMario::HandleFly()
{

	SetSpeedY(MARIO_FLY_SPEED);
}

void CMario::HandleFall()
{
	isFalling = true;
	isJumping = false;
	force = 0;
	DebugOut(L"FALL\n");
	SetState(MARIO_STATE_FALL);
}

void CMario::HandleRun()
{
	auto input = CLocator<IHandleInput>().Get();
	vx = MARIO_RUNNING_SPEED * nx;
	SetState(MARIO_STATE_RUN);
	if (input->IsKeyDown(DIK_S))
	{
		SetState(MARIO_STATE_FLY);
		isFlying = true;
		HandleFly();
	}
}

void CMario::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	//DebugOut(L"asdasd\n");
	if (go->GetTag() == ObjectTag::GhostPlatform || go->GetTag() == ObjectTag::Solid || go->GetTag() == ObjectTag::Ground)
	{
		if (other->ny == -1.0f)
		{
			
			StandingOnGround();
		}

	}
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	//SetPosition(startX, startY);
	SetSpeed(0, 0);
}

