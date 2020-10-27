#include "CScenePlayKeyHandler.h"
#include "CMario.h"
#include "CScenePlay.h"

bool CScenePlayKeyHandler::IsKeyDown(int keyCode, BYTE* keyStates)
{
	return (keyStates[keyCode] & 0x80) > 0;
}

void CScenePlayKeyHandler::KeyState(BYTE* states)
{
	if (IsKeyDown(DIK_A, states)) DebugOut(L"HOLD A\n");
	/*//
	CGame* game = CGame::Instance();
	CMario* mario = ((CScenePlay*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else
		mario->SetState(MARIO_STATE_IDLE);
	//*/
}

void CScenePlayKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_X) DebugOut(L"PUSH A\n");
	/*//
	CMario* mario = ((CScenePlay*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMPING);
		break;
	case DIK_A:
		mario->Reset();
		break;
	}
	//*/
}

void CScenePlayKeyHandler::OnKeyUp(int KeyCode)
{
}
