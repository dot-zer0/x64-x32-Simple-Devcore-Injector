#pragma once

#include <Windows.h>

class Inject
{
public:
    DWORD pid = 0;

    void* InjectToProcess();
    void* DevcoreForever();

    const char* DevcoreLink = "https://vk.com/devcore_community/";
    const char* DevcoreLink2 = "https://vk.com/devcore_posidelki/";

    const char* DllWay = "C:\\blablabla\\bla\\your_dll_name.dll";
};

Inject cInject;
Inject *pInject; // указатель для вызова функции, аче)