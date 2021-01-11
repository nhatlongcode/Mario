#include "CQuestionBrick.h"
#include "CRewardObject.h"
#include "CCoin.h"
#include "CMushroom.h"
#include "CGame.h"

CQuestionBrick::CQuestionBrick()
{
	listReward.push(BrickObjectTag::Coin);
	listReward.push(BrickObjectTag::Coin);
	listReward.push(BrickObjectTag::Buff);
	IsCollisionEnabled = true;
	SetBoundingBox(48, 48);
	SetAnimationSet(30002);
	SetTag(ObjectTag::QuestionBrick);
	bounceBegin = -1;
	this->state = 0;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (bounceBegin > 0)
	{

		bounceBegin += dt;
		if (bounceBegin < 100)
		{
			dy = -0.5 * dt;
			reward->TriggerReward();
		}
		else if (bounceBegin > 100)
		{
			dy = 0.5 * dt;
		}
		
		if (bounceBegin > 150) // bounce done
		{
			dy = 0;
			IsCollisionEnabled = true;
			this->y = beginY;
			bounceBegin = -1;
			if (rewardTag == BrickObjectTag::Buff)
			CGame::Instance()->GetCurrentScene()->AddCoGameObject(reward);
		}
	}
	if (reward != nullptr)
	{
		reward->Update(dt, coObjects);
	}
	y += dy;
}

void CQuestionBrick::SetBrickReward(BrickObjectTag reward)
{
	
}

void CQuestionBrick::AddBrickReward(BrickObjectTag id)
{
	listReward.push(id);
}

void CQuestionBrick::TriggerBrick()
{
	if (listReward.size() == 0) return;
	auto dt = CGame::Instance()->GetDeltaTime();
	if (bounceBegin == -1)
	{
		BrickObjectTag tag = listReward.front();
		listReward.pop();
		if (reward != nullptr) delete reward;
		if (tag == BrickObjectTag::Buff)
		{
			reward = new CMushroom();
			rewardTag = BrickObjectTag::Buff;
			reward->SetPosition(this->x, this->y);

		}
		else
		{
			reward = new CCoin();
			rewardTag = BrickObjectTag::Coin;
			reward->SetPosition(this->x, this->y + 60.0f);
		}
		beginY = this->y;
		IsCollisionEnabled = false;
		bounceBegin = dt;
	}
}

void CQuestionBrick::SetState(int state)
{
	if (this->state == 0 && state == 0)
	{
		TriggerBrick();
	}
	if (listReward.size() == 0) this->state = 1;
}

void CQuestionBrick::Bounce()
{

}

void CQuestionBrick::Render()
{
	if (reward != nullptr) reward->Render();
	animSet->at(state)->Render(this->x, this->y,1, 1, alpha);
}
