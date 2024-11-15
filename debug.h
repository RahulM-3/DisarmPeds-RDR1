#include <pch.h>
std::ofstream logfile("debug.log");

// CALCULATE MEMORY USAGE
char* getMemoryUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo)) {
        DWORDLONG totalMemoryMB = memInfo.ullTotalPhys / (1024 * 1024);
        DWORDLONG usedMemoryMB = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024);

        // Create the memory usage string
        std::string memoryUsage = "Memory: " + std::to_string(usedMemoryMB) + "MB/" +
            std::to_string(totalMemoryMB) + "MB";

        // Allocate and copy the string to a char*
        char* result = new char[memoryUsage.size() + 1];
        std::memcpy(result, memoryUsage.c_str(), memoryUsage.size() + 1);

        return result;
    }
    else {
        const char* error = "Memory: -1";
        char* result = new char[std::strlen(error) + 1];
        std::memcpy(result, error, std::strlen(error) + 1);

        return result;
    }
}

// DISPLAY SYSTEM RESOURCE USAGE
void MonitorResource()
{
    // DRAW RECT
	float xrect = 0.05000002f;
	float yrect = 0.96f;
	float wrect = 1.9f;
	float hrect = 0.08f;
	RH_DrawRect(xrect, yrect, wrect, hrect, 0, 0, 0, 100);

    // DISPLAY CPU USAGE


    // DISPLAY MEMORY USAGE
    const char* memoryusage = getMemoryUsage();
    float xmem = 0.11f;
    float ymem = 0.979999f;
    float scale = 0.03f;
    RH_DrawText(memoryusage, xmem, ymem, 1, scale, 255, 255, 255, 255, TextAlignment_Center);
}

// On screen Debug
void onScreenDebug(std::vector<const char*> texts, float x, float y, float scale = 0.03f, int bgalpha = 150, int fgalpha = 300)
{
    float width = 0.0f;
    float height = 0.0f;
    for (const char* text : texts)
    {
        height += scale;
        width = max(width, RH_GetTextWidth(text, 1, scale));
    }
    
    RH_DrawRect(x+(width/2), y+((height - scale)/2), width + scale, height + scale, 0, 0, 0, bgalpha);
    for (const char* text : texts)
    {
        RH_DrawText(text, x, y, 1, scale, 255, 255, 255, fgalpha, TextAlignment_Left);
        y += scale;
    }
}