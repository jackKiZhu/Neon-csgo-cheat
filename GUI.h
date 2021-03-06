#pragma once
#include "ImGUI/imgui_internal.h"
#include "ByteArrays/Flags.h"
#include "ByteArrays/glow_bytez.h"
#include "ByteArrays/modelka.h"
#include "ByteArrays/icons.h"
#include "ImGUI/DX9/imgui_impl_dx9.h"
//#include "ImGUI/DX9/imgui_impl_win32.h"
#include <d3d9.h>
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <map>
#include <dos.h>
#include <iostream>

#include <wininet.h>
#include <d3dx9.h>
#pragma comment (lib, "Wininet.lib")
#pragma comment (lib, "d3dx9.lib")
#include "skinsdef.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "DrawManager.h"
#include "ImGUI/imgui_internal.h"
#include <stdint.h>
#include "DrawManager.h"
#include "Legitbot.h"
#include <iostream>

#include <fstream>  
#include <ctime>

static int weaponnum = 0;
static bool needupdate = false;
static bool autoopred = true;
static bool safetychanger;
static std::pair<int, int> selected_knife = { knifesidn[Options::SkinChanger::KnifeTT] + 29, g_Weapons[U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT)].skininmenu};
static std::pair<int, int> selected_weapon = {3, g_Weapons[7].skininmenu};
static int selected_glove = Options::SkinChanger::Glovemenu;

void updateprev() {
	selected_knife = { knifesidn[Options::SkinChanger::KnifeTT] + 29, g_Weapons[U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT)].skininmenu };
	selected_weapon = { 3, g_Weapons[7].skininmenu };
	selected_glove = Options::SkinChanger::Glovemenu;
}

void showcurrentversion() {
	const char * vers = g_pEngine->GetProductVersionString();
	ImGui::Text(vers);
	static char chch4[15];
	itoa(g_pEngine->GetEngineBuildNumber(), chch4, 15);
	ImGui::Text(chch4);
}


bool ret_gloves(short idx) {
	switch (idx)
	{
	case GLOVE_STUDDED_BLOODHOUND:
	case GLOVE_T_SIDE:
	case GLOVE_CT_SIDE:
	case GLOVE_SPORTY:
	case GLOVE_SLICK:
	case GLOVE_LEATHER_WRAP:
	case GLOVE_MOTORCYCLE:
	case GLOVE_SPECIALIST:
	case GLOVE_HYDRA:
		return true;
	}
	return false;
}

IDirect3DTexture9 * getTexture(int gun, int index) {
	if ((alltextures[gun]).count(index) > 0) {
		return (alltextures[gun])[index];
	}
	//std::string linkToSkin = alllinks[gun][index];
	IDirect3DTexture9 *skinImg = nullptr;
	if (skinImg == nullptr) {
		//const char *skin = linkToSkin.c_str();
		//std::string imData = DownloadSkinBytes(skin);
		std::string imData = preres[{gun, index}];
		D3DXCreateTextureFromFileInMemoryEx(mydevice, imData.data(), imData.length(), 92, 69, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &skinImg);
	}
	(alltextures[gun])[index] = skinImg;
	return skinImg;
}

int GetLocalPing( ) {
	static DWORD PTAB = *( DWORD* )( U::FindPattern( "client_panorama.dll", "PRES", "8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7" ) );
	static auto local_pl = C_BasePlayer::LocalPlayer( );
	if( g_pEngine->IsConnected( ) )
		return *( int* )( PTAB + 0x0B28 + ( int )local_pl->GetIndex( ) * 4 );

	return 0;
}
#define WINDOW_INDENT 10
#define WINDOW_CENTER 400

/*__forceinline void Buyer() {
	GUI::Text("Buy the full version");
	if (GUI::Button("Buy"))ShellExecute(0, "open", "https://vk.com/aquacheat", 0, 0, SW_SHOWNORMAL);

}*/

int MenuH = 400, MenuW = 800;

bool DrawWeapon = false;
ItemDefinitionIndex CurrentWeapon = 0;
ItemDefinitionIndex LastWeapon = 0;

#pragma once

static bool nupdate = 0;
static bool inittime = 0;
static time_t ltime;
static bool language = Options::Misc::Language;
static int tab = 0;
static int sab_tab[7] = { 0,0,0,0,0,0,0 };
static int hovered_tab[8] = { 0,0,0,0,0,0,0,0 };
static int prosrachnost_spect = 170;
static bool texturing = false;

namespace ImGui
{
	bool Tab(const char* label, const ImVec2& size_arg, bool selected) {
		return ImGui::Button(label, size_arg);
	}

	using key_bind = std::pair<int, const char*>;
	std::vector<key_bind> vtable =
	{
	{ 0, ("None") },
	{ 1, ("Left Mouse") },
	{ 2, ("Right Mouse") },
	{ 3, ("Scroll Lock") },
	{ 4, ("Middle Mouse") },
	{ 5, ("X1 Mouse") },
	{ 6, ("X2 Mouse") },
	{ 8, ("Backspace") },
	{ 9, ("Tab") },
	{ 12, ("Num 5") },
	{ 13, ("Enter") },
	{ 16, ("Shift") },
	{ 17, ("Ctrl") },
	{ 18, ("RAlt") },
	{ 20, ("Caps Lock") },
	{ 27, ("Esc") },
	{ 32, ("Space") },
	{ 33, ("Num 9") },
	{ 34, ("Num 3") },
	{ 35, ("Num 1") },
	{ 36, ("Num 7") },
	{ 37, ("Num 4") },
	{ 38, ("Num 8") },
	{ 39, ("Num 6") },
	{ 40, ("Num 2") },
	{ 44, ("Sys Req") },
	{ 45, ("Num 0") },
	{ 46, ("Num Del") },
	{ 48, ("0") },
	{ 49, ("1") },
	{ 50, ("2") },
	{ 51, ("3") },
	{ 52, ("4") },
	{ 53, ("5") },
	{ 54, ("6") },
	{ 55, ("7") },
	{ 56, ("8") },
	{ 57, ("9") },
	{ 65, ("A") },
	{ 66, ("B") },
	{ 67, ("C") },
	{ 68, ("D") },
	{ 69, ("E") },
	{ 70, ("F") },
	{ 71, ("G") },
	{ 72, ("H") },
	{ 73, ("I") },
	{ 74, ("J") },
	{ 75, ("K") },
	{ 76, ("L") },
	{ 77, ("M") },
	{ 78, ("N") },
	{ 79, ("O") },
	{ 80, ("P") },
	{ 81, ("Q") },
	{ 82, ("R") },
	{ 83, ("S") },
	{ 84, ("T") },
	{ 85, ("U") },
	{ 86, ("V") },
	{ 87, ("W") },
	{ 88, ("X") },
	{ 89, ("Y") },
	{ 90, ("Z") },
	{ 96, ("Num 0") },
	{ 97, ("Num 1") },
	{ 98, ("Num 2") },
	{ 99, ("Num 3") },
	{ 100, ("Num 4") },
	{ 101, ("Num 5") },
	{ 102, ("Num 6") },
	{ 103, ("Num 7") },
	{ 104, ("Num 8") },
	{ 105, ("Num 9") },
	{ 106, ("Num *") },
	{ 107, ("Num +") },
	{ 109, ("Num -") },
	{ 110, ("Num Del") },
	{ 111, ("/") },
	{ 112, ("F1") },
	{ 113, ("F2") },
	{ 114, ("F3") },
	{ 115, ("F4") },
	{ 116, ("F5") },
	{ 117, ("F6") },
	{ 118, ("F7") },
	{ 119, ("F8") },
	{ 120, ("F9") },
	{ 121, ("F10") },
	{ 122, ("F11") },
	{ 123, ("F12") },
	{ 144, ("Pause") },
	{ 145, ("Scroll Lock") },
	{ 160, ("Shift") },
	{ 161, ("Right Shift") },
	{ 162, ("Ctrl") },
	{ 163, ("Ctrl") },
	{ 164, ("LAlt") },
	{ 165, ("LAlt") },
	{ 172, ("M") },
	{ 173, ("D") },
	{ 174, ("C") },
	{ 175, ("B") },
	{ 176, ("P") },
	{ 177, ("Q") },
	{ 178, ("J") },
	{ 179, ("G") },
	{ 183, ("F") },
	{ 186, (";") },
	{ 187, ("=") },
	{ 188, (",") },
	{ 189, ("-") },
	{ 190, (".") },
	{ 191, ("/") },
	{ 192, ("`") },
	{ 194, ("F15") },
	{ 219, ("[") },
	{ 220, ("\\") },
	{ 221, ("]") },
	{ 222, ("'") },
	{ 226, ("\\") },
	};

	std::string GetNameFromCode(int code, std::string deftxt) {
		auto it = std::find_if(vtable.begin(), vtable.end(), [code](const key_bind& a) { return (UINT)a.first == code; });

		std::string name;
		if (it == vtable.end())
			name = deftxt;
		else
			name = it->second;
		if (name == "None") {
			name = deftxt;
		}
		return name;
	}


	bool KeyBox(int* code, std::string deftxt, const ImVec2& size = { 0.f, 0.f }) {
		static bool key_input = false;
		static int* key_output = nullptr;

		auto text = deftxt;

		if (key_input && key_output == code) {
			text = "...";

			static const int mouse_code_array[5] = {
				1,
				2,
				4,
				5,
				6,
			};

			if (auto a_pres = GetKeyIndex(ImGuiKey_ALT)) {
				if (IsKeyReleased(a_pres)) {
					key_input = false;
					*code = a_pres;
				}
			}

			ImGuiIO& io = ImGui::GetIO();

			if (io.KeyAlt) {
				key_input = false;
				*code = GetKeyIndex(ImGuiKey_LAlt);
			}

			for (int i = 0; i < 5; i++) {
				if (IsMouseReleased(i)) {
					key_input = false;
					*code = mouse_code_array[i];
					break;
				}
			}

			for (auto keyPair : vtable) {
				if (IsKeyReleased((UINT)keyPair.first)) {
					key_input = false;
					*code = (UINT)keyPair.first;
					break;
				}
			}

		}
		else {
			auto name = GetNameFromCode(*code, deftxt);
			text = name;
			std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		}

		if (Button(text.c_str())) {
			key_input = true;
			key_output = code;
		}

		if (IsKeyReleased(27)) {
			key_input = false;
			*code = 0;
		}

		return false;
	}


	bool KeyBox(const char* label, int* code, std::string deftxt = "kek", const ImVec2& size = { 0.f, 0.f }) {
		KeyBox(code, deftxt, size);

		ImGui::SameLine();
		ImGui::Text(label);

		return false;
	}



	IMGUI_API bool TabLabels(const char** tabLabels, int tabSize, int& tabIndex, int* tabOrder) {
		ImGuiStyle& style = ImGui::GetStyle();

		const ImVec2 itemSpacing = style.ItemSpacing;
		const ImVec4 color = style.Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		const ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		const ImVec4 colorText = style.Colors[ImGuiCol_Text];
		style.ItemSpacing.x = 2.5;
		style.ItemSpacing.y = 1;
		const ImVec4 colorSelectedTab = ImVec4(color.x, color.y, color.z, color.w * 0.5f);
		const ImVec4 colorSelectedTabHovered = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w * 0.5f);
		const ImVec4 colorSelectedTabText = ImVec4(colorText.x * 0.8f, colorText.y * 0.8f, colorText.z * 0.8f, colorText.w * 0.8f);

		if (tabSize > 0 && (tabIndex < 0 || tabIndex >= tabSize)) {
			if (!tabOrder)
				tabIndex = 0;
			else
				tabIndex = -1;
		}

		float windowWidth = 0.f, sumX = 0.f;
		windowWidth = ImGui::GetWindowWidth() - style.WindowPadding.x - (ImGui::GetScrollMaxY() > 0 ? style.ScrollbarSize : 0.f);

		const bool isMMBreleased = ImGui::IsMouseReleased(2);
		int justClosedTabIndex = -1, newtabIndex = tabIndex;

		bool selection_changed = false; bool noButtonDrawn = true;

		for (int j = 0, i; j < tabSize; j++) {
			i = tabOrder ? tabOrder[j] : j;
			if (i == -1) continue;

			if (sumX > 0.f) {
				sumX += style.ItemSpacing.x;
				sumX += ImGui::CalcTextSize(tabLabels[i]).x + 2.f * style.FramePadding.x;

				if (sumX > windowWidth)
					sumX = 0.f;
				else
					ImGui::SameLine();
			}

			if (i != tabIndex) {
				// Push the style
				style.Colors[ImGuiCol_Button] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonActive] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonHovered] = colorSelectedTabHovered;
				style.Colors[ImGuiCol_Text] = colorSelectedTabText;
			}
			// Draw the button
			ImGui::PushID(i);   // otherwise two tabs with the same name would clash.
			if (ImGui::Button(tabLabels[i], ImVec2((windowWidth / tabSize) - 3, 30))) { selection_changed = (tabIndex != i); newtabIndex = i; }
			ImGui::PopID();
			if (i != tabIndex) {
				// Reset the style
				style.Colors[ImGuiCol_Button] = color;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				style.Colors[ImGuiCol_Text] = colorText;
			}
			noButtonDrawn = false;
			if (sumX == 0.f) sumX = style.WindowPadding.x + ImGui::GetItemRectSize().x; // First element of a line
		}

		tabIndex = newtabIndex;

		// Change selected tab when user closes the selected tab
		if (tabIndex == justClosedTabIndex && tabIndex >= 0) {
			tabIndex = -1;
			for (int j = 0, i; j < tabSize; j++) {
				i = tabOrder ? tabOrder[j] : j;
				if (i == -1)
					continue;
				tabIndex = i;
				break;
			}
		}

		// Restore the style
		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.Colors[ImGuiCol_Text] = colorText;
		style.ItemSpacing = itemSpacing;

		return selection_changed;
	}

	IMGUI_API bool TabLabelsGlobal(const char** tabLabels, int tabSize, int& tabIndex, int* tabOrder) {
		ImGuiStyle& style = ImGui::GetStyle();

		const ImVec2 itemSpacing = style.ItemSpacing;
		const ImVec4 color = style.Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		const ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		const ImVec4 colorText = style.Colors[ImGuiCol_Text];
		style.ItemSpacing.x = 2.5;
		style.ItemSpacing.y = 1;
		const ImVec4 colorSelectedTab = ImVec4(color.x, color.y, color.z, color.w * 0.5f);
		const ImVec4 colorSelectedTabHovered = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w * 0.5f);
		const ImVec4 colorSelectedTabText = ImVec4(colorText.x * 0.8f, colorText.y * 0.8f, colorText.z * 0.8f, colorText.w * 0.8f);

		if (tabSize > 0 && (tabIndex < 0 || tabIndex >= tabSize)) {
			if (!tabOrder)
				tabIndex = 0;
			else
				tabIndex = -1;
		}

		float windowWidth = 0.f, sumX = 0.f;
		windowWidth = ImGui::GetWindowWidth() - style.WindowPadding.x - (ImGui::GetScrollMaxY() > 0 ? style.ScrollbarSize : 0.f);

		const bool isMMBreleased = ImGui::IsMouseReleased(2);
		int justClosedTabIndex = -1, newtabIndex = tabIndex;

		bool selection_changed = false; bool noButtonDrawn = true;

		for (int j = 0, i; j < tabSize; j++) {
			i = tabOrder ? tabOrder[j] : j;
			if (i == -1) continue;

			if (sumX > 0.f) {
				sumX += style.ItemSpacing.x;
				sumX += ImGui::CalcTextSize(tabLabels[i]).x + 2.f * style.FramePadding.x;

				if (sumX > windowWidth)
					sumX = 0.f;
				else
					ImGui::SameLine();
			}

			if (i != tabIndex) {

				style.Colors[ImGuiCol_Button] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonActive] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonHovered] = colorSelectedTabHovered;
				style.Colors[ImGuiCol_Text] = colorSelectedTabText;
			}

			ImGui::PushID(i);
			if (ImGui::Button(tabLabels[i], ImVec2((windowWidth / tabSize) - 2, 30))) { selection_changed = (tabIndex != i); newtabIndex = i; }
			ImGui::PopID();
			if (i != tabIndex) {

				style.Colors[ImGuiCol_Button] = color;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				style.Colors[ImGuiCol_Text] = colorText;
			}
			noButtonDrawn = false;
			if (sumX == 0.f) sumX = style.WindowPadding.x + ImGui::GetItemRectSize().x;
		}

		tabIndex = newtabIndex;


		if (tabIndex == justClosedTabIndex && tabIndex >= 0) {
			tabIndex = -1;
			for (int j = 0, i; j < tabSize; j++) {
				i = tabOrder ? tabOrder[j] : j;
				if (i == -1)
					continue;
				tabIndex = i;
				break;
			}
		}


		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.Colors[ImGuiCol_Text] = colorText;
		style.ItemSpacing = itemSpacing;

		return selection_changed;
	}
};

class Tab
{
private:
	std::vector<std::string> labels;
public:
	void add(std::string name)
	{
		labels.push_back(name);
	}
	void draw(int *selected, ImDrawList* list)
	{
		float size_x = 126.f, size_y = 44.f, size_x_on = 167.f;
		for (int i = 0; i < 3; i++) ImGui::Spacing();
		for (size_t i = 0; i < labels.size(); i++)
		{
			if (ImGui::Button(labels.at(i).c_str(), { size_x, size_y }, 1))
				*selected = i;
			if (ImGui::IsItemHovered()) {
				hovered_tab[i] = 1;
			}
			else {
				hovered_tab[i] = 0;
			}
		}
	}
};

//сука дибил бляяяяяяяяяяяя я забыл что похерил кнопку

bool gButton(const char * text) {
	return ImGui::ImageButton(text, button, buttonh, ImVec2(120, 25));
}

namespace Moveable
{
	bool _MousePressed;
	int lastMouseX, lastMouseY;
	int mouseX, mouseY;

	void Run( int* pX, int* pY, int iWidth, int iHeight ) {
		const int OUTLINE_SIZE = 6;
		const int HEADER_SIZE = 16;
		const int RESIZE_DOT_SIZE = 8;

		int x = *pX;
		int y = *pY;

		if( G::MenuOpened && _MousePressed &&
			lastMouseX > ( x - OUTLINE_SIZE ) && lastMouseX < ( x + iWidth + OUTLINE_SIZE ) &&
			lastMouseY >( y - OUTLINE_SIZE - HEADER_SIZE ) && lastMouseY < ( y + iHeight + OUTLINE_SIZE ) ) {
			*pX += mouseX - lastMouseX;
			*pY += mouseY - lastMouseY;
		}
	}

	void End( ) {
		lastMouseX = mouseX;
		lastMouseY = mouseY;
	}

	void WndProc( UINT msg, WPARAM wParam, LPARAM lParam ) {
		switch( msg ) {
		case WM_LBUTTONDOWN:
			_MousePressed = true;
			break;
		case WM_LBUTTONUP:
			_MousePressed = false;
			break;
		case WM_MOUSEMOVE:
			mouseX = ( signed short )( lParam );
			mouseY = ( signed short )( lParam >> 16 );
			break;
		}
	}
};
//ща 1 вешь чекну

void s() {
	ImGui::Text(""); ImGui::SameLine(10);
}

void pi() {
	ImGui::PushItemWidth(100);
}

void pp() {
	ImGui::PopItemWidth(); //шо бля ЗАЕБАЛ экс инже кБтУиДЕШЬЛ ИГРАТЬ СО МНОЙ ПРИЕДУ И ЕБУЧКУ НАЧИЩУ туп?
}

void Othermenu();

