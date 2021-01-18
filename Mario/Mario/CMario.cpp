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
		canOneTimeFly = true;
		forceJump = 0.0f;
		forceFly = 0.0f;
	}
	isFalling = false;
	if (abs(vx) <= 0.0001f && !isAttacking) SetState(MARIO_STATE_IDLE);
}

CMario::CMario()
{
	state = MARIO_STATE_IDLE;
	unTouchable = false;
	isAlive = true;
	SetTag(ObjectTag::Player);
	IsCollisionEnabled = true;
	ax = 0.0f;
	animSpeed = 1.0f;
	isCanFly = false;
	isGrounded = false;
	canHighJump = false;
	forceJump = 0.0f;
}

void CMario::Init()
{
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//DebugOut(L"%d\n", level);
	if (!isAlive)
	{
		diedTime += dt;
		IsCollisionEnabled = false;
		this->SetState(17);
		if (diedTime < 270) vy += -0.05f;
		else vy += 0.05;
		return;
	}

	if (unTouchableStart > 0)
	{
		int time = GetTickCount() - unTouchableStart;
		if (time < 5000)
		{
			unTouchable = true;
			alpha = 128;
		}
		else
		{
			unTouchable = false;
			unTouchableStart = -1;
			alpha = 255;
		}
	}

	vy += MARIO_GRAVITY;
	if (vy > 0.1f) isGrounded = false;
	this->dt = dt;
	this->currentSpeedX = vx;
	auto input = CLocator<IHandleInput>().Get();
	
	/*
	if (input->IsKeyDown(DIK_DOWN))
	{
		vy = 0.3f;
	}
	else if (input->IsKeyDown(DIK_UP))
	{
		vy = -0.3f;
	}
	else vy = 0.0f;
	DebugOut(L"pos X: %f.2\n", x);
	DebugOut(L"pos Y: %f.2\n", y);
	//*/

	//DebugOut(L"%d\n",canHighFly);

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
			//HandleSlowDown();
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
			if (canOneTimeFly)
			{
				HandleFly(MARIO_FLY_HIGH_FORCE);
			}
		}
		else
		{
			if (canHighJump)
			{
				HandleJump(MARIO_JUMP_HIGH_SPEED); // high but one time jump
				forceJump += MARIO_JUMP_HIGH_SPEED * CGame::Instance()->GetTimeScale();
			}
			if (abs(forceJump) > MARIO_JUMP_MAX) canHighJump = false;
		}

	}


	if (input->IsKeyDown(DIK_X))
	{
		canHighJump = false;
		if (!isFalling && isCanFly)
		{
			HandleFly(-0.9f);
			isGrounded = false;
			canOneTimeFly = false;
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
		isFalling = true;
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
			Koopas->SetPosition(this->x + 40 * nx, this->y - 2);
		}
		else DebugOut(L"NULL KOOPAS\n");
	}
	
}


void CMario::Render()
{
	animSet->at(state)->Render(x, y, nx, 1, alpha);
}

void CMario::SetState(int state)
{
	if (this->state == MARIO_STATE_ATK && isAttacking) return;
	CGameObject::SetState(state);
}

void CMario::SetLevel(int level)
{
	//this->level = level;
	CGame::Instance()->GetCurrentScene()->SetPlayer(level, this->x, this->y-24.0f);
}

void CMario::LevelUp()
{
	if (level == MARIO_TYPE_SMALL)
	{
		SetLevel(MARIO_TYPE_SUPER);
	}
	else if (level == MARIO_TYPE_SUPER)
	{
		SetLevel(MARIO_TYPE_RACCOON);
		
	}
	else if (level == MARIO_TYPE_RACCOON)
	{

	}
}

void CMario::LevelDown()
{
	if (level == MARIO_TYPE_SMALL)
	{
		Die();
	}
	else if (level == MARIO_TYPE_SUPER)
	{
		CGame::Instance()->GetCurrentScene()->GetPlayer(MARIO_TYPE_SMALL)->StartUntouchable();
		SetLevel(MARIO_TYPE_SMALL);
		//DebugOut(L"big to small\n");
	}
	else if (level == MARIO_TYPE_RACCOON)
	{
		CGame::Instance()->GetCurrentScene()->GetPlayer(MARIO_TYPE_SUPER)->StartUntouchable();
		SetLevel(MARIO_TYPE_SUPER);
		//DebugOut(L"rac to big\n");
	}
}

void CMario::Die()
{
	SetLevel(MARIO_TYPE_SMALL);
	isAlive = false;
}

void CMario::StartUntouchable()
{
	unTouchableStart = GetTickCount();
	unTouchable = true;
}


void CMario::OnKeyDown(int keyCode)
{

}

