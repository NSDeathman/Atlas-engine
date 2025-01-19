///////////////////////////////////////////////////////////////
//Created: 14.01.2025
//Author: NS_Deathman
//Precompiled header - place your includes here
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
#include <iostream>
#include <ppl.h>
#include <cstddef>

#include <Windows.h>
#include <mmsystem.h>

#include <vector>

#pragma warning(disable : 4996) // disable deprecated warning
#include <strsafe.h>
#pragma warning(default : 4996)
///////////////////////////////////////////////////////////////
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "msdmo.lib")
#pragma comment(lib, "Strmiids.lib")
///////////////////////////////////////////////////////////////
#include "defines.h"
#include "types.h"
///////////////////////////////////////////////////////////////
#include <d3dx9.h>
///////////////////////////////////////////////////////////////
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
///////////////////////////////////////////////////////////////
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_dx9.h>
#include <Imgui/backends/imgui_impl_win32.h>
///////////////////////////////////////////////////////////////
#pragma comment(lib, "Imgui.lib")
///////////////////////////////////////////////////////////////
// If you will create separated build 
// configuration, you must define in manually 
#ifdef DEBUG_BUILD
#define USE_OPTICK (1)
#endif
///////////////////////////////////////////////////////////////
#include <optick/optick.h>
///////////////////////////////////////////////////////////////
#ifdef USE_OPTICK
#pragma comment(lib, "OptickCore.lib")
#endif
///////////////////////////////////////////////////////////////
#include <SDL/SDL.h>
///////////////////////////////////////////////////////////////