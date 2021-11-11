#include "startup_reg.h"

bool StartupReg::uninstall()
{
    return false;
}

bool StartupReg::install()
{
    HKEY hKey = NULL;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
    {
        printf("[!] RegOpenKeyEx error %d\n", GetLastError());
        return false;
    }
    cout << "[*] RegOpenKeyEx success" << endl;

    if (RegSetValueExA(hKey, "startup_by_reg_demo", 0, REG_SZ, (const BYTE*)m_target_path.c_str(),
        m_target_path.length() + 1) != ERROR_SUCCESS)
    {
        printf("[!] RegSetValueEx error %d\n", GetLastError());
        return false;
    }
    cout << "[*] RegSetValueEx success" << endl;

    RegCloseKey(hKey);
    return true;
}
