#pragma once
#include "CSceneKeyHandler.h"
#include "CSceneMap.h"

class CSceneMapKeyHandler : public CScenceKeyHandler
{
private:
	CSceneMap* scene;
public:
	CSceneMapKeyHandler(CSceneMap* s);
	void KeyState(BYTE* states) override;
	void OnKeyDown(int KeyCode) override;
	void OnKeyUp(int KeyCode) override;
};