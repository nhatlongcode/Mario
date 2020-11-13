#include "CFireMario.h"
#include "CGame.h"

void CFireMario::HandleAtk()
{
	auto dt = CGame::Instance()->GetDeltaTime();
	if (attackBegin == -1)
	{
		// atk
		attackBegin = dt;
		isAttacking = true;
		int atkState;
		if (isGrounded) atkState = MARIO_STATE_ATK;
		else atkState = MARIO_STATE_FLY_ATK;
		SetState(atkState);
		animSet->at(atkState)->Render(x, y, nx, attackBegin, attackTime);
	}
}

CFireMario::CFireMario()
{
	SetAnimationSet(MARIO_TYPE_FIRE);
	state = MARIO_STATE_IDLE;
	IsCollisionEnabled = true;
	SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
}

void CFireMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
}
