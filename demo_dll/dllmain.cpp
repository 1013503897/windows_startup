#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    //HANDLE hMutex = CreateMutex(NULL, TRUE, L"demo_dll");
    //if (GetLastError() == ERROR_ALREADY_EXISTS) {
        //if (hMutex) 
            //CloseHandle(hMutex);
        //return FALSE;
    //}
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        MessageBoxA(0, "hello world", "hello world", 0);
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

