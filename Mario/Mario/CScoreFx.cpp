#include "CScoreFx.h"

CSCoreFx::CSCoreFx(int scoreState)
{
	IsCollisionEnabled = false;
	vx = 0.0f;
	vy = 0.0f;
	startTime = -1;
	effectDone = false;
	SetAnimationSet(50001);
	SetState(scoreState);
}

bool CSCoreFx::IsEffectBegin()
{
	if (startTime != -1) return true;
	return false;
}

void CSCoreFx::BeginEffect()
{
	startTime = GetTickCount();
}

void CSCoreFx::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (startTime != -1)
	{
		int time = GetTickCount() - startTime;
		if (time < 300)
		{
			vy = -0.4f;
		}
		else
		{
			vy = 0;
			effectDone = true;
		}
	}
	CGameObject::Update(dt);
}

void CSCoreFx::SetScoreState(int scoreState)
{
	this->state = scoreState;
}

void CSCoreFx::ResetEffect()
{
	startTime = -1;
	effectDone = false;
}

void CSCoreFx::Render()
{
	if (effectDone || startTime == -1) return;
	animSet->at(state)->Render(x, y, 1, 1, alpha);
}
