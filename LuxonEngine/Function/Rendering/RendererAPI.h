/**
 * @file	RendererAPI.h
 * @brief	与平台无关的渲染器接口
 * @author	LambShaun
 **/

#pragma once

#include "Resource/Texture.h"
#include "core/Math/Vec2D.h"
#include <cstdint>
#include <memory>

namespace Luxon {
namespace Function {
namespace Rendering {
	struct Color {
		uint8_t r, g, b, a; // RGBA (0~255)
	};

	class RendererAPI {
	public:
		virtual ~RendererAPI() = default;
		virtual void Init(void* nativeWindowHandle) = 0;		// 初始化渲染器
		virtual void BeginScene() = 0;							// 渲染开始
		virtual void EndScene() = 0;
		virtual void SetClearColor(const Color& color) = 0;		// 设置清屏颜色
		virtual void Clear() = 0;								// 清屏
		// 绘图(矩形)
		virtual void DrawRect(int x, int y, int width, int height, const Color& color) = 0;
		virtual void DrawImage(int x, int y, const Resource::Texture& texture) = 0;
		// 绘图(精灵图)
		virtual void DrawSubTexture(int x, int y, const Resource::Texture& texture,
			const Core::Math::Vector2i& subPos,			// 子区域在精灵图的坐标
			const Core::Math::Vector2i& subSize) = 0;	// 子区域大小
	};

} // namespace Rendering
} // namespace Function
} // namespace Luxon