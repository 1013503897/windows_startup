#pragma once
#include "windows_startup.h"
class StartupSchtasks :public Startup
{
public:
	bool install();
	bool uninstall();
};

