#include "Tail.h"
#include "CGameObject.h"

Tail::Tail()
{
	isHiting = false;
	tag = ObjectTag::None;
	IsCollisionEnabled = true;
	SetBoundingBox(26, 18);
}


void Tail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt, coObjects);
	// xet va cham cho tail
	float tl, tt, tr, tb, gl, gt, gr, gb;
	this->GetBoundingBox(tl, tt, tr, tb);
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT go = coObjects->at(i);
		go->GetBoundingBox(gl, gt, gr, gb);
		if (!(tr < gl || tl > gr || tt > gb || tb < gt))
		{
			LPCOLLISIONEVENT e = new CCollisionEvent(0, 1, 1);
			e->obj = go;
			OnCollisionEnter(e);
		}

	}
}

void Tail::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	if (other->obj->GetTag() == ObjectTag::Koopas && isHiting)
	{
		other->obj->SetState(KOOPAS_STATE_DIE);
		DebugOut(L"hit\n");
	}
}

void Tail::Render()
{
	if (isHiting) CGameObject::RenderCollisionBox();
}