void Aimbotmenu()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize; // | ImGuiWindowFlags_NoScrollWithMouse;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag); //447
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();
	{
			draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 49), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
			
			if (sab_tab[1] == 0)
			{
				draw3->AddRectFilled(ImVec2(child_pos.x + 20, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(28, 36, 51));
				draw3->AddImage(glow_tab[1], ImVec2(child_pos.x - 132, child_pos.y - 20), ImVec2(child_pos.x + 275, child_pos.y + 54));
				draw3->AddRectFilled(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 48), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(28, 36, 51)); 
				
			}
			else if (sab_tab[1] == 1)
			{
				draw3->AddRectFilled(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(28, 36, 51));
				draw3->AddImage(glow_tab[1], ImVec2(child_pos.x - 25, child_pos.y - 20), ImVec2(child_pos.x + 395, child_pos.y + 54));
				draw3->AddRectFilled(ImVec2(child_pos.x + 20, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 48), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(28, 36, 51));
				
			}
			
			draw3->AddRectFilled(ImVec2(child_pos.x - 5, child_pos.y - 10), ImVec2(child_pos.x + 400, child_pos.y + 12), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x + 125, child_pos.y + 12), ImVec2(child_pos.x + 130, child_pos.y + 48), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x - 5, child_pos.y - 5), ImVec2(child_pos.x + 18, child_pos.y + 48), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x + 240, child_pos.y + 10), ImVec2(child_pos.x + 400, child_pos.y + 48), ImColor(1, 10, 24));
		}
		//снизу идут сами конпки для сабтабов
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		ImGui::Spacing();	ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20);

		if (language) draw3->AddText(ImVec2(child_pos.x + 56, child_pos.y + 23), ImColor(255, 255, 255), u8"Global"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		else draw3->AddText(ImVec2(child_pos.x + 40, child_pos.y + 23), ImColor(255, 255, 255), u8"Все оружия"); //сейчас будет ебала с ебан оно относительно гуи отрисов

		if (language) draw3->AddText(ImVec2(child_pos.x + 152, child_pos.y + 23), ImColor(255, 255, 255), u8"One weapon"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		else draw3->AddText(ImVec2(child_pos.x + 162, child_pos.y + 23), ImColor(255, 255, 255), u8"Текущее"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		

		if (ImGui::Button("##Style", { 107, 25 }, 1)) sab_tab[1] = 0;
		//ImGui::PopFont();
		//вторая цвет изи фиксануть а ту хуйню в отрисокве щас попытаюсь
		ImGui::SameLine(133);
		//ImGui::PushFont((sab_tab[1] == 1) ? Dejavu_bold[14] : Dejavu[15]); //нужн
		if (ImGui::Button("##Other", { 107, 25 }, 1)) sab_tab[1] = 1;
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 476), false, dwFlag);
		{
			
			auto draw_child = ImGui::GetWindowDrawList();
			ImVec2 child_pos = ImGui::GetWindowPos();

			ImColor razdel = { 1, 10, 24, 255 };

			//draw_child->AddRectFilled(ImVec2(child_pos.x + 0, child_pos.y + 250), ImVec2(child_pos.x + 510, child_pos.y + 260), razdel);
			switch (sab_tab[1])
			{
			case 0:
			{
				ImGui::Spacing();
				//const char* t = std::to_string(CurrentWeapon); 
		

				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Enabled aimbot" : u8"Включить Аим", &Options::Legitbot::Enabled);

				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Aiming on teammates" : u8"Стрелять по напарникам", &Options::Legitbot::Deathmatch);
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Dont aiming on smoke" : u8"Не наводится в смок", &Options::Legitbot::SmokeCheck);
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Dont aiming on air" : u8"Не наводиться в прыжке", &Options::Legitbot::JumpCheck);
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Dont aiming on flashed" : u8"Не наводиться когда ослеплен", &Options::Legitbot::FlashCheck); // смок джамп чек а как же флэш

				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"To emulate human aiming" : u8"Эмуляция человеческого аима", &Options::Legitbot::Randomize);
				
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Block crosshair on the model" : u8"Удержание на ближайшей кости", &Options::Legitbot::NearestLock);
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Show fov" : u8"Показать Фов", &Options::Legitbot::DrawFov);
				ImGui::Text(""); ImGui::SameLine(10);
				
				ImGui::Checkbox(language ? u8"Aiming through wall" : u8"Наводится через стены", &Options::Legitbot::MinDamage);
				if (Options::Legitbot::MinDamage) {
					ImGui::Text(""); ImGui::SameLine(10);
					ImGui::SliderFloat(language ? u8"Minimum damage to aiming" : u8"Минимальный урон", &Options::Legitbot::MinDamageValue, 0, 100, "%.2f");
				}
				//s(); ImGui::Checkbox(language ? u8"Auto scope" : u8"Включить автоскоп", &Options::Legitbot::autoscope);
				s(); ImGui::Checkbox(language ? u8"Auto shoot" : u8"Включить автовыстрел", &Options::Legitbot::autofire);
				s(); ImGui::KeyBox(language ? u8"Auto shoot Key" : u8"Кнопка автовыстрела", &Options::Legitbot::autofirekey);
				//s(); ImGui::Checkbox(language ? u8"Auto stop" : u8"Включить автостоп", &Options::Legitbot::autostop);


				ImGui::Spacing();
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Kill delay" : u8"Задержка после убийства", &Options::Legitbot::KillDelay);
				if (Options::Legitbot::KillDelay) {
					ImGui::Text(""); ImGui::SameLine(10);
					ImGui::SliderFloat(language ? u8"Time(seconds)" : u8"Время(секунды)", &Options::Legitbot::KillDelayTime, 0.1f, 2, "%.2f");
				}

				s();
				ImGui::SliderInt(language ? u8"Max fov" : u8"Максимальный фов", &Options::Legitbot::MaxFov, 1, 180);
				//ImGui::Text(""); ImGui::SameLine(10);
				//s(); ImGui::SliderFloat(language ? u8"baim after X hp" : u8"баим после Х хп", &Options::Legitbot::baim_max_hp, 0, 100, "%.1f");
				s(); ImGui::Checkbox(language ? u8"Autopistol" : u8"Автоматический пистолет", & Options::Misc::auto_pistol);
			}
			break;
			case 1:
			{
				ImGui::Spacing();
				s(); ImGui::Checkbox(language ? u8"Weapon auto define" : u8"Автоматическое определение оружия", &autoopred);
				
				//showcurrentversion();

				if (CurrentWeapon > 0) {
					
					s(); ImGui::Checkbox(language ? u8"To activate the fire for this weapon" : u8"Включить аим на текущее оружие", &g_Weapons[CurrentWeapon].Enabled);
					
					s(); 
					ImGui::PushItemWidth(150); ImGui::SliderInt(language ? u8"Start bullet" : u8"Пуля начала ", &g_Weapons[CurrentWeapon].StartBullet, 0, 30);
					pp();
					ImGui::SameLine();
					ImGui::PushItemWidth(150);
					ImGui::SliderInt(language ? u8"Finish bullet" : u8"Пуля конца", &g_Weapons[CurrentWeapon].EndBullet, 0, 30);
					pp();
					 //s(); ImGui::SliderFloat(language ? u8"Fov" : u8"Фов", &g_Weapons[CurrentWeapon].Fov, 0, Options::Legitbot::MaxFov);
					//s(); ImGui::SliderFloat(language ? u8"Smooth" : u8"Плавность", &g_Weapons[CurrentWeapon].Smooth, 0, 10);
					//s(); ImGui::Checkbox(language ? u8"Auto delay" : u8"Автоматическая задержка", &g_Weapons[CurrentWeapon].AutoDelay);
					ImGui::Spacing();
					s(); ImGui::Checkbox(language ? u8"RCS Custom FOV" : u8"Кастомный фов для РКС", &g_Weapons[CurrentWeapon].RcsCustomFov);
					ImGui::SameLine(200);
					ImGui::Checkbox(language ? u8"RCS Custom Smooth" : u8"Кастомный смуч для РКС", &g_Weapons[CurrentWeapon].RcsCustomSmooth);

					if (!g_Weapons[CurrentWeapon].RcsCustomFov) {
						s(); ImGui::SliderFloat(language ? u8"Fov" : u8"Фов", &g_Weapons[CurrentWeapon].Fov, 0, Options::Legitbot::MaxFov);
					}
					else {
						s();
						ImGui::PushItemWidth(150);
						ImGui::SliderFloat(language ? u8"Fov" : u8"Фов", &g_Weapons[CurrentWeapon].Fov, 0, Options::Legitbot::MaxFov);
						pp();
						ImGui::SameLine();
						ImGui::PushItemWidth(150);
						ImGui::SliderFloat(language ? u8"RCS FOV" : u8"Фов зажима", &g_Weapons[CurrentWeapon].RcsFovValue, 0, Options::Legitbot::MaxFov);

						pp();
					}


					if (!g_Weapons[CurrentWeapon].RcsCustomSmooth) {
						s(); ImGui::SliderFloat(language ? u8"Smooth" : u8"Плавность", &g_Weapons[CurrentWeapon].Smooth, 0, 10);
					}
					else {
						s();
						ImGui::PushItemWidth(150);
						ImGui::SliderFloat(language ? u8"Smooth" : u8"Плавность", &g_Weapons[CurrentWeapon].Smooth, 0, 10);
						pp();
						ImGui::SameLine();
						ImGui::PushItemWidth(150);
						ImGui::SliderFloat(language ? u8"RCS Smooth" : u8"Плавность зажима", &g_Weapons[CurrentWeapon].RcsSmoothValue, 0, 10);

						pp();
					}
					ImGui::Spacing();
					s(); ImGui::Checkbox(language ? u8"RCS Stand alone" : u8"Постоянный контроль отдачи", &g_Weapons[CurrentWeapon].StandAloneRCS);

					s(); ImGui::SliderInt(language ? u8"RCS X" : u8"Контроль Отдачи по оси X", &g_Weapons[CurrentWeapon].RcsX, 0, 110, "%.0f%%");
					s(); ImGui::SliderInt(language ? u8"RCS Y" : u8"Контроль Отдачи по оси Y", &g_Weapons[CurrentWeapon].RcsY, 0, 110, "%.0f%%");

					/*
					if (g_Weapons[CurrentWeapon].RcsCustomFov) {
						s(); ImGui::SliderFloat(language ? u8"RCS Custom FOV Value" : u8"Значение фова для РКС", &g_Weapons[CurrentWeapon].RcsFovValue, 0, Options::Legitbot::MaxFov);
					}
					if (g_Weapons[CurrentWeapon].RcsCustomSmooth) {
						s(); ImGui::SliderFloat(language ? u8"RCS Custom Smooth" : u8"Значение смуча для РКС", &g_Weapons[CurrentWeapon].RcsSmoothValue, 0, 10);
					}
					*/
					s();  ImGui::Checkbox(language ? u8"Nearest" : u8"До ближайшей кости", &g_Weapons[CurrentWeapon].Nearest);
					if (g_Weapons[CurrentWeapon].Nearest) {
						s(); ImGui::Combo(language ? u8"Priority" : u8"Приоритетный Хитбокс", &g_Weapons[CurrentWeapon].Priority, u8"Random\0 Head\0 Neck\0 Belly\0 Legs\0\0");
						//s(); ImGui::Combo(language ? u8"Bone aiming" : u8"Кость аима", &g_Weapons[CurrentWeapon].NearestType, u8"Main\0Main + Legs\0All bones\0\0");
					}
					else {
						s(); ImGui::SliderInt(language ? u8"Bone of aiming" : u8"Кость аима", &g_Weapons[CurrentWeapon].Bone, 3, 8);
					}
					//ImGui::Checkbox(u8"Invisible aiming", &g_Weapons[CurrentWeapon].pSilent);
					/*if (g_Weapons[CurrentWeapon].pSilent)
						g_Weapons[CurrentWeapon].FireDelayEnabled = false;*/
					s(); ImGui::Checkbox(language ? u8"Silent aim" : u8"Сайлент аим", &g_Weapons[CurrentWeapon].pSilent);
					if (g_Weapons[CurrentWeapon].pSilent) {
						s(); ImGui::Checkbox(language ? u8"Silent + main" : u8"Сайлент + обычый", &g_Weapons[CurrentWeapon].Integration);
						s(); ImGui::SliderInt(language ? u8"Percent" : u8"Шанс попадания", &g_Weapons[CurrentWeapon].pSilentPercentage, 0, 100);
						s(); ImGui::SliderInt(language ? u8"End silent bullet" : u8"Пуля конца сайлента", &g_Weapons[CurrentWeapon].pSilentBullet, 0, 30);
						s(); ImGui::SliderFloat(language ? u8"Silent Fov" : u8"Фов сайлента", &g_Weapons[CurrentWeapon].pSilentFov, 0, 15);
						//ImGui::SliderFloat(u8"Smooth aiming ", &g_Weapons[CurrentWeapon].pSilentSmooth, 0, 10);
					}

					bool bIsPistol = CurrentWeapon.IsPistol();
					s();  ImGui::Checkbox(language ? u8"Delay before firing after aiming" : u8"Задержка перед 1 выстрелом", &g_Weapons[CurrentWeapon].FireDelayEnabled);
					if (g_Weapons[CurrentWeapon].FireDelayEnabled)
						g_Weapons[CurrentWeapon].pSilent = false;
					if (g_Weapons[CurrentWeapon].FireDelayEnabled) {
						s(); ImGui::SliderFloat(language ? u8"Time(ms) " : u8"Задержка(мс)", &g_Weapons[CurrentWeapon].FireDelay, 0.02f, 1.f, u8"%.3f ");
					}

					/*if (!CurrentWeapon.IsSniperRifle()) {
						s(); ImGui::Checkbox(language ? (bIsPistol ? u8"Tapping pistol" : u8"Delay before shots") : (bIsPistol ? u8"Тап Мод" : u8"Задержка между выстрелами"), &g_Weapons[CurrentWeapon].Repeat);
						if (g_Weapons[CurrentWeapon].Repeat) {
							s(); ImGui::SliderFloat(language ? u8"Time(ms)" : u8"Время(мс)", &g_Weapons[CurrentWeapon].RepeatTime, 0.02f, bIsPistol ? 0.06f : 1.f, u8"%.3f ");
						}
					}*/

					s(); ImGui::SliderInt(language ? u8"Backtrack ticks" : u8"Тики бэкктрека", &g_Weapons[CurrentWeapon].Backtrack, 0, 15, "%.0f");
				}
				else {
					s(); ImGui::Text(language ? u8"Take a weapon" : u8"Возьмите оружие"); // так сойдет?
				}

			}
			break;
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}





void WallHack()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize; //| ImGuiWindowFlags_NoScrollWithMouse;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag); //447
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		//снизу много говнокода, можно реализовать по другому и намного проще но я даун немного
		//пс. это отрисовка сабтабов (сам врубай мозг и понимай где и как отрисовано и подгоняй размеры для следующих сабтабов)
		{
			draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 49), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
			if (sab_tab[1] == 0)
			{
				draw3->AddRectFilled(ImVec2(child_pos.x + 20, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(28, 36, 51));
				draw3->AddImage(glow_tab[1], ImVec2(child_pos.x - 132, child_pos.y - 20), ImVec2(child_pos.x + 275, child_pos.y + 54));
				draw3->AddRectFilled(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 48), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(28, 36, 51));
			}
			else if (sab_tab[1] == 1)
			{
				draw3->AddRectFilled(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(28, 36, 51));
				draw3->AddImage(glow_tab[1], ImVec2(child_pos.x - 25, child_pos.y - 20), ImVec2(child_pos.x + 395, child_pos.y + 54));
				draw3->AddRectFilled(ImVec2(child_pos.x + 20, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 48), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(28, 36, 51));
			}
			draw3->AddRectFilled(ImVec2(child_pos.x - 5, child_pos.y - 10), ImVec2(child_pos.x + 400, child_pos.y + 12), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x + 125, child_pos.y + 12), ImVec2(child_pos.x + 130, child_pos.y + 48), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x - 5, child_pos.y - 5), ImVec2(child_pos.x + 18, child_pos.y + 48), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x + 240, child_pos.y + 10), ImVec2(child_pos.x + 400, child_pos.y + 48), ImColor(1, 10, 24));
		}
		//снизу идут сами конпки для сабтабов
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		ImGui::Spacing();	ImGui::Spacing();
		// пы.сы. нахера я текст пустой юзаю? ибо имгуй вещь ебанутая из за чего просто так айтем не сдвинешь, приходится сдвигать от другого айтема 
		//ImGui::Text(""); ImGui::SameLine(language == 0 ? ((sab_tab[1] == 0) ? 47.f : 49.f) : ((sab_tab[1] == 0) ? 50.f : 52.f));
		//первая кнопка, прикинь да?
		//ImGui::PushFont((sab_tab[1] == 0) ? Dejavu_bold[14] : Dejavu[15]); инжектить?да
		//ImGui::Text(""); ImGui::SameLine(language == 0 ? ((sab_tab[1] == 0) ? 47.f : 49.f) : ((sab_tab[1] == 0) ? 50.f : 52.f));
		//первая кнопка, прикинь да?
		//ImGui::PushFont((sab_tab[1] == 0) ? Dejavu_bold[14] : Dejavu[15]); 
		ImGui::Text(""); ImGui::SameLine(20);
		
		if (language) draw3->AddText(ImVec2(child_pos.x + 58, child_pos.y + 23), ImColor(255, 255, 255), "Style"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		else draw3->AddText(ImVec2(child_pos.x + 56, child_pos.y + 23), ImColor(255, 255, 255), u8"Cтиль"); //сейчас будет ебала с ебан оно относительно гуи отрисов

		if (language) draw3->AddText(ImVec2(child_pos.x + 171, child_pos.y + 23), ImColor(255, 255, 255), "Other"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		else draw3->AddText(ImVec2(child_pos.x + 166, child_pos.y + 23), ImColor(255, 255, 255), u8"Другое"); //сейчас будет ебала с ебан оно относительно гуи отрисов


		if (ImGui::Button("##Style", { 107, 25 }, 1)) sab_tab[1] = 0;
		//ImGui::PopFont();
		//вторая
		ImGui::SameLine(133);
		//ImGui::PushFont((sab_tab[1] == 1) ? Dejavu_bold[14] : Dejavu[15]); //нужн
		if (ImGui::Button("##Other", { 107, 25 }, 1)) sab_tab[1] = 1;
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 476), false, dwFlag);
		{
			auto draw_child = ImGui::GetWindowDrawList();
			ImVec2 child_pos = ImGui::GetWindowPos();
			switch (sab_tab[1])
			{
			case 0:
			{
				//отрисовка модели и бокса
				const int sdvig = -5; // открой прошлый сурс м
				child_pos.y -= 20;
				draw_child->AddImage(model2, ImVec2(child_pos.x + 266 - sdvig, child_pos.y + 95), ImVec2(child_pos.x + 436 - sdvig, child_pos.y + 316));
				//draw_child->AddRect(ImVec2(child_pos.x + 238 - sdvig, child_pos.y + 20), ImVec2(child_pos.x + 487 - sdvig, child_pos.y + 360), ImColor(28, 36, 51), 3.f);
				static float box_size;
				//я имею ввиду, чтоб можно было внутри вкладки в ограниченной области работы координат передвигать типа мелкая фича хоть и не очень полезная
				box_size = Options::Visuals::ESP::BoxSize;
				if (box_size > 0) box_size *= 1.3; 
				// lx  vy
				//
				//  ny    rx     

				const int lx = 298, rx = 424, vy = 80, ny = 326; 
				static float corsx, corsy;
				corsy = 153.f / Options::Visuals::ESP::CornerOffsets + 10; 
				corsx = 83.f / Options::Visuals::ESP::CornerOffsets + 5;
				
				
				
				if (Options::Visuals::ESP::WeaponIcon) {
					//draw_child->AddText(Font::IconsBig, 16, ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + vy - box_size), ImColor(255, 255, 255), wIcon)
					if (Options::Visuals::ESP::WeaponIconPos == 0) {
						if (!Options::Visuals::ESP::Name) draw_child->AddImage(glock, ImVec2(child_pos.x + rx + 3 + box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + rx + 33 + box_size - sdvig, child_pos.y + vy + 20 - box_size));//, ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 255, 255, 255));
						else draw_child->AddImage(glock, ImVec2(child_pos.x + rx + 3 + box_size - sdvig, child_pos.y + vy + 20 - box_size), ImVec2(child_pos.x + rx + 33 + box_size - sdvig, child_pos.y + vy + 40 - box_size));//, ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 255, 255, 255));
					}
					if (Options::Visuals::ESP::WeaponIconPos == 1) {
						draw_child->AddImage(glock, ImVec2(child_pos.x + lx - 33 - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + lx - 3 - box_size - sdvig, child_pos.y + vy + 20 - box_size));//, ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 255, 255, 255));

					}
					if (Options::Visuals::ESP::WeaponIconPos == 2) {
						draw_child->AddImage(glock, ImVec2(child_pos.x + lx + 45 - sdvig, child_pos.y + vy - box_size - 30), ImVec2(child_pos.x + lx + 75 - sdvig, child_pos.y + vy - box_size - 10));//, ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 255, 255, 255));

					}
					if (Options::Visuals::ESP::WeaponIconPos == 3) {
						draw_child->AddImage(glock, ImVec2(child_pos.x + lx + 45 - sdvig, child_pos.y + ny + box_size + 9), ImVec2(child_pos.x + lx + 75 - sdvig, child_pos.y + ny + box_size + 29));//, ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 255, 255, 255));

					}
					//draw_child->AddImage(glocki, ImVec2(child_pos.x + lx - 7 - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + lx - 7 - box_size - sdvig + 20, child_pos.y + vy - box_size + 30));//, ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 255, 255, 255));
				}

				if (Options::Visuals::ESP::Box) {
					if (Options::Visuals::ESP::Style < 2) 
						draw_child->AddRect(ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0), 5.f);
					else {
						draw_child->AddLine(ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + vy - box_size + corsy), ImColor(0, 255, 0), 1.f);
						draw_child->AddLine(ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + lx - box_size - sdvig + corsx, child_pos.y + vy - box_size), ImColor(0, 255, 0), 1.f);
						draw_child->AddLine(ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + ny + box_size - corsy), ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0), 1.f);
						draw_child->AddLine(ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + ny + box_size), ImVec2(child_pos.x + lx - box_size - sdvig + corsx, child_pos.y + ny + box_size), ImColor(0, 255, 0), 1.f);
						
						draw_child->AddLine(ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + vy - box_size + corsy), ImColor(0, 255, 0), 1.f);
						draw_child->AddLine(ImVec2(child_pos.x + rx - corsx + box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + vy - box_size), ImColor(0, 255, 0), 1.f);
						draw_child->AddLine(ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + ny + box_size - corsy), ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0), 1.f);
						draw_child->AddLine(ImVec2(child_pos.x + rx - corsx + box_size - sdvig, child_pos.y + ny + box_size), ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0), 1.f);


					}
				}
				if (Options::Visuals::ESP::Name) draw_child->AddText(ImVec2(child_pos.x + rx + 7 + box_size - sdvig, child_pos.y + vy - box_size), ImColor(255, 255, 255), "Name");

				if (Options::Visuals::ESP::Health) {
					if (Options::Visuals::ESP::HealthPos == 0)
						draw_child->AddRectFilled(ImVec2(child_pos.x + lx - 7 - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + lx - 2 - box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0));
					else if (Options::Visuals::ESP::HealthPos == 1)
						draw_child->AddRectFilled(ImVec2(child_pos.x + rx + 2 + box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + rx + 7 + box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0));
					else if (Options::Visuals::ESP::HealthPos == 2){
						draw_child->AddRectFilled(ImVec2(child_pos.x + lx - 7 - box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + lx - 2 - box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0));
						draw_child->AddRectFilled(ImVec2(child_pos.x + rx + 2 + box_size - sdvig, child_pos.y + vy - box_size), ImVec2(child_pos.x + rx + 7 + box_size - sdvig, child_pos.y + ny + box_size), ImColor(0, 255, 0));
					}
					else if (Options::Visuals::ESP::HealthPos == 3)
						draw_child->AddRectFilled(ImVec2(child_pos.x + lx - box_size - sdvig, child_pos.y + ny + box_size + 2), ImVec2(child_pos.x + rx + box_size - sdvig, child_pos.y + ny + box_size + 7), ImColor(0, 255, 0));


				}
				for (int i = 0; i < 2; i++) ImGui::Spacing();
				child_pos.y += 40;
				ImGui::Spacing();
				//ImGui::Text(""); ImGui::SameLine(10);
				//ImGui::Checkbox(language ? u8"Spectator List" : u8"Список следящих за вами", &Options::Misc::SpectatorList);
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Activated" : u8"Включить", &Options::Visuals::ESP::Enabled);
				ImGui::Text(""); ImGui::SameLine(10);

				ImGui::Checkbox(language ? u8"Enabled boxes" : u8"Включить боксы", &Options::Visuals::ESP::Box);
				if (Options::Visuals::ESP::Box) {
					if (Options::Visuals::ESP::Style == 0) {
						ImGui::PushItemWidth(150);
						ImGui::Text(""); ImGui::SameLine(10);
						ImGui::SliderInt(language ? u8"Size" : u8"Размер", &Options::Visuals::ESP::BoxSize, -10, 20);
						s(); ImGui::SliderInt(language ? u8"Rounding" : u8"Закругление", &Options::Visuals::ESP::BoxRounding, 0, 10);
						pi();
						s(); ImGui::SliderFloat(language ? u8"Width" : u8"Толщина", &Options::Visuals::ESP::BoxWidth, 1, 5);
						pp();
						ImGui::PopItemWidth();
					}
					ImGui::Spacing();
					ImGui::Text(""); ImGui::SameLine(10);
					pi();
					
					ImGui::Combo(language ? u8"Boxes style" : u8"Стиль боксов", &Options::Visuals::ESP::Style, language ? u8"Main\0Main outline\0Angular\0Angular outline\0\0" : u8"Обычные\0Обведенные\0Угловые\0Угловые обведенные\0\0");
					pp();
					if (Options::Visuals::ESP::Style == 2) {
						ImGui::Text(""); ImGui::SameLine(10); //ЭТО ТЫ ТРАТИШЬ МОЁ ВРЕМЯ ТОРМОЗ БЛЯТЬ ник бы уже всё давно закончил а ты с 1 хуйнёй разобрать pishow открой гуи х старое
						pi();
						ImGui::SliderFloat(language ? u8"size of the corners" : u8"Размер углов", &Options::Visuals::ESP::CornerOffsets, 0.960, 12);
						pp();
					}
					if (Options::Visuals::ESP::Style == 3) {
						ImGui::Text(""); ImGui::SameLine(10);
						pi(); ImGui::SliderFloat(language ? u8"size of the corners" : u8"Размер углов", &Options::Visuals::ESP::CornerOffsets, 1, 12); pp();
					}
				}
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Color based health" : u8"Цвет есп основаный на хп", &Options::Visuals::ESP::BoxCheckColor);
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Show health" : u8"Показать хп", &Options::Visuals::ESP::Health);
				if (Options::Visuals::ESP::Health) {
					s();
					pi();
					ImGui::SliderInt(language ? u8"Helth Width" : u8"Толщина хелбара", &Options::Visuals::ESP::HealthWidth, 1, 10);
					pp();
					s();
					ImGui::Checkbox(language ? u8"Color health indicator based health" : u8"Цвет хп индикатора основаный на хп", &Options::Visuals::ESP::HealthCheckColor);
					s();
					pi(); ImGui::Combo(language ? u8"Health indicator position " : u8"Позиция хп индикатор", &Options::Visuals::ESP::HealthPos, language ? u8"Left\0Right\0Both sides\0Down\0\0" : u8"Слева\0Справа\0С обеих сторон\0Снизу\0\0"); pp();
					
					s();
					pi(); ImGui::Combo(language ? u8"Health indicator style" : u8"Стиль хп индикатор", &Options::Visuals::ESP::HealthType, language ? u8"0Type 1\0Type 2\0\0" : u8"0Тип 1\0Тип 2\0\0"); pp();
				}
				ImGui::Text(""); ImGui::SameLine(10);
				ImGui::Checkbox(language ? u8"Show name" : u8"Показать имя", &Options::Visuals::ESP::Name); 
				ImGui::Text(""); ImGui::SameLine(10); 

				
				ImGui::Checkbox(language ? u8"Show weapon icons" : u8"Показать оружие иконками", &Options::Visuals::ESP::WeaponIcon);
				if (Options::Visuals::ESP::WeaponIcon) {

					//GUI::Text(u8"Позиция иконкиё:"); 
					s();
					pi(); ImGui::Combo(language ? u8"The position of the icons" : u8"Позиция иконки", &Options::Visuals::ESP::WeaponIconPos, u8"Right\0Left\0Up\0Down\0\0"); pp();
				}
				s();
				ImGui::Checkbox(language ? u8"Do not show teammates" : u8"Не показывать тимейтов", &Options::Visuals::ESP::EnemyOnly);
				s();
				ImGui::Checkbox(language ? u8"Do not show through walls" : u8"Не через стены", &Options::Visuals::ESP::VisibleOnly);
				s();
				ImGui::Checkbox(language ? u8"Do not show through smoke" : u8"Не через смок", &Options::Visuals::ESP::SmokeCheck);

			}
			break;
			case 1:
			{
				ImGui::Spacing();
				s();
				ImGui::Checkbox(language ? u8"Activated" : u8"Включить чамсы", &Options::Visuals::Chams::Enabled);
				s(); ImGui::Checkbox(language ? (u8"ОБС байпасс чамсы") : "OBS bypass", &Options::Visuals::Chams::bStreamSafe);
				if (!Options::Visuals::Chams::bStreamSafe) {
					s(); ImGui::Checkbox(language ? u8"Do not display through wall" : u8"Не через стены", &Options::Visuals::Chams::VisibleOnly);
					s(); ImGui::Combo(language ? u8"Style  " : u8"Стиль", &Options::Visuals::Chams::Style, u8"Material\0Filed\0Console\0Light\0Metallic\0\0");
					s(); ImGui::Checkbox(language ? u8"Do not display teammates" : u8"Не показывать тимейтов", &Options::Visuals::Chams::EnemyOnly);
					s(); ImGui::Checkbox(language ? u8"The fill color is based on the number of lives" : u8"Заполненость цвета базируется на хп", &Options::Visuals::ESP::ChamsCheckColor);

					if (Options::Visuals::ESP::ChamsCheckColor)
						Options::Visuals::ESP::RainbowChams = false;

					s(); ImGui::Checkbox(language ? u8"RGB Dynamic color" : u8"Радужный цвет", &Options::Visuals::ESP::RainbowChams);

					if (Options::Visuals::ESP::RainbowChams)
						Options::Visuals::ESP::ChamsCheckColor = false;

					if (Options::Visuals::Chams::Style == 3) {
						s(); ImGui::SliderInt(language ? u8"Intensity" : u8"Интенсивность", &Options::Visuals::Chams::Intensity, -100, 30);
					}

					if (Options::Visuals::Chams::Style == 4) {
						s(); ImGui::SliderInt(language ? u8"Intensity " : u8"Интенсивность", &Options::Visuals::Chams::Intensity, 0, 30);
					}

					s(); ImGui::Checkbox(language ? u8"Hands chams" : u8"Чамсы на руки", &Options::Visuals::Hands::Enabled);
					s(); ImGui::Combo(language ? u8"Hands style" : u8"Стиль рук", &Options::Visuals::Hands::Style,
						language ? u8"Disabled\0Wireframe\0Chams\0Chams & Wireframe\0Rainbow\0Rainbow & Wireframe\0\0" : u8"Выключены\0Сетка\0Чамсы\0Чамсы и Сетка\0Радуга\0Радуга и сетка\0Метал\0\0");
					
				
					s(); ImGui::Checkbox(language ? u8"Enable blur" : u8"Включить свечение", & Options::Visuals::ESP::blur_enable);
					s(); ImGui::SliderFloat(language ? u8"Blur amount" : u8"Сила свечения", &Options::Visuals::ESP::blur_amount, 0.f, 10.f, "%.1f", 1.0F);


					//s(); ImGui::Checkbox(language ? u8"Light hands chams" : u8"Светящиеся чамсы на руки", &Options::Visuals::Hands::brightness);
					//if (Options::Visuals::Hands::brightness) {
					//	ImGui::SliderFloat(language ? u8"Intensity hands light" : u8"Интенсивность света рук", &Options::Texture::lightness, 0, 30, "%.1f", 1.0F);
					//}
					//s(); ImGui::Combo(language ? u8"Backtrack chams " : u8"Бэктрек чамсы", &Options::Visuals::Chams::BacktrackChams,
					//language ? u8"Off\0Latest\0All\0\0" : u8"Выключены\0Последний тик\0Все тики\0\0");
					//s(); ImGui::Checkbox(language ? u8"Flat backtrack chams" : u8"Залитые бэктрек чамсы", &Options::Visuals::Chams::FlatBacktrackChams);

					s(); ImGui::Combo(language ? u8"Backtrack chams " : u8"Бэктрек чамсы", & Options::Visuals::Chams::BacktrackChams,
						language ? u8"Off\0Latest\0All\0\0" : u8"Выключены\0Последний тик\0Все тики\0\0");

					s(); ImGui::Checkbox(language ? u8"Desync chams" : u8"Десинк чамсы", &Options::Visuals::Chams::DesyncChams);
					s(); ImGui::Combo(language ? u8"Desync Style" : u8"Десинк Стиль", &Options::Visuals::Chams::DesStyle, u8"Material\0Filed\0Console\0Light\0Метал\0\0");

					s(); ImGui::SliderFloat((u8"Прозрачность чамсов"), &Options::Visuals::Chams::alpha, 0, 255, "%.1f", 1.0F);
				}
				else {
					s(); ImGui::Checkbox((u8"Материал чамсы"), &Options::Visuals::Chams::bMaterialChams);
					s(); ImGui::Checkbox((u8"Плоские чамсы      "), &Options::Visuals::Chams::bFlatChams);
					s(); ImGui::Checkbox((u8"Чамсы в сеточку"), &Options::Visuals::Chams::bWireFrameChams);
					s(); ImGui::Checkbox((u8"Только видимые      "), &Options::Visuals::Chams::VisibleOnly);
					s(); ImGui::SliderFloat((u8"Яркость чамсов"), &Options::Visuals::Chams::flMaterialChamsBrightness, 0, 255, "%.1f", 1.0F);

					//ImGui::SliderFloat( ( u8"Яркость чамсов" ), &Options::Visuals::Chams::flMaterialChamsBrightness, 0, 255, "%.1f", 1.0F );
				}
				s(); ImGui::SliderFloat(language ? u8"Glow " : u8"Обводка", &Options::Visuals::Misc::glow_alpha, 0, 255, "%.1f");
				ImGui::Spacing();
				s(); ImGui::Combo(language ? u8"Glow style" : u8"Стиль Обводки", &Options::Visuals::Hands::GlowStyle,
					language ? u8"Default\0Pulse\0Outline\0Outline Pulse\0\0" : u8"Обычный\0Пульсирующий\0Обводка\0Обводка пульс\0\0");

				s(); ImGui::Checkbox(language ? u8"Sound esp" : u8"Есп на шаги", &Options::Misc::SoundESP);
					//GUI::Checkbox("No Scope", &Options::Visuals::Misc::NoScope);
				s(); ImGui::Checkbox(language ? u8"Bullet trace" : u8"Линии по траектории выстрела", &Options::Visuals::Misc::BulletTracers);
				//GUI::Space();
				
				s(); ImGui::Checkbox(language ? u8"Show bomb" : u8"Включить Бомб Таймер", &Options::Visuals::Misc::BombTimer);
				if (Options::Visuals::Misc::BombTimer)
				{
					s(); ImGui::Combo(language ? u8"Bomb style" : u8"Стиль Бомб Таймера", &Options::Visuals::Misc::BombTimerType, u8"Ingame\0In display\0All\0\0");
				}
				s(); ImGui::Checkbox(language ? u8"Show drop" : u8"Показывать дроп", &Options::Visuals::Misc::DropESP);
				if (Options::Visuals::Misc::DropESP)
				{
					s(); ImGui::Combo(language ? u8"Drop style" : u8"Стиль показа дропа", &Options::Visuals::Misc::DropESPStyle, u8"Text\0Icon\0\0");
				}
				s(); ImGui::Checkbox(language ? u8"To show the grenade " : u8"Показывать Гранаты", &Options::Visuals::Misc::GrenadeESP);
				s(); ImGui::Checkbox(language ? u8"Grenage prediction " : u8"Траектория гранат", &Options::Visuals::Misc::GrenadeHelper);
				s(); ImGui::Checkbox(language ? u8"To change the viewing angle" : u8"Смена угла обзора", &Options::Visuals::Misc::FovChanger);
				if (Options::Visuals::Misc::FovChanger)
				{
					s(); ImGui::SliderFloat(language ? u8"Value " : u8"Угол обзора", &Options::Visuals::Misc::FovChangerValue, 70, 160, "%.1f");
				}
				s(); ImGui::Checkbox(language ? u8"Enable playerlist" : u8"Включить лист игроков", &Options::Visuals::ESP::playerlist::enable);


			}
			break;
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}


