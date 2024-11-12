#include <pch.h>

void MonitorResource()
{
	float x = 0.05000002;
	float y = 0.96;
	float w = 1.9;
	float h = 0.08;
	RH_DrawRect(x, y, w, h, 0, 0, 0, 100);
	RH_DrawText("Test", x, y, 0, 0.1, 255, 255, 255, 200, TextAlignment_Left);
}