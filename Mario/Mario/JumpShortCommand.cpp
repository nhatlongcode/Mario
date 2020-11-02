#include "JumpShortCommand.h"
#include "CMario.h"

void JumpShortCommand::Execute(CMario* mario)
{
	mario->ShortJump();
}