void Radarmenu();
void Colorsmenu();



class Protobuffs
{
public:
	static void WritePacket(std::string packet, void* thisPtr, void* oldEBP, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
	void ReceiveMessage(void* thisPtr, void* oldEBP, uint32_t messageType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
	bool PreSendMessage(uint32_t& unMsgType, void* pubData, uint32_t& cubData);
	bool SendClientHello();
	bool SendMatchmakingClient2GCHello();
	bool SendClientGcRankUpdate();
	bool EquipWeapon(int weaponid, int classid, int slotid);
	void EquipAll();
};

Protobuffs ProtoFeatures;
IDirect3DTexture9* skin_texture = NULL;
extern IDirect3DDevice9* d3d_offset;

template<typename T>
inline std::string get_4bytes(T value)
{
	return std::string{ reinterpret_cast<const char*>(reinterpret_cast<void*>(&value)), 4 };
}

auto delete_list_elem(std::vector<wskin>& list1, int k)
{
	std::vector<wskin>::iterator it = list1.begin();
	std::advance(it, k);
	if (it != list1.end())
	{
		return list1.erase(it);
	}
	return it;
}

void Inventory_tab() {
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag);
	{
		static bool is_equip = false;

		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 15), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);

		for (int i = 0; i < 2; i++)ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 510), false, dwFlag);
		{
			auto draw4 = ImGui::GetWindowDrawList();
			static bool fastfrimen = 0;
			if (!inittime) {
				inittime = 1;
				ltime = time(NULL);
			}

			static int selected_sticker = 0;

			static int folder_inv = 0;

			if (folder_inv == 0)
			{
				ImGui::PushItemWidth(130);

				if (ImGui::Button(language ? "Add new skin" : u8"Добавить новый скин", ImVec2(256, 20))) {
					folder_inv = 1;
				}

				ImGui::SameLine();
				if (ImGui::Button(language ? "Change profile" : u8"Изменить профиль", ImVec2(256, 20))) {
					folder_inv = 2;
				}


				ImGui::BeginGroup(); {
					s(); ImGui::Text(language ? "General" : u8"Основное");
					s(); ImGui::Checkbox(language ? "Synchronize": u8"Синхронизировать", &Options::inventory::synchronize_inventory);
				}
				ImGui::EndGroup();

				ImGui::BeginGroup(); {
					if (g_skins.size() > 0) {
						int count_item = 0;
						int same_line_counter = 0;

						if (g_skins.size() > 0) {
							for (auto list : g_skins) {


								int counter_item = count_item;

								if (ImGui::ImageButton(
									std::string("##" + std::to_string(counter_item) + std::to_string(
										getwep(list.wId) + getskin(list.wId, list.paintkit)
									)).c_str(),
									getTexture(getwep(list.wId), getskin(list.wId, list.paintkit)),
									getTexture(getwep(list.wId), getskin(list.wId, list.paintkit)),
									ImVec2(92, 69))
									)
								{
									if (g_skins.size() > 0) {
										delete_list_elem(g_skins, counter_item);
									}
									g_pEngine->ExecuteConsoleCommand("econ_clear_inventory_images");
								}

								if (same_line_counter < 3) {
									ImGui::SameLine();
									same_line_counter++;
								}
								else {
									same_line_counter = 0;
								}

								count_item++;
							}
						}
					}
				}
				ImGui::EndGroup();

				ImGui::PopItemWidth();

				if (gButton(language ? "Update" : u8"Обновить")) {
					g_pEngine->ExecuteConsoleCommand("econ_clear_inventory_images");
					ProtoFeatures.SendClientHello();
					ProtoFeatures.SendMatchmakingClient2GCHello();
					ProtoFeatures.SendClientGcRankUpdate();
					U::FullUpdate();
					g_bForceFullUpdate = true;
				}
			}
			else
				if (folder_inv == 1) {
					if (ImGui::Button(language ? "Return" : u8"Назад", ImVec2(515, 20))) {
						folder_inv = 0;
					}
					ImGui::PushItemWidth(130);

					ImGui::BeginGroup(); {
						s(); ImGui::Text(language ? "General" : u8"Основное");
						s(); ImGui::Checkbox(language ? "Equip" : u8"Экипировать", &is_equip);

						if (globalstatus < 3) {
							s(); ImGui::SliderFloat(language ? "Wear" : u8"Поношенность ", &g_Weapons[gun_definitioni[status]].inv_wear, 0.f, 1.f, "%.9f");
							s(); ImGui::SliderInt(language ? "Seed" : u8"Паттерн", &g_Weapons[gun_definitioni[status]].inv_seed, 0, 99999);
							s(); ImGui::SliderInt("Stat track", &g_Weapons[gun_definitioni[status]].inv_statrack, 0, 99999);
							s(); ImGui::SliderInt(language ? "Rarity" : u8"Редкость", &g_Weapons[gun_definitioni[status]].inv_rarity, 0, 8);
							s(); ImGui::InputText(language ? u8"Name" : u8"Имя", g_Weapons[gun_definitioni[status]].inv_weapon_name, 100);
						}
					}
					ImGui::EndGroup();

					ImGui::SameLine();

					ImGui::BeginGroup(); {
						if (globalstatus < 3) {
							s(); ImGui::Text(language ? "Stickers" : u8"Стикеры");
							s(); ImGui::SliderInt((language ? "Slot" : u8"Слот"), &selected_sticker, 0, 4);
							s(); ImGui::InputInt((u8"Id"), &g_Weapons[gun_definitioni[status]].Stickers[selected_sticker].iID);
							s(); ImGui::SliderFloat((language ? "Scale" : u8"Размер"), &g_Weapons[gun_definitioni[status]].Stickers[selected_sticker].flScale, 0.f, 1.f);
							s(); ImGui::SliderFloat((language ? "Sticker wear" : u8"Поношенность стикера"), &g_Weapons[gun_definitioni[status]].Stickers[selected_sticker].flWear, 0.f, 1.f);

							s();
							if (ImGui::Button(language ? "Add sticker" : u8"Добавить стикер")) {
								Sticker_t new_sticker;
								new_sticker.iID = g_Weapons[gun_definitioni[status]].Stickers[selected_sticker].iID;
								new_sticker.flWear = g_Weapons[gun_definitioni[status]].Stickers[selected_sticker].flWear;
								new_sticker.flScale = g_Weapons[gun_definitioni[status]].Stickers[selected_sticker].flScale;
								if (g_Weapons[gun_definitioni[status]].add_stick.size() < 5) {
									g_Weapons[gun_definitioni[status]].add_stick.push_back(new_sticker);
								}
							}

							ImGui::SameLine();

							if (ImGui::Button(language ? "Delete sticker" : u8"Удалить стикер")) {
								if (g_Weapons[gun_definitioni[status]].add_stick.size() > 0) {
									g_Weapons[gun_definitioni[status]].add_stick.clear();
								}
							}
						}


						/*	for (int i = 0; i < (int)g_Weapons[gun_definitioni[status]].add_stick.size(); i++) {
								sticker_list.push_back(
									std::to_string(g_Weapons[gun_definitioni[status]].add_stick[i].iID) + " " +
									std::to_string(g_Weapons[gun_definitioni[status]].add_stick[i].flWear) + " "+
									std::to_string(g_Weapons[gun_definitioni[status]].add_stick[i].flScale));
							}

							ImGui::ListBox("##scl", &sd, sticker_list);*/
					}
					ImGui::EndGroup();
					ImGui::PopItemWidth();

					/*	std::vector<std::string> weapon_curr_list;
						for (int i = 0; i < (int)g_skins.size(); i++) {
							std::list<wskin>::iterator it_max = g_skins.begin();
							std::advance(it_max, i);
							weapon_curr_list.push_back(std::to_string(getwep(it_max->wId)) + " " + std::to_string(getskin(it_max->wId,it_max->paintkit)));


						}
						static int current_select_g_skin = 0;
						ImGui::ListBox("##g456456sk", &current_select_g_skin, weapon_curr_list);
					*/
					static time_t curtime;
					if (globalstatus == 0) {
						ImGui::Text("");
						updateprev();

						if (percent == 60) {
							if (ImGui::ImageButton("", getTexture(selected_weapon.first, selected_weapon.second), getTexture(selected_weapon.first, selected_weapon.second), ImVec2(92, 69))) {
								globalstatus = 1;
							}
							ImGui::SameLine(150);
							if (ImGui::ImageButton("", getTexture(selected_knife.first, selected_knife.second), getTexture(selected_knife.first, selected_knife.second), ImVec2(92, 69))) {
								globalstatus = 2;
								status = skins_weapon_count - 1;
							}
							ImGui::SameLine(300);
							if (ImGui::ImageButton("", getTexture(54, 0), getTexture(54, 0), ImVec2(92, 69))) {
								globalstatus = 3;
								status = skins_weapon_count + skins_knife_count;
							}
						}
						else {
							draw4->AddText(ImVec2(ImGui::GetWindowPos().x + 400, ImGui::GetWindowPos().y + 495), ImColor(255, 255, 255), std::string("Loading:" + std::to_string(int(percent * 1.67f)) + "%").c_str());
						}
					}
					if (globalstatus == 1) {
						if (status == 0) {
							s();
							if (ImGui::ImageButton("", nazad, nazad, ImVec2(33, 28))) globalstatus = 0;

							for (int i = 1; i < skins_weapon_count; ++i) {
								if ((i - 1) % 4 != 0) ImGui::SameLine(120 * ((i - 1) % 4) + 17);
								else {
									ImGui::Text("");
									ImGui::SameLine(17);
								}
								if (getwep(CurrentWeapon) == i) {
									ImGui::Image(podsvetka, ImVec2(101, 74));
								}
								else ImGui::Image(skinfon, ImVec2(101, 74));
								if ((i - 1) % 4 == 0) {
									ImGui::SameLine(17);
								}
								else ImGui::SameLine(120 * ((i - 1) % 4) + 17);
								if (ImGui::ImageButton("", getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), ImVec2(92, 69))) status = i;


							}
						}

						if (status > 0) {
							if (!fastfrimen) {
								s();
								if (ImGui::ImageButton("", nazad, nazad, ImVec2(32, 28))) {
									status = 0;
								}
							}

							for (int i = 0; i < gunLen[status] && status != 0; ++i) {
								if (needupdate == 1) {
									if (nupdate == 0) {
										nupdate = 1;
										curtime = time(NULL);
										ltime = time(NULL);
									}
									else {
										curtime = time(NULL);
										if (curtime - ltime > 0) {
											//g_bForceFullUpdate = true;
											//U::FullUpdate();
											ltime = curtime;
											nupdate = 0;
											needupdate = 0;
										}
									}

								}

								if (gunLen[status] > i) {

									if (i % 4 != 0) ImGui::SameLine(120 * (i % 4) + 17);
									else {
										ImGui::Text(""); ImGui::SameLine(17);
									}

									//if (gunSkins[status] == i) //ImGui::Image(skinfon, ImVec2(101, 74), ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 0, 87, 155));
									if (g_Weapons[gun_definitioni[status]].skininmenu == i)
										ImGui::Image(podsvetka, ImVec2(101, 74));
									else ImGui::Image(skinfon, ImVec2(101, 74));

									//if (i % 4 != 0) 
									if (i % 4 == 0) ImGui::SameLine(17);
									else ImGui::SameLine(120 * (i % 4) + 17);

									if (ImGui::ImageButton("", getTexture(status, i), getTexture(status, i), ImVec2(92, 69))) {

										gunSkins[status] = i;
										g_Weapons[gun_definitioni[status]].skininmenu = i;
										//	g_Weapons[gun_definitioni[status]].ChangerSkinTT = vskns[status][i];

										//	wskin(int weapon_id, int weapon_paintkit, bool  weapon_is_equip, int  weapon_seed, float weapon_wear)

										g_skins.push_back({
												gun_definitioni[status],
												vskns[status][i],
												is_equip,
												g_Weapons[gun_definitioni[status]].inv_seed,
												g_Weapons[gun_definitioni[status]].inv_wear,
												g_Weapons[gun_definitioni[status]].inv_statrack,
												g_Weapons[gun_definitioni[status]].add_stick,
												g_Weapons[gun_definitioni[status]].inv_rarity,
												g_Weapons[gun_definitioni[status]].inv_weapon_name
											});

										if (!safetychanger) {
											//g_bForceFullUpdate = true;
											//U::FullUpdate();
											needupdate = 1;
										}
										updateprev();
										if (fastfrimen) status = 0;
										//break; 
									}

								}


							}
						}
					}

					if (globalstatus == 2) {

						if (status == skins_weapon_count - 1) {
							s();
							if (ImGui::ImageButton("", nazad, nazad, ImVec2(32, 29))) {
								globalstatus = 0;
								status = 0;
							}

							for (int i = skins_weapon_count; i < skins_weapon_count + skins_knife_count; ++i) {

								if ((i + 1) % 4 != 0) ImGui::SameLine(120 * ((i + 1) % 4) + 17);
								else {
									ImGui::Text("");
									ImGui::SameLine(17);
								}
								ImGui::Image(skinfon, ImVec2(101, 74));

								//draw4->AddImage(skinfon, ImVec2(child_pos2.x + 20 + 120 * i  - 135 - 3, child_pos2.y + 6), ImVec2(child_pos2.x + 112 + 120 * i - 135 + 3, child_pos2.y + 69 + 6)); не то, идея в том была, чтоб настраивая тут была кнопка назад(режим настройки скин ченжера детальный) так ты это в контексте перчаток и ножей песал что 3 кнопки (я их потом картинками сделаю) ножи перрчатки и оружия и на кажой конпки настройка своего 
								if ((i + 1) % 4 == 0) {
									ImGui::SameLine(17);
								}
								else ImGui::SameLine(120 * ((i + 1) % 4) + 17);


								if (ImGui::ImageButton("", getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), ImVec2(92, 69))) status = i;
								//if (i % 4 != 0) ImGui::SameLine(120 * (i % 4));

							}
						}

						if (status > skins_weapon_count - 1) {

							if (!fastfrimen) {
								s();
								if (ImGui::ImageButton("", nazad, nazad, ImVec2(33, 29))) {
									status = skins_weapon_count - 1;
								}
							}
							//ImGui::Text("");
							for (int i = 0; i < gunLen[status] && status != 0; ++i) {

								if (gunLen[status] > i) {

									if (i % 4 != 0) ImGui::SameLine(120 * (i % 4) + 17);
									else {
										ImGui::Text(""); ImGui::SameLine(17);
									}
									if (g_Weapons[gun_definitioni[status]].skininmenu == i) ImGui::Image(podsvetka, ImVec2(101, 74));
									else ImGui::Image(skinfon, ImVec2(101, 74));

									//if (i % 4 != 0) 
									if (i % 4 == 0) ImGui::SameLine(17);
									else ImGui::SameLine(120 * (i % 4) + 17);


									if (ImGui::ImageButton("", getTexture(status, i), getTexture(status, i), ImVec2(92, 69))) {

										gunSkins[status] = i;
										g_Weapons[gun_definitioni[status]].skininmenu = i;
										Options::SkinChanger::KnifeTT = knifesid[status - 29];
										//	g_Weapons[gun_definitioni[status]].ChangerSkinTT = vskns[status][i];
										//	g_skins.push_back({ U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT), vskns[status][i],is_equip });


										g_skins.push_back({
										U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT),
										vskns[status][i],
										is_equip,
										g_Weapons[gun_definitioni[status]].inv_seed,
										g_Weapons[gun_definitioni[status]].inv_wear,
										g_Weapons[gun_definitioni[status]].inv_statrack,
										g_Weapons[gun_definitioni[status]].add_stick,
										g_Weapons[gun_definitioni[status]].inv_rarity,
										g_Weapons[gun_definitioni[status]].inv_weapon_name
											});


										//	if (!safetychanger) U::FullUpdate();	
										updateprev();
										if (fastfrimen) status = skins_weapon_count - 1;

									}

								}


							}
						}
					}

					if (globalstatus == 3) {
						s();
						if (ImGui::ImageButton("", nazad, nazad, ImVec2(31, 28))) {
							globalstatus = 0;
							status = 0;
						}

						static vector<int> glove_def = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 50, 61, 62, 63, 64 };
						int count_item = 0;
						int same_line_counter = 0;

						for (auto a : GlovesSkin_Array) {
							int counter_item = count_item;
							if (ImGui::ImageButton(
								std::string("##glvidxesmenu" + std::to_string(counter_item)).c_str(),
								getTexture(getwep(a.ItemIndex), getskin(a.ItemIndex, a.PaintKit)),
								getTexture(getwep(a.ItemIndex), getskin(a.ItemIndex, a.PaintKit)),
								ImVec2(92, 69))) {

								Options::SkinChanger::Glovemenu = counter_item;
								gunSkins[status] = counter_item;
								Options::SkinChanger::GLoveIdx = glove_def[counter_item];

								g_skins.push_back({
								GlovesSkin_Array[counter_item].ItemIndex,
								GlovesSkin_Array[counter_item].PaintKit,
								is_equip,
								0,
								0,
								0,
								g_Weapons[0].add_stick,
								0,
								0 });
							}

							if (same_line_counter < 3) {
								ImGui::SameLine();
								same_line_counter++;
							}
							else {
								same_line_counter = 0;
							}

							count_item++;
							//updateprev();
							//status = 0;
						}
					}
				}
				else
				if (folder_inv == 2) {

					if (ImGui::Button(language ? "Return" : u8"Назад", ImVec2(515, 20))) {
						folder_inv = 0;
					}

					s(); ImGui::SliderInt(language ? u8"Friendly " : u8"Дружелюбный", & Options::inventory::friendly, 0, 99999);
					s(); ImGui::SliderInt(language ? u8"Teacher " : u8"Учитель", & Options::inventory::teacher, 0, 99999);
					s(); ImGui::SliderInt(language ? u8"Leader " : u8"Лидер", & Options::inventory::leader, 0, 99999);
			
					s(); ImGui::SliderInt(language ? u8"Level " : u8"Уровень", & Options::inventory::level, 0, 40);

					s(); ImGui::SliderInt(language ? u8"Rank " : u8"Ранг", & Options::inventory::rank_id, 0, 18);
					s(); ImGui::SliderInt(language ? u8"Wins " : u8"Победы", & Options::inventory::wins, 0, 99999);

					s(); ImGui::SliderInt(language ? u8"Wingman rank " : u8"Ранг напарники", & Options::inventory::wingman_rank, 0, 18);
					s(); ImGui::SliderInt(language ? u8"Wingman wins " : u8"Победы напарники", & Options::inventory::wingman_wins, 0, 99999);

					s(); ImGui::SliderInt(language ? u8"Dangerzone rank " : u8"Ранг опасная зона", & Options::inventory::danger_zone_rank, 0, 18);
					s(); ImGui::SliderInt(language ? u8"Dangerzone wins " : u8"Победы опасная зона", & Options::inventory::danger_zone_wins, 0, 99999);




				}

		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}


