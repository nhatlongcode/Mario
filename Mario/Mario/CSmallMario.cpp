#include "CSmallMario.h"
#include "MarioDefines.h"


CSmallMario::CSmallMario()
{
	SetAnimationSet(MARIO_TYPE_SMALL);
	state = MARIO_STATE_IDLE;
}
