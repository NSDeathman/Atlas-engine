﻿///////////////////////////////////////////////////////////////
//Created: 14.01.2025
//Author: NS_Deathman
//CApplication class realization
///////////////////////////////////////////////////////////////
#include "Application.h"
#include "render.h"
#include "log.h"
#include "build_identification_helper.h"
#include "threading.h"
///////////////////////////////////////////////////////////////
CRender* Render = NULL;
CLog* Log = NULL;
///////////////////////////////////////////////////////////////
void CApplication::Destroy()
{
	Log->Print("Destroying application...");

	delete(Render);
	delete(Log);
}

void CApplication::Start()
{
	Render = new(CRender);

    Render->Initialize();
}

void CApplication::ThreadWork()
{
	OPTICK_THREAD("Atlas worker thread")
	OPTICK_FRAME("ThreadWork")
	OPTICK_EVENT("ThreadWork")
	Sleep(200);
	Log->Print("Worker is free");
}

void CApplication::OnFrame()
{
	OPTICK_THREAD("Atlas primary thread")
	OPTICK_FRAME("CApplication::OnFrame")
	OPTICK_EVENT("CApplication::OnFrame")

	//Scheduler.Add(ThreadWork);
	concurrency::task_group task_secondary;
	task_secondary.run([&]() 
		{ 
			ThreadWork();
		});

	Render->RenderFrame();

	task_secondary.wait();
}

void CApplication::EventLoop()
{
	Log->Print("Starting event loop...");

	MSG msg_struct;
	ZeroMemory(&msg_struct, sizeof(msg_struct));
	while (msg_struct.message != WM_QUIT)
	{
		if (PeekMessage(&msg_struct, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg_struct);
			DispatchMessage(&msg_struct);
		}
		else
		{
			OnFrame();
		}
	}
}

void CApplication::Process()
{
	Log = new (CLog);

#ifdef _DEBUG
	Log->CreateConsole();
#endif

	Log->Print("Atlas engine");

	u32 MajorBuildID = compute_build_id_major();
	u32 MinorBuildID = compute_build_id_minor();
	Log->Print("BuildID: %d.%d", MajorBuildID, MinorBuildID);

#ifdef _DEBUG
	Log->Print("Build type: Debug");
#else
	Log->Print("Build type: Release");
#endif

	Log->Print("\n");

	Log->Print("Starting Application...");

	App->Start();

	Log->Print("Application started successfully");
	Log->Print("\n");

	App->EventLoop();

	Log->Print("Destroying Application...");

	App->Destroy();
}
///////////////////////////////////////////////////////////////
