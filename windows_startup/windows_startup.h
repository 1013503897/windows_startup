#pragma once
#include <iostream>
#include <Windows.h> 
#include <string>
#include <shlobj_core.h>

using namespace std;

class Startup
{
public:
	virtual bool uninstall() = 0;
	virtual bool install() = 0;
	void set_target(string target_path);

protected:
	string m_target_path;
	string m_target_file;
};