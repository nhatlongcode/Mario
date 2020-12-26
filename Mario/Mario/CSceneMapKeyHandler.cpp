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
		case DIK_UPARROW:
		{
			scene->PlayerMove(3);
			break;
		}		
		case DIK_LEFTARROW:
		{
			scene->PlayerMove(0);
			break;
		}		
		case DIK_DOWNARROW:
		{
			scene->PlayerMove(2);
			break;
		}		
		case DIK_RIGHTARROW:
		{
			scene->PlayerMove(1);
			break;
		}
		case DIK_X:
		{
			scene->PlayerScelect();
			break;
		}
	}
}

void CSceneMapKeyHandler::OnKeyUp(int KeyCode)
{
}
