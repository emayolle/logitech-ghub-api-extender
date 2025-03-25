#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcessID(const wchar_t* processName)
{
    // Create a snapshot of all processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    // Iterate over all processes
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(hSnapshot, &pe))
    {
        do
        {
            // Check if the process name matches
            if (wcscmp(pe.szExeFile, processName) == 0)
            {
                CloseHandle(hSnapshot);
                return pe.th32ProcessID;
            }
        } while (Process32NextW(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return 0;
}

int main()
{
    // Get the full path of the DLL
    char dllPath[MAX_PATH];
    GetFullPathNameA("lgextender.dll", MAX_PATH, dllPath, NULL);

    // Get the PID of the process named 
    DWORD processId = 0;

    printf("Searching for lghub_agent.exe...\n");

    do
    {
        processId = GetProcessID(L"lghub_agent.exe");
        Sleep(10);
    } while (processId == 0);

    printf("Found lghub_agent.exe with PID %d\n", processId);
    

    // Open the process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    // Allocate memory in the process
    LPVOID dllPathAddress = VirtualAllocEx(hProcess, NULL, sizeof(dllPath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    // Write the DLL path in the process
    WriteProcessMemory(hProcess, dllPathAddress, dllPath, sizeof(dllPath), NULL);

    // Get the address of LoadLibraryA
    HMODULE kernel32 = GetModuleHandleA("Kernel32.dll");
    FARPROC loadLibrary = GetProcAddress(kernel32, "LoadLibraryA");
    // Create a remote thread in the process
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, dllPathAddress, 0, NULL);

    printf("Injected lgextender.dll into lghub_agent.exe\n");

    return 0;
}