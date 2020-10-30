#include "CBigMario.h"
#include "IHandleInput.h"
#include "CInput.h"

CBigMario::CBigMario()
{
	SetAnimationSet(MARIO_TYPE_SUPER);
	state = MARIO_STATE_IDLE;
}

void CBigMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CMario::Update(dt, colliable_objects);
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_DOWN))
	{
		SetState(MARIO_STATE_CRUNCH);
	}
	
	if (input->IsKeyDown(DIK_RIGHT))
	{
		nx = DIRECTION_RIGHT;
		SetSpeedX(0.19f);
		if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
	}
	else if (input->IsKeyDown(DIK_LEFT))
	{
		nx = DIRECTION_LEFT;
		SetSpeedX(-0.19f);
		if (isGrounded && !isJumping) SetState(MARIO_STATE_WALK);
	}
	
}

