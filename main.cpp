#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

int main() {

    DWORD procId = GetProcId(L"Among Us.exe");

    if(procId == 0)
    {
        std::cout << "Could not find Among Us.exe! Exiting..." << std::endl;
        Sleep(1.5 * 1000);
        return 0;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"GameAssembly.dll");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x02C6C310;

    std::vector<unsigned int> addrOffsets = { 0x5c, 0x0, 0x60, 0x2c, 0x8, 0x5c, 0x30};
    uintptr_t yPosAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, addrOffsets);
    uintptr_t xPosAddr = yPosAddr - 4;

    float xPosValue = 0.0f, yPosValue = 0.0f;

    ReadProcessMemory(hProcess, (BYTE*)xPosAddr, &xPosValue, sizeof(xPosValue), nullptr);
    ReadProcessMemory(hProcess, (BYTE*)yPosAddr, &yPosValue, sizeof(yPosValue), nullptr);

    float xMedBay = -9.157f, yMedBay = -4.309f;
    float xUpperEngine = -16.837f, yUpperEngine = 2.415f;
    float xReactor = -20.348f, yReactor = -5.288f;
    float xSecurity = -13.371f, ySecurity = -4.901f;
    float xLowerEngine = -15.158f, yLowerEngine = -11.839f;
    float xElectrical = -7.667f, yElectrical = -8.463f;
    float xStorage = -1.790f, yStorage = -15.586f;
    float xCommunications = 3.846f, yCommunications = -15.574f;
    float xShields = 9.309f, yShields = -12.609f;
    float xNavigation = 16.579f, yNavigation = -4.589f;
    float xOxygen = 6.459f, yOxygen = -3.470f;
    float xWeapons = 8.726f, yWeapons = 1.609f;
    float xCafeteria = -0.859f, yCafeteria = 2.368f;
    float xAdmin = 5.344f, yAdmin = -7.453f;

    WriteProcessMemory(hProcess, (BYTE*)xPosAddr, &xStorage, sizeof(xStorage), nullptr);
    WriteProcessMemory(hProcess, (BYTE*)yPosAddr, &yStorage, sizeof(yStorage), nullptr);

    getchar();
    return 0;

}
