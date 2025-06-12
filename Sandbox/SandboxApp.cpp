#include "Platform/Window.h"
#include "Function/Rendering/Renderer.h"
#include "Function/Input/Input.h"
#include "Core/Math/Vec2D.h"

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
				Luxon::Core::Vector2f direction = { 0.0f,0.0f }; // 方向向量

				if (Luxon::Input::isKeyPressed('W')) {
					direction.y = -1.0f;
				}

				if (Luxon::Input::isKeyPressed('S')) {
					direction.y = 1.0f;
				}

				if (Luxon::Input::isKeyPressed('A')) {
					direction.x = -1.0f;
				}

				if (Luxon::Input::isKeyPressed('D')) {
					direction.x = 1.0f;
				}

				// 将方向向量乘以速度，得到最终的速度向量，并更新位置
				float speed = 1.0f;
				m_RectPosition += direction * speed;

				// Renderer
				Luxon::Renderer::BeginScene();
				Luxon::Renderer::SetClearColor({ 50, 30, 30, 255 });
				Luxon::Renderer::Clear();
				Luxon::Renderer::DrawRect((int)m_RectPosition.x,
										  (int)m_RectPosition.y, 
										100, 100, { 0,0,255,255 });
				Luxon::Renderer::EndScene();
			}
		}
	}

private:
	std::unique_ptr<Luxon::Window> m_Window;
	Luxon::Core::Vector2f m_RectPosition = { 100.0f,100.0f }; // 位置向量
};
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	SandboxApp* app = new SandboxApp();
	app->Run();
	return 0;
}