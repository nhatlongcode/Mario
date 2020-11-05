#include "CSmallMario.h"
#include "MarioDefines.h"


CSmallMario::CSmallMario()
{
	SetAnimationSet(MARIO_TYPE_SMALL);
	SetBoundingBox(MARIO_SMALL_BBOX_WIDTH, MARIO_SMALL_BBOX_HEIGHT);
	state = MARIO_STATE_IDLE;
}