void CMario::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_S && !isGrounded)
	{
		canHighJump = false;
		canOneTimeFly = false;
	}

	if (keyCode == DIK_A)
	{
		if (Koopas != NULL)
		{
			Koopas->IsCollisionEnabled = true;
			this->SetState(MARIO_STATE_KICK);
			Koopas->SetSpeedY(0.0f);
			Koopas->SetState(KOOPAS_STATE_SPIN);
			Koopas->SetDirection(this->nx);
			//Koopas->SetPosition()
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
	else if (input->IsKeyDown(DIK_S) && canOneTimeFly)
	{
		vy = flyForce;
		forceFly += flyForce;
		isFlying = true;
		isGrounded = false;
		if (abs(forceFly) > MARIO_FLY_MAX) canOneTimeFly = false;
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
	auto input = CLocator<IHandleInput>().Get();
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
		if (input->IsKeyDown(DIK_X)) isCanFly = true;
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
	int countDead = 0;
	auto input = CLocator<IHandleInput>().Get();
	LPGAMEOBJECT go = other->obj;
	ObjectTag tag = go->GetTag();
	//DebugOut(L"asdasd\n");
	if (tag == ObjectTag::GhostPlatform || 
		tag == ObjectTag::Ground ||
		tag == ObjectTag::Solid ||
		tag == ObjectTag::QuestionBrick ||
		tag == ObjectTag::Pipe || 
		tag == ObjectTag::BreakableBrick)
	{
		if (other->ny == -1.0f)
		{
			StandingOnGround();
		}

	}
	if (unTouchable) return;
	
	if (tag == ObjectTag::QuestionBrick && other->ny == 1.0f)
	{
		go->SetState(0);
		canHighJump = false;
	}


	if (tag == ObjectTag::Goomba)
	{
		if (other->ny == -1.0f)
		{
			go->SetState(GOOMBA_STATE_DIE);
			vy = -0.5f;
		}
		else if (abs(other->nx) == 1)
		{
			LevelDown();
		}
	}

	if (tag == ObjectTag::Koopas)
	{
		int koopasState;
		go->GetState(koopasState);

		if (koopasState == KOOPAS_STATE_WALK)
		{
			if (other->ny == -1.0f)
			{
				go->SetState(KOOPAS_STATE_SHELL);
				vy = -0.5f;
			}
			else if (abs(other->nx) == 1)
			{
				LevelDown();
			}
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

		if (koopasState == KOOPAS_STATE_SPIN)
		{
			if (abs(other->nx) == 1)
			{
				LevelDown();
			}
		}
		
	}


	if (tag == ObjectTag::KoopasFly)
	{
		int koopasState;
		go->GetState(koopasState);
		if (koopasState == 0)
		{
			if (other->ny == -1.0f)
			{
				go->SetState(1);
				vy = -0.5f;
			}
			else if (abs(other->nx) == 1)
			{
				LevelDown();
			}
		}

		if (koopasState == 1)
		{
			if (other->ny == -1.0f)
			{
				go->SetState(2);
				vy = -0.5f;
			}
			else if (abs(other->nx) == 1)
			{
				LevelDown();
			}
		}

		if (koopasState == 2 && (nx != 0))
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
				go->SetState(3);
				go->SetDirection(this->nx);
				vy = -0.5f;
			}
		}

		if (koopasState == 3)
		{
			if (abs(other->nx) == 1)
			{
				LevelDown();
			}
		}

	}

	if (tag == ObjectTag::GoombaFly)
	{
		int goomflyState;
		go->GetState(goomflyState);
		if (goomflyState == 0) //fly state
		{
			if (other->ny = -1.0f)
			{
				go->SetState(1);
				vy = -0.5f;
			}
			else
			{
				LevelDown();
			}
		}
		else if (goomflyState == 1) //walk state
		{
			if (other->ny == -1.0f)
			{
				go->SetState(2);
				vy = -0.5f;
			}
			else
			{
				LevelDown();
			}
		}
		
	}

	if (tag == ObjectTag::Buff)
	{
		vy = -0.1f;
		go->SetState(-1);
		LevelUp();
	}

	if (tag == ObjectTag::Venus)
	{
		LevelDown();
	}

	if (tag == ObjectTag::Pipe && (other->ny == -1.0f || other->ny == 1.0f))
	{
		go->SetState(1);
	}
	
	if (tag == ObjectTag::FireFromEnemy)
	{
		DebugOut(L"detect fire from venus");
		LevelDown();
	}

	if (tag == ObjectTag::BreakableBrick && other->ny == 1.0f)
	{
		go->SetState(-1);
	}
	
}

void CMario::Reset()
{
	isCanFly = false;
	isGrounded = false;
	canHighJump = false;
	isAlive = true;
	unTouchable = false;
	unTouchableStart = -1;
	IsCollisionEnabled = true;
	vx = vy = 0.0f;
	forceJump = 0.0f;
}

