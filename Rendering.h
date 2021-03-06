#pragma once
#include <intrin.h>  
#include <memory>

int g_iScreenWidth, g_iScreenHeight;
int g_iScreenCenterX, g_iScreenCenterY;

#include "Visuals.h"
#include "GUI.h"

CVMTHookManager* d3d_hook = nullptr;

//void SetGameFps( ) {
//	static DWORD NetGraphPanel = **( DWORD** )( ( DWORD )( U::FindPattern( "client.dll", "NetGraphPanelThis", "C7 05 ? ? ? ? ? ? ? ? C7 06 ? ? ? ? 8B 8E ? ? ? ?" ) + 0x2 ) );
//
//	//	printf("client - 0x%X\nNetGraphPanel - 0x%X\n", ClientAdr, NetGraphPanel);
//	float& framerate = *( float* )( NetGraphPanel + 0x131B8 );
//	framerate = Options::Misc::fakeFPS;
//}

void Render( IDirect3DDevice9* device ) {
	//if( g_pServer )
	//	g_pServer->ReceiveMessage( );

	//Sequrity::OnRender( );

	if( !D::m_bSetuped ) {
		CChams::Generate( device );
		g_pEngine->GetScreenSize( g_iScreenWidth, g_iScreenHeight );
		g_iScreenCenterX = g_iScreenWidth / 2;
		g_iScreenCenterY = g_iScreenHeight / 2;
	}

	if( D::Begin( device ) && D::m_bSetuped && Font::ESP ) {
		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );
		CVisuals::Render( );
		CChams::Render( device );
		D::Render( false, true );

		//if( Options::Misc::FakeFPSEnable )
		//	SetGameFps( );

		if( G::MenuOpened )
			CMenu::Render( );
		
		if( D::m_bSetuped && Font::ESP ) {
			CMenu::DrawRadar( );
			CMenu::DrawSpectatorList( );
			//WalkBot::Run( );
			NotifySystem::Render( );	
			EventList::Render( );
		}

		D::Render( );
		D::PostRender( );
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
	}
}

//typedef long( __stdcall* PresentFn )( IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion );
//PresentFn oPresent;

typedef long( __stdcall* ResetFn )( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp );
ResetFn oReset;


typedef HRESULT(WINAPI* EndSceneFn)(IDirect3DDevice9* device);
EndSceneFn oEndScene;


extern  void Init();


//long __stdcall Hooked_Present( IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
HRESULT WINAPI  Hooked_EndScene(IDirect3DDevice9* device)
{	
	
	/*static DWORD gameoverlay_return_address = 0;

	if (!gameoverlay_return_address) {
		MEMORY_BASIC_INFORMATION info;
		fnZwQueryVirtualMemory(_GetCurrentProcess(), _ReturnAddress(), MemoryBasicInformation, &info, sizeof(info), 0);

		char mod[MAX_PATH];
		GetModuleFileNameA((HMODULE)info.AllocationBase, mod, MAX_PATH);

		if (_strstr(mod, ("gameoverlay")))
			gameoverlay_return_address = (DWORD)(_ReturnAddress());
	}

	if (gameoverlay_return_address != (DWORD)(_ReturnAddress())) {
		return oEndScene(device);
	}
*/




	IDirect3DVertexDeclaration9* vertDec;
	IDirect3DVertexShader9* vertShader;
	device->GetVertexDeclaration(&vertDec);
	device->GetVertexShader(&vertShader);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);

	device->SetVertexDeclaration(nullptr);
	device->SetVertexShader(nullptr);

	DWORD colorwrite;
	device->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);


	Render(device);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	device->SetVertexDeclaration(vertDec);
	device->SetVertexShader(vertShader);

	return oEndScene(device);
}

long __stdcall Hooked_Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters ) {
	auto tramploline = d3d_hook->get_original<ResetFn>( 16 );

	if( !D::m_bSetuped )
		return tramploline( pDevice, pPresentationParameters );

	CChams::Reset( );
	ImGui_ImplDX9_InvalidateDeviceObjects( );
	D::Lost( );

	auto hr = oReset( pDevice, pPresentationParameters );
	
	D::m_bSetuped = false;
	ImGui_ImplDX9_CreateDeviceObjects( );
	return hr;
}
