#include "CPiranha.h"
#include "CGame.h"

CPiranha::CPiranha()
{
	startY = -1;
	SetAnimationSet(23000);
	SetState(0);
	SetBoundingBox(48, 90);
	startY = -1;
	coverPipe = CLocator<ISpritesManager>().Get()->Get(60000);
}

void CPiranha::Render()
{
	if (state == -1) return;
	animSet->at(state)->Render(this->x, this->y);
	coverPipe->Draw(this->x, startY);
}

void CPiranha::SetState(int state)
{
	this->state = state;
}

void CPiranha::SetCoverPipe(int id)
{
	coverPipe = CLocator<ISpritesManager>().Get()->Get(id);
}

void CPiranha::OnCollisionEnter(LPCOLLISIONEVENT other)
{
}

bool CPiranha::GetThrought(ObjectTag tag, float nx, float ny)
{
	return true;
}

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float pX, pY;
	CGame::Instance()->GetCurrentScene()->GetPlayer()->GetPosition(pX, pY);

	if (steps == 0) // stay in pipe
	{
		if (startY == -1) startY = this->y;
		if (!((abs(this->x - pX) < 100.0f) || (abs(this->x - pX) > 350)))
		{
			IsCollisionEnabled = true;
			steps = 1;
		}
	}
	else if (steps == 1) // go up
	{
		vy = -0.05f;
		if (abs(this->y - startY) >= 90.0f)
		{
			this->y = startY - 90.0f;
			vy = 0.0f;
			stayTime = 0;
			steps = 2;
		}
	}
	else if (steps == 2)
	{
		vy = 0.0f;
		stayTime += dt;
		if (stayTime > 2000)
		{
			stayTime = 0;
			steps = 3;
		}
	}
	else if (steps == 3) // go down
	{
		vy = 0.05f;
		if (abs(startY - this->y) <= 2.0f)
		{
			vy = 0.0f;
			this->y = startY;
			IsCollisionEnabled = false;
			steps = 0;
		}

	}
}
