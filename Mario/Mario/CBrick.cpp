#include "CBrick.h"

CBrick::CBrick()
{
	SetBoundingBox(BRICK_BBOX_WIDTH, BRICK_BBOX_HEIGHT);
	IsCollisionEnabled = true;
	x = 300.0f;
	y = 1100.75f;
}

void CBrick::Render()
{
	CGameObject::RenderCollisionBox();
	//animSet->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::CheckCollision(coObjects);
}


