#include "CSceneMapKeyHandler.h"
#include "CMario.h"
#include "CSceneMap.h"
#include <dinput.h>

CSceneMapKeyHandler::CSceneMapKeyHandler(CSceneMap* s) : CScenceKeyHandler(s)
{
	scene = s;
}

void CSceneMapKeyHandler::KeyState(BYTE* states)
{
}

void CSceneMapKeyHandler::OnKeyDown(int KeyCode)
{
	
	switch (KeyCode)
	{
		case DIK_W:
		{
			scene->PlayerMove(3);
			break;
		}		
		case DIK_A:
		{
			scene->PlayerMove(0);
			break;
		}		
		case DIK_S:
		{
			scene->PlayerMove(2);
			break;
		}		
		case DIK_D:
		{
			scene->PlayerMove(1);
			break;
		}
		case DIK_X:
		{
			
			break;
		}
	}
}

void CSceneMapKeyHandler::OnKeyUp(int KeyCode)
{
}
