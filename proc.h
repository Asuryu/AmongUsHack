#pragma once

#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>

DWORD GetProcId(const wchar_t* procName);

std::uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

std::uintptr_t FindDMAAddy(HANDLE hProc, std::uintptr_t ptr, std::vector<unsigned int> offsets);
