#include <windows.h>
#include <iostream>
#include "PatternScanner.h"
#include "minhook/MinHook.h"
#include "sdk/lghub_agent.h"

#include "hooks/LuaVMInitializer.h"

using namespace PatternScanner;

int main() {
    uintptr_t lghub_agent = (uintptr_t)GetModuleHandleA("lghub_agent.exe");

    if (lghub_agent == NULL) {
        MessageBoxA(0, "lghub_agent.exe not found", "Error", MB_ICONERROR);
        return 1;
    }

    // PatternScanning to search for the LuaVMInitializer function
    auto pattern = CREATE_PATTERN("4C 89 44 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24", 0, PatternScanner::PatternType::FUNCTION);
    auto LuaVMInitializerAddress = PatternScanner::FindPattern(pattern, "lghub_agent.exe");

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "lghub_agent.exe: " << std::hex << lghub_agent << std::endl;

    if (LuaVMInitializerAddress == 0) {
        std::cout << "Pattern not found" << std::endl;
        return 1;
    }

    std::cout << "Pattern found at: " << std::hex << (lghub_agent + LuaVMInitializerAddress) << std::endl;

    if (MH_Initialize() != MH_OK) {
        std::cout << "Failed to initialize MinHook" << std::endl;
        return 1;
    }

    if (MH_CreateHook((LPVOID)(lghub_agent + LuaVMInitializerAddress), hkLuaVMInitializer, (LPVOID*)&LuaVMInitializer) != MH_OK) {
        std::cout << "Failed to create hook" << std::endl;
        return 1;
    }

    if (MH_EnableHook((LPVOID)(lghub_agent + LuaVMInitializerAddress)) != MH_OK) {
        std::cout << "Failed to enable hook" << std::endl;
        return 1;
    }


    return 0;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved )  // reserved
{
    if ( fdwReason == DLL_PROCESS_ATTACH) 
    {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}