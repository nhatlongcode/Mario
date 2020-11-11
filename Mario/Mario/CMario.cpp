#include "CMario.h"
#include "IHandleInput.h"
#include "CGoomba.h"
#include "CInput.h"
#include "CGame.h"
#include "CBrick.h"

void CMario::StandingOnGround()
{
	isGrounded = true;
	force = 0.0f;
	if (abs(vx) <= 0.0001f && !isAttacking) SetState(MARIO_STATE_IDLE);
}

CMario::CMario()
{
	level = MARIO_TYPE_SMALL;
	state = MARIO_STATE_IDLE;
	ax = 0.0f;
	animSpeed = 1.0f;
	isGrounded = false;

	force = 0.0f;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += MARIO_GRAVITY;
	this->dt = dt;
	this->currentSpeedX = vx;
	auto input = CLocator<IHandleInput>().Get();
	


	if (input->IsKeyDown(DIK_LEFT) || input->IsKeyDown(DIK_RIGHT))
	{
		if (input->IsKeyDown(DIK_LEFT)) HandleChangeDirection(DIRECTION_LEFT);
		if (input->IsKeyDown(DIK_RIGHT)) HandleChangeDirection(DIRECTION_RIGHT);
		
		if (isGrounded && !isAttacking) SetState(MARIO_STATE_WALK);

		if (input->IsKeyDown(DIK_A))
		{
			HandleRun();
		}
		else
		{
			
			HandleWalk();
		}
	}
	else
	{
		HandleSlowDown();
	}

	if (currentSpeedX * nx < 0 && isGrounded)
	{
		//Handle skid
		SetState(MARIO_STATE_SKID);
	}

	if (input->IsKeyDown(DIK_S) && isGrounded)
	{
		//handle jump short
		HandleJump();
		SetState(MARIO_STATE_JUMP);
	}

	if (vy > 0 && !isGrounded)
	{
		//handle fall, overide for raccon slow fall
		HandleFall();
	}

	if (input->IsKeyDown(DIK_Z))
	{
		HandleAtk();
	}
	CGameObject::Update(dt, coObjects);
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
	DWORD dt = CGame::Instance()->GetDeltaTime();
	if (keyCode == DIK_S)
	{
		//isFinishHighJump = true;
	}

	if (keyCode == DIK_A)
	{
		//isFlying = false;
	}
}

void CMario::HandleMovement()
{

}

void CMario::HandleJump()
{
	if (isFlying && !isAttacking) HandleFly();
	else vy = -1.0f;
	isGrounded = false;
}

void CMario::HandleChangeDirection(int direction)
{
	//if (nx != direction) SetState(MARIO_STATE_SKID);
	nx = direction;
}

void CMario::HandleFly()
{
	auto input = CLocator<IHandleInput>().Get();
	vy = -1.5f;
	SetState(MARIO_STATE_FLY); // set threshold
	DebugOut(L"fly\n");
	isFlying = true;
}

void CMario::HandleFall()
{
	if (isAttacking) return;
	if (isFlying) SetState(MARIO_STATE_FLY);
	else SetState(MARIO_STATE_FALL);
}

void CMario::HandleAtk()
{
}

void CMario::HandleWalk()
{
	isFlying = false;
	float maxWalk = 0.2f;
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > maxWalk && !(currentSpeedX * nx < 0))
	{
		if (currentSpeedX - ax * dt > maxWalk) // chuyen dong cham dan khi ko speed up
		{
			vx = currentSpeedX - ax * dt;
		}
		else vx = maxWalk * nx;
	}
	else  vx = currentSpeedX + ax * dt;
}

void CMario::HandleRun()
{
	float maxRun = 0.5f;
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > maxRun && !(currentSpeedX * nx < 0))
	{
		vx = maxRun * nx; // handle fly	
	}
	else  vx = currentSpeedX + ax * dt;

	if (abs(vx - maxRun * nx) < 0.01f)
	{
		isFlying = true;
		if (!isAttacking) SetState(MARIO_STATE_FLY);
	}
	else isFlying = false;
}

void CMario::HandleSlowDown()
{
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > 0)
	{
		if (!(currentSpeedX * nx < 0)) //slow down with same direction with vx
		{
			if (nx * (currentSpeedX - ax * dt) > 0)
			{
				vx = currentSpeedX - ax * dt;
			}
			else
			{
				vx = 0;
				if (!isAttacking) SetState(MARIO_STATE_IDLE);
			}
		}
		else // slow down when change direction
		{
			if (nx * (currentSpeedX + ax * dt) < 0)
			{
				vx = currentSpeedX + ax * dt;
				//skid
			}
			else
			{
				vx = 0;
				if (!isAttacking) SetState(MARIO_STATE_IDLE);
			}

		}
	}
}

void CMario::HandleInput()
{

	


}

void CMario::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	//DebugOut(L"asdasd\n");
	if (go->GetTag() == ObjectTag::GhostPlatform || go->GetTag() == ObjectTag::Ground || go->GetTag() == ObjectTag::Solid)
	{
		if (other->ny == -1.0f)
		{
			
			StandingOnGround();
		}

	}
	else if (go->GetTag() == ObjectTag::Goomba && other->ny == -1.0f)
	{
		go->SetState(GOOMBA_STATE_DIE);
		vy = -0.5f;
	}
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	//SetPosition(startX, startY);
	SetSpeed(0, 0);
}

