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

	ani->Render(x, y);
}

CGameObject::~CGameObject()
{
}