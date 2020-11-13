#include "CKoopas.h"
#include "MarioDefines.h"

CKoopas::CKoopas()
{
	SetBoundingBox(KOOPAS_BBOX_WIDTH, KOOPAS_BBOX_HEIGHT);
	SetAnimationSet(KOOPAS_ANIMSET);
	SetState(KOOPAS_STATE_WALKING);
	nx = DIRECTION_RIGHT;
	IsCollisionEnabled = true;
	tag = ObjectTag::Koopas;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


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
	case KOOPAS_STATE_WALKING:
		vx = nx * -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		SetBoundingBox(KOOPAS_SHELL_BBOX_WIDTH, KOOPAS_SHELL_BBOX_HEIGHT);
		break;
	case KOOPAS_STATE_SPIN:
		vx = nx * 0.5f;
		break;
	case KOOPAS_STATE_DIE:
		vy = -0.8f;
		vx = 0;
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
		//vx = nx * 0.5f;
	}
}
