#include "CMarioIcon.h"

CMarioIcon::CMarioIcon() : CGameObject()
{
	IsCollisionEnabled = false;
	isMoving = false;
	SetAnimationSet(11000);
	posXGoingTo = -1;
	posYGoingTo = -1;
	state = 0;
	x = 0;
	y = 0;
}

void CMarioIcon::MoveToCell(int x, int y, bool instant)
{
	if (isMoving) return;
	float posY = float(x * 48);
	float posX = float(y * 48);
	if (instant) 
	{
		SetPosition(posX, posY);
		return;
	}
	posXGoingTo = posX;
	posYGoingTo = posY;
}

void CMarioIcon::Render()
{
	animSet->at(state)->Render(x, y, DIRECTION_RIGHT, 1, alpha);
}

void CMarioIcon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (posXGoingTo != -1)
	{
		isMoving = true;
		if (x > posXGoingTo)
		{
			vx = -0.4f;
		}
		else if (x < posXGoingTo)
		{
			vx = 0.4f;
		}

		if (abs(this->x - posXGoingTo) < 5.0f)
		{
			this->x = posXGoingTo;
			//DebugOut(L"STOPPPP: %f %f\n", this->x, posXGoingTo);
			vx = 0.0f;
			isMoving = false;
			posXGoingTo = -1;
		}
	}
	else if (posYGoingTo != -1)
	{
		isMoving = true;
		if (y > posYGoingTo)
		{
			vy = -0.4f;
		}
		else if (y < posYGoingTo)
		{
			vy = 0.4f;
		}

		if (abs(this->y - posYGoingTo) < 5.0f)
		{
			this->y = posYGoingTo;
			vy = 0.0f;
			isMoving = false;
			posYGoingTo = -1;
		}
	}
	else
	{
		vx = vy = 0.0f;

	}

	CGameObject::Update(dt, coObjects);
}
