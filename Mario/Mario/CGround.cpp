#include "CGround.h"

CGround::CGround()
{
	IsCollisionEnabled = true;
	tag = ObjectTag::Ground;
}

void CGround::Render()
{
	CGameObject::RenderCollisionBox();
}
