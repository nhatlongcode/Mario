#include "CStandingState.h"
#include "CWalkingState.h"
void CStandingState::Init()
{
}

void CStandingState::Update(DWORD dt)
{
}

void CStandingState::KeyState(BYTE* states)
{
	CMarioState::KeyState(states);
	if (IsKeyDown(DIK_LEFT))
	{
		CMarioState* newState = new CWalkingState();
		newState->SetMario(mario);
		newState->Init();
		mario->SetMarioState(newState);

	}
}

void CStandingState::OnKeyDown(int keyCode)
{
}

void CStandingState::OnKeyUp(int keyCode)
{
}
