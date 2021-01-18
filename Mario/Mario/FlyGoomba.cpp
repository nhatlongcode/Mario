#include "FlyGoomba.h"
#include "CGame.h"

FlyGoomba::FlyGoomba()
{

	SetBoundingBox(35,35);
	SetAnimationSet(20001);
	this->state = 0;
	SetTag(ObjectTag::GoombaFly);
	IsCollisionEnabled = true;
	step = 0;
	nx = DIRECTION_LEFT;
}

void FlyGoomba::Render()
{
	animSet->at(state)->Render(this->x, this->y);
}

void FlyGoomba::SetState(int state)
{
	//0: canh, 1 thuong, 2 chet bep, 3 chet nguoc
	this->state = state;
	switch (state)
	{
	case 2:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE - 1.3f;
		vx = 0;
		vy = 0;
		IsCollisionEnabled = false;
		break;
	case 3:
		int marionx;
		CGame::Instance()->GetCurrentScene()->GetPlayer()->GetDirection(marionx);
		SetSpeedX(marionx * 0.3f);
		SetSpeedY(-0.8f);
		IsCollisionEnabled = false;
		break;
	}

}

void FlyGoomba::OnCollisionEnter(LPCOLLISIONEVENT other)
{
	LPGAMEOBJECT go = other->obj;
	auto tag = go->GetTag();

	if (tag == ObjectTag::Ground || tag == ObjectTag::QuestionBrick) isGround = true;

}

void FlyGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == 0 && isGround)
	{
		if (step < 2)
		{
			vy = -0.2f;
			vx = 0.05f * nx;
			isGround = false;
			step += 1;
		}
		else if (step >= 2 && step <4)
		{
			vy = -0.5f;
			vx = 0.05f * nx;
			isGround = false;
			step += 1;
		}
		else if (step >= 4)
		{
			step = 0;
		}
	}
	else if (state == 1)
	{
		vx = nx * 0.05f;
	}
	vy += 0.03f;
}
