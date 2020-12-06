#include "CQuestionBrick.h"
#include "CGame.h"

CQuestionBrick::CQuestionBrick()
{
	SetBoundingBox(48, 48);
	SetAnimationSet(30002);
	SetTag(ObjectTag::QuestionBrick);
	bounceBegin = -1;
	SetState(0);
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (bounceBegin > 0)
	{
		bounceBegin += dt;
		if (bounceBegin < 100)
		{
			dy = -0.5 * dt;
		}
		else if (bounceBegin > 100)
		{
			dy = 0.5 * dt;
		}
		
		if (bounceBegin > 200)
		{
			dy = 0;
			IsCollisionEnabled = true;
			this->y = beginY;
			bounceBegin = -1;
		}
	}

	y += dy;
}

void CQuestionBrick::SetState(int state)
{
	if (state == 1)
	{
		Bounce();
	}
}

void CQuestionBrick::Bounce()
{
	auto dt = CGame::Instance()->GetDeltaTime();
	if (bounceBegin == -1)
	{
		beginY = this->y;
		IsCollisionEnabled = false;
		bounceBegin = dt;
		SetState(1);
	}
}

void CQuestionBrick::Render()
{
	animSet->at(state)->Render(this->x, this->y);
}
