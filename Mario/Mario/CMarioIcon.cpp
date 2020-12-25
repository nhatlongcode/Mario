#include "CMarioIcon.h"

CMarioIcon::CMarioIcon() : CGameObject()
{
	IsCollisionEnabled = false;
	SetAnimationSet(11000);
	state = 0;
	x = 0;
	y = 0;
}

void CMarioIcon::MoveToCell(int x, int y)
{
	float posY = float(x * 48);
	float posX = float(y * 48);
	SetPosition(posX, posY);
}

void CMarioIcon::Render()
{
	animSet->at(state)->Render(x, y, DIRECTION_RIGHT);
}
