#include "misc.h"
#include "../globals.h"
#include "variables.h"

void misc::BunnyHop(CUserCmd* cmd)
{
	if (variables::misc::bunnyHop)
	{
		if (!(globals::local->GetFlags() & CEntity::FL_ONGROUND))
			cmd->buttons &= ~CUserCmd::IN_JUMP;
	}
}
