#include "BrickPiece.h"

BrickPiece::BrickPiece()
{
	vx = 0.0f;
	vy = 0.0f;
	IsCollisionEnabled = false;
	isBreaked = false;
}

void BrickPiece::SetSprite(int id)
{
	this->sprite = CLocator<ISpritesManager>().Get()->Get(id);
}

void BrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, NULL);
	if (isBreaked) vy += 0.03f;
}

void BrickPiece::Render()
{
	if (!isBreaked) return;
	sprite->Draw(x, y);
}
