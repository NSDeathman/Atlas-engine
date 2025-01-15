///////////////////////////////////////////////////////////////
//Created: 15.01.2025
//Author: NS_Deathman
//Log realization
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
#include "stdafx.h"
///////////////////////////////////////////////////////////////
class CLog
{
private:

public:
	void CreateConsole();
	void __cdecl Print(LPCSTR format, ...);
	void __cdecl Debug_Print(LPCSTR format, ...);

	CLog();
	~CLog() = default;
};
///////////////////////////////////////////////////////////////
extern CLog* Log;
///////////////////////////////////////////////////////////////
