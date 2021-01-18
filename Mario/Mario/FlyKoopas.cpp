#include "FlyKoopas.h"
#include "CGame.h"

FlyKoopas::FlyKoopas()
{
	SetAnimationSet(21001);
	SetState(0);
	isGround = false;
	SetTag(ObjectTag::KoopasFly);
	IsCollisionEnabled = true;
	nx = DIRECTION_LEFT;
}

void FlyKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	vy += 0.01f;
	if (state == 4)
	{
		vy += 0.04f;
	}
	else if (state == 0)
	{
		if (isGround)
		{
			vy = -0.3f;
			vx = nx * 0.07f;
			isGround = false;
		}
	}
	if (startTime != -1)
	{
		int time = GetTickCount() - startTime;
		if (time > 7000 && state == 2)
		{
			SetState(1);
			this->y -= 20.0f;
			startTime = -1;
		}
	}
}

void FlyKoopas::SetHoldByMario(bool hold)
{
	isBeingHold = true;
}

void FlyKoopas::SetState(int state)
{
	this->state = state;
	CGameObject::SetState(state);
	switch (state)
	{
	case 0:

		SetBoundingBox(KOOPAS_BBOX_WIDTH, KOOPAS_BBOX_HEIGHT);

	case 1:
		vx = nx * KOOPAS_SPEED_WALK;
		SetBoundingBox(KOOPAS_BBOX_WIDTH, KOOPAS_BBOX_HEIGHT);
		break;
	case 2:
		vx = 0;
		startTime = GetTickCount();
		SetBoundingBox(KOOPAS_SHELL_BBOX_WIDTH, KOOPAS_SHELL_BBOX_HEIGHT);
		break;
	case 3:
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(nx);
		startTime = -1;
		vx = nx * KOOPAS_SPEED_SPIN;
		vy = 0.3f;
		break;
	case 4:

		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(nx);
		SetSpeedX(nx * 0.3f);
		SetSpeedY(-0.7f);
		IsCollisionEnabled = false;
		break;
	}
}

void FlyKoopas::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	auto tag = go->GetTag();

	if ((tag == ObjectTag::Ground || tag == ObjectTag::QuestionBrick || tag == ObjectTag::GhostPlatform || tag == ObjectTag::Brick))
	{
		if (other->ny == -1.0f)
		{
			isGround = true;
		}
	}

	if (tag == ObjectTag::Solid || tag == ObjectTag::QuestionBrick)
	{
		if (state == 3)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_SPIN;
		}
		else if (state == 1)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_WALK;
		}


	}
	else if (tag == ObjectTag::Ground && other->nx != 0)
	{
		if (state == 3)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_SPIN;
		}
		else if (state == 1)
		{
			this->nx = -1 * this->nx;
			this->vx = this->nx * KOOPAS_SPEED_WALK;
		}
	}
	else if (tag == ObjectTag::Goomba)
	{
		if (state == 3)
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
}

void FlyKoopas::Render()
{
	animSet->at(state)->Render(x, y, nx, 1, alpha);
}

bool FlyKoopas::GetThrought(ObjectTag tag, float nx, float ny)
{
	return (ny != -1.0f);
}
