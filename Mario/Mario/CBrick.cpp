#include "CBrick.h"

CBrick::CBrick()
{
	tag = ObjectTag::Solid;
	SetBoundingBox(BRICK_BBOX_WIDTH, BRICK_BBOX_HEIGHT);
	IsCollisionEnabled = true;
	x = 300.0f;
	y = 1150;
}

void CBrick::Render()
{
	CGameObject::RenderCollisionBox();
}



