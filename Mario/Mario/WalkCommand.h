#pragma once
#include "ICommand.h"
class WalkCommand : public ICommand
{
private:
	int direction;
public:
	WalkCommand(int direction);
	void Execute(CMario* mario);
};