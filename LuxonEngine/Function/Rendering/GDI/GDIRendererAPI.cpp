#include "GDIRendererAPI.h"

#include <stdexcept>

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
	
	void GDIRendererAPI::EndScene() {
		BitBlt(s_hWindowDC, 0, 0, s_Width, s_Height, s_hMemoryDC, 0, 0, SRCCOPY); // 复制画面到屏幕
	}

	void GDIRendererAPI::DrawImage(int x, int y, const Resource::Texture& texture) {
		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = texture.GetWidth();
		// 使用负数高度来告诉 StretchDIBits像素数据是自上而下存储的
		bmi.bmiHeader.biHeight = -static_cast<LONG>(texture.GetHeight());
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32; // 内部统一使用32位ARGB格式
		bmi.bmiHeader.biCompression = BI_RGB;

		StretchDIBits(
			s_hMemoryDC,          // 目标DC：我们的后台内存画板
			x, y,                 // 目标矩形的左上角坐标
			texture.GetWidth(),   // 目标矩形的宽度
			texture.GetHeight(),  // 目标矩形的高度
			0, 0,                 // 源矩形的左上角坐标(从图片的0,0开始)
			texture.GetWidth(),   // 源矩形的宽度
			texture.GetHeight(),  // 源矩形的高度
			texture.GetData(),    // 指向像素数据内存块的指针
			&bmi,                 // 指向描述像素数据格式的 BITMAPINFO 结构
			DIB_RGB_COLORS,       // 表示颜色数据是RGB值
			SRCCOPY               // 直接复制像素
		);
	}

} // namespace GDI
} // namespace Rendering
} // namespace Function
} // namespace Luxon