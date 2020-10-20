#include "CScenePlayKeyHandler.h"
#include "CMario.h"
#include "CScenePlay.h"

void CScenePlayKeyHandler::KeyState(BYTE* states)
{
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
}

void CScenePlayKeyHandler::OnKeyDown(int KeyCode)
{
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
}