void Skins()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize ;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag);
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 15), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		for (int i = 0; i < 2; i++)ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 510), false, dwFlag);


		{

			ImGuiWindow* window1 = ImGui::GetCurrentWindow();

			if (window1->SkipItems)
				return;
			ImGuiStyle& style = ImGui::GetStyle();
			auto draw4 = ImGui::GetWindowDrawList();
			ImVec2 child_pos2 = ImGui::GetWindowPos(); // все хуйня 
			//ImGui::Text("Only for private version");
			//ImGui::SliderInt("paintkit", &g_Weapons[CurrentWeapon].PaintKit, 0, 1000);
			//ImGui::SliderInt("skintt", &g_Weapons[CurrentWeapon].ChangerSkinTT, 0, 1000);
			//ImGui::SliderInt("skinct", &g_Weapons[CurrentWeapon].ChangerSkinCT, 0, 1000);
			//if (ImGui::Button("Update")) U::FullUpdate(); 
			static bool fastfrimen = 0;
			if (!inittime) {
				inittime = 1;
				ltime = time(NULL);
			}
			static time_t curtime;
			if (globalstatus == 0) {
				ImGui::Text("");
				updateprev();
				//ImGui::SliderInt("GLOVE", &Options::SkinChanger::GLoveIdx, 0, 1000);
				//ImGui::SliderInt("GLOVE", &Options::SkinChanger::KnifeTT, 0, 1000);
				s(); ImGui::Checkbox(language ? "Enable Changer" : u8"Включить скины", &Options::SkinChanger::EnabledSkin);
				s(); ImGui::Checkbox(language ? "Enable Glove Changer" : u8"Включить перчатки", &Options::SkinChanger::EnabledGlove);
				s(); ImGui::Checkbox(language ? "Enable Knife Changer" : u8"Включить ножи", &Options::SkinChanger::EnabledKnife);
				s(); ImGui::Checkbox(language ? "Enable Stickers" : u8"Включить стикеры", &g_Weapons[CurrentWeapon].StickersEnabled);
				s(); ImGui::Checkbox(language ? "Fast changer" : u8"Быстрый ченжер", &fastfrimen);
				/*s(); ImGui::Checkbox(language ? "Safety changer" : u8"Безопасный ченжер", &safetychanger);
				if (safetychanger) {
					s(); if (ImGui::Button(language ? "Update skins" : u8"Обновить скины")) {
						g_bForceFullUpdate = true;
						U::FullUpdate();
					}
				}*/
							
				
				if (percent == 60) {
					if (ImGui::ImageButton("", getTexture(selected_weapon.first, selected_weapon.second), getTexture(selected_weapon.first, selected_weapon.second), ImVec2(92, 69))) {
						globalstatus = 1;
					}
					ImGui::SameLine(150);
					if (ImGui::ImageButton("", getTexture(selected_knife.first, selected_knife.second), getTexture(selected_knife.first, selected_knife.second), ImVec2(92, 69))) {
						globalstatus = 2;
						status = skins_weapon_count - 1;
					}
					ImGui::SameLine(300);
					if (ImGui::ImageButton("", getTexture(54, 0), getTexture(54, 0), ImVec2(92, 69))) {
						globalstatus = 3;
						status = skins_weapon_count + skins_knife_count;
					}
				}
				else {		
					draw4->AddText(ImVec2(ImGui::GetWindowPos().x + 400, ImGui::GetWindowPos().y + 495), ImColor(255, 255, 255), std::string("Loading:" + std::to_string(int(percent * 1.67f)) + "%").c_str());
				}
			}
			if (globalstatus == 1) {
				if (safetychanger) {
					s(); if (ImGui::Button(language ? "Update skins" : u8"Обновить скины")) {
						g_bForceFullUpdate = true;
						U::FullUpdate();
					}
				}
				if (status == 0) {
					s();
					if (ImGui::ImageButton("", nazad, nazad, ImVec2(33, 28))) globalstatus = 0;

					for (int i = 1; i < skins_weapon_count; ++i) {
						if ((i - 1) % 4 != 0) ImGui::SameLine(120 * ((i - 1) % 4) + 17);
						else {
							ImGui::Text("");
							ImGui::SameLine(17);
						}
						if (getwep(CurrentWeapon) == i) {
							//ImGui::Image(skinfon, ImVec2(101, 74), ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 0, 87, 155));
							ImGui::Image(podsvetka, ImVec2(101, 74));
						}
						else ImGui::Image(skinfon, ImVec2(101, 74));
						//draw4->AddImage(skinfon, ImVec2(child_pos2.x + 20 + 120 * i  - 135 - 3, child_pos2.y + 6), ImVec2(child_pos2.x + 112 + 120 * i - 135 + 3, child_pos2.y + 69 + 6)); не то, идея в том была, чтоб настраивая тут была кнопка назад(режим настройки скин ченжера детальный) так ты это в контексте перчаток и ножей песал что 3 кнопки (я их потом картинками сделаю) ножи перрчатки и оружия и на кажой конпки настройка своего 
						if ((i - 1) % 4 == 0) {
							ImGui::SameLine(17);
						}
						else ImGui::SameLine(120 * ((i - 1) % 4) + 17);
						if (ImGui::ImageButton("", getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), ImVec2(92, 69))) status = i;
						//if (i % 4 != 0) ImGui::SameLine(120 * (i % 4));

					}
				}

				if (status > 0) {
					//ImGui::SliderFloat("test", &gunWear[status], 0.f, 100.f);
					/*
					ImGui::PushItemWidth(60); ImGui::InputInt("1", &sticker1[status], 0, 100); ImGui::PopItemWidth();
					ImGui::SameLine();
					ImGui::PushItemWidth(60); ImGui::InputInt("2", &sticker2[status], 0, 100); ImGui::PopItemWidth();
					ImGui::SameLine();
					ImGui::PushItemWidth(60); ImGui::InputInt("3", &sticker3[status], 0, 100); ImGui::PopItemWidth();
					ImGui::SameLine();
					ImGui::PushItemWidth(60); ImGui::InputInt("4", &sticker4[status], 0, 100); ImGui::PopItemWidth();

					*/

					//for (int i = 1; i <= gunLen[status] && status != 0; ++i) {
					//	ImGui::Image(skinfon, ImVec2(child_pos2.x + 20 + 120 * ((i - 1) % 4 + 1)- 135 - 3, child_pos2.y + ((i - 1) / 4) * 87 + 37), ImVec2(child_pos2.x + 112 + 120 * ((i - 1) % 4 + 1) - 135 + 3, child_pos2.y + 69 + ((i - 1) / 4) * 87 + 37));
					//}


					//ImGui::SliderInt("StatTrack", &StatTrack[status], 0, 1000);
					if (!fastfrimen) {
						s();
						if (ImGui::ImageButton("", nazad, nazad, ImVec2(32, 28))) {
							status = 0;
						}
					}
					//ImGui::Text("");
					
					for (int i = 0; i < gunLen[status] && status != 0; ++i) {
						if (needupdate == 1) {
							if (nupdate == 0) {
								nupdate = 1;
								curtime = time(NULL);
								ltime = time(NULL);
							}
							else {
								curtime = time(NULL);
								if (curtime - ltime > 0) {
									g_bForceFullUpdate = true;
									U::FullUpdate();
									ltime = curtime;
									nupdate = 0;
									needupdate = 0;
								}
							}
							
						}
						
						if (gunLen[status] > i) {
							
							if (i % 4 != 0) ImGui::SameLine(120 * (i % 4) + 17);
							else {
								ImGui::Text(""); ImGui::SameLine(17);
							}
							
							//if (gunSkins[status] == i) //ImGui::Image(skinfon, ImVec2(101, 74), ImVec2(0, 0), ImVec2(0, 0), ImColor(255, 0, 87, 155));
							if (g_Weapons[gun_definitioni[status]].skininmenu == i)
								ImGui::Image(podsvetka, ImVec2(101, 74));
							else ImGui::Image(skinfon, ImVec2(101, 74));

							//if (i % 4 != 0) 
							if (i % 4 == 0) ImGui::SameLine(17);
							else ImGui::SameLine(120 * (i % 4) + 17);

							if (ImGui::ImageButton("", getTexture(status, i), getTexture(status, i), ImVec2(92, 69))) {
								
								gunSkins[status] = i;
								g_Weapons[gun_definitioni[status]].skininmenu = i;
								g_Weapons[gun_definitioni[status]].ChangerSkinTT = vskns[status][i];
								
								if (!safetychanger) {
									g_bForceFullUpdate = true;
									U::FullUpdate();

									needupdate = 1;
								}

								//ImGui::SliderInt("skinct", &g_Weapons[CurrentWeapon].ChangerSkinCT, 0, 1000);
								//vskns[status]		
								updateprev();
								if (fastfrimen) status = 0;
								//break; 
							}

						}


					}
				}
				/* 
				ImGui::SliderInt("tt", &g_Weapons[CurrentWeapon].ChangerSkinTT, 0, 1000);
				ImGui::SliderInt("ct", &g_Weapons[CurrentWeapon].ChangerSkinCT, 0, 1000); //кстати  утебя неправильно поставлены некоторые ножи когда ставишь фальшион ставится боуи
				*/



			}

			if (globalstatus == 2) {

				if (status == skins_weapon_count - 1) {
					s(); if (ImGui::Button(language ? "Update skins" : u8"Обновить скины")) {
						g_bForceFullUpdate = true;
						U::FullUpdate();
					}
					s();
					if (ImGui::ImageButton("", nazad, nazad, ImVec2(32, 29))) {
						globalstatus = 0;
						status = 0;
					}
					
					
					
					for (int i = skins_weapon_count; i < skins_weapon_count + skins_knife_count; ++i) {
						
						if ((i + 1) % 4 != 0) ImGui::SameLine(120 * ((i + 1) % 4) + 17);
						else {
							ImGui::Text("");
							ImGui::SameLine(17);
						}
						ImGui::Image(skinfon, ImVec2(101, 74));
						 
						//draw4->AddImage(skinfon, ImVec2(child_pos2.x + 20 + 120 * i  - 135 - 3, child_pos2.y + 6), ImVec2(child_pos2.x + 112 + 120 * i - 135 + 3, child_pos2.y + 69 + 6)); не то, идея в том была, чтоб настраивая тут была кнопка назад(режим настройки скин ченжера детальный) так ты это в контексте перчаток и ножей песал что 3 кнопки (я их потом картинками сделаю) ножи перрчатки и оружия и на кажой конпки настройка своего 
						if ((i + 1) % 4 == 0) {
							ImGui::SameLine(17);
						}
						else ImGui::SameLine(120 * ((i + 1) % 4) + 17);
						
						
						if (ImGui::ImageButton("", getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), getTexture(i, g_Weapons[gun_definitioni[i]].skininmenu), ImVec2(92, 69))) status = i;
						//if (i % 4 != 0) ImGui::SameLine(120 * (i % 4));
						
					}
				}

				if (status > skins_weapon_count - 1) {

					if (!fastfrimen) {
						s();
						if (ImGui::ImageButton("", nazad, nazad, ImVec2(33, 29))) {
							status = skins_weapon_count - 1;
						}
					}
					//ImGui::Text("");
					for (int i = 0; i < gunLen[status] && status != 0; ++i) {

						if (gunLen[status] > i) {

							if (i % 4 != 0) ImGui::SameLine(120 * (i % 4) + 17);
							else {
								ImGui::Text(""); ImGui::SameLine(17);
							}
							if (g_Weapons[gun_definitioni[status]].skininmenu == i) ImGui::Image(podsvetka, ImVec2(101, 74));
							else ImGui::Image(skinfon, ImVec2(101, 74));

							//if (i % 4 != 0) 
							if (i % 4 == 0) ImGui::SameLine(17);
							else ImGui::SameLine(120 * (i % 4) + 17);

							
							if (ImGui::ImageButton("", getTexture(status, i), getTexture(status, i), ImVec2(92, 69))) {
								
								gunSkins[status] = i;
								g_Weapons[gun_definitioni[status]].skininmenu = i;
								Options::SkinChanger::KnifeTT = knifesid[status - 29];

								g_Weapons[gun_definitioni[status]].ChangerSkinTT = vskns[status][i];
								//U::FullUpdate();
								if (!safetychanger) U::FullUpdate();
								//ImGui::SliderInt("skinct", &g_Weapons[CurrentWeapon].ChangerSkinCT, 0, 1000);
								//vskns[status]		
								updateprev();
								if (fastfrimen) status = skins_weapon_count - 1;
								//break; 
							}

						}


					}
				}
				/* мразь есля я выбрал не эту карту то значит это неспроста????
				ImGui::SliderInt("tt", &g_Weapons[CurrentWeapon].ChangerSkinTT, 0, 1000);
				ImGui::SliderInt("ct", &g_Weapons[CurrentWeapon].ChangerSkinCT, 0, 1000); //кстати  утебя неправильно поставлены некоторые ножи когда ставишь фальшион ставится боуи
				*/



			}

			if (globalstatus == 3) {
				if (safetychanger) {
					if (ImGui::Button(language ? "Update skins" : u8"Обновить скины")) {
						g_bForceFullUpdate = true;
						U::FullUpdate();
					}
				}
				s();
				if (ImGui::ImageButton("", nazad, nazad, ImVec2(31, 28))) {
					globalstatus = 0;
					status = 0;
				}

				static vector<int> glove_def = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 50, 61, 62, 63, 64 };
				int count_item = 0;
				int same_line_counter = 0;

				for (auto a : GlovesSkin_Array) {
					int counter_item = count_item;
					if (ImGui::ImageButton(
						std::string("##asdhalhsdcv" + std::to_string(counter_item)).c_str(),
						getTexture(getwep(a.ItemIndex), getskin(a.ItemIndex, a.PaintKit)),
						getTexture(getwep(a.ItemIndex), getskin(a.ItemIndex, a.PaintKit)),
						ImVec2(92, 69))) {

						Options::SkinChanger::Glovemenu = counter_item;
						gunSkins[status] = counter_item;
						Options::SkinChanger::GLoveIdx = glove_def[counter_item];

						if (!safetychanger) {
							g_bForceFullUpdate = true;
							U::FullUpdate();
							needupdate = 1;
						}

						//updateprev();
						globalstatus = 0;
						status = 0;
					}
				
					if (same_line_counter < 3) {
						ImGui::SameLine();
						same_line_counter++;
					}
					else {
						same_line_counter = 0;
					}

					count_item++;
				}
			}
			
			if ((g_pEngine->IsConnected() || g_pEngine->IsInGame() ) && isdownloaded)
			{
				s(); ImGui::InputText((language ? "Name tag" : u8"Нейм тег"), g_Weapons[CurrentWeapon].ChangerNameTT, 32);
				s(); ImGui::InputInt((language ? "Stat track" : u8"Статтрек"), &g_Weapons[CurrentWeapon].ChangerStatTrakTT);
				s(); ImGui::SliderInt((language ? "Seed" : u8"Сид"), &g_Weapons[CurrentWeapon].ChangerSeedTT, 0, 100);
				s(); ImGui::SliderFloat((language ? "Wear" : u8"Поношенность"), &g_Weapons[CurrentWeapon].ChangerWearTT, 0, 1);

				int unk_xuina = 0;
				s(); ImGui::Spacing();
				//ImGui::Combo("##SkinGLOVE", &Options::SkinChanger::GLoveIdx, gloves_listbox_items, ARRAYSIZE(gloves_listbox_items));
				s(); ImGui::Text(language ? "Stickers" : u8"Стикеры");
				s(); ImGui::SliderInt((language ? "Slot" : u8"Слот"), &selected_sticke, 1, 4);
				s(); ImGui::SliderFloat((language ? "Scale" : u8"Размер"), &g_Weapons[CurrentWeapon].Stickers[selected_sticke].flScale, 0.f, 1.f);
				//ImGui::SliderFloat((language ? "Enable Sticke" : u8"Включить стикеры"), &g_Weapons[CurrentWeapon].Stickers[selected_sticke].flScale, 0.f, 1.f);
				s(); ImGui::SliderFloat((language ? "Sticker wear" : u8"Поношенность стикера"), &g_Weapons[CurrentWeapon].Stickers[selected_sticke].flWear, 0.f, 1.f);

				s(); ImGui::InputInt((u8"Id"), &g_Weapons[CurrentWeapon].Stickers[selected_sticke].iID);
				s();
				if (ImGui::Button(language ? "Full update" : u8"Обновить скины")) {
					g_bForceFullUpdate = true;
					U::FullUpdate();
				}
			}
			
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

