///////////////////////////////////////////////////////////////
//Created: 14.01.2025
//Author: NS_Deathman
//Precompiled header - place your includes here
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
//#define USE_DX11
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

#ifdef USE_DX11
#include "render_DX11_stdafx.h"
#else
#include "render_DX9_stdafx.h"
#endif
///////////////////////////////////////////////////////////////
#include <imgui/imgui.h>
#include <Imgui/backends/imgui_impl_sdl2.h>
#ifdef USE_DX11
#include <imgui/backends/imgui_impl_dx11.h>
#else
#include <imgui/backends/imgui_impl_dx9.h>
#endif
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
#pragma comment(lib, "SDL2.lib")
///////////////////////////////////////////////////////////////