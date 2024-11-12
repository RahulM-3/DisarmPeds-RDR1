#include <pch.h>
#include "debug.h"

// global variable
bool display = true;

void Application::Initialize(HMODULE _Module)
{
	InputsManager::Register();

	ScriptRegister(_Module, []
	{
		std::ofstream logfile("DisarmPeds.log");
		while (true)
		{
			MonitorResource();
			WAIT(0);
		}
	});
}



void Application::Shutdown(HMODULE _Module)
{
	ScriptUnregister(_Module);

	InputsManager::Unregister();
}