void Triggermenu()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag);
	{


		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 15), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		for (int i = 0; i < 2; i++)ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 510), false, dwFlag);


		{
			if (CurrentWeapon > 0) {
				ImGui::Spacing();
				s(); ImGui::Checkbox(language ? u8"Enable" : u8"Включить", &Options::Triggerbot::Enabled);
				s(); ImGui::Checkbox(language ? u8"Enable for this weapon" : u8"Включить для текущего оружия", &g_Weapons[CurrentWeapon].TriggerEnabled);
				s(); ImGui::Checkbox(language ? u8"On Key" : u8"На кнопку", &Options::Triggerbot::OnKey);
				s(); ImGui::KeyBox(language ? u8"Key Bind" : u8"Кнопка", &Options::Triggerbot::Key, "no");

				s(); ImGui::SliderInt(language ? u8"Chance of hit" : u8"Шанс попадания", &g_Weapons[CurrentWeapon].TriggerHitChance, 0, 100);
				s(); ImGui::SliderInt(language ? u8"Minimum damage" : u8"Минимальный урон", &g_Weapons[CurrentWeapon].TriggerMinDamage, 0, 100);
				s(); ImGui::SliderFloat(language ? u8"First shot delay(ms)" : u8"Задержка на первый выстрел(мс)", &g_Weapons[CurrentWeapon].TriggerFirstShotDelay, 0.f, 1.f);
				ImGui::Spacing();
				s(); ImGui::Checkbox(language ? u8"Head" : u8"Голова", &g_Weapons[CurrentWeapon].TriggerHitboxHead);
				s(); ImGui::Checkbox(language ? u8"Chest" : u8"Плечи", &g_Weapons[CurrentWeapon].TriggerHitboxChest);
				s(); ImGui::Checkbox(language ? u8"Stomach" : u8"Живот", &g_Weapons[CurrentWeapon].TriggerHitboxStomach);
				s(); ImGui::Checkbox(language ? u8"Arms" : u8"Руки", &g_Weapons[CurrentWeapon].TriggerHitboxArms);
				s(); ImGui::Checkbox(language ? u8"Legs" : u8"Ноги", &g_Weapons[CurrentWeapon].TriggerHitboxLegs);
			}
			else {
				ImGui::Spacing();
				s(); ImGui::Text(u8"Возьмите оружие в руки");
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}



namespace CMenu
{
	void WeaponList()
	{

		//ImGui::SetNextWindowSize(ImVec2(130, 900), ImGuiSetCond_FirstUseEver);
		if (ImGui::BeginChild(("Weapons"), ImVec2(250, 715), &Options::Visuals::ESP::playerlist::enable, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
		{
			
			//ImGui::SetNextWindowPos(ImVec2(200, 700));
			ImGui::ListBoxHeader(("##weapons"), ImVec2(250, 715));
			{
				static int selectedItm = 0;
				for (int i = 0; i < 33; i++) {
					bool selected = i == selectedItm;

					if (ImGui::Selectable(weaponnames[i], selected)){
						selectedItm = i;
						
					}
					//if (!autoopred)	CurrentWeapon = U::GetWeaponIdByName(selectedItm);
				}
			}
			ImGui::ListBoxFooter();

		}
		ImGui::EndChild();
	}


	void PlayerList()
	{
		//C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer();

		//ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiSetCond_FirstUseEver);
		//if (ImGui::Begin(("Player list"), &Options::Visuals::ESP::playerlist::enable, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
		//{
		//	static int currentPlayer = -1;

		//	if (!g_pEngine->IsInGame() || !pLocalPlayer)
		//		currentPlayer = -1;

		//	ImGui::ListBoxHeader(("##PLAYERS"), ImVec2(-1, (ImGui::GetWindowSize().y - 300)));
		//	{
		//		if (g_pEngine->IsInGame())
		//		{
		//			for (int i = 0; i <= g_pGlobals->maxclients; i++)
		//			{

		//				if (i == g_pEngine->GetLocalPlayer())
		//					continue;

		//				auto Target = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
		//				if (!Target)
		//					continue;
		//				if (Target->GetClientClass()->iClassID != 40)
		//					continue;

		//				if (Target->Team() == pLocalPlayer->Team())
		//					continue;

		//				player_info_t entityInformation;
		//				g_pEngine->GetPlayerInfo(i, &entityInformation);

		//				if (strcmp(entityInformation.name, "GOTV") && !Target->Weapon())
		//					continue;

		//				ImGui::Separator();
		//				char buf[255]; sprintf_s(buf, u8"%s", entityInformation.name);
		//				if (ImGui::Selectable(buf, i == currentPlayer, ImGuiSelectableFlags_SpanAllColumns))
		//					currentPlayer = i;
		//			}
		//		}
		//	}
		//	ImGui::ListBoxFooter();

		//	//Vars.Players.AAA.MiscFixes

		//	if (currentPlayer != -1)
		//	{
		//		player_info_t entityInformation;
		//		g_pEngine->GetPlayerInfo(currentPlayer, &entityInformation);

		//		ImVec2 siz = ImVec2(120, 1000 - ImGui::GetCursorPosY() - 40);
		//		ImVec2 size = ImVec2(200, 1000 - ImGui::GetCursorPosY() - 40);
		//		if (ImGui::BeginChild(("##PLISTFIX-CHILD"), siz, false))
		//		{
		//			ImGui::Checkbox("Highlight", &Options::Visuals::ESP::playerlist::whitelist[currentPlayer - 1]);
		//			ImGui::Checkbox("Disable Aimbot", &Options::Visuals::ESP::playerlist::no_aim[currentPlayer - 1]);
		//			ImGui::Checkbox("Disable ESP", &Options::Visuals::ESP::playerlist::no_esp[currentPlayer - 1]);
		//			ImGui::Checkbox("Disable Resolver", &Options::Visuals::ESP::playerlist::dontresolve[currentPlayer - 1]);

		//		} ImGui::EndChild(); ImGui::SameLine();
		//	}
		//}
		//ImGui::End();
		return;
	}
	void color( ) {
		

		ImGuiStyle& style = ImGui::GetStyle();
		//		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowPadding = ImVec2(15, 15);
		style.WindowRounding = 5.0f;
		style.FramePadding = ImVec2(5, 5);
		style.FrameRounding = 4.0f;
		style.ItemSpacing = ImVec2(12, 8);
		style.ItemInnerSpacing = ImVec2(8, 6);
		style.IndentSpacing = 25.0f;
		style.ScrollbarSize = 15.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 3.0f;


		style.Colors[ImGuiCol_Text] = ImVec4(0.83f, 0.95f, 0.95f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.39f, 0.80f, 0.80f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImColor(1, 10, 24); //ImVec4(0.09f, 0.27f, 0.27f, 0.87f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.75f, 0.75f, 0.00f); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImColor(1, 10, 24);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(1, 10, 24);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(1, 10, 24);
		style.Colors[ImGuiCol_TitleBg] = ImColor(1, 10, 24); //ImVec4(0.16f, 0.49f, 0.49f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.49f, 0.49f, 0.60f);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(1, 10, 24); //ImVec4(0.18f, 0.56f, 0.56f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.47f, 0.47f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.04f, 0.08f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.f, 1.f, 1.f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.95f, 0.95f, 0.95f, 1.f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f); //заинжекти
		//style.Colors[ImGuiCol_ComboBg] = ImVec4(0.18f, 0.55f, 0.55f, 0.99f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.44f, 0.81f, 0.81f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.33f, 0.78f, 0.78f, 0.60f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.33f, 0.78f, 0.78f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f); //style.Colors[ImGuiCol_Button] = ImVec4(0.4f, 0.55f, 0.55f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.7f, 0.7f, 0.7f, 1.f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.15f, 0.44f, 0.44f, 0.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.33f, 0.78f, 0.78f, 0);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.33f, 0.78f, 0.78f, 0);
		style.Colors[ImGuiCol_Column] = ImVec4(0.25f, 0.74f, 0.74f, 0.40f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.25f, 0.74f, 0.74f, 0.60f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.25f, 0.74f, 0.74f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.53f, 0.84f, 0.84f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.53f, 0.84f, 0.84f, 1.00f);
		//	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.22f, 0.67f, 0.67f, 1.00f); //
		//	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.53f, 0.84f, 0.84f, 0.40f);
		//	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.53f, 0.84f, 0.84f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.53f, 0.84f, 0.84f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 0.84f, 0.84f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.53f, 0.84f, 0.84f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.84f, 0.84f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.13f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.09f, 0.27f, 0.27f, 0.67f);






	}

	void styled( ) {
		ImGuiStyle& style = ImGui::GetStyle( );
		style.ItemSpacing = ImVec2( 8, 4 );
		style.WindowRounding = 0.f;
	//	style.FramePadding = ImVec2(4, 0);
		style.FramePadding = ImVec2( 5, 5 );
		style.WindowPadding = ImVec2( 7, 7 );
		style.ScrollbarSize = 10.f;
		style.ScrollbarRounding = 0.f;
		style.GrabMinSize = 16.f;
		style.GrabRounding = 5.f;

	}

	bool worldtexture = false;
	bool legitTab = true;
	bool visualsTab = false;
	bool radarTab = false;
	bool changerTab = false;
	bool colorsTab = false;
	bool miscTab = false;
	bool configTab = false;
	bool InventoryTab = false;
	bool triggerTab = false;
	bool visEspTab = true;
	bool visChamsTab = false;
	bool visHandsTab = false;
	bool visMiscTab = false;

	int windowWidth = 1000;
	int windowHeight = 500;
	int curWidth = 0;
	int curHeight = 0;
	int curX = 0;
	int curY = 0;
	int tabHeight = 48;

	void SelectTab( bool* tab ) {
		legitTab = false;
		visualsTab = false;
		radarTab = false;
		changerTab = false;
		colorsTab = false;
		miscTab = false;
		configTab = false;
		InventoryTab = false;
		triggerTab = false;
		*tab = true;
	}

	void SelectVisualsSubTab( bool* tab ) {
		visEspTab = false;
		visChamsTab = false;
		visHandsTab = false;
		visMiscTab = false;

		*tab = true;
	}

	bool DrawTab( char* name, int tabWidth, int tabHeight, bool *boole, bool forceTabs = true ) {
		bool ret = false;
		if( ImGui::Tab( name, ImVec2( tabWidth, tabHeight ), *boole ) ) {
			ret = true;
			*boole = true;
			if( forceTabs ) SelectTab( boole );
		}
		return ret;
	}

	bool DrawTab( char* name, int tabWidth, int tabHeight, bool boole, bool forceTabs = true ) {
		return DrawTab( name, tabWidth, tabHeight, &boole, forceTabs );
	}

	int viagra = 0;
	bool Watermarkboolean;
	void DrawWatermark( ) {

		if( ImGui::Begin( ( "Watermark" ), &G::MenuOpened, ImVec2( 210, 27 ), 1.0F, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize ) ) {
			ImGuiContext* io = ImGui::GetCurrentContext( );
			ImGuiStyle& style = ImGui::GetStyle( );
			io->FontSize = 20;
			ImGui::Text( "NEON" );
		}
		ImGui::End( );
	}
	int CalcTabWidth( int tabs ) {
		ImGuiStyle& style = ImGui::GetStyle( );
		//return ((windowWidth - (style.WindowPadding.x * 2)) / tabs) - (style.ItemSpacing.x * tabs);
		return ( curWidth - ( ( style.WindowPadding.x ) + ( style.ItemSpacing.x * tabs ) ) ) / tabs;
		//return windowWidth / tabs;
	}

	bool DrawTabs( ) {
		
		DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize; //| ImGuiWindowFlags_NoScrollWithMouse;
		if (ImGui::Begin("##MainWindowz", &G::MenuOpened, ImVec2(900, 900), 0.f, dwFlag)) {
			{

				ImGuiContext* io = ImGui::GetCurrentContext();
				ImGuiStyle& style = ImGui::GetStyle();
				ImDrawList* draw = ImGui::GetWindowDrawList();
				ImVec2 win_pos = ImGui::GetWindowPos();

				//снизу идёт код для отрисовки бг + бг ДЛЯ табов //482 вмсето 630
				{
					draw->AddRectFilled(ImVec2(win_pos.x + 12, win_pos.y + 38), ImVec2(win_pos.x + 187, win_pos.y + 578), ImColor(9, 20, 37, 255));
					draw->AddRectFilledMultiColor(ImVec2(win_pos.x + 12, win_pos.y + 36), ImVec2(win_pos.x + 187, win_pos.y + 38), ImColor(1, 10, 24, 255), ImColor(1, 10, 24, 255), ImColor(9, 20, 37, 255), ImColor(9, 20, 37, 255));
					draw->AddRectFilledMultiColor(ImVec2(win_pos.x + 12, win_pos.y + 578), ImVec2(win_pos.x + 187, win_pos.y + 578), ImColor(9, 20, 37, 255), ImColor(9, 20, 37, 255), ImColor(1, 10, 24, 255), ImColor(1, 10, 24, 255));
					int kostilchik[2];
					switch (tab)
					{
					case 0: kostilchik[0] = 18, kostilchik[1] = 131; break;
					case 1: kostilchik[0] = 71, kostilchik[1] = 184; break;
					case 2: kostilchik[0] = 125, kostilchik[1] = 237; break;
					case 3: kostilchik[0] = 176, kostilchik[1] = 289; break;
					case 4: kostilchik[0] = 228, kostilchik[1] = 341; break;
					case 5: kostilchik[0] = 280, kostilchik[1] = 393; break;
					case 6: kostilchik[0] = 332, kostilchik[1] = 445; break;
					case 7: kostilchik[0] = 384, kostilchik[1] = 497; break;
					}
					draw->AddImage(glow_tab[0], ImVec2(win_pos.x + 13, win_pos.y + kostilchik[0]), ImVec2(win_pos.x + 66, win_pos.y + kostilchik[1]));
					draw->AddRectFilled(ImVec2(win_pos.x + 187, win_pos.y + 36), ImVec2(win_pos.x + 736, win_pos.y + 578), ImColor(1, 10, 24, 255));
					draw->AddRectFilled(ImVec2(win_pos.x + 12, win_pos.y + 578), ImVec2(win_pos.x + 736, win_pos.y + 578), ImColor(1, 10, 24, 255));


					//часть отрисовки бг (верхняя панель + обводка)
					draw->AddRectFilled(ImVec2(win_pos.x + 12, win_pos.y + 2), ImVec2(win_pos.x + 736, win_pos.y + 34), ImColor(10, 31, 51, 255));
					draw->AddRectFilledMultiColor(ImVec2(win_pos.x + 12, win_pos.y + 34), ImVec2(win_pos.x + 736, win_pos.y + 36), ImColor(10, 31, 51, 255), ImColor(10, 31, 51, 255), ImColor(1, 10, 24, 255), ImColor(1, 10, 24, 255));
					draw->AddRect(ImVec2(win_pos.x + 11, win_pos.y + 1), ImVec2(win_pos.x + 737, win_pos.y + 578), ImColor(0, 0, 0, 90), 1.f, -1, 1.f);
				}
				//отрисовка закончилась

				//ImGuiStyle& style = ImGui::GetStyle();
				style.Colors[ImGuiCol_ChildWindowBg] = ImColor(0, 0, 0, 0);
				style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
				draw->AddImage(logotip, ImVec2(win_pos.x + 20, win_pos.y + 12), ImVec2(win_pos.x + 85, win_pos.y + 26));

				draw->AddImage(!language ? Flags[0] : Flags[1], ImVec2(win_pos.x + 665, win_pos.y + 10), ImVec2(win_pos.x + 688, win_pos.y + 27));
				//ImGui::PushFont(Dejavu[15]);
				draw->AddText(ImVec2(win_pos.x + 689, win_pos.y + 10), ImColor(255, 255, 255), (language == 1) ? " RU" : " US");
				//ImGui::PopFont();
				//ImGui::PushFont(Dejavu[12]);
				ImGui::Text(""); ImGui::SameLine(660);	if (ImGui::Button("##Memes", ImVec2(55, 12), 1)) language = !(language);

				//сами табы
				ImGui::BeginChild("##Tabs", ImVec2(173, 600), false, dwFlag);
				{
					style.Colors[ImGuiCol_Button] = ImVec4(0.f, 0.f, 0.f, 0.f);
					style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
					style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
					ImDrawList* draw2 = ImGui::GetWindowDrawList();
					std::string tabz[8] = { "Aim","Wallhack","Radar","Skins","Colors","Inventory", "Triggerbot", "Other" };
					std::string tabz_rus[8] = { u8"Аим",u8"Валлхак",u8"Радар",u8"Скины",u8"Цвета",u8"Инвентарь", u8"Триггербот", u8"Другое" };
					std::string tabz_kostil[8] = { "##Aim","##Wallhack","##Radar","##Skins","##Colors","##Inventory", "##Triggerbot", "##Other" };
					int x_tab_txt[8] = { 67,120,173,225,277,329,381,433 };
					Tab tabs;
					for (int i = 0; i < 8; i++) tabs.add(tabz_kostil[i]);
					tabs.draw(&tab, draw2);
					//ImGui::PushFont(Dejavu[12]);
					//отрисовка текста табов
					for (int i = 0; i < 8; i++) {
						if (hovered_tab[i]) draw2->AddText(ImVec2(win_pos.x + 82, win_pos.y + x_tab_txt[i]), (tab == i) ? ImColor(255, 0, 87) : ImColor(180, 0, 87), !language ? tabz_rus[i].c_str() : tabz[i].c_str());
						else draw2->AddText(ImVec2(win_pos.x + 82, win_pos.y + x_tab_txt[i]), (tab == i) ? ImColor(255, 0, 87) : ImColor(255, 255, 255), !language ? tabz_rus[i].c_str() : tabz[i].c_str());
					}


					//отрисовка иконок табов
					for (int i = 0; i < 8; i++) {
						if (hovered_tab[i]) draw2->AddImage(icons[i], ImVec2(win_pos.x + 48, win_pos.y + x_tab_txt[i] - ((i == 5) ? (-2) : 2)), ImVec2(win_pos.x + 68, win_pos.y + ((i == 5) ? x_tab_txt[i] + 14 : x_tab_txt[i] + 18)), ImVec2(0, 0), ImVec2(1, 1), (tab == i) ? ImColor(255, 0, 87) : ImColor(180, 0 ,87));
						else draw2->AddImage(icons[i], ImVec2(win_pos.x + 48, win_pos.y + x_tab_txt[i] - ((i == 5) ? (-2) : 2)), ImVec2(win_pos.x + 68, win_pos.y + ((i == 5) ? x_tab_txt[i] + 14 : x_tab_txt[i] + 18)), ImVec2(0, 0), ImVec2(1, 1), (tab == i) ? ImColor(255, 0, 87) : ImColor(255, 255, 255));
					}

					//ImGui::PopFont();

				}
				ImGui::EndChild();
				ImGui::SameLine(187.f);
				//выше идёт отступ для разметки и после него добавляется child для окна таба
				switch (tab)
				{
				case 0:	Aimbotmenu();		 break; //Aimbot Child
				case 1: WallHack();				 break; //Wallhack 
				case 2: Radarmenu();		 break; //Radar
				case 3:	Skins();				 break; //Skins
				case 4:	Colorsmenu();				 break; //Colors
				case 5:	Inventory_tab();				 break; //Inventory
				case 6:	Triggermenu();				 break; //Triggerbot
				case 7:	Othermenu();			 break; //Other (дополнительно)
				}
				int tabWidth = CalcTabWidth(8);
				//style.Colors[ImGuiCol_WindowBg].w = 0.0f;

				float lastSize = io->FontSize;
				io->FontSize = 20;
				ImGui::SameLine(740.f);
				if (!autoopred) WeaponList();
				//ImGui::BeginGroup();  //я так и сказал)

					//DrawTab(("LEGIT"), 150, tabHeight, &legitTab);
					//DrawTab(("VISUALS"), 150, tabHeight, &visualsTab);
					//DrawTab(("TRIGGER"), 150, tabHeight, &triggerTab);
					//DrawTab(("RADAR"), 150, tabHeight, &radarTab);
					//DrawTab(("CHANGER"), 150, tabHeight, &changerTab);
					//DrawTab(("COLORS"), 150, tabHeight, &colorsTab);
					//DrawTab(("MISC"), 150, tabHeight, &miscTab);
					//DrawTab(("INVENTORY"), 150, tabHeight, &InventoryTab);


				//io->FontSize = lastSize;
				//ImGui::EndGroup(); //объединяем объекты в группу

				//ImGui::SameLine(/*posX*/); //сдвигаем фрейм в право

				//ImGui::BeginGroup();  //создаем  новую группу объектов //ты на галку нажимал?стоп там с задержкой жмётся у меня такого не было у ккккк				  ImVec2(windowPos.x + windowWidth + style.WindowPadding.x - 1, windowPos.y + 53), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), 0.0F, -1, 2.0F);
			}

			return true;
		}
		return false;
	}
	
	void DrawSpectatorList() {
		if (!Options::Misc::SpectatorList)
			return;

		Moveable::Run(&Options::Misc::SpectatorListX, &Options::Misc::SpectatorListY, 100, 200);

		// Clamp pos
		int specs = 0;
		std::string spect = u8"";
		int localIndex = g_pEngine->GetLocalPlayer();
		C_BasePlayer* pLocalEntity = g_pEntityList->GetClientEntity<C_BasePlayer>(localIndex);
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
			player_info_t pinfo;

			// The entity isn't some laggy peice of shit or something
			if (pBaseEntity &&  pBaseEntity != pLocalEntity) {
				if (!pLocalEntity)
					continue;
				if (g_pEngine->GetPlayerInfo(i, &pinfo) && !pBaseEntity->Health() > 0 && !pBaseEntity->IsDormant()) {
					DWORD obs = pBaseEntity->GetObserverTargetHandle();

					if (obs) {
						IClientEntity *pTarget = g_pEntityList->GetClientEntityFromHandle(obs);
						player_info_t pinfo2;
						if (pTarget) {
							if (g_pEngine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2)) {
								if (pTarget->GetIndex() == pLocalEntity->GetIndex()) {
									spect += pinfo.name;
									spect += " -> ";
									spect += pinfo2.name;
									spect += "\n";
									specs++;
								}
							}
						}
					}
				}
			}
		}


		int X = Options::Misc::SpectatorListX;
		int Y = Options::Misc::SpectatorListY;
		int Size = Options::Radar::Size;

		const int SPACE = 4;
		const int DOT = 6;

		Color MainColor = Options::Radar::MainColor;
		MainColor[3] = Options::Radar::Alpha;
		Color OutlineColor = Options::Radar::OutlineColor;
		OutlineColor[3] = 150;

		//bool bTrueRadar = Options::Radar::Textured && TrueRadar::m_bLoaded;
		//if (bTrueRadar) // check for true radar loaded вижуалка пиздаболина
		//	TrueRadar::Render();
		//else
		//	D::RectFilled(X, Y, Size, Size, MainColor, false);

		ImVec2 siz = ImGui::CalcTextSize(spect.c_str()); //спек лист тестил? нет тести сейчас
		Color kekcolor = { 1, 4, 27, 200 };
		//D::RectFilled(ImVec2(win_pos4.x + 0, win_pos4.y + 0), ImVec2(win_pos4.x + 200, win_pos4.y + 5), ImColor(255, 0, 87, min(prosrachnost_spect + 40, 255))); //нарисовать ебучий черный прямоугольни
		D::RectFilled(X - SPACE, Y - SPACE, 200 + SPACE * 2, 5, Color(255, 0, 87)); //нарисовать ебучий черный прямоугольни
		D::RectFilled(X - SPACE, Y - SPACE + 5, 200 + SPACE * 2, siz.y + 30 + SPACE * 2, kekcolor); //нарисовать ебучий черный прямоугольни

		for (int i = 0; i < specs; ++i) {
			D::CircleFilled(X - SPACE + 10, Y + 13 * i + 17, 5, Color(255, 0, 87)); // тут я рисую кружок. 
		}
		
		D::Text(X + 15, Y + 10, Color(255, 255, 255, 255), false, false, Font::ESP, spect.c_str()); // я ебал имгуи, что ТУТ СУКА НЕПОНЧЧТНО НАПИСАНо??????к даю тебе ещё 5 м //


		//D::Rect(X - SPACE, Y - SPACE, Size + (SPACE * 2), Size + (SPACE * 2), 1, OutlineColor, false, false); // outline
		//D::Line(X - SPACE, Y + (Size / 2), X + Size + SPACE, Y + (Size / 2), OutlineColor, 1, false); // line1
		//D::Line(X + (Size / 2), Y - SPACE, X + (Size / 2), Y + Size + SPACE, OutlineColor, 1, false); // line2
		//D::RectFilled(X + (Size / 2), Y + (Size / 2), DOT, DOT, Color::White(), true);



		//vector2 spec_min, spec_max;
		//spec_min[0] = Options::Misc::SpectatorListX;
		//spec_min[1] = Options::Misc::SpectatorListY; 



		if (G::MenuOpened) {
			using vector2 = float[2];
			vector2 radar_min, radar_max;

			radar_min[0] = Options::Misc::SpectatorListX;
			radar_min[1] = Options::Misc::SpectatorListY;



			radar_max[0] = Options::Misc::SpectatorListX + 240;
			radar_max[1] = Options::Misc::SpectatorListY + 65;

			//D::TriangleFilled(radar_max[0] - 20, radar_max[1], radar_max[0], radar_max[1], radar_max[0], radar_max[1] - 20, Color(200, 200, 200, 200));

			POINT p;
			if (GetCursorPos(&p)) {
				vector2 cursor;
				cursor[0] = p.x;
				cursor[1] = p.y;

				static bool save_pos = false;
				static bool was_resized = false;
				static bool was_moved = false;
				static vector2 saved{};

				auto mouse_in_pos = [cursor](vector2 start, vector2 end) {
					return ((cursor[0] >= start[0] + 125) && (cursor[1] >= start[1] + 90) && (cursor[0] <= end[0] + 125) && (cursor[1] <= end[1] + 90));
				};

				auto hold = GetAsyncKeyState(VK_LBUTTON);

				vector2 grab = { radar_max[0] - 20, radar_max[1] - 20 };
				vector2 grab2 = { radar_max[0] + 10, radar_max[1] + 10 };
				//if ((was_resized || hold && mouse_in_pos(grab, grab2))) {
				//	Options::Radar::Size = (cursor[0] - radar_min[0]) + 10;
				//}
				if (was_moved || hold && mouse_in_pos(radar_min, radar_max)) {
					if (save_pos == false) {
						saved[0] = cursor[0] - Options::Misc::SpectatorListX;
						saved[1] = cursor[1] - Options::Misc::SpectatorListY;
						save_pos = true;
					}
					Options::Misc::SpectatorListX = cursor[0];
					Options::Misc::SpectatorListY = cursor[1];
					Options::Misc::SpectatorListX -= saved[0];
					Options::Misc::SpectatorListY -= saved[1];

					was_resized = false;
				}
				else {
					save_pos = was_moved = was_resized = false;
				}

				if (!was_resized)
					was_resized = hold && mouse_in_pos(grab, radar_max);
				else
					was_resized = hold;

				if (!was_moved)
					was_moved = hold && mouse_in_pos(radar_min, radar_max);
				else
					was_moved = hold;
			}
		}

	}
	void DrawSpectatorList2( ) {

		if( !Options::Misc::SpectatorList )
			return;

		if( !g_pEngine->IsConnected( ) || !g_pEngine->IsInGame( ) )
			return;


		int CordY;
		int CordX;
		int specs = 0;
		std::string spect = u8"";
		int localIndex = g_pEngine->GetLocalPlayer( );
		C_BasePlayer* pLocalEntity = g_pEntityList->GetClientEntity<C_BasePlayer>( localIndex );
		for( int i = 1; i < g_pEngine->GetMaxClients( ); i++ ) {
			C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>( i );
			player_info_t pinfo;

			// The entity isn't some laggy peice of shit or something
			if( pBaseEntity &&  pBaseEntity != pLocalEntity ) {
				if( !pLocalEntity )
					continue;
				if( g_pEngine->GetPlayerInfo( i, &pinfo ) && !pBaseEntity->Health( ) > 0 && !pBaseEntity->IsDormant( ) ) {
					DWORD obs = pBaseEntity->GetObserverTargetHandle( );

					if( obs ) {
						IClientEntity *pTarget = g_pEntityList->GetClientEntityFromHandle( obs );
						player_info_t pinfo2;
						if( pTarget ) {
							if( g_pEngine->GetPlayerInfo( pTarget->GetIndex( ), &pinfo2 ) ) {
								if( pTarget->GetIndex( ) == pLocalEntity->GetIndex( ) ) {
									spect += pinfo.name;
									spect += " -> ";
									spect += pinfo2.name;
									spect += "\n";
									specs++;
								}
							}
						}
					}
				}
			}
		}
		//DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize;
		DWORD dwFlag5 = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar;
		ImVec2 siz1 = ImGui::CalcTextSize(spect.c_str());
		if( ImGui::Begin( ( "Spectator List" ), 0, ImVec2(200, 200), 0, dwFlag5) ) { //ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
			ImGuiStyle& style = ImGui::GetStyle( );
			ImDrawList* draw4 = ImGui::GetWindowDrawList();
			ImVec2 win_pos4 = ImGui::GetWindowPos(); 

			
			//if( specs > 1 )
				//spect += "\n"; //пока это затесть
			ImVec2 siz = ImGui::CalcTextSize( spect.c_str( ) );
			//ImGui::SetWindowSize( ImVec2( 200, 45 + siz.y ) ); // сука это не поможет блять сейчас могу сделать 100% рабочую реализацию по времени
			//ImGui::Text( ( spect.c_str( ) ) ); //инжекти
			draw4->AddRectFilled(ImVec2(win_pos4.x + 0, win_pos4.y + 0), ImVec2(win_pos4.x + 200, win_pos4.y + 5), ImColor(255, 0, 87, min(prosrachnost_spect + 40, 255))); //нарисовать ебучий черный прямоугольни
			draw4->AddRectFilled(ImVec2(win_pos4.x + 0, win_pos4.y + 5), ImVec2(win_pos4.x + 200, win_pos4.y + 25 + siz.y), ImColor(1, 4, 27, prosrachnost_spect)); //нарисовать ебучий черный прямоугольни
			
			for (int i = 0; i < specs; ++i) {
				draw4->AddCircleFilled(ImVec2(win_pos4.x + 7, win_pos4.y + 18 * i + 12), 5, ImColor(255, 0, 87));
			}
			draw4->AddText(ImVec2(win_pos4.x + 15, win_pos4.y + 10), ImColor(255, 255, 255), spect.c_str()); // я ебал имгуи, что ТУТ СУКА НЕПОНЧЧТНО НАПИСАНо??????к даю тебе ещё 5 м //
			

			

		}
		ImGui::End( );
	}

	void Render( ) {
	#pragma region English
		static const char* tabNames[] = {
			"Aimbot",
			"Visuals",
			"Trigger",
			"Changer",
			"Radar",
			"Misc",
			"Settings"
		};

		static const char* AimTabNames[] = {
			"Global",
			"Weapon"
		};

		static const char* ProfileTabNames[] = {
			"Inventory",
			"Profile"
		};

		static const char* VisualTabNames[] = {
			"Esp",
			"Chams",
			"Misc"
		};

		static const char* TrigerTabNames[] = {
			"Global",
			"Weapon"
		};

		static const char* ChangerTabNames[] = {
			"Inv",
			"Skinchanger"
		};

		static const char* MiscTabNames[] = {
			"Global",
			"Exploits"
		};

	#pragma endregion

			//вот тута трогай
	#pragma region Russian
		static const char* RustabNames[] = {
			u8"Наводка",
			u8"Визуалы",
			u8"Триггер",
			u8"Скины",
			u8"Радар",
			u8"Разное",
			u8"Настройки"
		};

		static const char* RusAimTabNames[] = {
			u8"Под все оружия",
			u8"Под текущее оружие" // там не пометится длинная фраза
		};

		static const char* RusVisualTabNames[] = {
			u8"Внешняя отрисовка",
			u8"Заливка моделей",
			u8"Разное"
		};

		static const char* RusTrigerTabNames[] = {
			u8"Общие настройки",
			u8"Под текущее оружие"
		};

		static const char* RusChangerTabNames[] = {
			u8"Инвентарь",
			u8"Профиль"
		};

		static const char* RusMiscTabNames[] = {
			u8"Основные",
			u8"Уязвимости"
		};

	#pragma endregion
		PlayerList();
		//WeaponList();
		auto& style = ImGui::GetStyle( );
		static ImVec2 mainWindowPos;
		static int otherpages = 0;
		static int aimtabs = 0;
		static int visualtabs = 0;
		static int trigertabs = 0;
		static int changertabs = 0;
		static int misctabs = 0;
		static bool language;
		static bool mouse_enabled = false;
		

		static int pX, pY, ScreenX, ScreenY;
		g_pInput->GetCursorPosition( &pX, &pY );
		g_pEngine->GetScreenSize( ScreenX, ScreenY );
		ImGuiIO& io = ImGui::GetIO( );
		io.MousePos.x = ( float )( pX );
		io.MousePos.y = ( float )( pY );

		static DWORD flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar;
		
		
		LastWeapon = U::SafeWeaponID();
		if (autoopred) {
			if (LastWeapon.IsAimable()) {
				CurrentWeapon = LastWeapon;
			}
		}
		
		DrawWeapon = CurrentWeapon != 0 && CurrentWeapon.IsAimable( );
		if( Options::Misc::SpectatorList )
			DrawSpectatorList( );

		DrawTabs();
		
		//ImGui::EndGroup( );
		ImGui::End( );




		DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize;
		//if (ImGui::Begin("##MainWindowz", &G::MenuOpened, ImVec2(960, 700), 0.f, dwFlag))
		
		
		if (texturing) {
			static int PIDOR_SYKA_NENAVIHY = 0;
			
		}

	}
	
	void DrawRadar() {
		if( !Options::Radar::Enabled )
			return;
		if( Options::Radar::Style != 0 )
			return;

		Moveable::Run( &Options::Radar::X, &Options::Radar::Y, Options::Radar::Size, Options::Radar::Size );

		// Clamp pos
		Math::Clamp( Options::Radar::X, 0, g_iScreenWidth - Options::Radar::Size );
		Math::Clamp( Options::Radar::Y, 0, g_iScreenHeight - Options::Radar::Size );

		int X = Options::Radar::X;
		int Y = Options::Radar::Y;
		int Size = Options::Radar::Size;

		const int SPACE = 4;
		const int DOT = 6;

		Color MainColor = Options::Radar::MainColor;
		MainColor[3] = Options::Radar::Alpha;
		Color OutlineColor = Options::Radar::OutlineColor;
		OutlineColor[3] = 150;

		bool bTrueRadar = Options::Radar::Textured && TrueRadar::m_bLoaded;
		if( bTrueRadar ) // check for true radar loaded вижуалка пиздаболина
			TrueRadar::Render( );
		else
			D::RectFilled( X, Y, Size, Size, MainColor, false );

		D::Rect( X - SPACE, Y - SPACE, Size + ( SPACE * 2 ), Size + ( SPACE * 2 ), 1, OutlineColor, false, false ); // outline
		D::Line( X - SPACE, Y + ( Size / 2 ), X + Size + SPACE, Y + ( Size / 2 ), OutlineColor, 1, false ); // line1
		D::Line( X + ( Size / 2 ), Y - SPACE, X + ( Size / 2 ), Y + Size + SPACE, OutlineColor, 1, false ); // line2
		//D::RectFilled(X + (Size / 2), Y + (Size / 2), DOT, DOT, Color::White(), true);

		// Rendering players
		if( g_pEngine->IsInGame( ) && g_pEngine->IsConnected( ) ) {
			C_BasePlayer* pLocalEntity = g_pEntityList->GetClientEntity<C_BasePlayer>( g_pEngine->GetLocalPlayer( ) );
			if( pLocalEntity ) {
				Vector3 LocalPos = pLocalEntity->EyePosition( );
				Vector3 LocalMapPos = TrueRadar::WorldToMap( LocalPos );
				Vector3 ang;
				g_pEngine->GetViewAngles( ang );
				for( int i = 0; i < g_pEngine->GetMaxClients( ); i++ ) {
					C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>( i );

					if( !pBaseEntity )
						continue;
					if( pBaseEntity->Health( ) < 1 )
						continue;
					if( pBaseEntity->Dormant( ) )
						continue;
					if( pBaseEntity == pLocalEntity )
						continue;

					bool bIsEnemy =  pLocalEntity->Team( ) != pBaseEntity->Team( ) ;
					bool isVisibled = G::VisibledPlayers[i];
					bool isVisibledSmoke = G::VisibledPlayersSmoke[i];

					if( Options::Radar::EnemyOnly && !bIsEnemy )
						continue;

					Vector3 EntityPos;
					if( bTrueRadar ) {
						EntityPos = pBaseEntity->GetOrigin( );
						EntityPos = TrueRadar::WorldToMap( EntityPos );
						EntityPos.x = ( LocalMapPos.x - EntityPos.x );
						EntityPos.y = ( LocalMapPos.y - EntityPos.y );
						//EntityPos.x = -(EntityPos.y - LocalMapPos.y);
						//EntityPos.y = EntityPos.x - LocalMapPos.x;
						EntityPos.x += X + ( Size / 2 );
						EntityPos.y += Y + ( Size / 2 );
						Math::RotatePoint( EntityPos, Size, X, Y, ang.y );
						Math::Clamp( EntityPos.x, X - 10, X + Size - 10 );
						Math::Clamp( EntityPos.y, Y - 10, Y + Size - 10 );
					} else
						EntityPos = U::RotatePoint( pBaseEntity->GetOrigin( ), LocalPos, X, Y, Size, Size, ang.y, Options::Radar::Zoom );


					Color clr = bIsEnemy ? ( isVisibled ? Options::Radar::VisibleColor : Options::Radar::InvisibleColor ) : Options::Radar::TeammateColor;

					if( Options::Radar::VisibleOnly && !isVisibled )
						continue;
					if( Options::Radar::SmokeCheck && !isVisibledSmoke )
						continue;

					// fix for AA
					EntityPos.x = ( int )EntityPos.x;
					EntityPos.y = ( int )EntityPos.y;

					int s = Options::Radar::BoxSize;
					Vector3 vDiff = pBaseEntity->GetOrigin( ) - pLocalEntity->GetOrigin( );
					if( Options::Radar::CheckZPos ) {
						if( vDiff.z > 80 ) {
							D::m_pDrawList->AddTriangleFilled( { EntityPos.x - s, EntityPos.y }, { EntityPos.x , EntityPos.y - s }, { EntityPos.x + s, EntityPos.y }, D::GetImColor( clr ) );
						}
						if( vDiff.z < -80 ) {
							D::m_pDrawList->AddTriangleFilled( { EntityPos.x - s, EntityPos.y }, { EntityPos.x , EntityPos.y + s }, { EntityPos.x + s, EntityPos.y }, D::GetImColor( clr ) );
						}
					}
					{
						switch( Options::Radar::BoxType ) {
						case 0:
						{
							D::Rect( EntityPos.x, EntityPos.y, s, s, 3, Color::Black( ), true, false );
							D::Rect( EntityPos.x, EntityPos.y, s, s, 1, clr, true, false );
							break;
						}
						case 1:
						{
							D::RectFilled( EntityPos.x, EntityPos.y, s + 2, s + 2, Color::Black( ), true );
							D::RectFilled( EntityPos.x, EntityPos.y, s, s, clr, true );
							break;
						}
						case 2:
						{
							D::Circle( EntityPos.x, EntityPos.y, s, 12, 2, Color::Black( ) );
							D::Circle( EntityPos.x, EntityPos.y, s, 12, 1, clr );
							break;
						}
						case 3:
						{
							D::CircleFilled( EntityPos.x, EntityPos.y, s + 1, Color::Black( ) );
							D::CircleFilled( EntityPos.x, EntityPos.y, s, clr );
							break;
						}
						default:
							break;
						}

					}
				}
			}
		}

		//vector2 spec_min, spec_max;
		//spec_min[0] = Options::Misc::SpectatorListX;
		//spec_min[1] = Options::Misc::SpectatorListY; 


		
		


		if( G::MenuOpened ) {
			using vector2 = float[2];
			vector2 radar_min, radar_max;
			
			radar_min[0] = Options::Radar::X;
			radar_min[1] = Options::Radar::Y;

			

			radar_max[0] = Options::Radar::X + Options::Radar::Size;
			radar_max[1] = Options::Radar::Y + Options::Radar::Size;

			D::TriangleFilled( radar_max[0] - 20, radar_max[1], radar_max[0], radar_max[1], radar_max[0], radar_max[1] - 20, Color( 200, 200, 200, 200 ) );

			POINT p;
			if( GetCursorPos( &p ) ) {
				vector2 cursor;
				cursor[0] = p.x;
				cursor[1] = p.y;

				static bool save_pos = false;
				static bool was_resized = false;
				static bool was_moved = false;
				static vector2 saved{};

				auto mouse_in_pos = [cursor] ( vector2 start, vector2 end ) {
					return ( ( cursor[0] >= start[0] ) && ( cursor[1] >= start[1] ) && ( cursor[0] <= end[0] ) && ( cursor[1] <= end[1] ) );
				};

				auto hold = GetAsyncKeyState( VK_LBUTTON );

				vector2 grab = { radar_max[0] - 20, radar_max[1] - 20 };
				vector2 grab2 = { radar_max[0] + 10, radar_max[1] + 10 };
				if( ( was_resized || hold && mouse_in_pos( grab, grab2 ) ) ) {
					Options::Radar::Size = ( cursor[0] - radar_min[0] ) + 10;
				} else if( was_moved || hold && mouse_in_pos( radar_min, radar_max ) ) {
					if( save_pos == false ) {
						saved[0] = cursor[0] - Options::Radar::X;
						saved[1] = cursor[1] - Options::Radar::Y;
						save_pos = true;
					}
					Options::Radar::X = cursor[0];
					Options::Radar::Y = cursor[1];
					Options::Radar::X -= saved[0];
					Options::Radar::Y -= saved[1];

					was_resized = false;
				} else {
					save_pos = was_moved = was_resized = false;
				}

				if( !was_resized )
					was_resized = hold && mouse_in_pos( grab, radar_max );
				else
					was_resized = hold;

				if( !was_moved )
					was_moved = hold && mouse_in_pos( radar_min, radar_max );
				else
					was_moved = hold;
			}
		}

	}
	// тут  2 спеклиста сейчас чекну что эт за хуйня(второй) икстати тут вроде поддерживается сохранение
	

};

void Radarmenu()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag);
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 15), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		for (int i = 0; i < 2; i++)ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 510), false, dwFlag);
		{

			s(); ImGui::Checkbox(language ? u8"Activated" : u8"Включить", &Options::Radar::Enabled);
			s(); ImGui::SliderInt(language ? u8"Radar position X" : u8"Позиция по оси X", &Options::Radar::X, 0, g_iScreenWidth);
			s(); ImGui::SliderInt(language ? u8"Radar position Y" : u8"Позиция по оси Y", &Options::Radar::Y, 0, g_iScreenHeight);
			s(); ImGui::SliderFloat(language ? u8"The scale of the radar" : u8"Размер приближения", &Options::Radar::Zoom, 0, 4);
			s(); ImGui::SliderInt(language ? u8"Alpha background radar " : u8"Прозрачность", &Options::Radar::Alpha, 0, 255);
			s(); ImGui::SliderInt(language ? u8"Radar size " : u8"Размер", &Options::Radar::Size, 0, 800);
			s(); ImGui::SliderInt(language ? u8"Fiqure size " : u8"Размер отображеных игроков", &Options::Radar::BoxSize, 1, 12);
			s(); ImGui::Combo(language ? u8"Radar Type  " : u8"Тип радара", &Options::Radar::Style, u8"Extrenal\0Internal\0\0");

			if (Options::Radar::Style == 0) {
				s(); ImGui::Checkbox(language ? u8"Texture" : u8"Включить текстуру карты", &Options::Radar::Textured);
			}
				

			s(); ImGui::Combo(language ? u8"External radar shape type      " : u8"Тип отображения игроков", &Options::Radar::BoxType, u8"Boxes\0Filed boxes\0Cricle\0Filed cricle\0\0");
			s(); ImGui::Checkbox(language ? u8"Do not show allies" : u8"Отображать только врагов", &Options::Radar::EnemyOnly);
			s(); ImGui::Checkbox(language ? u8"Do not display models that are behind the wall" : u8"Отображать видимых игроков", &Options::Radar::VisibleOnly);
			s(); ImGui::Checkbox(language ? u8"Do not display models that are in smoke" : u8"Не отображать игроков через смок", &Options::Radar::SmokeCheck);
			s(); ImGui::Checkbox(language ? u8"Take into account the radar height of the model" : u8"Учитывать высоту модели", &Options::Radar::CheckZPos);


		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}


