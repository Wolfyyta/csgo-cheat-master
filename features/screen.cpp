#include <Windows.h>
#include "screen.h"
#include "variables.h"
#include "../globals.h"

void screen::DrawOnScreen(ImDrawList* drawList)
{
	// watermark
	char buf[MAX_PATH] = "WolfHook";

	for (int i = 0; i < ImGui::CalcTextSize(buf).x; i++)
		if (interfaces::globals->frameCount % (i + 2) == 0)
			buf[i] = '$';

	drawList->AddText({ 10, 10 }, ImColor(255, 255, 0, 255), buf);

	if (variables::screen::debugInfo)
	{
		
	}

	if (variables::players::boxEsp && globals::local)
	{
		for (int i = 1; i < interfaces::globals->maxClients; i++)
		{
			CEntity* ent = interfaces::entityList->GetEntityFromIndex(i);

			if (!ent)
				continue;

			if (!ent->IsAlive())
				return;

			if (globals::local->GetTeam() == ent->GetTeam())
				continue;

			CVector min, max;
			if (!utils::GetBBox(ent, min, max))
				continue;

			float x = min.x;
			float y = min.y;
			float w = max.x + min.x;
			float h = max.y + min.y;

			// todo: skeleton
			// todo: name
			// todo: health bar (gradient)
			// todo: ammo bar (gradient)

			// todo: name (this is example)
			drawList->AddText({x - ImGui::CalcTextSize("[bot] Chet").x + 2, y}, ImColor(255, 255, 255, 255), "[bot] Chet");
			
			int hp = ent->GetHealth();

			// hp
			drawList->AddText({x - ImGui::CalcTextSize(std::to_string(hp).c_str()).x, y - ImGui::CalcTextSize("[bot] Chet").y}, ImColor(255, 255, 255, 255), std::to_string(hp).c_str());
			
			// box (gradient?)
			drawList->AddRect({ min.x, min.y }, { max.x, max.y }, ImColor(255, 0, 0, 255));
		}
	}
}
