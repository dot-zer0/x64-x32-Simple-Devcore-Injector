#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <cstdio>
#include "class_inject.hpp"

int main()
{
    std::cout << "Devcore Injector\n";
    std::cout << "Process ID: ";

    std::cin >> cInject.pid;

    pInject->InjectToProcess();
}

void* Inject::InjectToProcess()
{
    HANDLE HandleGame = OpenProcess(PROCESS_ALL_ACCESS, false, cInject.pid);

    if (!OpenProcess(PROCESS_ALL_ACCESS, false, cInject.pid))
    {
        std::cout << "OpenProcess failed. GetLastError(): %d\n", GetLastError();
        system("pause");
    }
    else
    {
        std::cout << "OpenProcess Successfully!\n";
    }

    HMODULE HandleKernel32 = GetModuleHandleA("kernel32.dll");

    if (!GetModuleHandleA("kernel32.dll"))
    {
        std::cout << "GetModuleHandleA failed. GetLastError(): %d\n", GetLastError();
    }
    else
    {
        std::cout << "GetModuleHandleA Successfully!\n";
    }

    LPVOID LPLoadLibrary = GetProcAddress(HandleKernel32, "LoadLibraryA");

    if (!GetProcAddress(HandleKernel32, "LoadLibraryA"))
    {
        std::cout << "LoadLibraryA failed. GetLastError(): %d\n", GetLastError();
    }
    else
    {
        std::cout << "LoadLibraryA Successfully!\n";
    }

    LPVOID VirtualAllocExProcess = VirtualAllocEx(HandleGame, NULL, strlen(cInject.DllWay), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (!VirtualAllocEx(HandleGame, NULL, strlen(cInject.DllWay), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE))
    {
        std::cout << "VirtualAllocEx failed. GetLastError(): %d\n", GetLastError();
    }
    else
    {
        std::cout << "VirtualAllocEx Successfully!\n";
    }

    WriteProcessMemory(HandleGame, VirtualAllocExProcess, cInject.DllWay, strlen(cInject.DllWay), NULL);

    CreateRemoteThread(HandleGame, NULL, NULL, (LPTHREAD_START_ROUTINE)LPLoadLibrary, VirtualAllocExProcess, NULL, NULL);

    if (!CreateRemoteThread(HandleGame, NULL, NULL, (LPTHREAD_START_ROUTINE)LPLoadLibrary, VirtualAllocExProcess, NULL, NULL))
    {
        std::cout << "CreateRemoteThread failed. GetLastError(): %d\n", GetLastError();
    }
    else
    {
        std::cout << "DLL Successfully Injected!\n";
        pInject->DevcoreForever();
        Beep(277, 500);
    }

    return 0;
}

void* Inject::DevcoreForever()
{
    ShellExecuteA(NULL, "open", cInject.DevcoreLink, NULL, NULL, SW_SHOWNORMAL);
    ShellExecuteA(NULL, "open", cInject.DevcoreLink2, NULL, NULL, SW_SHOWNORMAL);

    return 0;
}
