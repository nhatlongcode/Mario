#include "Tail.h"
#include "CGameObject.h"

Tail::Tail()
{
	isHiting = false;
	IsCollisionEnabled = false;
	SetBoundingBox(26, 18);
}

void Tail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isHiting)
	{
		IsCollisionEnabled = true;
	}
	else
	{
		IsCollisionEnabled = false;
	}
	CGameObject::Update(dt, coObjects);
}

void Tail::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	if (other->obj->GetTag() == ObjectTag::Koopas) DebugOut(L"hit\n");
}

void Tail::Render()
{
	CGameObject::RenderCollisionBox();
}
