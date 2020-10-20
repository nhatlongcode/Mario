#include "CMarioState.h"
#include "CMario.h"

bool CMarioState::IsKeyDown(int keyCode)
{
	return (keyStates[keyCode] & 0x80) > 0;
}

void CMarioState::Update(DWORD dt)
{
}

void CMarioState::KeyState(BYTE* states)
{
	keyStates = states;
}

void CMarioState::OnKeyDown(int keyCode)
{
}

void CMarioState::OnKeyUp(int keyCode)
{
}

void CMarioState::SetMario(CMario* mario)
{
	this->mario  = mario;
}

