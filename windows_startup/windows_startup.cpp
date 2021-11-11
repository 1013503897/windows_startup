#include "windows_startup.h"
#include "startup_dir.h"
#include "startup_reg.h"
#include "com_hijack.h"
#include "schtasks.h"

int main(int argc, char* argv[])
{
	/*
	string type = argv[1];
	if (argc > 2) {
		if (strcmp(argv[1], "-type"))
		{
			if (strcmp(argv[4], "reg"))
			{

			}
			else if (strcmp(argv[4], "wmi"))
			{

			}
			else if (strcmp(argv[4], "dir"))
			{

			}
			else if (strcmp(argv[4], "wmi"))
			{

			}
		}

		if (strcmp(argv[3], "-target_file"))
		{
		}
	}
	else
	{
		printf("Usage:\n	windows_startup.exe -install install startup\n	windows_startup.exe -uninstall uninstall startup\r\n");
	}*/
	Startup* startup;
	startup = new StartupSchtasks();
	startup->set_target("C:\\Users\\weixingyu\\Desktop\\demo_exe.exe");
	//startup->set_target("C:\\Users\\weixingyu\\Desktop\\demo_dll.dll");
	startup->install();
	return 0;
}

void Startup::set_target(string target_path)
{
	m_target_path= target_path;
	m_target_file = target_path.substr(target_path.find_last_of("/\\") + 1);
}
