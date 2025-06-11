#include "Platform/Window.h"
#include "Function/Rendering/Renderer.h"
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
				Luxon::Renderer::BeginScene();
				Luxon::Renderer::SetClearColor({ 255, 30, 30, 255 });
				Luxon::Renderer::Clear();
				Luxon::Renderer::DrawRect(100, 200, 100, 100, { 0,0,255,255 });
				Luxon::Renderer::EndScene();
			}
		}
	}

private:
	std::unique_ptr<Luxon::Window> m_Window;
};
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	SandboxApp* app = new SandboxApp();
	app->Run();
	return 0;
}