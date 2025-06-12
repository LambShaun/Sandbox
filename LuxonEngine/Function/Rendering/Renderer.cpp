#include "Renderer.h"
#include "GDI/GDIRendererAPI.h"

namespace Luxon {
namespace Function {
namespace Rendering {
	std::unique_ptr<Rendering::RendererAPI> Renderer::s_RendererAPI = nullptr;
	
	void Renderer::Init(void* nativeWindowHandle) {
		s_RendererAPI = std::make_unique<Rendering::GDI::GDIRendererAPI>();
		s_RendererAPI->Init(nativeWindowHandle);
	}

	void Renderer::Shutdown() {
		s_RendererAPI.reset();	
	}

	void Renderer::BeginScene() {
		s_RendererAPI->BeginScene();
	}

	void Renderer::EndScene() {
		s_RendererAPI->EndScene();
	}

	void Renderer::SetClearColor(const Color& color) {
		s_RendererAPI->SetClearColor(color);
	}

	void Renderer::Clear() {
		s_RendererAPI->Clear();
	}

	void Renderer::DrawRect(int x, int y, int width, int height, const Color& color) {
		s_RendererAPI->DrawRect(x, y, width ,height, color);
	}

} // namespace Rendering
} // namespace Function
} // namespace Luxon