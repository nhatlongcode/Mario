#include "CQuestionBrick.h"

CQuestionBrick::CQuestionBrick()
{
	SetBoundingBox(48, 48);
	SetAnimationSet(30002);
	SetState(0);
}

void CQuestionBrick::Render()
{
	animSet->at(state)->Render(this->x, this->y);
}
