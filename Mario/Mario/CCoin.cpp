#include "CCoin.h"

CCoin::CCoin()
{
	SetBoundingBox(0, 0);
	SetAnimationSet(30002);
	SetState(0);
}

void CCoin::SetState(int state)
{

	this->state = state;
}

void CCoin::Render()
{
	animSet->at(state)->Render(this->x, this->y);
}
