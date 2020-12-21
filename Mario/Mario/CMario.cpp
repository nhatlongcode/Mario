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
				HandleFly(MARIO_FLY_HIGH_FORCE);
			}
		}
		else
		{
			if (canHighJump)
			{
				HandleJump(MARIO_JUMP_HIGH_SPEED); // high but one time jump
				forceJump += MARIO_JUMP_HIGH_SPEED;
			}
			if (abs(forceJump) > MARIO_JUMP_MAX) canHighJump = false;
		}

	}


	if (input->IsKeyDown(DIK_X))
	{
		canHighJump = false;
		if (isMaxSpeed)
		{
			HandleFly(MARIO_FLY_SHORT_FORCE);
			canHighFly = false;
		}
		else if(isGrounded)
		{
			 HandleJump(MARIO_JUMP_SHORT_SPEED);
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

	if (isHoldingKoopas)
	{
		if (Koopas != NULL)
		{
			this->SetState(MARIO_STATE_BRING);
			Koopas->SetPosition(this->x + 40 * nx, this->y + 10);
		}
		else DebugOut(L"NULL KOOPAS\n");
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
	if (keyCode == DIK_S && !isGrounded)
	{
		canHighJump = false;
		canHighFly = false;
	}

	if (keyCode == DIK_A)
	{
		if (Koopas != NULL)
		{
			Koopas->IsCollisionEnabled = true;
			isHoldingKoopas = false;
			Koopas = NULL;
		}
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
		if (abs(forceFly) > MARIO_FLY_MAX) canHighFly = false;
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
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > MARIO_MAX_WALK && (currentSpeedX * nx > 0))
	{
		if (abs(currentSpeedX - ax * dt) > MARIO_MAX_WALK) // chuyen dong cham dan khi ko speed up
		{
			vx = currentSpeedX - ax * dt;
		}
		else vx = MARIO_MAX_WALK * nx;
	}
	else  vx = currentSpeedX + ax * dt;
}

void CMario::HandleRun()
{
	ax = MARIO_ACCELERATION * nx;
	if (abs(vx) > MARIO_MAX_RUN && (currentSpeedX * nx > 0))
	{
		vx = MARIO_MAX_RUN * nx; // handle fly	
	}
	else if (currentSpeedX * nx < 0) vx = currentSpeedX + ax * 3.0f * dt;
	else  vx = currentSpeedX + ax * dt;

	if (abs(vx - MARIO_MAX_RUN * nx) < 0.01f)
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
	auto input = CLocator<IHandleInput>().Get();
	LPGAMEOBJECT go = other->obj;
	//DebugOut(L"asdasd\n");
	if (go->GetTag() == ObjectTag::GhostPlatform || 
		go->GetTag() == ObjectTag::Ground || 
		go->GetTag() == ObjectTag::Solid || 
		go->GetTag() == ObjectTag::QuestionBrick)
	{
		if (other->ny == -1.0f)
		{
			StandingOnGround();
		}

	}
	
	if (go->GetTag() == ObjectTag::QuestionBrick && other->ny == 1.0f)
	{
		go->SetState(1);
		canHighJump = false;
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
		if (koopasState == KOOPAS_STATE_WALK && other->ny == -1.0f)
		{
			go->SetState(KOOPAS_STATE_SHELL);
			vy = -0.5f;
		}
		
		if (koopasState == KOOPAS_STATE_SHELL && (nx != 0))
		{
			if (input->IsKeyDown(DIK_A))
			{
				Koopas = go;
				Koopas->IsCollisionEnabled = false;
				isHoldingKoopas = true;
			}
			else
			{
				this->SetState(MARIO_STATE_KICK);
				go->SetState(KOOPAS_STATE_SPIN);
				go->SetDirection(this->nx);
				vy = -0.5f;
			}
		}
		
	}
}

void CMario::Reset()
{

}

