#include "CCoin.h"

CCoin::CCoin()
{
	IsCollisionEnabled = false;
	SetBoundingBox(0, 0);
	SetAnimationSet(30003);
	SetState(0);
	scoreFx = new CSCoreFx();
	
	bounceDone = false;
}

void CCoin::Bounce()
{
	startTime = GetTickCount();
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int time = GetTickCount() - startTime;
	if (startTime != -1)
	{
		if (time < 150)
		{
			this->vy = -0.6f;
		}
		else if (time > 150 && time < 250)
		{
			this->vy = 0.6f;
		}
		else if (time > 250)
		{
			bounceDone = true;
			startTime = -1;
			scoreFx->SetPosition(this->x, this->y - 12.0f);
			scoreFx->BeginEffect();
		}
	}
	if (scoreFx->IsEffectBegin()) scoreFx->Update(dt, NULL);
	CGameObject::Update(dt);
}

void CCoin::SetState(int state)
{

	this->state = state;
}

bool CCoin::GetBounceDone()
{
	return bounceDone;
}

void CCoin::Render()
{
	if (scoreFx->IsEffectBegin()) scoreFx->Render();
	if (bounceDone) return;
	animSet->at(state)->Render(this->x, this->y-100);
}
