#include <pch.h>
#include "debug.h"
#include "utils.h"

void Application::Initialize(HMODULE _Module)
{
	InputsManager::Register();

	ScriptRegister(_Module, []
	{
			Actor peds[1203];
			int pedcount = 0;
			while (true)
			{
				std::vector<const char*> Debugs;

				MonitorResource();

				Actor player = GET_PLAYER_ACTOR(-1);
				Vector3 playerpos = GET_OBJECT_POSITION(player);

				pedcount = worldGetAllPeds(1203, peds);
				Debugs.push_back(concatCharArr(2, "Player coords: ", toConstChar(playerpos)));
				Debugs.push_back(concatCharArr(2, "Total NPC: ", toConstChar(pedcount)));
				Debugs.push_back(concatCharArr(2, "Weapon model:", toConstChar(GET_WEAPON_IN_HAND(player))));


				// world get all peds test
				if (Input::IsKeyPressed(KEY_0))
				{
					Actor peds[1203];
					int pedcount = worldGetAllPeds(1203, peds);
					logfile << "Total NPC: " << pedcount << "\n";
					Vector3 pos;

					for(int i=0; i<pedcount; i++)
					{
						while (Input::IsKeyPressed(KEY_0))
						{
							pos = GET_OBJECT_POSITION(peds[i]);
							Vector2 screencoords = worldToScreen(pos, 1366, 768);
							logfile << screencoords.x << " " << screencoords.y << " " << GET_CAMERA_ASPECT_RATIO(GET_GAME_CAMERA()) << "\n";
							RH_DrawText("OK", screencoords.x, screencoords.y, 0, 0.03f , 255, 255, 255, 1000, TextAlignment_Center);
							WAIT(0);
						}
						logfile << GET_ACTOR_ENUM(peds[i]) << "\n";
						logfile << "X:" << pos.x << " Y:" << pos.y << " Z:" << pos.z << "\n";
						logfile << "Distance: " << getDistanceBetweenCoords(playerpos, pos) << "\n\n";
					}
					logfile << "\n\n\n\n\n";
				}

				onScreenDebug(Debugs, 0.1, 0.1, 0.03f, 400, 500);
				logfile.flush();
				WAIT(0);
			}
	});
}



void Application::Shutdown(HMODULE _Module)
{
	ScriptUnregister(_Module);

	InputsManager::Unregister();
}