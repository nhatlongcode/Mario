#include "CBrick.h"

CBrick::CBrick()
{
	tag = ObjectTag::Solid;
	SetBoundingBox(BRICK_BBOX_WIDTH, BRICK_BBOX_HEIGHT);
	IsCollisionEnabled = true;
}

void CBrick::Render()
{

}



