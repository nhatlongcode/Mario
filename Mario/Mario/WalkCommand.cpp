#include "WalkCommand.h"
#include "CMario.h"
WalkCommand::WalkCommand(int direction)
{
	this->direction = direction;
}

void WalkCommand::Execute(CMario* mario)
{
	mario->Walk(this->direction);
}
