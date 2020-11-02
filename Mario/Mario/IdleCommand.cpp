#include "IdleCommand.h"
#include "CMario.h"
void IdleCommand::Execute(CMario* mario)
{
	mario->Idle();
}
