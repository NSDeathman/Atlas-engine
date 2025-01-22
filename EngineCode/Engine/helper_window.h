///////////////////////////////////////////////////////////////
// Created: 16.01.2025
// Author: NS_Deathman
// ImGui helping window
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
#include "stdafx.h"
///////////////////////////////////////////////////////////////
extern bool g_bNeedRestart;
extern bool g_bWireframeMode;
///////////////////////////////////////////////////////////////
class CHelperWindow
{
  private:
	bool m_bNeedDraw;
	bool m_bNeedQuitToMainMenu;

	bool m_bNeedDrawSettings;

  public:
	CHelperWindow();
	~CHelperWindow() = default;

	void DrawSettings();

	void Draw();
	void Show();
	void Hide();

	bool NeedQuitToMainMenu();
	void QuitingToMainMenuIsDone();
};
///////////////////////////////////////////////////////////////
extern CHelperWindow* HelperWindow;
///////////////////////////////////////////////////////////////
