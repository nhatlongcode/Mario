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
	vy += MARIO_GRAVITY;

	if (!isGrounded)
	{
	}
	


	auto input = CLocator<IHandleInput>().Get();

	if (input->IsKeyDown(DIK_LEFT) || input->IsKeyDown(DIK_RIGHT))
	{
		if (input->IsKeyDown(DIK_LEFT)) HandleChangeDirection(DIRECTION_LEFT);
		if (input->IsKeyDown(DIK_RIGHT)) HandleChangeDirection(DIRECTION_RIGHT);


		if (input->IsKeyDown(DIK_A))
		{
			//a.x = 0.003f * nx; // tai sao no chi tang 1 luc ma ko tang nua hay la no tang cham qua
			a.x = 0.0005f * nx;
		}
		else HandleWalk();
	}
	else 
	{
		
		if (nx * vx <= 0)
		{
			vx = 0;
			a.x = 0;
			SetState(MARIO_STATE_IDLE);
		}
		else
		{
			a.x = MARIO_ACCELERATION * 3 * -nx;

		}
	}

	if (input->IsKeyDown(DIK_S))
	{
		//HandleJump();
		vy = MARIO_JUMP_HIGH_SPEED;
	}


	if (vx != 0) SetState(MARIO_STATE_WALK);

	

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
	vx = MARIO_WALKING_SPEED * nx;
	SetState(MARIO_STATE_WALK);
}

void CMario::HandleRun()
{

}

void CMario::HandleInput()
{

	


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

