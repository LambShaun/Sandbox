/**
 * @file	RendererAPI.h
 * @brief	与平台无关的渲染器接口
 * @author	LambShaun
 **/

#pragma once

#include <cstdint>

namespace Luxon {
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
	};
} // namespace Luxon