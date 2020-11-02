#pragma once
#include "ICommand.h"

class JumpShortCommand : public ICommand
{
public:
	virtual void Execute(CMario* mario);
};