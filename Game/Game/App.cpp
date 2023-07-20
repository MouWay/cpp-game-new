#include "App.h"
#include <memory>
#include <algorithm>
#include "MathExtension.h"
#include "imgui.h"
#include "DynamicConstant.h"
#include "Testing.h"
#include "PerfLog.h"
#include "TestModelProbe.h"
#include "Testing.h"
#include "Camera.h"
#include "Channels.h"

#pragma comment(lib, "assimp-vc143-mt.lib")

namespace dx = DirectX;

App::App(const std::string& commandLine)
	:
	commandLine(commandLine),
	wnd(1280, 720, "Game"),
	light(wnd.Gfx(), { 10.0f,5.0f,0.0f })
{
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "A", dx::XMFLOAT3{ -30.0f, 31.0f, 60.0f }, PI / 9.0f, PI * 5.0f / 6.0f));
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "B", dx::XMFLOAT3{ -13.5f, 28.8f, -6.4f }, PI / 180.0f * 13.0f, PI / 180.0f * 61.0f));
	cameras.AddCamera(light.ShareCamera());

	cube.SetPos({ 10.0f,5.0f,6.0f });
	cube2.SetPos({ 10.0f,5.0f,14.0f });

	cube.LinkTechniques(rg);
	cube2.LinkTechniques(rg);
	light.LinkTechniques(rg);
	room.LinkTechniques(rg);
	lady.LinkTechniques(rg);
	revolver.LinkTechniques(rg);
	revolver2.LinkTechniques(rg);
	cameras.LinkTechniques(rg);

	rg.BindShadowCamera(*light.ShareCamera());
}

void App::HandleInput(float dt)
{
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		case VK_RETURN:
			savingDepth = true;
			break;
		}
	}

	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			cameras->Translate({ 0.0f,0.0f,dt });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			cameras->Translate({ -dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			cameras->Translate({ 0.0f,0.0f,-dt });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			cameras->Translate({ dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('R'))
		{
			cameras->Translate({ 0.0f,dt,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('F'))
		{
			cameras->Translate({ 0.0f,-dt,0.0f });
		}
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			cameras->Rotate((float)delta->x, (float)delta->y);
		}
	}
}

void App::DoFrame(float dt)
{
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	light.Bind(wnd.Gfx(), cameras->GetMatrix());
	rg.BindMainCamera(cameras.GetActiveCamera());

	light.Submit(Chan::main);
	cube.Submit(Chan::main);
	room.Submit(Chan::main);
	lady.Submit(Chan::main);
	revolver.Submit(Chan::main);
	revolver2.Submit(Chan::main);
	cube2.Submit(Chan::main);
	cameras.Submit(Chan::main);

	cube.Submit(Chan::shadow);
	room.Submit(Chan::shadow);
	lady.Submit(Chan::shadow);
	revolver.Submit(Chan::shadow);
	revolver2.Submit(Chan::shadow);
	cube2.Submit(Chan::shadow);
	
	rg.Execute(wnd.Gfx());

	if (savingDepth)
	{
		rg.DumpShadowMap(wnd.Gfx(), "shadow.png");
		savingDepth = false;
	}

	// imgui windows
	static MP roomProbe{"Room"};
	static MP ladyProbe{"Lady"};
	static MP rv1Probe{"Revolver1"};
	static MP rv2Probe{"Revolver2"};
	cameras.SpawnWindow(wnd.Gfx());
	light.SpawnControlWindow();
	roomProbe.SpawnWindow(room);
	ladyProbe.SpawnWindow(lady);
	rv1Probe.SpawnWindow(revolver);
	rv2Probe.SpawnWindow(revolver2);
	ShowImguiDemoWindow();
	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");
	rg.RenderWindows(wnd.Gfx());

	// present
	wnd.Gfx().EndFrame();

	rg.Reset();
}

void App::ShowImguiDemoWindow()
{
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}

App::~App()
{}

int App::Go() {
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return *ecode;
		}
		// execute the game logic
		const auto dt = timer.Mark() * speed_factor;
		HandleInput(dt);
		DoFrame(dt);
	}
}