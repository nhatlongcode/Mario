#include "CSmallMario.h"
#include "MarioDefines.h"


CSmallMario::CSmallMario()
{
	SetTag(ObjectTag::Player);
	SetAnimationSet(MARIO_TYPE_SMALL);
	SetBoundingBox(MARIO_SMALL_BBOX_WIDTH, MARIO_SMALL_BBOX_HEIGHT);
	level = MARIO_TYPE_SMALL;
	state = MARIO_STATE_IDLE;
	IsCollisionEnabled = true;
}
