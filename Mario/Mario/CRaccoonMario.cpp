#include "CRaccoonMario.h"

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
