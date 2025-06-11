#include "Platform/Window.h"
#include <memory>

#include <Windows.h>

class SandboxApp {
public: 
	SandboxApp() {
		m_Window = std::unique_ptr<Luxon::Window>(Luxon::Window::Create());
	}

	void Run() {
		bool running = true;
		MSG Msg;
		while (running) {
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
				if (Msg.message == WM_QUIT) {
					running = false;
				}
				else {
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}

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