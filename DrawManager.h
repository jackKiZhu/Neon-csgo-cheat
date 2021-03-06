#pragma once
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_internal.h"
#include "ImGUI/DX9/imgui_impl_dx9.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ByteArrays/Flags.h"
#include "ByteArrays/glow_bytez.h" //открой папку проекта
#include "ByteArrays/modelka.h"
#include "ByteArrays/ararry.h"
#include "ByteArrays/icons.h"
#include "ByteArrays/button.h"
#include "kekekek.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "PreDLLMain.h"
//#include "configimport.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "ImGUI/imgui_internal.h"
#include <stdint.h>
//#include "Legitbot.h"
#include <iostream>
#include <fstream>  
#include <corecrt_io.h>

#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")
// 580 854

static int ispicinit = 0;
IDirect3DDevice9* mydevice;
IDirect3DTexture9* glow_tab[2] = { nullptr, nullptr };
IDirect3DTexture9*  galka = nullptr;
IDirect3DTexture9*  glock = nullptr;
IDirect3DTexture9*  skinfon = nullptr;
IDirect3DTexture9*  logotip = nullptr;
IDirect3DTexture9*  Flags[2] = { nullptr , nullptr };
IDirect3DTexture9*  model = nullptr;
IDirect3DTexture9*  button = nullptr;
IDirect3DTexture9*  nazad = nullptr;
IDirect3DTexture9*  podsvetka = nullptr;
IDirect3DTexture9*  buttonh = nullptr;
IDirect3DTexture9*  model2 = nullptr;
IDirect3DTexture9*  icons[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
ImFont*             Dejavu_bold[64];
ImFont*             Dejavu[64];


struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

class TempText
{
public:
	wchar_t szText[256];
	D3DCOLOR dwColor;
	int iX;
	int iY;
	ID3DXFont* pFont;
	bool bOutlined;
	bool bCenteredX;
	bool bCenteredY;
	bool bScissor;
	RECT cScissorRect;
	TempText( ) {
		wcscpy( szText, L"" );
		dwColor = 0;
		iX = 0;
		iY = 0;
		pFont = NULL;
		bOutlined = false;
		bScissor = false;
		cScissorRect = RECT( );
	}
	TempText( wchar_t _Text[256], D3DCOLOR _Color, int _X, int _Y, ID3DXFont* _Font, bool _Outlined, bool _CenteredX, bool _CenteredY ) {
		wcscpy( szText, _Text );
		dwColor = _Color;
		iX = _X;
		iY = _Y;
		pFont = _Font;
		bOutlined = _Outlined;
		bCenteredX = _CenteredX;
		bCenteredY = _CenteredY;
		bScissor = false;
		cScissorRect = RECT( );
	}
};

class TempRect
{
public:
	int iX;
	int iY;
	int iWidth;
	int iHeight;
	D3DCOLOR Color;
	TempRect( ) {
		iX = 0;
		iY = 0;
		iWidth = 0;
		iHeight = 0;
		Color = D3DCOLOR_RGBA( 0, 0, 0, 255 );
	}
	TempRect( int _X, int _Y, int _Width, int _Height, D3DCOLOR _Color ) {
		iX = _X;
		iY = _Y;
		iWidth = _Width;
		iHeight = _Height;
		Color = _Color;
	}
};

/*
void InitFonts() {
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x044F, // Cyrillic
		0,
	};
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF(u8"C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());

	for (int i = 0; i < 64; i++)
		Dejavu_bold[i] = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", (i + 1), 0, ranges); //tahomabd
	for (int i = 0; i < 64; i++)
		Dejavu[i] = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahomabd.ttf", (i + 1), 0, ranges); // который ты мне кидал
}
*/
void InitImgs(IDirect3DDevice9* device)
{
	if (logotip == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &LOGO, sizeof(LOGO), 129, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logotip);
	if (Flags[0] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &RUS, sizeof(RUS), 23, 17, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Flags[0]);
	if (Flags[1] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &USA, sizeof(USA), 23, 17, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Flags[1]);
	if (model == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &CTModel, sizeof(CTModel), 221, 288, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &model);
	if (model2 == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &NameArarry, sizeof(NameArarry), 580, 854, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &model2);
	if (glow_tab[0] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Glow, sizeof(Glow), 51, 118, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &glow_tab[0]);
	if (glow_tab[1] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Glow180, sizeof(Glow180), 118, 86, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &glow_tab[1]);
	if (icons[0] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Aim, sizeof(Aim), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[0]);
	if (icons[1] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Wallhack, sizeof(Wallhack), 21, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[1]);
	if (icons[2] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Radar, sizeof(Radar), 21, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[2]);
	if (icons[3] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Skinss, sizeof(Skinss), 21, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[3]);
	if (icons[4] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Colors, sizeof(Colors), 21, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[4]);
	if (icons[5] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Inventory, sizeof(Inventory), 21, 14, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[5]);
	if (icons[6] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Triggerbot, sizeof(Triggerbot), 21, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[6]);
	if (icons[7] == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Other, sizeof(Other), 21, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &icons[7]);
	if (button == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &iButton, sizeof(iButton), 129, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &button);
	if (buttonh == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &ibuttonh, sizeof(ibuttonh), 129, 27, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &buttonh);
	if (skinfon == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &Fon, sizeof(Fon), 92, 69, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &skinfon);
	if (nazad == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &kekekek, sizeof(kekekek), 32, 28, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &nazad);
	if (podsvetka == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &pods, sizeof(pods), 32, 28, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &podsvetka);
	if (glock == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &glocki, sizeof(glocki), 270, 169, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &glock);

}
bool FileExists(const char *fname)
{
	return access(fname, 0) != -1;
}


namespace Font
{
	ID3DXFont* ESP;
	ID3DXFont* Menu;
	ID3DXFont* MenuTitle;
	ID3DXFont* MenuItem;
	ID3DXFont* Small;
	ID3DXFont* Icons;
	ID3DXFont* IconsBig;
	ID3DXFont* Watermark;
};

namespace D
{
	IDirect3DDevice9*		m_pDevice;
	IDirect3DStateBlock9*	m_pStateBlock; 
	ID3DXSprite*			m_pTextSprite;
	ImDrawList*				m_pDrawList;
	ImDrawData				m_pDrawData;
	ImDrawListSharedData m_SharedData;

	bool					m_bSetuped;
	std::vector<TempText>	m_Strings( 512 );			// 
	std::vector<TempText>	m_PostStrings( 128 );		// This getto shit cuz i want render d3d font AND imgui drawlist
	std::vector<TempRect>	m_PostRects( 128 );		// 

	ImU32 GetImColor( const Color c ) {
		return ( ImU32 )ImColor( c[0], c[1], c[2], c[3] );
	}

	D3DCOLOR GetD3DColor( const Color c ) {
		return D3DCOLOR_ARGB( c[3], c[0], c[1], c[2] );
	}

	RECT GetTextSize( const char* text, ID3DXFont* font ) {
		RECT rcRect = { 0,0,0,0 };
		font->DrawText( NULL, text, strlen( text ), &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB( 0, 0, 0 ) );
		return rcRect;
	}

	RECT GetTextSize( wchar_t* text, ID3DXFont* font ) {
		RECT rcRect = { 0,0,0,0 };
		font->DrawTextW( NULL, text, lstrlenW( text ), &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB( 0, 0, 0 ) );
		return rcRect;
	}



	

	bool Setup( IDirect3DDevice9* pDevice ) {
		
		//InitFonts();
		
		if (ispicinit == 0) {
			mydevice = pDevice;
			InitImgs(pDevice);
			ispicinit = 1;
		}
		static bool anime = true; //найс названия f[ f[f[сf[раf[зу понятно что значат + инжекть хуи
		if( anime ) {
			m_SharedData = ImDrawListSharedData( );
			anime = false;

			ImGui_ImplWin32_Init( G::WindowHandle );
			ImGui_ImplDX9_Init( pDevice );

			ImFontConfig* cfg = new ImFontConfig();
			cfg->OversampleH = cfg->OversampleV = 1.0f;
			cfg->PixelSnapH = true;

			ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 13.0f, cfg, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		}

		if( !pDevice )
			return false;

		m_Strings.reserve( 512 );
		m_PostStrings.reserve( 128 );
		m_PostRects.reserve( 128 );

		m_pDevice = pDevice;

		if( !m_pDrawList )
			m_pDrawList = new ImDrawList( &m_SharedData );

		if( FAILED( D3DXCreateFontA( m_pDevice, 14, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, "Arial", &Font::ESP ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 14, 0, FW_BOLD, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, "Arial", &Font::Watermark ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 11, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "csgo_icons", &Font::Icons ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 16, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "csgo_icons", &Font::IconsBig ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 12, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &Font::Menu ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 42, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &Font::MenuTitle ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 28, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &Font::MenuItem ) ) )
			return false;
		if( FAILED( D3DXCreateFontA( m_pDevice, 11, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &Font::Small ) ) )
			return false;
		if( FAILED( m_pDevice->CreateStateBlock( D3DSBT_PIXELSTATE, &m_pStateBlock ) ) )
			return false;
		if( FAILED( D3DXCreateSprite( m_pDevice, &m_pTextSprite ) ) )
			return false;

		return true;
	}

	bool Begin( IDirect3DDevice9* pDevice ) {
		if( !m_bSetuped ) {
			if( !Setup( pDevice ) )
				return false;

			wchar_t icon[32] = { 0xE007 }; // ak47
			RECT iconRect = GetTextSize( icon, Font::Icons );
			if( iconRect.right != 31 ) {
				/*Options::Visuals::ESP::WeaponIconBlocked = true;
				Options::Visuals::ESP::WeaponIcon = false;*/

				DEVMSG( "Installing font..." );
				wchar_t szTemp[MAX_PATH]; GetTempPathW( MAX_PATH, szTemp );
				wchar_t szPath[MAX_PATH];
				swprintf_s( szPath, L"%srx_font.ttf", szTemp );

				DWORD dwDownloadToFile = URLDownloadToFileW( NULL, L"http://cheat.best/font.ttf", szPath, 0, NULL );

				if( dwDownloadToFile != S_OK ) {
					DEVMSG( "Failed loading font!" );
					//MakeNotify("ERROR: Failed initializing icons!");
					Options::Visuals::ESP::WeaponIconBlocked = true;
					Options::Visuals::ESP::WeaponIcon = false;
				} else {
					if( !AddFontResourceW( szPath ) ) {
						DEVMSG( "Failed adding font!" );
						//MakeNotify("ERROR: Failed initializing icons!");
						Options::Visuals::ESP::WeaponIconBlocked = true;
						Options::Visuals::ESP::WeaponIcon = false;
					} else {
						DEVMSG( "Font was installed!" );
						D3DXCreateFontA( m_pDevice, 11, 0, 0, 0, false, DEFAULT_CHARSET | RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "csgo_icons", &Font::Icons );
					}
					_wremove( szPath );
				}
			}

			m_bSetuped = true;
		}

		ImGui_ImplDX9_NewFrame( );
		m_pDrawData.Valid = false;
		m_pDrawList->Clear( );
		m_pDrawList->PushClipRectFullScreen( );
		return true;
	}

	bool End( ) {

		return true;
	}

	bool Lost( ) {
		SAFERELEASE( Font::ESP );
		SAFERELEASE( Font::Watermark );
		SAFERELEASE( Font::Menu );
		SAFERELEASE( Font::MenuTitle );
		SAFERELEASE( Font::MenuItem );
		SAFERELEASE( Font::Small );
		SAFERELEASE( Font::Icons );
		SAFERELEASE( Font::IconsBig );
		SAFEDELETE( m_pDrawList );
		SAFERELEASE( m_pStateBlock );
		SAFERELEASE( m_pTextSprite );

		m_pDrawList = nullptr;

		return true;
	}

	bool Cursor( float offsetX, float offsetY ) {
		m_pDrawList->PathLineTo( { offsetX, offsetY } );
		m_pDrawList->PathLineTo( { offsetX + 6, offsetY + 12 } );
		m_pDrawList->PathLineTo( { offsetX + 12, offsetY + 6 } );
		m_pDrawList->PathFillConvex( GetImColor( Color::White( ) ) );
		return true;
	}

	bool Text( int x, int y, const Color color, bool centeredX, bool centeredY, ID3DXFont* font, const char* text, ... ) {
		if( !font )
			return false;

		static char buffer[256] = "";
		va_list va;
		va_start( va, text );
		vsnprintf_s( buffer, 256, text, va );
		va_end( va );
		wchar_t szString[256] = L"";
		MultiByteToWideChar( CP_UTF8, 0, buffer, -1, szString, 256 );

		bool bOutlined = font == Font::ESP || Font::Watermark || font == Font::Menu;
		m_Strings.push_back( TempText( szString, GetD3DColor( color ), x, y, font, bOutlined, centeredX, centeredY ) );

		return true;
	}

	bool Text( int x, int y, const Color color, bool centeredX, bool centeredY, ID3DXFont* font, wchar_t* text, ... ) {
		if( !font )
			return false;

		static wchar_t buffer[256] = L"";
		va_list va;
		va_start( va, text );
		_vsnwprintf_s( buffer, 256, text, va );
		va_end( va );

		bool bOutlined = font == Font::ESP || font == Font::Menu;
		m_Strings.push_back( TempText( buffer, GetD3DColor( color ), x, y, font, bOutlined, centeredX, centeredY ) );

		return true;
	}

	bool TextNew( int x, int y, const Color color, bool centeredX, bool centeredY, ID3DXFont* font, const char* text, ... ) {
		/*if (!font)
			return false;

		static char buffer[256] = "";
		va_list va;
		va_start(va, text);
		vsnprintf_s(buffer, 256, text, va);
		va_end(va);

		bool bOutlined = font == Font::ESP || font == Font::Menu;
		m_Strings.push_back(TempText(buffer, GetD3DColor(color), x, y, font, bOutlined, centeredX, centeredY));

		int i = 0;
		int j = 0;
		const char* p = text;
		while (*p)
		{
			if (*p == '\n')
			{
				i++;
				m_Strings.push_back(TempText((std::string(buffer).substr(j, i).c_str()), GetD3DColor(color), x, y, font, bOutlined, centeredX, centeredY));
				j = i;
			}
			else p += 1;
		}*/

		return true;
	}

	void Line( float x1, float y1, float x2, float y2, const Color color, float w = 1.0f, bool antialias = true ) {
		/*x1 = (int)x1;
		y1 = (int)y1;
		x2 = (int)x2;
		y2 = (int)y2;*/

		//    if (Flags & ImDrawListFlags_AntiAliasedLines)

		auto backup = m_pDrawList->Flags;
		if( !antialias )
			m_pDrawList->Flags &= ~ImDrawListFlags_AntiAliasedLines;
		else
			m_pDrawList->Flags |= ImDrawListFlags_AntiAliasedLines;

		m_pDrawList->AddLine( { x1, y1 }, { x2, y2 }, GetImColor( color ), w ); 
		m_pDrawList->Flags = backup;
	}

	void Rect(float x, float y, float w, float h, float thickness, const Color color, bool hui = 0, bool centered = false, bool aa = true) {
		if( centered ) {
			x -= w / 2;
			y -= h / 2;
		}
		x = ( int )x;
		y = ( int )y;
		w = ( int )w;
		h = ( int )h;

		auto backup = m_pDrawList->Flags;
		if( !aa )
			m_pDrawList->Flags &= ~ImDrawListFlags_AntiAliasedLines;
		else
			m_pDrawList->Flags |= ImDrawListFlags_AntiAliasedLines;

		m_pDrawList->AddRect( { x, y }, { x + w, y + h }, GetImColor( color ), Options::Visuals::ESP::BoxRounding, -1, Options::Visuals::ESP::BoxWidth);
		m_pDrawList->Flags = backup;
	}

	void RectFilled( float x, float y, float w, float h, const Color color, bool centered = false, bool centeredX = false ) {
		if( centered ) {
			x -= w / 2;
			if( !centeredX ) y -= h / 2;
		}

		m_pDrawList->AddRectFilled( { x, y }, { x + w, y + h }, GetImColor( color ), Options::Visuals::ESP::BoxRounding);
	}

	bool RenderRect( int x1, int y1, int w, int h, const Color color, int outline = 0, const Color outlineColor = Color::Black( ) ) {
		if( outline > 0 )
			RectFilled( x1 - outline, y1 - outline, w + ( outline * 2 ), h + ( outline * 2 ), outlineColor, false, false );

		D::RectFilled( x1, y1, w, h, color, false, false );
		return true;
	}

	void RectFilledXY( float x1, float y1, float x2, float y2, const Color color ) {
		m_pDrawList->AddRectFilled( { x1, y1 }, { x2, y2 }, GetImColor( color ) );
	}

	void TriangleFilled( float x1, float y1, float x2, float y2, float x3, float y3, const Color color ) {
		m_pDrawList->AddTriangleFilled( ImVec2{ x1, y1 }, ImVec2{ x2, y2 }, { x3, y3 }, GetImColor( color ) );
	}

	void PostRect( int x, int y, int width, int height, Color color, bool bOutlined = false ) {
		if( bOutlined ) D::m_PostRects.push_back( TempRect( x - 1, y - 1, width + 2, height + 2, D3DCOLOR_RGBA( 0, 0, 0, 255 ) ) );
		D::m_PostRects.push_back( TempRect( x, y, width, height, D::GetD3DColor( color ) ) );
	}

	void Circle( float x, float y, int r, int segments, float w, const Color col ) {
		m_pDrawList->AddCircle( { x, y }, r, GetImColor( col ), segments, w );
	}

	void CircleFilled( float x, float y, int r, const Color col ) {
		m_pDrawList->AddCircleFilled( { x, y }, r, GetImColor( col ) );
	}

	void Circle3D( Vector3 vPosition, float flRadius, Color cColor, bool bCrosshair = false ) {
		static float flStep = M_PI * 2.0f / 40;
		Vector3 vPrev;

		vPosition.z -= 64.f;
		Vector3 vCenter;
		if( !Math::WorldToScreen( vPosition, vCenter ) )
			return;

		for( float flLat = 0, i = 0; flLat <= M_PI * 2.0f + flStep; flLat += flStep, i++ ) {
			float flSin1 = sin( flLat );
			float flCos1 = cos( flLat );

			float flSin3 = sin( 0.0 );
			float flCos3 = cos( 0.0 );

			Vector3 vPoint1;
			vPoint1 = Vector3( flSin1 * flCos3, flCos1, flSin1 * flSin3 ) * flRadius;

			Vector3 vPoint3 = vPosition + vPoint1;
			if( Math::WorldToScreen( vPoint3, vPoint3 ) ) {
				if( flLat != 0 ) {
					D::Line( vPrev.x, vPrev.y, vPoint3.x, vPoint3.y, cColor, 2, false );

					if( bCrosshair && i >= 4 ) {
						i = -1;
						D::Line( vCenter.x, vCenter.y, vPoint3.x, vPoint3.y, cColor, 1, false );
					}
				}
			} else return;

			vPrev = vPoint3;
		}
	}

	bool Render( bool bRenderImGUI = true, bool bRenderD3D = true ) {
		if( bRenderImGUI ) {
			if( !m_pDrawList->VtxBuffer.empty( ) ) {
				m_pDrawData.Valid = true;
				m_pDrawData.CmdLists = &m_pDrawList;
				m_pDrawData.CmdListsCount = 1;
				m_pDrawData.TotalVtxCount = m_pDrawList->VtxBuffer.Size;
				m_pDrawData.TotalIdxCount = m_pDrawList->IdxBuffer.Size;
				m_pDrawData.DisplaySize = ImGui::GetIO().DisplaySize;
			}
			ImGui_ImplDX9_RenderDrawData( &m_pDrawData );
		}

		if( bRenderD3D ) {
			m_pStateBlock->Capture( ); // imgui shit
			m_pDevice->SetPixelShader( NULL );
			m_pDevice->SetVertexShader( NULL );
			m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
			m_pDevice->SetRenderState( D3DRS_LIGHTING, false );
			m_pDevice->SetRenderState( D3DRS_ZENABLE, false );
			m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
			m_pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, false );
			m_pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
			m_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			m_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			m_pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, true );
			m_pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, 0xFFFFFFFF );
			m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
			m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
			m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
			m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
			m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
			m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

			DWORD dwOldFVF;
			m_pTextSprite->Begin( D3DXSPRITE_ALPHABLEND );
			m_pDevice->GetFVF( &dwOldFVF );
			m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
			for each ( TempText t in m_Strings ) {
				if( !t.pFont )
					continue;
				if( !wcscmp( t.szText, L"" ) )
					continue;
				wchar_t szString[256] = L"";
				wcscpy( szString, t.szText );

				RECT rcRect = GetTextSize( szString, t.pFont );
				if( t.bCenteredX )
					t.iX -= ( rcRect.right - rcRect.left ) / 2;
				if( t.bCenteredY )
					t.iY -= ( rcRect.bottom - rcRect.top ) / 2;

				m_pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, t.bScissor );
				m_pDevice->SetScissorRect( &t.cScissorRect );
				int iLength = wcslen( szString );
				RECT Pos;
				Pos.left = t.iX + 1;
				Pos.top = t.iY + 1;
				if( t.bOutlined ) t.pFont->DrawTextW( m_pTextSprite, szString, iLength, &Pos, DT_NOCLIP, GetD3DColor( Color::Black( ( t.dwColor >> 24 ) & 255 ) ) );
				Pos.left = t.iX;
				Pos.top = t.iY;
				t.pFont->DrawTextW( m_pTextSprite, szString, iLength, &Pos, DT_NOCLIP, t.dwColor );
				m_pDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, false );
			}
			m_Strings.clear( );
			m_pDevice->SetFVF( dwOldFVF );
			m_pTextSprite->End( );
			m_pStateBlock->Apply( );
		}

		return true;
	}

	bool PostRender( ) {
		if( m_PostRects.size( ) > 0 ) {
			for each ( TempRect r in m_PostRects ) {
				D3DRECT Rect = { r.iX, r.iY, r.iX + r.iWidth, r.iY + r.iHeight };
				m_pDevice->Clear( 1, &Rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, r.Color, 0, 0 );
			}
			m_PostRects.clear( );
		}

		if( m_PostStrings.size( ) > 0 ) {
			m_Strings.swap( m_PostStrings );
			m_PostStrings.clear( );
		}
		Render( false, true );

		return true;
	}

};
