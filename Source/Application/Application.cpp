#include <pch.h>
#include "debug.h"
#include "utils.h"

void Application::Initialize(HMODULE _Module)
{
	InputsManager::Register();

	ScriptRegister(_Module, []
	{
			while (true)
			{
				MonitorResource();

				Actor player = GET_PLAYER_ACTOR(-1);
				Vector3 playerpos = GET_OBJECT_POSITION(player);

				if (Input::IsKeyJustPressed(KEY_0))
				{
					Actor peds[1203];
					int pedcount = worldGetAllPeds(1203, peds);
					logfile << "Total NPC: " << pedcount << "\n";
					Vector3 pos;
					for(int i=0; i<pedcount; i++)
					{
						pos = GET_OBJECT_POSITION(peds[i]);
						logfile << GET_ACTOR_ENUM(peds[i]) << "\n";
						logfile << "X:" << pos.x << " Y:" << pos.y << " Z:" << pos.z << "\n";
						logfile << "Distance: " << getDistance(playerpos, pos) << "\n\n";
					}	
					logfile << "\n\n\n\n\n";
				}

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