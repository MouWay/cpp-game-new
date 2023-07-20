#include "ImguiManager.h"
#include "imgui.h"
#include <filesystem>

ImguiManager::ImguiManager()
{
	namespace fs = std::filesystem;
	if (!fs::exists("imgui.ini") && fs::exists("imgui_default.ini"))
	{
		fs::copy_file("imgui_default.ini", "imgui.ini");
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::StyleColorsDark();
}

ImguiManager::~ImguiManager()
{
	ImGui::DestroyContext();
}