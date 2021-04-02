#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
//#include <json/value.h>
#include <fstream>

void moveTo(float x, float y, HANDLE hProcess, uintptr_t xPosAddr, uintptr_t yPosAddr)
{
    WriteProcessMemory(hProcess, (BYTE*)xPosAddr, &x, sizeof(x), nullptr);
    WriteProcessMemory(hProcess, (BYTE*)yPosAddr, &y, sizeof(y), nullptr);
}

void tpHack(DWORD procId)
{
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"GameAssembly.dll");

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x02C6C310;

    std::vector<unsigned int> addrOffsets = { 0x5c, 0x0, 0x60, 0x2c, 0x8, 0x5c, 0x30 };
    uintptr_t yPosAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, addrOffsets);
    uintptr_t xPosAddr = yPosAddr - 4;

    float xPosValue = 0.0f, yPosValue = 0.0f;

    ReadProcessMemory(hProcess, (BYTE*)xPosAddr, &xPosValue, sizeof(xPosValue), nullptr);
    ReadProcessMemory(hProcess, (BYTE*)yPosAddr, &yPosValue, sizeof(yPosValue), nullptr);

    const float xMedBay = -9.157f, yMedBay = -4.309f,
                xUpperEngine = -16.837f, yUpperEngine = 2.415f,
                xReactor = -20.348f, yReactor = -5.288f,
                xSecurity = -13.371f, ySecurity = -4.901f,
                xLowerEngine = -15.158f, yLowerEngine = -11.839f,
                xElectrical = -7.667f, yElectrical = -8.463f,
                xStorage = -1.790f, yStorage = -15.586f,
                xCommunications = 3.846f, yCommunications = -15.574f,
                xShields = 9.309f, yShields = -12.609f,
                xNavigation = 16.579f, yNavigation = -4.589f,
                xOxygen = 6.459f, yOxygen = -3.470f,
                xWeapons = 8.726f, yWeapons = 1.609f,
                xCafeteria = -0.859f, yCafeteria = 2.368f,
                xAdmin = 5.344f, yAdmin = -7.453f;

    int tpLocation;
    
    std::cout << "Where to teleport?" << std::endl
              << "0 - Exit" << std::endl
              << "1 - Med Bay" << std::endl
              << "2 - Upper Engine" << std::endl
              << "3 - Reactor" << std::endl
              << "4 - Security" << std::endl
              << "5 - Lower Engine" << std::endl
              << "6 - Electrical" << std::endl
              << "7 - Storage" << std::endl
              << "8 - Communications" << std::endl
              << "9 - Shields" << std::endl
              << "10 - Navigation" << std::endl
              << "11 - Oxygen" << std::endl
              << "12 - Weapons" << std::endl
              << "13 - Cafeteria" << std::endl
              << "14 - Admin" << std::endl;

    while(true)
    {
        std::cin >> tpLocation;
        switch (tpLocation)
        {
            case 0:
                return;
            case 1:
                moveTo(xMedBay, yMedBay, hProcess, xPosAddr, yPosAddr);
                break; 
            case 2:    
                moveTo(xUpperEngine, yUpperEngine, hProcess, xPosAddr, yPosAddr);
                break; 
            case 3:    
                moveTo(xReactor, yReactor, hProcess, xPosAddr, yPosAddr);
                break; 
            case 4:    
                moveTo(xSecurity, ySecurity, hProcess, xPosAddr, yPosAddr);
                break; 
            case 5:    
                moveTo(xLowerEngine, yLowerEngine, hProcess, xPosAddr, yPosAddr);
                break; 
            case 6:    
                moveTo(xElectrical, yElectrical, hProcess, xPosAddr, yPosAddr);
                break; 
            case 7:    
                moveTo(xStorage, yStorage, hProcess, xPosAddr, yPosAddr);
                break; 
            case 8:    
                moveTo(xCommunications, yCommunications, hProcess, xPosAddr, yPosAddr);
                break; 
            case 9:    
                moveTo(xShields, yShields, hProcess, xPosAddr, yPosAddr);
                break; 
            case 10:   
                moveTo(xNavigation, yNavigation, hProcess, xPosAddr, yPosAddr);
                break; 
            case 11:   
                moveTo(xOxygen, yOxygen, hProcess, xPosAddr, yPosAddr);
                break; 
            case 12:   
                moveTo(xWeapons, yWeapons, hProcess, xPosAddr, yPosAddr);
                break; 
            case 13:   
                moveTo(xCafeteria, yCafeteria, hProcess, xPosAddr, yPosAddr);
                break; 
            case 14:   
                moveTo(xAdmin, yAdmin, hProcess, xPosAddr, yPosAddr);
                break;
            default:
                return;
        }
    }
}

int main() 
{
    DWORD procId = GetProcId(L"Among Us.exe");

    if(procId == 0)
    {
        std::cout << "Could not find Among Us.exe! Exiting..." << std::endl;
        Sleep(1.5 * 1000);
        return 0;
    }

    tpHack(procId);

    getchar();
    return 0;

}
