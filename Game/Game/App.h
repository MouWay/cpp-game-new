#pragma once
#include "Window.h"
#include "Timer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "TestPlane.h"
#include "TestCube.h"
#include "Mesh.h"
#include <set>
#include "Stencil.h"
#include "FrameCommander.h"

class App
{
public:
	App(const std::string& commandLine = "");
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
private:
	std::string commandLine;
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	//ScriptCommander scriptCommander;
	Timer timer;
	float speed_factor = 1.0f;
	Camera cam;
	FrameCommander fc;
	PointLight light;
	//Model room{ wnd.Gfx(),"Models\\Room\\room_mat.glb" };
	//TestPlane bluePlane{ wnd.Gfx(),6.0f,{ 0.3f,0.3f,1.0f,0.0f } };
	//TestPlane redPlane{ wnd.Gfx(),6.0f,{ 1.0f,0.3f,0.3f,0.0f } };
	TestCube cube{ wnd.Gfx(),4.0f };
	TestCube cube2{ wnd.Gfx(),4.0f };
};