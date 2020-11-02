#pragma once
#include "ICommand.h"
class IdleCommand : public ICommand
{
public:
	virtual void Execute(CMario* mario);
};
