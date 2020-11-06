#include "CGhostPlatform.h"

CGhostPlatform::CGhostPlatform()
{
	tag = ObjectTag::GhostPlatform;
	IsCollisionEnabled = true;
	SetBoundingBox(144, 144);
	x = 500.0f;
	y = 1100.75f;
}

void CGhostPlatform::Render()
{
	CGameObject::RenderCollisionBox();
}
