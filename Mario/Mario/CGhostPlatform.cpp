#include "CGhostPlatform.h"

CGhostPlatform::CGhostPlatform()
{
	IsCollisionEnabled = true;
}

bool CGhostPlatform::GetThrought(ObjectTag tag, float nx, float ny)
{
	return this->tag == ObjectTag::GhostPlatform && ny >= 0;
}

void CGhostPlatform::Render()
{

}
