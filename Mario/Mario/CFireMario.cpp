#include "CFireMario.h"

CFireMario::CFireMario()
{
	SetAnimationSet(MARIO_TYPE_FIRE);
	state = MARIO_STATE_IDLE;
	IsCollisionEnabled = true;
	SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
}
