#include "Platform/Window.h"
#include "Function/Rendering/Renderer.h"
#include "Function/Input/Input.h"
#include "Core/Math/Vec2D.h"
#include "Core/Time/Time.h"

#include <memory>
#include <Windows.h>

class SandboxApp {
public: 
	SandboxApp() {
		m_Window = std::unique_ptr<Luxon::Platform::Window>(Luxon::Platform::Window::Create());
		Luxon::Function::Rendering::Renderer::Init(m_Window->GetNativeWindow());	
	}
	~SandboxApp() {
		Luxon::Function::Rendering::Renderer::Shutdown();
	}

	void OnUpdate()
	{
		// ������ʱ�ӻ�ȡ��ǰ֡��ʱ������
		Luxon::Core::Time::Timestep ts = Luxon::Core::Time::Time::GetDeltaTime();

		// �߼�����
		Luxon::Core::Math::Vector2f direction = { 0.0f, 0.0f };
		if (Luxon::Function::Input::Input::IsKeyPressed('W')) direction.y = -1.0f;
		if (Luxon::Function::Input::Input::IsKeyPressed('S')) direction.y = 1.0f;
		if (Luxon::Function::Input::Input::IsKeyPressed('A')) direction.x = -1.0f;
		if (Luxon::Function::Input::Input::IsKeyPressed('D')) direction.x = 1.0f;

		if (direction.LengthSquared() > 0.0f) direction.Normalize();

		float speed = 1000.0f;
		m_RectPosition += direction * speed * ts;

		// Renderer
		Luxon::Function::Rendering::Renderer::BeginScene();
		Luxon::Function::Rendering::Renderer::SetClearColor({ 30,30,30,255 });
		Luxon::Function::Rendering::Renderer::Clear();
		Luxon::Function::Rendering::Renderer::DrawRect((int)m_RectPosition.x, (int)m_RectPosition.y, 200, 150, { 255,0,0,255 });
		Luxon::Function::Rendering::Renderer::EndScene();
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
				Luxon::Core::Time::Time::Tick(); 
				OnUpdate();
			}
		}
	}

private:
	std::unique_ptr<Luxon::Platform::Window> m_Window;
	Luxon::Core::Math::Vector2f m_RectPosition = { 100.0f,100.0f }; // λ������
};
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	SandboxApp* app = new SandboxApp();
	app->Run();
	return 0;
}