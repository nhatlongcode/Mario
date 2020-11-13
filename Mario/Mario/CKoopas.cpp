#include "CKoopas.h"
#include "MarioDefines.h"

CKoopas::CKoopas()
{
	SetBoundingBox(KOOPAS_BBOX_WIDTH, KOOPAS_BBOX_HEIGHT);
	SetAnimationSet(KOOPAS_ANIMSET);
	SetState(KOOPAS_STATE_WALK);
	nx = DIRECTION_LEFT;
	IsCollisionEnabled = true;
	tag = ObjectTag::Koopas;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == KOOPAS_STATE_WALK)
	{
		vx = nx * KOOPAS_SPEED_WALK;
	}
	else if (state == KOOPAS_STATE_SPIN)
	{
		vx = nx * KOOPAS_SPEED_SPIN;
	}

	vy += MARIO_GRAVITY;
	CGameObject::Update(dt, coObjects);

}

void CKoopas::Render()
{
	animSet->at(state)->Render(x, y, nx);
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALK:
		
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		SetBoundingBox(KOOPAS_SHELL_BBOX_WIDTH, KOOPAS_SHELL_BBOX_HEIGHT);
		break;
	case KOOPAS_STATE_SPIN:
		
		break;
	case KOOPAS_STATE_DIE:
		IsCollisionEnabled = false;
		break;
	}
}

void CKoopas::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	auto tag = go->GetTag();
	if (tag == ObjectTag::Solid)
	{
		nx = -nx;
	}
}
