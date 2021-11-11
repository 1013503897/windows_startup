#pragma once
#include "windows_startup.h"

class StartupReg :public Startup
{
public:
	bool uninstall();
	bool install();
};

