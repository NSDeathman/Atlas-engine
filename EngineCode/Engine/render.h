///////////////////////////////////////////////////////////////
// Created: 15.01.2025
// Author: NS_Deathman
// Renderer realization
///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
#include "stdafx.h"
///////////////////////////////////////////////////////////////
class CRender
{
  private:
	HWND m_hWindow;
	LPDIRECT3D9 m_pDirect3D;
	LPDIRECT3DDEVICE9 m_pDirect3dDevice;
	D3DPRESENT_PARAMETERS m_pDirect3DPresentParams;

	LPD3DXMESH m_pMesh;
	std::vector<D3DMATERIAL9> m_pMeshMaterials;
	std::vector<LPDIRECT3DTEXTURE9> m_pMeshTextures;
	DWORD m_dwNumMaterials;

	BOOL m_bDeviceLost;

  public:
	void CreateMainWindow();
	void InitializeDirect3D();
	void CreateMatrices();
	void Initialize();
	void RenderFrame();
	void HandleDeviceLost();
	void Reset();
	void Destroy();

	void LoadGeometry();
	void LoadMaterials();
	void LoadTextures();
	void LoadScene();

	CRender();
	~CRender() = default;
};
///////////////////////////////////////////////////////////////
extern CRender* Render;
///////////////////////////////////////////////////////////////
