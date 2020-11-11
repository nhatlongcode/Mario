#include "CFireMario.h"

void CFireMario::HandleAtk()
{
	SetState(MARIO_STATE_ATK);
	DebugOut(L"fire atk\n");
}

CFireMario::CFireMario()
{
	SetAnimationSet(MARIO_TYPE_FIRE);
	state = MARIO_STATE_IDLE;
	IsCollisionEnabled = true;
	SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
}
