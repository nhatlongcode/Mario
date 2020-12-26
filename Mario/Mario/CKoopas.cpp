#include "CKoopas.h"
#include "CGame.h"
#include "MarioDefines.h"

CKoopas::CKoopas()
{
	SetAnimationSet(KOOPAS_ANIMSET);
	nx = DIRECTION_LEFT;
	SetState(KOOPAS_STATE_WALK);
	IsCollisionEnabled = true;
	tag = ObjectTag::Koopas;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	DebugOut(L"vx: %f\n", vx);
	vy += MARIO_GRAVITY;
	if (startTime != -1)
	{
		int time = GetTickCount() - startTime;
		if (time > 3000 && state == KOOPAS_STATE_SHELL)
		{
			SetState(KOOPAS_STATE_WALK);
			this->y -= 80.0f;
			startTime = -1;
		}
	}
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
		vx = nx * KOOPAS_SPEED_WALK;
		SetBoundingBox(KOOPAS_BBOX_WIDTH, KOOPAS_BBOX_HEIGHT);
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		startTime = GetTickCount();
		SetBoundingBox(KOOPAS_SHELL_BBOX_WIDTH, KOOPAS_SHELL_BBOX_HEIGHT);
		break;
	case KOOPAS_STATE_SPIN:
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(nx);
		vx = nx * KOOPAS_SPEED_SPIN;
		break;
	case KOOPAS_STATE_DIE:
		
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(nx);
		SetSpeedX(nx * 0.3f);
		SetSpeedY(-0.8f);
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
		if (state == KOOPAS_STATE_SPIN)
		{
			this->vx = this->nx * -1 * KOOPAS_SPEED_SPIN;
		}
		else if (state == KOOPAS_STATE_WALK)
		{
			this->vx = this->nx * -1 * KOOPAS_SPEED_WALK;
		}
		

	}

	if (tag == ObjectTag::Ground && other->nx != 0)
	{
		nx = -nx;
	}
}
