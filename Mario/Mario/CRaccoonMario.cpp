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
	if (attackStart == -1)
	{
		// atk
		attackStart = dt;
		isAttacking = true;
		SetState(MARIO_STATE_ATK);
		animSet->at(MARIO_STATE_ATK)->Render(x, y, nx, attackStart, marioAttackTime);
	}

}

void CRaccoonMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario::Update(dt, coObjects);
	if (attackStart > 0)
	{
		attackStart += dt;
		if (attackStart > marioAttackTime)
		{
			attackStart = -1;
			isAttacking = false;
		}
	
	}
	DebugOut(L"at %d", attackStart);
}
