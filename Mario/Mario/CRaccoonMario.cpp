#include "CRaccoonMario.h"
#include "CGame.h"
CRaccoonMario::CRaccoonMario()
{
	SetTag(ObjectTag::Player);
	SetAnimationSet(MARIO_TYPE_RACCOON);
	state = MARIO_STATE_IDLE;
	level = MARIO_TYPE_RACCOON;
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
	if (!isCanFly) return;
	SetState(MARIO_STATE_FLY);
	auto input = CLocator<IHandleInput>().Get();

	if (input->IsKeyDown(DIK_X))
	{
		vy = -0.25f;
		isFlying = true;
		isGrounded = false;
	}

}

void CRaccoonMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario::Update(dt, coObjects);
	tail->SetPosition(this->x + 35 * nx, this->y + 20);
	tail->Update(dt, coObjects);
	if (attackBegin > 0)
	{
		attackBegin += dt;

		if (attackBegin > 100 && attackBegin < 200)
		{
			tail->isHiting = true;
		}
		else tail->isHiting = false;

		if (attackBegin > attackTime)
		{
			attackBegin = -1;
			isAttacking = false;
			tail->isHiting = false;
		}
	}

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

