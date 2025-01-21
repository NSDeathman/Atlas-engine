///////////////////////////////////////////////////////////////
// Created: 15.01.2025
// Author: NS_Deathman
// Renderer realization
///////////////////////////////////////////////////////////////
#include "render.h"
#include "Log.h"
#include "filesystem.h"
#include "resource.h"
#include "render_backend.h"
#include "OptickAPI.h"
#include "helper_window.h"
#include "scene.h"
#include "user_interface.h"
#include "main_window.h"
#include "camera.h"
///////////////////////////////////////////////////////////////
UINT g_ResizeWidth = NULL;
UINT g_ResizeHeight = NULL;
///////////////////////////////////////////////////////////////
extern LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
///////////////////////////////////////////////////////////////
CRender::CRender()
{
	m_hWindow = nullptr;
	m_pDirect3D = nullptr;
	m_pDirect3dDevice = nullptr;
	ZeroMemory(&m_pDirect3DPresentParams, sizeof(m_pDirect3DPresentParams));

	m_bDeviceLost = false;
	m_bNeedReset = false;

	m_bWireframe = false;

	m_iFrame = 0;
}

void CRender::Initialize()
{
	Msg("Initializing render...");
	InitializeDirect3D();
}

void CRender::Destroy()
{
	Msg("Destroying render...");

	SAFE_RELEASE(m_pDirect3dDevice);

	SAFE_RELEASE(m_pDirect3D);
}

void CRender::InitializeDirect3D()
{
	Msg("Initializing Direct3D...");

	m_hWindow = MainWindow->GetWindow();

	// Create the D3D object.
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	ASSERT(!(m_pDirect3D == NULL), "An error occurred while creating the Direct3D9");

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	ZeroMemory(&m_pDirect3DPresentParams, sizeof(m_pDirect3DPresentParams));
	m_pDirect3DPresentParams.Windowed = TRUE;
	m_pDirect3DPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pDirect3DPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
	m_pDirect3DPresentParams.EnableAutoDepthStencil = TRUE;
	m_pDirect3DPresentParams.AutoDepthStencilFormat = D3DFMT_D24X8;

	// Create the D3DDevice
	HRESULT hresult = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, 
												D3DDEVTYPE_HAL, 
												m_hWindow, 
												D3DCREATE_HARDWARE_VERTEXPROCESSING,
												&m_pDirect3DPresentParams, 
												&m_pDirect3dDevice);

	ASSERT(SUCCEEDED(hresult), "An error occurred while creating the Direct3D Device");

	if (SUCCEEDED(hresult))
		Msg("Direct3D created successfully");

	ShowWindow(m_hWindow, SW_SHOWDEFAULT);
	UpdateWindow(m_hWindow);

	GetCapabilities();
}

void CRender::GetCapabilities()
{
	D3DCAPS9 Capabilities;
	m_pDirect3dDevice->GetDeviceCaps(&Capabilities);

	MaxSimultaneousTextures = Capabilities.MaxSimultaneousTextures;
}

void CRender::CreateMatrices()
{
	// Create a camera
	CCamera Camera(D3DXVECTOR3(0.0f, 0.0f, -3.0f), // Position
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// Target
					D3DXVECTOR3(0.0f, 1.0f, 0.0f),	// Up
					90.0f,							// Field of View
					600.0f / 600.0f,				// Aspect Ratio
					0.1f,							// Near Plane
					100.0f							// Far Plane
	);

	// Get view and projection matrices
	D3DXMATRIX view = Camera.GetViewMatrix();
	m_pDirect3dDevice->SetTransform(D3DTS_VIEW, &view);

	D3DXMATRIX projection = Camera.GetProjectionMatrix();
	m_pDirect3dDevice->SetTransform(D3DTS_PROJECTION, &projection);

	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	m_pDirect3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

void CRender::Reset()
{
	Msg("Resetting render...");

	OnResetBegin();

	HRESULT result = m_pDirect3dDevice->Reset(&m_pDirect3DPresentParams);

	if (result == D3DERR_INVALIDCALL)
		ERROR_MESSAGE("Invalid call while device resetting");

	OnResetEnd();
}

void CRender::OnResetBegin()
{
	UserInterface->OnResetBegin();
}

void CRender::OnResetEnd()
{
	UserInterface->OnResetEnd();
}

void CRender::HandleDeviceLost()
{
	Msg("Device was lost, resetting render...");

	HRESULT result = m_pDirect3dDevice->TestCooperativeLevel();

	if (result == D3DERR_DEVICELOST)
		Sleep(10);

	if (result == D3DERR_DEVICENOTRESET)
		Reset();

	m_bDeviceLost = false;
}

void CRender::OnFrame()
{
	OnFrameBegin();
	RenderFrame();
	OnFrameEnd();
}

void CRender::RenderFrame()
{
	OPTICK_EVENT("CRender::RenderFrame")

	if (Scene->Ready())
		RenderScene();
}

void CRender::OnFrameBegin()
{
	OPTICK_EVENT("CRender::OnFrameBegin")

	if (m_bDeviceLost)
		HandleDeviceLost();

	if (m_bNeedReset || g_bNeedRestart)
	{
		Reset();
		m_bNeedReset = false;
		g_bNeedRestart = false;
	}

	UserInterface->OnFrameBegin();

	// Handle window resize (we don't resize directly in the WM_SIZE handler)
	if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
	{
		m_pDirect3DPresentParams.BackBufferWidth = g_ResizeWidth;
		m_pDirect3DPresentParams.BackBufferHeight = g_ResizeHeight;
		g_ResizeWidth = g_ResizeHeight = 0;
		m_bNeedReset = true;
	}

	// Clear the backbuffer and the zbuffer
	D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)1.0f * 255, (int)1.0f * 255, (int)1.0f * 255, (int)1.0f * 255);

	m_pDirect3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);

	// Setup the world, view, and projection matrices
	CreateMatrices();

	// Begin the scene
	HRESULT hresult = m_pDirect3dDevice->BeginScene();

	if (FAILED(hresult))
		Msg("Failed to begin scene render");
}

void CRender::OnFrameEnd()
{
	UserInterface->OnFrameEnd();

	// End the scene
	m_pDirect3dDevice->EndScene();

	// Present the backbuffer contents to the display
	HRESULT present_result = m_pDirect3dDevice->Present(NULL, NULL, NULL, NULL);

	if (present_result == D3DERR_DEVICELOST)
		m_bDeviceLost = true;

	m_iFrame++;
}

void CRender::RenderScene()
{
	// Turn on the zbuffer
	m_pDirect3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	RenderBackend->set_CullMode(CBackend::CULL_CCW);

	if (g_bWireframeMode)
		RenderBackend->set_FillMode(CBackend::FILL_WIREFRAME);

	Scene->DrawGeometry();

	if (g_bWireframeMode)
		RenderBackend->set_FillMode(CBackend::FILL_SOLID);
}
///////////////////////////////////////////////////////////////
