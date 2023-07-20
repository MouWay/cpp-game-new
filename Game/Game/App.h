#pragma once
#include "Window.h"
#include "Timer.h"
#include "ImguiManager.h"
#include "CameraContainer.h"
#include "PointLight.h"
#include "TestCube.h"
#include "Model.h"
#include "BlurOutlineRenderGraph.h"
#include "MathExtension.h"

class App
{
public:
	App(const std::string& commandLine = "");
	int Go();
	~App();
private:
	void DoFrame(float dt);
	void HandleInput(float dt);
	void ShowImguiDemoWindow();
private:
	std::string commandLine;
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	Rgph::BlurOutlineRenderGraph rg{ wnd.Gfx() };
	Timer timer;
	float speed_factor = 1.0f;
	//Camera cam{ { -30.0f,31.0f,60.0f },PI / 9.0f,PI * 5.0f / 6.0f };
	CameraContainer cameras;
	PointLight light;
	Model room{ wnd.Gfx(),"Models\\Room\\room_mat.glb" };
	Model lady{ wnd.Gfx(), "Models\\Entity\\Lady\\lady.obj" };
	Model revolver{ wnd.Gfx(),"Models\\Weapons\\Revolver\\revolver.glb" };
	Model revolver2{ wnd.Gfx(),"Models\\Weapons\\Revolver\\revolver.glb" };
	TestCube cube{ wnd.Gfx(),4.0f };
	TestCube cube2{ wnd.Gfx(),4.0f };
	bool savingDepth = false;
};