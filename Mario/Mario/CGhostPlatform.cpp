#include "CGhostPlatform.h"

CGhostPlatform::CGhostPlatform()
{
	tag = ObjectTag::GhostPlatform;
	IsCollisionEnabled = true;
}

void CGhostPlatform::Render()
{
	CGameObject::RenderCollisionBox();
}
