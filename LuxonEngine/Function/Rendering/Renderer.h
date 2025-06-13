/**
 * @file	Renderer.h
 * @brief	全局渲染器接口 将底层的RendererAPI隐藏 为未来更换Vulkan 做铺垫
 * @author	LambShaun
 **/

#pragma once

#include "RendererAPI.h"
#include "resource/Texture.h"

#include <memory>

namespace Luxon {
namespace Function {
namespace Rendering {
	class Renderer {
	public:
		static void Init(void* nativeWindowHandle);
		static void Shutdown();

		static void BeginScene();
		static void EndScene();
		static void SetClearColor(const Color& color);
		static void Clear();
		static void DrawRect(int x, int y, int width, int height, const Color& color);
		static void DrawImage(int x, int y, const Resource::Texture& texture);
		static void DrawSubTexture(int x, int y, const Resource::Texture& texture,
			const Core::Math::Vector2i& subPos,
			const Core::Math::Vector2i& subSize);
	private:
		static std::unique_ptr<RendererAPI>s_RendererAPI;
	};

} // namespace Rendering
} // namespace Function
} // namespace Luxon