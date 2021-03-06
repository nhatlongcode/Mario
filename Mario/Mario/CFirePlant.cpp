#include "CFirePlant.h"
#include "CGame.h"


CFirePlant::CFirePlant()
{
	nx = DIRECTION_LEFT;
	SetAnimationSet(22000);
	SetTag(ObjectTag::Venus);
	SetBoundingBox(48, 90);
	this->state = 0;
	fired = false;
	steps = 0;
	goOutDist = 0.0f;
	startY = 1128.0f;
	coverPipe = CLocator<ISpritesManager>().Get()->Get(60000);
	startFire = 0;
}

void CFirePlant::Fire()
{
	if (fired) return;
	fired = true;
	CFireFromPlant* fireBall2 = new CFireFromPlant(this->x, this->y - 48.0f, -this->nx);
	fireBall2->SetTag(ObjectTag::FireFromMario);
	CGame::Instance()->GetCurrentScene()->AddGameObject(fireBall2);

}

void CFirePlant::Render()
{
	animSet->at(state)->Render(x,y,nx);
	coverPipe->Draw(this->x, startY);
}

void CFirePlant::SetState(int state)
{
	//0: look down 1: look up 2: goDown
	this->state = state;
}

void CFirePlant::SetCoverPipe(int id)
{
	//coverPipe = CLocator<ISpritesManager>().Get()->Get(id);
}

void CFirePlant::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	//DebugOut(L"asdad");
}

bool CFirePlant::GetThrought(ObjectTag tag, float nx, float ny)
{
	return true;
}

void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float pX, pY;
	CGame::Instance()->GetCurrentScene()->GetPlayer()->GetPosition(pX, pY);
	if ((this->x - pX) > 0) nx = DIRECTION_RIGHT;
	else nx = DIRECTION_LEFT;

	if (this->y - pY < 0) SetState(0);
	else SetState(1);

	if (steps == 0) // stay in pipe
	{
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
			steps = 2;
			startFire = 0;
		}
	}
	else if (steps == 2)
	{
		vy = 0.0f;
		startFire += dt;
		fired = false;
		if (startFire > 2000)
		{
			Fire();
			startFire = 0;
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
