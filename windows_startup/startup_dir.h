#pragma once
#include "windows_startup.h"

class StartupDir : public Startup
{
public:
	bool uninstall();
	bool install();
};

