///////////////////////////////////////////////////////////////
// Created: 21.01.2025
// Author: ChatGPT, NS_Deathman
// Input realization
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
#include "stdafx.h"
///////////////////////////////////////////////////////////////
class CInput
{
  private:
	const Uint8* m_KeyBoardStates;

	// Array to track key pressed states
	bool m_bKeyPressed[SDL_NUM_SCANCODES];

  public:
	CInput();
	~CInput() = default;

	void OnFrame();
	bool KeyPressed(int key);
	bool KeyHolded(int key);
};
///////////////////////////////////////////////////////////////
extern CInput* Input;
///////////////////////////////////////////////////////////////
