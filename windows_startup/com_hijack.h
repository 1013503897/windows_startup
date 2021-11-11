#pragma once
#include "windows_startup.h"

class StartupCom : public Startup
{
public:
	bool uninstall();
	bool install();
};
