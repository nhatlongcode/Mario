#include "CScenePlayKeyHandler.h"
#include "CMario.h"
#include "CScenePlay.h"

bool CScenePlayKeyHandler::IsKeyDown(int keyCode, BYTE* keyStates)
{
	return (keyStates[keyCode] & 0x80) > 0;
}

void CScenePlayKeyHandler::KeyState(BYTE* states)
{
	
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
	scene->GetPlayer()->OnKeyDown(KeyCode);

	switch (KeyCode)
	{
		case DIK_1:
		{
			scene->SetPlayer(MARIO_TYPE_SMALL, 300.0f, 300.0f);
			break;
		}
		case DIK_2:
		{
			scene->SetPlayer(MARIO_TYPE_SUPER, 300.0f, 300.0f);
			break;
		}
		case DIK_3:
		{
			scene->SetPlayer(MARIO_TYPE_FIRE, 300.0f, 300.0f);
			break;
		}
		case DIK_4:
		{
			scene->SetPlayer(MARIO_TYPE_RACCOON, 300.0f, 300.0f);
			break;
		}
	}


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
	scene->GetPlayer()->OnKeyUp(KeyCode);
}
