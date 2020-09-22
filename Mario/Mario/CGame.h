#pragma once
#include "CWindow.h"

class CGame
{
private:
	CGame();
	static CGame* _instance;
	CWindow wnd;

public:
	~CGame();
	static CGame* Instance();
	void PublicTestVoid();
	void InitGame(HINSTANCE hInstance, int nCmdShow);

};

