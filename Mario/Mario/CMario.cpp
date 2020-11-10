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
	ax = 0.0f;
	animSpeed = 1.0f;
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
	vy += MARIO_GRAVITY;
	float currentSpeed = vx;
	float maxWalk = 0.2f;
	float maxRun = 0.5f;
	auto input = CLocator<IHandleInput>().Get();
	

	if (input->IsKeyDown(DIK_LEFT) || input->IsKeyDown(DIK_RIGHT))
	{
		if (input->IsKeyDown(DIK_LEFT)) HandleChangeDirection(DIRECTION_LEFT);
		if (input->IsKeyDown(DIK_RIGHT)) HandleChangeDirection(DIRECTION_RIGHT);
		
		SetState(MARIO_STATE_WALK);

		if (input->IsKeyDown(DIK_A))
		{
			ax = 0.0003f;
			if (abs(vx) > maxRun && !(currentSpeed * nx < 0))
			{
				vx = maxRun * nx;
			}
			else  vx = currentSpeed + ax * nx * dt;
		}
		else
		{
			ax = 0.0003f; 
			if (abs(vx) > maxWalk && !(currentSpeed * nx < 0))
			{
				if (currentSpeed + ax * -nx * dt > maxWalk) // chuyen dong cham dan khi ko speed up
				{
					vx = currentSpeed + ax * -nx * dt;
				}
				else vx = maxWalk * nx;
			}
			else  vx = currentSpeed + ax * nx * dt;
		}

	}
	else if (isGrounded)
	{
		ax = 0.0005f ;
		if (abs(vx) > 0)
		{
			if (!(currentSpeed * nx < 0))
			{
				if (nx * (currentSpeed - ax * nx * dt) > 0)
				{
					vx = currentSpeed - ax* nx * dt;
				}
				else
				{
					vx = 0;
					SetState(MARIO_STATE_IDLE);
				}
			}
			else
			{
				if (nx == 1)
				{
					if (currentSpeed + 0.0005f * nx * dt < 0) vx = currentSpeed + 0.0005f * nx * dt;
					else
					{
						vx = 0;
						SetState(MARIO_STATE_IDLE);
					}
				}
				else if (nx == -1)
				{
					if (currentSpeed + 0.0005f * nx * dt > 0) vx = currentSpeed + 0.0005f * nx * dt;
					else
					{
						vx = 0;
						SetState(MARIO_STATE_IDLE);
					}
				}
			}
		}


	}

	if (input->IsKeyDown(DIK_S) && isGrounded)
	{
		vy = MARIO_JUMP_SHORT_SPEED;
		isGrounded = false;
	}



	CGameObject::Update(dt, coObjects);



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

	if (keyCode == DIK_A)
	{
		isFlying = false;
	}
}

void CMario::HandleMovement()
{

}

void CMario::HandleJump()
{


}

void CMario::HandleChangeDirection(int direction)
{
	//if (nx != direction) SetState(MARIO_STATE_SKID);
	nx = direction;
}

void CMario::HandleFly()
{

}

void CMario::HandleFall()
{

}

void CMario::HandleAtk()
{
}

void CMario::HandleWalk()
{
	vx = 0.105f * nx;
	SetState(MARIO_STATE_WALK);
}

void CMario::HandleRun(float currentSpeed, DWORD dt)
{
	vx = currentSpeed + 0.0005f * dt * nx;
}

void CMario::HandleInput()
{

	


}

void CMario::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	//DebugOut(L"asdasd\n");
	if (go->GetTag() == ObjectTag::GhostPlatform || go->GetTag() == ObjectTag::Ground || go->GetTag() == ObjectTag::Ground)
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

