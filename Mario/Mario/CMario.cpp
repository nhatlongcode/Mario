#include "CMario.h"
#include "IHandleInput.h"
#include "CGoomba.h"
#include "CInput.h"
#include "CGame.h"
#include "CBrick.h"

void CMario::StandingOnGround()
{
	isGrounded = true;
	isFlying = false;
	auto input = CLocator<IHandleInput>().Get();
	if (!input->IsKeyDown(DIK_S))
	{
		canHighJump = true;
		canHighFly = true;
		forceJump = 0.0f;
		forceFly = 0.0f;
	}
	if (abs(vx) <= 0.0001f && !isAttacking) SetState(MARIO_STATE_IDLE);
}

CMario::CMario()
{
	level = MARIO_TYPE_SMALL;
	state = MARIO_STATE_IDLE;
	IsCollisionEnabled = true;
	ax = 0.0f;
	animSpeed = 1.0f;
	isGrounded = false;
	canHighJump = true;
	forceJump = 0.0f;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += MARIO_GRAVITY;
	if (vy > 0.1f) isGrounded = false;
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
		SetState(MARIO_STATE_SKID);
	}

	if (input->IsKeyDown(DIK_S))
	{
		if (isMaxSpeed)
		{
			if (canHighFly)
			{
				HandleFly(-0.5f);
			}
		}
		else
		{
			if (canHighJump)
			{
				HandleJump(-0.5f); // high but one time jump
				forceJump += -0.5f;
			}
			if (abs(forceJump) > 10.0f) canHighJump = false;
		}

	}


	if (input->IsKeyDown(DIK_X))
	{
		canHighJump = false;
		if (isMaxSpeed)
		{
			HandleFly(-0.8f);
			canHighFly = false;
		}
		else if(isGrounded)
		{
			 HandleJump(-0.8f);
			 canHighJump = false;
		}
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
	if (this->state == MARIO_STATE_ATK && isAttacking) return;
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
	auto input = CLocator<IHandleInput>().Get();
	if (keyCode == DIK_S && !isGrounded)
	{
		canHighJump = false;
		canHighFly = false;
	}
}

void CMario::HandleMovement()
{

}

void CMario::HandleJump(float jumpForce)
{
	SetState(MARIO_STATE_JUMP);
	vy = jumpForce;
	isGrounded = false;
}

void CMario::HandleChangeDirection(int direction)
{
	nx = direction;
}

void CMario::HandleFly(float flyForce)
{
	SetState(MARIO_STATE_FLY);
	auto input = CLocator<IHandleInput>().Get();
	

	if (input->IsKeyDown(DIK_X) && isGrounded)
	{
		vy = flyForce;
		isFlying = true;
		isGrounded = false;
	}
	else if (input->IsKeyDown(DIK_S) && canHighFly)
	{
		vy = flyForce;
		forceFly += flyForce;
		isFlying = true;
		isGrounded = false;
		if (abs(forceFly) > 15.0f) canHighFly = false;
	}

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
	isMaxSpeed = false;
	float maxWalk = 0.2f;
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > maxWalk && (currentSpeedX * nx > 0))
	{
		if (abs(currentSpeedX - ax * dt) > maxWalk) // chuyen dong cham dan khi ko speed up
		{
			vx = currentSpeedX - ax * dt;
		}
		else vx = maxWalk * nx;
	}
	else  vx = currentSpeedX + ax * dt;
}

void CMario::HandleRun()
{
	float maxRun = 0.7f;
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > maxRun && (currentSpeedX * nx > 0))
	{
		vx = maxRun * nx; // handle fly	
	}
	else if (currentSpeedX * nx < 0) vx = currentSpeedX + ax * 3.0f * dt;
	else  vx = currentSpeedX + ax * dt;

	if (abs(vx - maxRun * nx) < 0.01f)
	{
		isMaxSpeed = true;
		if (!isAttacking && isGrounded) SetState(MARIO_STATE_RUN);
	}
	else isMaxSpeed = false;
}

void CMario::HandleSlowDown()
{
	ax = MARIO_ACCELERATION * 2.0f * nx;
	if (abs(vx) > 0)
	{
		SetState(MARIO_STATE_WALK);
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
	
	if (go->GetTag() == ObjectTag::Goomba && other->ny == -1.0f)
	{
		go->SetState(GOOMBA_STATE_DIE);
		vy = -0.5f;
	}

	if (go->GetTag() == ObjectTag::Koopas)
	{
		int koopasState;
		go->GetState(koopasState);
		if (koopasState == KOOPAS_STATE_WALKING && other->ny == -1.0f)
		{
			go->SetState(KOOPAS_STATE_SHELL);
			vy = -0.5f;
		}
		
		if (koopasState == KOOPAS_STATE_SHELL && (nx != 0))
		{
			this->SetState(MARIO_STATE_KICK);
			go->SetState(KOOPAS_STATE_SPIN);
			vy = -0.5f;
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

