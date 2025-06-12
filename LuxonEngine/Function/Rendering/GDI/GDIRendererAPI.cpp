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
		BitBlt(s_hWindowDC, 0, 0, s_Width, s_Height, s_hMemoryDC, 0, 0, SRCCOPY); // ¸´ÖÆ»­Ãæµ½ÆÁÄ»
	}

} // namespace GDI
} // namespace Rendering
} // namespace Function
} // namespace Luxon