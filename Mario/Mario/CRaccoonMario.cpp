#include "CRaccoonMario.h"
#include "CGame.h"
CRaccoonMario::CRaccoonMario()
{
	SetAnimationSet(MARIO_TYPE_RACCOON);
	state = MARIO_STATE_IDLE;
	IsCollisionEnabled = true;
	SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
}

void CRaccoonMario::HandleFall()
{
	CMario::HandleFall();
	vy -= 0.01f;
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
		animSet->at(MARIO_STATE_ATK)->Render(x, y, nx, attackBegin, attackTime);
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
}
