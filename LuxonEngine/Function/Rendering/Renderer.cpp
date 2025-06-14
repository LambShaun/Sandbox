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

	void Renderer::DrawImage(int x, int y, const Resource::Texture& texture) {
		s_RendererAPI->DrawImage(x, y, texture);
	}

	void Renderer::DrawSubTexture(int x, int y, const Resource::Texture& texture,
		const Core::Math::Vector2i& subPos,
		const Core::Math::Vector2i& subSize,
		bool flipHorizontal ) {
		s_RendererAPI->DrawSubTexture(x, y, texture, subPos, subSize, flipHorizontal);
	}
} // namespace Rendering
} // namespace Function
} // namespace Luxon