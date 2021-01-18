#include "BrickPiece.h"

BrickPiece::BrickPiece()
{
	vx = 0.0f;
	vy = 0.0f;
	IsCollisionEnabled = false;
	isBreaked = false;
}

void BrickPiece::Break()
{
	vy = bounceY;
	vx = bounceX;
	isBreaked = true;
}

void BrickPiece::SetBounceBreak(float vx, float vy, int nx)
{
	bounceX = vx * nx;
	bounceY = vy;

}

void BrickPiece::SetSprite(int id)
{
	this->sprite = CLocator<ISpritesManager>().Get()->Get(id);
}

void BrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (isBreaked) vy += 0.03f;
}

void BrickPiece::SetState(int state)
{
	if (state == -1)
	{
		Break();
	}
}

void BrickPiece::Render()
{
	if (!isBreaked) return;
	sprite->Draw(x, y);
}
