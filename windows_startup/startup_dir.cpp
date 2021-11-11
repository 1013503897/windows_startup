#include "startup_dir.h"

bool StartupDir::install()
{
	char szStartupPath[MAX_PATH] = { 0 };
	string dst_path;

	if (!SHGetSpecialFolderPathA(NULL, szStartupPath, CSIDL_STARTUP, TRUE))
	{
		cout << "[!] SHGetSpecialFolderPath error!" << endl;
		return false;
	}
	cout << "[*] startup dir:" << szStartupPath << endl;

	dst_path = szStartupPath + string("\\") + m_target_file;
	cout << "[*] startup file:" << dst_path << endl;

	if (!CopyFileA(m_target_path.c_str(), dst_path.c_str(), FALSE))
	{
		cout << "[!] CopyFile error with code:" << GetLastError() << "!" << endl;
		return false;
	}
	cout << "[*] copy file to" << dst_path << " success" << endl;
	return true;
}

bool StartupDir::uninstall()
{
	// TODO
	return false;
}

