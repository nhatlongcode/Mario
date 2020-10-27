#pragma once
#include "CSceneKeyHandler.h"

class CScenePlayKeyHandler : public CScenceKeyHandler
{

private:
	bool IsKeyDown(int keyCode, BYTE* states);
public:
	CScenePlayKeyHandler(CScene* s) : CScenceKeyHandler(s) {};
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
