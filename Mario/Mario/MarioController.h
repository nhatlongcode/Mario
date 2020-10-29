#pragma once
#include "CMario.h"

class MarioController
{
private:
	unordered_map<int, CMario*> list;
public:
	void Init();
	CMario* GetMario(int id, float posX = 0, float posY = 0);
};

