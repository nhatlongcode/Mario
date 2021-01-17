#include "CBigMario.h"
#include "IHandleInput.h"
#include "CInput.h"

CBigMario::CBigMario()
{
	SetTag(ObjectTag::Player);
	SetAnimationSet(MARIO_TYPE_SUPER);
	level = MARIO_TYPE_SUPER;
	IsCollisionEnabled = true;
	SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
	state = MARIO_STATE_IDLE;
	isCanFly = false;
	isGrounded = false;
	canHighJump = false;
}

void CBigMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CMario::Update(dt, colliable_objects);
	auto input = CLocator<IHandleInput>().Get();
	if (input->IsKeyDown(DIK_DOWN))
	{
		SetState(MARIO_STATE_CRUNCH);
		SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_CRUNCH_BBOX_HEIGHT);
		
	}
	else SetBoundingBox(MARIO_BIG_BBOX_WIDTH, MARIO_BIG_BBOX_HEIGHT);
	

	
}


