///////////////////////////////////////////////////////////////
//Created: 14.01.2025
//Author: NS_Deathman
//CApplication class realization
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
#include "stdafx.h"
///////////////////////////////////////////////////////////////
class CApplication
{
private:

public:
	void Start();
	void HandleSDLEvents();
	void OnFrame();
	void EventLoop();
	void Destroy();
	void Process();

	CApplication() = default;
	~CApplication() = default;
};
///////////////////////////////////////////////////////////////
extern CApplication* App;
///////////////////////////////////////////////////////////////