void Colorsmenu()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag);
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 15), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37); 
		for (int i = 0; i < 2; i++)ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 510), false, dwFlag);
		{
			
				static int selectedItem = 0;

				ImVec2 lastCursor = ImGui::GetCursorPos();

				ImGui::ListBoxHeader("##0", ImVec2(170, 509.0f)); //240
				for (int i = 0; i < Options::Colors.size(); i++) {
					bool selected = i == selectedItem;

					//if (ImGui::Selectable(Options::Colors[i].szName, selected))
					//	selectedItem = i;
					if (ImGui::Selectable(Options::Colors[i].szName, selected))
						selectedItem = i;
				}
				ImGui::ListBoxFooter();

				float nc = lastCursor.x + 180; //260 нах ты здесь 1 написал
				ImGui::SetCursorPos(ImVec2(nc, lastCursor.y));

				Color_t col = Options::Colors[selectedItem];
				int r = (col.pColor[0] * 255.f);
				int g = (col.pColor[1] * 255.f);
				int b = (col.pColor[2] * 255.f);
				int a = (col.pColor[3] * 255.f);

				//ImGui::NewLine(); ImGui::SetCursorPosX(nc);
				//ImGui::SliderInt("A", &a, 0, 255, "%.0f", ImVec4(0, 0, 0, 255));

				col.pColor[0] = r / 255.0f;
				col.pColor[1] = g / 255.0f;
				col.pColor[2] = b / 255.0f;
				col.pColor[3] = a / 255.0f;

				ImGui::NewLine(); ImGui::SetCursorPosX(nc);
				ImVec2 curPos = ImGui::GetCursorPos();
				ImVec2 curWindowPos = ImGui::GetWindowPos();
				curPos.x += curWindowPos.x;
				curPos.y += curWindowPos.y; 

				//ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(curPos.x + 255, curPos.y),
				//	ImVec2(curWindowPos.x + curWidth - 25, curPos.y + 200),
				//	ImGui::GetColorU32(ImVec4(col.pColor[0], col.pColor[1], col.pColor[2], 255))); 

				ImGui::PushItemWidth(310.0f);
				ImGui::ColorPicker3("##COLOR_PICKER", col.pColor);
				ImGui::PopItemWidth(); 
			
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}



