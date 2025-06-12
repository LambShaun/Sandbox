#include "Platform/Window.h"
#include "Function/Rendering/Renderer.h"
#include "Function/Input/Input.h"

#include <memory>
#include <Windows.h>

class SandboxApp {
public: 
	SandboxApp() {
		m_Window = std::unique_ptr<Luxon::Window>(Luxon::Window::Create());
		Luxon::Renderer::Init(m_Window->GetNativeWindow());	
	}
	~SandboxApp() {
		Luxon::Renderer::Shutdown();
	}

	void Run() {
		bool running = true;
		MSG Msg;
		while (running) {
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
				if (Msg.message == WM_QUIT) {
					running = false;
				}
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
			} else {
				// MOVE
				float speed = 1.0f;
				if (Luxon::Input::isKeyPressed('W')) {
					m_RectY -= speed;
				}

				if (Luxon::Input::isKeyPressed('S')) {
					m_RectY += speed;
				}

				if (Luxon::Input::isKeyPressed('A')) {
					m_RectX -= speed;
				}

				if (Luxon::Input::isKeyPressed('D')) {
					m_RectX += speed;
				}

				// Renderer
				Luxon::Renderer::BeginScene();
				Luxon::Renderer::SetClearColor({ 255, 30, 30, 255 });
				Luxon::Renderer::Clear();
				Luxon::Renderer::DrawRect(m_RectX, m_RectY, 100, 100, { 0,0,255,255 });
				Luxon::Renderer::EndScene();
			}
		}
	}

private:
	std::unique_ptr<Luxon::Window> m_Window;

	float m_RectY = 100.f;
	float m_RectX = 100.f;
};
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	SandboxApp* app = new SandboxApp();
	app->Run();
	return 0;
}