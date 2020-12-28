#include "CQuestionBrick.h"
#include "CGame.h"

CQuestionBrick::CQuestionBrick()
{
	IsCollisionEnabled = true;
	this->reward = BrickObjectTag::Coin;
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
			coin = new CCoin();
			coin->SetPosition(this->x, this->y + 60.0f);
			coin->Bounce();
		}
		else if (bounceBegin > 100)
		{
			dy = 0.5 * dt;
		}
		
		if (bounceBegin > 200) // bounce done
		{
			dy = 0;
			IsCollisionEnabled = true;
			this->y = beginY;
			bounceBegin = -1;
		}
	}
	if (coin != nullptr)
	{
		coin->Update(dt, NULL);
	}
	y += dy;
}

void CQuestionBrick::SetBrickReward(BrickObjectTag reward)
{
	this->reward = reward;
}

void CQuestionBrick::SetState(int state)
{
	if (state == 1 && this->state == 0)
	{
		Bounce();
	}
	this->state = state;
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
	if (coin != nullptr) coin->Render();
	animSet->at(state)->Render(this->x, this->y);
}
