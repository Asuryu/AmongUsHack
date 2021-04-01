#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

int main() {

    DWORD procId = GetProcId(L"Among Us.exe"); //IMPORTANTE MUDAR
    //std::cout << procId << std::endl;

    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"GameAssembly.dll"); //IMPORTANTE MUDAR

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    //std::cout << hProcess << std::endl;

    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x02C6C310; //IMPORTANTE MUDAR

    std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

    std::vector<unsigned int> ammoOffsets = { 0x5c, 0x0, 0x60, 0x2c, 0x8, 0x5c, 0x30}; //IMPORTANTE MUDAR 
    uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

    std::cout << "ammoAddr = " << "0x" << std::hex << ammoAddr << std::endl;

    float ammoValue = 0.0;

    /*ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "Current ammo = "  << ammoValue << std::endl;

    float newAmmo = -17.0;
    WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

    ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "New ammo = " << ammoValue << std::endl;*/


    getchar();
    return 0;

}
