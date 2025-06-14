/**
 * @file	GDIRendererAPI.h
 * @brief	GDI渲染器接口
 * @author	LambShaun
 **/

#pragma once

#include "Function/Rendering/RendererAPI.h"
#include "Resource/Texture.h"

#include <Windows.h>

namespace Luxon {
namespace Function {
namespace Rendering {
namespace GDI {
	class GDIRendererAPI :public RendererAPI {
	public:
		virtual void Init(void* nativeWindowHandle) override;
		virtual void BeginScene() override;
		virtual void EndScene() override;
		virtual void SetClearColor(const Color& color) override;
		virtual void Clear() override;
		virtual void DrawRect(int x, int y, int width, int height, const Color& color) override;
		virtual void DrawImage(int x, int y, const Resource::Texture& texture) override;
		virtual void DrawSubTexture(int x, int y, const Resource::Texture& texture,
			const Core::Math::Vector2i& subPos,
			const Core::Math::Vector2i& subSize,
			bool flipHorizontal = false) override;
	private:
		static HWND s_hWnd;				// 记录渲染目标窗口句柄 全局唯一窗口
		static HDC s_hWindowDC;			// 设备上下文(DC)
		static HDC s_hMemoryDC;			// 内存里(DC) 为了双缓冲
		static HBITMAP s_hBitmap;		// 位图 内存画图需要一个位图
		static HBITMAP s_hOldBitmap;	// 旧的位图 保存旧的位图以便还原
		static int s_Width, s_Height;	
		static COLORREF m_ClearColor;   // 清屏颜色
	};

} // namespace GDI
} // namespace Rendering
} // namespace Function
} // namespace Luxon
