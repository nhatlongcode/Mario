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
	//DebugOut(L"vx: %d\n", nx);
	vy += 0.01f;
	if (state == KOOPAS_STATE_DIE)
	{
		vy += 0.04f;
	}
	if (startTime != -1)
	{
		int time = GetTickCount() - startTime;
		if (time > 7000 && state == KOOPAS_STATE_SHELL)
		{
			SetState(KOOPAS_STATE_WALK);
			this->y -= 20.0f;
			startTime = -1;
		}
	}
}

void CKoopas::SetHoldByMario(bool hold)
{
	isBeingHold = hold;
}

void CKoopas::Render()
{
	animSet->at(state)->Render(x, y, nx,1, alpha);
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
		vy = 0;
		startTime = GetTickCount();
		SetBoundingBox(KOOPAS_SHELL_BBOX_WIDTH, KOOPAS_SHELL_BBOX_HEIGHT);
		break;
	case KOOPAS_STATE_SPIN:
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(nx);
		startTime = -1;
		vx = nx * KOOPAS_SPEED_SPIN;
		vy = 0.3f;
		break;
	case KOOPAS_STATE_DIE:
		
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(nx);
		SetSpeedX(nx * 0.3f);
		SetSpeedY(-0.7f);
		IsCollisionEnabled = false;
		break;
	}
}

void CKoopas::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	auto tag = go->GetTag();
	if (tag == ObjectTag::Solid || tag == ObjectTag::QuestionBrick)
	{
		if (state == KOOPAS_STATE_SPIN)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_SPIN;
		}
		else if (state == KOOPAS_STATE_WALK)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_WALK;
		}
		

	}
	else if (tag == ObjectTag::Ground && other->nx != 0)
	{
		if (state == KOOPAS_STATE_SPIN)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_SPIN;
		}
		else if (state == KOOPAS_STATE_WALK)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_WALK;
		}
	}
	else if (tag == ObjectTag::Goomba)
	{
		go->SetState(GOOMBA_STATE_DIE_INSTANT);
		this->vx = nx * KOOPAS_SPEED_SPIN;
	}
	else if (tag == ObjectTag::Venus)
	{
		if (state == 3)
		{
			go->SetState(-1);
			this->vx = this->nx * KOOPAS_SPEED_SPIN;
		}
	}
	else if (tag == ObjectTag::GoombaFly)
	{

	}
}

bool CKoopas::GetThrought(ObjectTag tag, float nx, float ny)
{
	return true;
}
