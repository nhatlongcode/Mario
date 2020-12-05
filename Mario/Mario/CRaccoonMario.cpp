#include "CRaccoonMario.h"
#include "CGame.h"
CRaccoonMario::CRaccoonMario()
{
	SetAnimationSet(MARIO_TYPE_RACCOON);
	state = MARIO_STATE_IDLE;
	tail = new Tail();
	IsCollisionEnabled = true;
	SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
}

void CRaccoonMario::HandleFall()
{
	//CMario::HandleFall();
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_X))
	{
		vy = MARIO_FALL_RACCOON;

	}
	SetState(MARIO_STATE_FALL);
}

void CRaccoonMario::HandleAtk()
{
	auto dt = CGame::Instance()->GetDeltaTime();
	if (attackBegin == -1)
	{
		// atk
		attackBegin = dt;
		isAttacking = true;
		SetState(MARIO_STATE_ATK);
	}

}

void CRaccoonMario::HandleFly(float flyForce)
{
	SetState(MARIO_STATE_FLY);
	auto input = CLocator<IHandleInput>().Get();

	if (input->IsKeyDown(DIK_X))
	{
		vy = flyForce;
		isFlying = true;
		isGrounded = false;
	}

}

void CRaccoonMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario::Update(dt, coObjects);
	if (attackBegin > 0)
	{
		attackBegin += dt;
		if (attackBegin > attackTime)
		{
			attackBegin = -1;
			isAttacking = false;
		}
	
	}
	tail->SetPosition(this->x + 34 * nx, this->y + 20);
	tail->Update(dt, coObjects);
}

void CRaccoonMario::RenderCollisionBox()
{
	CGameObject::RenderCollisionBox();
	
}

void CRaccoonMario::Render()
{

	CMario::Render();
	tail->Render();
}