void Othermenu()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize; // | ImGuiWindowFlags_NoScrollWithMouse;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag); //447
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		//снизу много говнокода, можно реализовать по другому и намного проще но я даун немного
		//пс. это отрисовка сабтабов (сам врубай мозг и понимай где и как отрисовано и подгоняй размеры для следующих сабтабов)
		{
			draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 49), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));

			if (sab_tab[1] == 0)
			{
				draw3->AddRectFilled(ImVec2(child_pos.x + 20, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(28, 36, 51));
				draw3->AddImage(glow_tab[1], ImVec2(child_pos.x - 132, child_pos.y - 20), ImVec2(child_pos.x + 275, child_pos.y + 54));
				draw3->AddRectFilled(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 48), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(28, 36, 51));

			}
			else if (sab_tab[1] == 1)
			{
				draw3->AddRectFilled(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 130, child_pos.y + 12), ImVec2(child_pos.x + 239, child_pos.y + 60), ImColor(28, 36, 51));
				draw3->AddImage(glow_tab[1], ImVec2(child_pos.x - 25, child_pos.y - 20), ImVec2(child_pos.x + 395, child_pos.y + 54));
				draw3->AddRectFilled(ImVec2(child_pos.x + 20, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 48), ImColor(9, 20, 37));
				draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 12), ImVec2(child_pos.x + 125, child_pos.y + 60), ImColor(28, 36, 51));

			}
			//else if (sab_tab[1] == 2) 
			//{

			//}
			draw3->AddRectFilled(ImVec2(child_pos.x - 5, child_pos.y - 10), ImVec2(child_pos.x + 400, child_pos.y + 12), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x + 125, child_pos.y + 12), ImVec2(child_pos.x + 130, child_pos.y + 48), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x - 5, child_pos.y - 5), ImVec2(child_pos.x + 18, child_pos.y + 48), ImColor(1, 10, 24));
			draw3->AddRectFilled(ImVec2(child_pos.x + 240, child_pos.y + 10), ImVec2(child_pos.x + 400, child_pos.y + 48), ImColor(1, 10, 24));
		}
		//снизу идут сами конпки для сабтабов
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		ImGui::Spacing();	ImGui::Spacing();
		// пы.сы. нахера я текст пустой юзаю? ибо имгуй вещь ебанутая из за чего просто так айтем не сдвинешь, приходится сдвигать от другого айтема 
		//ImGui::Text(""); ImGui::SameLine(language == 0 ? ((sab_tab[1] == 0) ? 47.f : 49.f) : ((sab_tab[1] == 0) ? 50.f : 52.f)); 
		//первая кнопка, прикинь да?
		//ImGui::PushFont((sab_tab[1] == 0) ? Dejavu_bold[14] : Dejavu[15]); инжектить?да
		//ImGui::Text(""); ImGui::SameLine(language == 0 ? ((sab_tab[1] == 0) ? 47.f : 49.f) : ((sab_tab[1] == 0) ? 50.f : 52.f));
		//первая кнопка, прикинь да?
		//ImGui::PushFont((sab_tab[1] == 0) ? Dejavu_bold[14] : Dejavu[15]);
		ImGui::Text(""); ImGui::SameLine(20);

		if (language) draw3->AddText(ImVec2(child_pos.x + 56, child_pos.y + 23), ImColor(255, 255, 255), u8"Misc"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		else draw3->AddText(ImVec2(child_pos.x + 40, child_pos.y + 23), ImColor(255, 255, 255), u8"Обычные"); //сейчас будет ебала с ебан оно относительно гуи отрисов

		if (language) draw3->AddText(ImVec2(child_pos.x + 152, child_pos.y + 23), ImColor(255, 255, 255), u8"Advanced"); //сейчас будет ебала с ебан оно относительно гуи отрисов
		else draw3->AddText(ImVec2(child_pos.x + 150, child_pos.y + 23), ImColor(255, 255, 255), u8"Расширенные"); //сейчас будет ебала с ебан оно относительно гуи отрисов


		if (ImGui::Button("##Style", { 107, 25 }, 1)) sab_tab[1] = 0;
		//ImGui::PopFont();
		//вторая цвет изи фиксануть а ту хуйню в отрисокве щас попытаюсь
		ImGui::SameLine(133);
		//ImGui::PushFont((sab_tab[1] == 1) ? Dejavu_bold[14] : Dejavu[15]); //нужн
		if (ImGui::Button("##Other", { 107, 25 }, 1)) sab_tab[1] = 1;
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 476), false, dwFlag);
		{

			auto draw_child = ImGui::GetWindowDrawList();
			ImVec2 child_pos = ImGui::GetWindowPos();

			ImColor razdel = { 1, 10, 24, 255 };

			//draw_child->AddRectFilled(ImVec2(child_pos.x + 0, child_pos.y + 250), ImVec2(child_pos.x + 510, child_pos.y + 260), razdel);
			switch (sab_tab[1])
			{
			case 0:
			{
				ImGui::Spacing();
				ImGui::Text(""); ImGui::SameLine(10);
				static int iConfig = 0;
				s();
				ImGui::Text(language ? u8"Config actions" : u8"Действия с конфигом");
				s();
				ImGui::Combo(language ? u8"Config" : u8"Конфигом", &iConfig, g_pConfig->szConfigs.c_str());

				s();
				// ct
				//if (ImGui::ImageButton(button, ImVec2(100, 20)))
				//{
				//	g_pConfig->ParseConfigs();
				//}

				if (ImGui::Button(language ? u8"Update" : u8"Обновить"))
					g_pConfig->ParseConfigs();

				ImGui::SameLine();
				if (ImGui::Button(language ? u8"Load" : u8"Загрузить")) {
					updateprev();
					g_pConfig->InitPath(&g_pConfig->vecConfigs[iConfig][0u]);
					g_pConfig->Read();
					
						g_bForceFullUpdate = true;
						U::FullUpdate();
					// ща буду делать сохранения конфигов с новым именем
				}

				ImGui::SameLine();
				//if (ImGui::ImageButton(language ? u8"Save" : u8"Сохранить", button, ImVec2(100, 25))) {
				if (ImGui::Button(language ? u8"Save" : u8"Сохранить")) {
					g_pConfig->InitPath(&g_pConfig->vecConfigs[iConfig][0u]);
					g_pConfig->Save();
				}
				ImGui::SameLine();
				//if (ImGui::Button(language ? u8"Open" : u8"Открыть папку с кофигами")) {
				if (ImGui::Button(language ? u8"Open" : u8"Открыть папку")) {
					char szCommand[512];
					sprintf(szCommand, "explorer %s", g_pConfig->szConfigFolder);
					system(szCommand);
				}

				static char cfgname[30] = "default";
				s();
				ImGui::InputText(language ? u8"Config name" : u8"Имя конфига", cfgname, 30);
				s();
				if (ImGui::Button(language ? u8"Add config" : u8"Добавить конфиг")) {
					std::string cfstring = cfgname;
					std::string cfgpath = "C:\\NEON\\" + cfstring + ".neon";
					std::ofstream outfile(cfgpath);
					outfile << " " << std::endl;
					outfile.close();
				}

				ImGui::Spacing();
				s();
				static int cfgmem = 0;
				int readysetting = 0;

				const char* skyboxes[] =
				{
					"Default",
					"cs_baggage_skybox",
					"cs_tibet",
					"embassy",
					"italy",
					"jungle",
					"nukeblank",
					"office",
					"sky_cs15_daylight_hdr",
					"sky_cs15_daylight2_hdr",
					"sky_cs15_daylight3_hdr",
					"sky_cs15_daylight4_hdr",
					"sky_csgo_cloudy",
					"sky_csgo_night",
					"sky_csgo_night2",
					"sky_dust",
					"sky_venice",
					"vertigo",
					"vertigoblue_hdr",
					"vietnam",
				};
				const char* Type[] =
				{
					"World",
					"StaticProp",
					"Model",

				};

				//ImGui::Checkbox(language ? u8"Open model changer" : u8"Развернуть модель ченжер", &texturing);
				s();
				ImGui::Checkbox((u8"Enable World Changer"), &Options::Texture::Enabled);
				s();
				ImGui::Combo("Sky", &Options::Texture::SkyBox, skyboxes, ARRAYSIZE(skyboxes));
				s();
				ImGui::Text("Settings for"); ImGui::SameLine();
				ImGui::Combo(("##0"), &cfgmem, Type, ARRAYSIZE(Type));

				if (cfgmem == 0) {
					s();
					ImGui::SliderFloat(u8"Red", &Options::Texture::WorldModel[0], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Green", &Options::Texture::WorldModel[1], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Blue", &Options::Texture::WorldModel[2], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Alpha", &Options::Texture::WorldModel[3], 0.f, 1.f);
				}
				if (cfgmem == 1) {
					s(); ImGui::SliderFloat(u8"Red", &Options::Texture::StaticProp[0], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Green", &Options::Texture::StaticProp[1], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Blue", &Options::Texture::StaticProp[2], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Alpha", &Options::Texture::StaticProp[3], 0.f, 1.f);
				}
				if (cfgmem == 2) {
					s(); ImGui::SliderFloat(u8"Red", &Options::Texture::Model[0], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Green", &Options::Texture::Model[1], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Blue", &Options::Texture::Model[2], 0.f, 1.f);
					s(); ImGui::SliderFloat(u8"Alpha", &Options::Texture::Model[3], 0.f, 1.f);
				}

				s(); ImGui::Text("Ready Settings");
				s(); if (gButton((u8"Night"))) readysetting = 1;
				s(); if (gButton((u8"Default"))) readysetting = 2;


				switch (readysetting) {
				default:break;
				case 1:
					Options::Texture::WorldModel[0] = 0.2f;
					Options::Texture::WorldModel[1] = 0.2f;
					Options::Texture::WorldModel[2] = 0.2f;
					Options::Texture::WorldModel[3] = 1.f;
					Options::Texture::StaticProp[0] = 0.3f;
					Options::Texture::StaticProp[1] = 0.3f;
					Options::Texture::StaticProp[2] = 0.3f;
					Options::Texture::StaticProp[3] = 1.f;
					Options::Texture::Model[0] = 0.60f;
					Options::Texture::Model[1] = 0.60f;
					Options::Texture::Model[2] = 0.60f;
					Options::Texture::Model[3] = 1.f;
					Options::Texture::SkyBox = 13;


					break;

				case 2:
					Options::Texture::WorldModel[0] = 1.f;
					Options::Texture::WorldModel[1] = 1.f;
					Options::Texture::WorldModel[2] = 1.f;
					Options::Texture::WorldModel[3] = 1.f;
					Options::Texture::StaticProp[0] = 1.f;
					Options::Texture::StaticProp[1] = 1.f;
					Options::Texture::StaticProp[2] = 1.f;
					Options::Texture::StaticProp[3] = 1.f;
					Options::Texture::Model[0] = 1.f;
					Options::Texture::Model[1] = 1.f;
					Options::Texture::Model[2] = 1.f;
					Options::Texture::Model[3] = 1.f;
					Options::Texture::SkyBox = 0;


					break;
				}

			}
			break;
			case 1:
			{
				if (Options::Visuals::Misc::StreamMode) {
					

					s(); ImGui::Text(language ? u8"You've activated streamer mode. Some features do not work." : u8"Ты находишся в стример моде. Некоторые функции могут не работать");
					s(); ImGui::Text(language ? u8"For security reasons, restart the game, " : u8"Перезапустите игру,");
					s(); ImGui::Text(language ? u8"and all functions will work as before." : u8"И все функции опять будут работать");
				}
				else {
					//ImGui::Checkbox(language ? u8"Streamer mode" : u8"Режим стримера", &Options::Visuals::Misc::BombTimer);
					//ImGui::Combo(u8"Mode type", &Options::Misc::AimModeType, u8"Le\0Палевный (рейдж)\0\0");
					s(); ImGui::Checkbox(language ? u8"Settings mode" : u8"Режим настройки", &Options::Misc::settingsmode);
					s(); ImGui::Checkbox(language ? u8"Spectator List" : u8"Список следящих за вами", &Options::Misc::SpectatorList);
					//ImGui::Combo(u8"Mode type", &Options::Misc::AimModeType, u8"Le\0Палевный (рейдж)\0\0");
					//s(); ImGui::Checkbox(language ? u8"Streamer mode" : u8"Режим стримера", &Options::Visuals::Misc::StreamMode);
					//ImGui::Checkbox(u8"Помощь в раскидках", &Options::Visuals::Misc::GrenadeHelper);
					s(); ImGui::Checkbox(language ? u8"Bhop" : u8"Авто распрыжка", &Options::Misc::Bunnyhop);
					s(); ImGui::Checkbox(language ? u8"AutoStrafe" : u8"Авто стрейф", &Options::Misc::AutoStrafe);
					s(); ImGui::Checkbox(language ? u8"RevealRanks" : u8"Показ рангов", &Options::Misc::RevealRanks);
					s(); ImGui::Checkbox(language ? u8"To show the damage " : u8"Информация о нанесёном уроне", &Options::Misc::HitInfo);
					//ImGui::Checkbox(u8"Анти кик", &Options::Misc::AntiKick);
					if (!Options::Visuals::Misc::StreamMode) {
						s(); ImGui::Checkbox(language ? u8"Play sound on hit" : u8"Проигрывать звук при попадании", &Options::Misc::HitSound);
					}
						
					if (!Options::Visuals::Misc::StreamMode) {
						s(); ImGui::Checkbox(language ? u8"Draw crosshair in snipers rifle" : u8"Рисовать приценл на снайперках", &Options::Misc::SniperCrosshair);
					}
					if (Options::Visuals::Misc::StreamMode) {
						s(); ImGui::Checkbox(u8"Рисовать прицел на снайперских винтовках", &Options::Misc::SniperCrosshair);
					}
						

					s(); ImGui::Checkbox(language ? u8"Flash grenade bypass" : u8"Снизить яркость ослепления", &Options::Misc::NoFlash);
					if (Options::Misc::NoFlash) {
						s(); ImGui::Text(language ? u8"Alpha" : u8"Прозрачность");
						if (!Options::Visuals::Misc::StreamMode) {
							s();
							ImGui::SliderFloat(u8"    ", &Options::Misc::NoFlashAlpha, 0, 255, "%.1f");
						}
						if (Options::Visuals::Misc::StreamMode) {
							s();
							ImGui::SliderFloat(u8"    ", &Options::Misc::NoFlashAlpha, 200, 255, "%.1f");
						}
					}

					s(); ImGui::Checkbox(language ? u8"Auto accept game" : u8"Автопринятие игры", &Options::Misc::AutoAccept);

					//	GUI::Checkbox(u8"Map prediction", &Options::Misc::MapPrediction);
					//		GUI::Checkbox(u8"Clear map from decals and blood", &Options::Misc::ClearD);
					///if (!Options::Visuals::Misc::StreamMode)GUI::Checkbox(u8"Freeze on fly(ALT)", &Options::Misc::AirStuck);
					//	if (Options::Visuals::Misc::StreamMode) {
					//		GUI::CheckboxFalse(u8"Freeze on fly(ALT)", &Options::Misc::AirStuckFalse);
					//		Options::Misc::AirStuck = false;
					//	}

					s(); ImGui::Checkbox(language ? u8"Knife bot" : u8"Аим на нож", &Options::Misc::KnifeBot);
					if (Options::Misc::KnifeBot) {
						if (Options::Misc::KnifeBot)Options::Misc::KnifeBotAuto = true;
						s(); ImGui::Checkbox(language ? u8"Cut automatic" : u8"Автоматически резать", &Options::Misc::KnifeBotAuto);
						if (!Options::Misc::KnifeBotAuto)Options::Misc::KnifeBot = false;
						//s(); ImGui::Checkbox(language ? u8"Cut on 360 " : u8"Резать на 360", &Options::Misc::KnifeBot360);
					}

					//s(); ImGui::Checkbox(language ? u8"To change the clan tag" : u8"Поменять клантег", &Options::Misc::ClanTagAnim);
					//s(); ImGui::InputText(language ? u8" " : u8"", Options::Misc::ClanTagAnimText, 100);
					//s(); ImGui::Combo(language ? u8"Style" : u8"Стиль", &Options::Misc::ClanTagAnimStyle, u8"Static\0Loading\0\0");
					//s(); ImGui::Checkbox(language ? u8"Name spam on chat" : u8"Спам имени в чат", &Options::Misc::NameSpam);
					//s(); ImGui::InputText(language ? u8"   " : u8"", Options::Misc::NameSpamText, 100);
					//s(); ImGui::Checkbox(language ? u8"Text spam on chat" : u8"Спам текста в чат", &Options::Misc::ChatSpam);
					//s(); ImGui::Checkbox(language ? u8"Your spam text" : u8"Ваш текст", &Options::Misc::ChatSpamCustom);
					//s(); ImGui::InputText(language ? u8"  " : u8"", Options::Misc::ChatSpamText, 100);
					//s(); ImGui::Checkbox(language ? u8"Radio spam" : u8"Спам в радио", &Options::Misc::RadioSpam);
					//s(); ImGui::Checkbox(language ? u8"Killed spam" : u8"Спам на убийстве", &Options::Misc::TrashTalk);
					//s(); ImGui::InputInt(language ? u8"Local MVPS" : u8"Изменить МВП", &Options::Misc::LocalMvps);
					//s(); ImGui::Checkbox(language ? u8"Fake FPS" : u8"Фейк ФПС", &Options::Misc::FakeFPSEnable);
					//s(); ImGui::SliderFloat(language ? u8"Fake fps ammount" : u8"Количество фейк фпса", &Options::Misc::fakeFPS, 0.0001f, 0.1f, "%.10f");
					
					s(); ImGui::Checkbox(language ? u8"Legit Desync" : u8"Легит десинки", & Options::Misc::Desync);
					//s(); ImGui::Checkbox(language ? u8"Flip des" : u8"Поменять стороны десинка", & Options::Legitbot::des_yaw_flip);
					//s(); ImGui::KeyBox(language ? u8"Flip key" : u8"Кнопка смены", & Options::Legitbot::flip_key, u8"Nоnе");
					//s(); ImGui::Checkbox(language ? u8"Show Desync" : u8"Показать десинки", & Options::Misc::desync_visual);
					//Options::Visuals::Misc::FakeduckKey
					//s(); ImGui::KeyBox(language ? u8"Legit Fakeduck Key" : u8"Легит фейкдак кнопка", &Options::Visuals::Misc::FakeduckKey, u8"None");
					//s(); ImGui::Checkbox(language ? u8"Delay shot on fakeduck" : u8"Делей выстрела для фейкдака", &Options::Misc::FakeduckDelayshot);
					s(); ImGui::KeyBox(language ? u8"Legit Slowmo Key" : u8"Легит замедление кнопка", &Options::Visuals::Misc::SlowmoKey, u8"Nоne");
					s(); ImGui::KeyBox(language ? u8"Fakelag Key" : u8"Фейк лаги кнопка", &Options::Visuals::Misc::fakelagKey, u8"Nonе");
					s(); ImGui::SliderInt(language ? u8"Fakelag limit " : u8"Фейк лаги ограничение", &Options::Visuals::Misc::fakelag_limit, 1, 14);
					ImGui::Spacing();
					s(); ImGui::Checkbox(language ? u8"Third Person" : u8"Третье лицо", &Options::Visuals::Misc::ThirdPerson);
					s(); ImGui::SliderFloat((u8"Third Person Дистанция"), &Options::Visuals::Chams::DisplayDistance, 0, 255, "%.1f", 1.0F);

					if (Options::Visuals::Misc::ThirdPerson) {
						s();  ImGui::KeyBox(language ? u8"Third Person Key" : u8"Третье лицо кнопка", &Options::Visuals::Misc::tpKey, u8"Nоnе");
					}
					s(); ImGui::Checkbox(language ? u8"Legit aa resolver" : u8"Фикс легит аа", &Options::Ragebot::Resolver);
					s(); ImGui::KeyBox(language ? u8"Override Key" : u8"Инверс Ресольвер кнопка", &Options::Visuals::Misc::overrideKey, u8"пone");
				}

			}
			break;
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}


/*
void Othermenuold()
{
	DWORD dwFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("##MainChildWindows", ImVec2(547, 543), false, dwFlag);
	{
		ImGuiStyle& style = ImGui::GetStyle();
		auto draw3 = ImGui::GetWindowDrawList();
		ImVec2 child_pos = ImGui::GetWindowPos();

		draw3->AddRect(ImVec2(child_pos.x + 19, child_pos.y + 15), ImVec2(child_pos.x + 531, child_pos.y + 527), ImColor(28, 36, 51));
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_ChildWindowBg] = ImColor(9, 20, 37);
		for (int i = 0; i < 2; i++)ImGui::Spacing();
		ImGui::Text(""); ImGui::SameLine(20.f);
		ImGui::BeginChild("##Child", ImVec2(510, 510), false, dwFlag);
		{
			ImGui::Text(""); ImGui::SameLine(10);
			static int iConfig = 0;
			s();
			ImGui::Text(language ? u8"Config actions" : u8"Действия с конфигом");
			s();
			ImGui::Combo(language ? u8"Config" : u8"Конфигом", &iConfig, g_pConfig->szConfigs.c_str());

			s();
			// ct
			//if (ImGui::ImageButton(button, ImVec2(100, 20)))
			//{
			//	g_pConfig->ParseConfigs();
			//}

			if (gButton(language ? u8"Update" : u8"Обновить"))
				g_pConfig->ParseConfigs();

			ImGui::SameLine();
			if (ImGui::Button(language ? u8"Load" : u8"Загрузить")) {
				g_pConfig->InitPath(&g_pConfig->vecConfigs[iConfig][0u]);
				g_pConfig->Read();
				U::FullUpdate(); // ща буду делать сохранения конфигов с новым именем
			}

			ImGui::SameLine();
			//if (ImGui::ImageButton(language ? u8"Save" : u8"Сохранить", button, ImVec2(100, 25))) {
			if (ImGui::Button(language ? u8"Save" : u8"Сохранить")) {
				g_pConfig->InitPath(&g_pConfig->vecConfigs[iConfig][0u]);
				g_pConfig->Save();
			}
			//ImGui::SameLine();
			//if (ImGui::Button(language ? u8"Open" : u8"Открыть папку с кофигами")) {
			if (ImGui::Button(language ? u8"Open" : u8"Открыть папку")) {
				char szCommand[512];
				sprintf(szCommand, "explorer %s", g_pConfig->szConfigFolder);
				system(szCommand);
			}
			if (gButton("kekekekkekekek")) {
				ImGui::Text("ehehehehehehheheeh");
			}
			static char cfgname[30] = "default";
			s();
			ImGui::InputText(language ? u8"Config name" : u8"Имя конфига", cfgname, 30);
			s();
			if (ImGui::Button(language ? u8"Add config" : u8"Добавить конфиг")) {
				std::string cfstring = cfgname;
				std::string cfgpath = "C:\\NEON\\" + cfstring + ".txt";
				std::ofstream outfile(cfgpath);
				outfile << " " << std::endl;
				outfile.close();
			}

			ImGui::Spacing();
			s();
			static int cfgmem = 0;
			int readysetting = 0;

			const char* skyboxes[] =
			{
				"Default",
				"cs_baggage_skybox",
				"cs_tibet",
				"embassy",
				"italy",
				"jungle",
				"nukeblank",
				"office",
				"sky_cs15_daylight_hdr",
				"sky_cs15_daylight2_hdr",
				"sky_cs15_daylight3_hdr",
				"sky_cs15_daylight4_hdr",
				"sky_csgo_cloudy",
				"sky_csgo_night",
				"sky_csgo_night2",
				"sky_dust",
				"sky_venice",
				"vertigo",
				"vertigoblue_hdr",
				"vietnam",
			};
			const char* Type[] =
			{
				"World",
				"StaticProp",
				"Model",

			};

			//ImGui::Checkbox(language ? u8"Open model changer" : u8"Развернуть модель ченжер", &texturing);
			s();
			ImGui::Checkbox((u8"Enable World Changer"), &Options::Texture::Enabled);
			s();
			ImGui::Combo("Sky", &Options::Texture::SkyBox, skyboxes, ARRAYSIZE(skyboxes));
			s();
			ImGui::Text("Settings for"); ImGui::SameLine();
			ImGui::Combo(("##0"), &cfgmem, Type, ARRAYSIZE(Type));

			if (cfgmem == 0) {
				s();
				ImGui::SliderFloat(u8"Red", &Options::Texture::WorldModel[0], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Green", &Options::Texture::WorldModel[1], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Blue", &Options::Texture::WorldModel[2], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Alpha", &Options::Texture::WorldModel[3], 0.f, 1.f);
			}
			if (cfgmem == 1) {
				s(); ImGui::SliderFloat(u8"Red", &Options::Texture::StaticProp[0], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Green", &Options::Texture::StaticProp[1], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Blue", &Options::Texture::StaticProp[2], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Alpha", &Options::Texture::StaticProp[3], 0.f, 1.f);
			}
			if (cfgmem == 2) {
				s(); ImGui::SliderFloat(u8"Red", &Options::Texture::Model[0], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Green", &Options::Texture::Model[1], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Blue", &Options::Texture::Model[2], 0.f, 1.f);
				s(); ImGui::SliderFloat(u8"Alpha", &Options::Texture::Model[3], 0.f, 1.f);
			}

			s(); ImGui::Text("Ready Settings");
			s(); if (gButton((u8"Night"))) readysetting = 1;
			s(); if (gButton((u8"Default"))) readysetting = 2;


			switch (readysetting) {
			default:break;
			case 1:
				Options::Texture::WorldModel[0] = 0.2f;
				Options::Texture::WorldModel[1] = 0.2f;
				Options::Texture::WorldModel[2] = 0.2f;
				Options::Texture::WorldModel[3] = 1.f;
				Options::Texture::StaticProp[0] = 0.3f;
				Options::Texture::StaticProp[1] = 0.3f;
				Options::Texture::StaticProp[2] = 0.3f;
				Options::Texture::StaticProp[3] = 1.f;
				Options::Texture::Model[0] = 0.60f;
				Options::Texture::Model[1] = 0.60f;
				Options::Texture::Model[2] = 0.60f;
				Options::Texture::Model[3] = 1.f;
				Options::Texture::SkyBox = 13;


				break;

			case 2:
				Options::Texture::WorldModel[0] = 1.f;
				Options::Texture::WorldModel[1] = 1.f;
				Options::Texture::WorldModel[2] = 1.f;
				Options::Texture::WorldModel[3] = 1.f;
				Options::Texture::StaticProp[0] = 1.f;
				Options::Texture::StaticProp[1] = 1.f;
				Options::Texture::StaticProp[2] = 1.f;
				Options::Texture::StaticProp[3] = 1.f;
				Options::Texture::Model[0] = 1.f;
				Options::Texture::Model[1] = 1.f;
				Options::Texture::Model[2] = 1.f;
				Options::Texture::Model[3] = 1.f;
				Options::Texture::SkyBox = 0;


				break;
			}
			//ImGui::Checkbox(language ? u8"Open model changer" : u8"Развернуть модель ченжер", &texturing); // поставь в кс max fps 30 у меня в кс лагает вивер ща настрою вивер, заебали лаги

		}
		ImGui::EndChild();
	}
	ImGui::EndChild();
}

*/