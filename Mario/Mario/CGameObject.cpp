#include "CGameObject.h"
CGameObject::CGameObject()
{
	x = y = 0;
	vx = 0.07f;
}

void CGameObject::Update(DWORD dt)
{
	x += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) vx = -vx;
}

void CGameObject::Render()
{
	LPANIMATION ani;
	//if (vx>0) ani = animations[0]; else ani = animations[1];

	if (vx > 0) ani = CLocator<CAnimationsManager>().Get()->Get(500);
	else ani = CLocator<CAnimationsManager>().Get()->Get(501);

	//ani = animations[0];
	ani->Render(x, y);
}

CGameObject::~CGameObject()
{
}