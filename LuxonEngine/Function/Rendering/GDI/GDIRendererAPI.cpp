#include "GDIRendererAPI.h"

#include <string>
#include <stdexcept>

#pragma comment(lib, "Msimg32.lib")
namespace Luxon {
namespace Function {
namespace Rendering {
namespace GDI {
	HWND GDIRendererAPI::s_hWnd = NULL;
	HDC GDIRendererAPI::s_hWindowDC = NULL;
	HDC GDIRendererAPI::s_hMemoryDC = NULL;
	HBITMAP GDIRendererAPI::s_hBitmap = NULL;
	HBITMAP GDIRendererAPI::s_hOldBitmap = NULL;
	int GDIRendererAPI::s_Width = NULL;
	int GDIRendererAPI::s_Height = NULL;
	COLORREF GDIRendererAPI::m_ClearColor = RGB(0,0,0);

	void GDIRendererAPI::Init(void* nativWindowHandle) {
		s_hWnd = static_cast<HWND>(nativWindowHandle);
		if (s_hWnd == NULL) {
			throw std::runtime_error("GDI Renderer Error: Window handle has not been set befor Init()!");
		}

		s_hWindowDC = GetDC(s_hWnd);
		if (s_hWindowDC == NULL) {
			throw std::runtime_error("GDI Renderer Error: GetDC failed!");
		}

		RECT clientRect;
		GetClientRect(s_hWnd, &clientRect);
		s_Width = clientRect.right - clientRect.left;
		s_Height = clientRect.bottom - clientRect.top;

		s_hMemoryDC = CreateCompatibleDC(s_hMemoryDC);
		if (s_hMemoryDC == NULL) {
			throw std::runtime_error("GDI Renderer Error: CreateCompatibleDC failed!");
		}

		s_hBitmap = CreateCompatibleBitmap(s_hWindowDC,s_Width,s_Height);
		if (s_hBitmap == NULL) {
			throw std::runtime_error("GDI Renderer Error: CreateCompatibleBitmap failed!");
		}
		
		s_hOldBitmap = (HBITMAP)SelectObject(s_hMemoryDC, s_hBitmap);
		if (s_hOldBitmap == NULL) {
			throw std::runtime_error("GDI Renderer Error: SelectObjcet failed!");
		}
	}

	void GDIRendererAPI::SetClearColor(const Color& color) {
		m_ClearColor = RGB(color.r, color.b, color.g);
	}

	void GDIRendererAPI::Clear() {
		RECT rect = { 0,0,s_Width,s_Height };
		HBRUSH brush = CreateSolidBrush(m_ClearColor);
		FillRect(s_hMemoryDC, &rect, brush);
		DeleteObject(brush);
	}

	void GDIRendererAPI::DrawRect(int x, int y, int width, int height, const Color& color) {
		RECT rect = { x, y ,x + width, y + height };
		COLORREF rectColor = RGB(color.r, color.g, color.b);
		HBRUSH brush = CreateSolidBrush(rectColor);
		FillRect(s_hMemoryDC, &rect, brush);
		DeleteObject(brush);
	}

	void GDIRendererAPI::BeginScene() {

	}
	
	void GDIRendererAPI::DrawImage(int x, int y, const Resource::Texture& texture) {
		DrawSubTexture(x, y, texture, { 0,0 }, { (int)texture.GetWidth(), (int)texture.GetHeight() }, false);
	}

	void GDIRendererAPI::DrawSubTexture(int x, int y, const Resource::Texture& texture, const Core::Math::Vector2i& subPos, const Core::Math::Vector2i& subSize, bool flipHorizontal) {
		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = texture.GetWidth();
		bmi.bmiHeader.biHeight = -static_cast<LONG>(texture.GetHeight()); // 负号表示自上而下
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32; // 数据是32位ARGB
		bmi.bmiHeader.biCompression = BI_RGB;

		HDC srcDC = CreateCompatibleDC(s_hMemoryDC);
		HBITMAP srcBitmap = CreateDIBitmap(s_hMemoryDC, &bmi.bmiHeader, CBM_INIT, texture.GetData(), &bmi, DIB_RGB_COLORS);
		if (srcBitmap == NULL) { DeleteDC(srcDC); return; }
		HBITMAP oldSrcBitmap = (HBITMAP)SelectObject(srcDC, srcBitmap);

		BLENDFUNCTION blendFunc = {};
		blendFunc.BlendOp = AC_SRC_OVER; // 标准的Alpha混合公式
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 255; // 使用图片每个像素自己的Alpha值
		blendFunc.AlphaFormat = AC_SRC_ALPHA; // 关键：指明源图片带有Alpha通道

		if (!flipHorizontal) {
			// 调用 AlphaBlend 函数
			AlphaBlend(
				s_hMemoryDC,        // 目标DC：后台内存画板
				x, y,               // 目标位置
				subSize.x,          // 目标宽高就是子区域的大小
				subSize.y,
				srcDC,        
				subPos.x, subPos.y, // 源位置 从图片的哪个坐标开始切
				subSize.x,          // 源大小
				subSize.y,
				blendFunc           // 传入配置好的混合函数
			);
		}
		else {
			HDC flipDC = CreateCompatibleDC(s_hMemoryDC);
			HBITMAP flipBitmap = CreateCompatibleBitmap(s_hMemoryDC, subSize.x, subSize.y);
			HBITMAP oldFlipBitmap = (HBITMAP)SelectObject(flipDC, flipBitmap);
			StretchBlt(
				flipDC,         
				subSize.x, 0,    // 从右上角开始画
				-subSize.x,      // 使用负数宽度来实现翻转
				subSize.y,
				srcDC,           // 源是包含原始精灵图的DC
				subPos.x, subPos.y,
				subSize.x, subSize.y,
				SRCCOPY
			);

			AlphaBlend(
				s_hMemoryDC, x, y, subSize.x, subSize.y,
				flipDC, 0, 0, subSize.x, subSize.y, 
				blendFunc
			);
			// 清理翻转
			SelectObject(flipDC, oldFlipBitmap);
			DeleteObject(flipBitmap);
			DeleteDC(flipDC);
		}
		// 清理临时的源DC资源
		SelectObject(srcDC, oldSrcBitmap);
		DeleteObject(srcBitmap);
		DeleteDC(srcDC);
	}

	void GDIRendererAPI::EndScene() {
		BitBlt(s_hWindowDC, 0, 0, s_Width, s_Height, s_hMemoryDC, 0, 0, SRCCOPY); // 复制画面到屏幕
	}


} // namespace GDI
} // namespace Rendering
} // namespace Function
} // namespace Luxon