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
		DrawSubTexture(x, y, texture, { 0,0 }, { (int)texture.GetWidth(), (int)texture.GetHeight() });
	}

	void GDIRendererAPI::DrawSubTexture(int x, int y, const Resource::Texture& texture, const Core::Math::Vector2i& subPos, const Core::Math::Vector2i& subSize) {
		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = texture.GetWidth();
		bmi.bmiHeader.biHeight = -static_cast<LONG>(texture.GetHeight()); // 负号表示自上而下
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32; // 数据是32位ARGB
		bmi.bmiHeader.biCompression = BI_RGB;

		BLENDFUNCTION blendFunc = {};
		blendFunc.BlendOp = AC_SRC_OVER; // 标准的Alpha混合公式
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 255; // 使用图片每个像素自己的Alpha值
		blendFunc.AlphaFormat = AC_SRC_ALPHA; // 关键：指明源图片带有Alpha通道

		// 调用 AlphaBlend 函数
		AlphaBlend(
			s_hMemoryDC,        // 目标DC：后台内存画板
			x, y,               // 目标位置
			subSize.x,          // 目标宽高就是子区域的大小
			subSize.y,

			s_hMemoryDC,        // 注意：GDI的一个怪癖，源DC和目标DC可以是同一个
			// 它需要一个DC来处理位图 用后台DC即可
			subPos.x, subPos.y, // 源位置 从图片的哪个坐标开始切
			subSize.x,          // 源大小
			subSize.y,
			blendFunc           // 传入配置好的混合函数
		);

		// AlphaBlend 在处理时，似乎需要一个位图被选入源DC中。
		// s_hMemoryDC 已经选入了 s_hBitmap，但里面的内容是上一帧的。
		// 一个更完整的实现，是为每个Texture创建一个HBITMAP，但这会很复杂。
		// 另一个方法是临时创建一个DC和位图，将texture数据放进去。
		// 但最简单且通常能工作的技巧，是欺骗一下AlphaBlend，
		// 它的内部实现会通过GetData指针重新读取数据。
		// 需要把texture的数据临时"blt"到后台画布的某个地方再AlphaBlend回来
		// 或者更简单：直接用StretchDIBits，因为它本身也能处理透明度，但AlphaBlend更专业。
		// 为了保持简单和功能正确，还是需要一个临时的DC来持有的源数据。

		HDC srcDC = CreateCompatibleDC(s_hMemoryDC);
		HBITMAP srcBitmap = CreateDIBitmap(s_hMemoryDC, &bmi.bmiHeader, CBM_INIT, texture.GetData(), &bmi, DIB_RGB_COLORS);
		if (srcBitmap == NULL) { DeleteDC(srcDC); return; }

		HBITMAP oldBitmap = (HBITMAP)SelectObject(srcDC, srcBitmap);

		AlphaBlend(
			s_hMemoryDC, x, y, subSize.x, subSize.y,
			srcDC, subPos.x, subPos.y, subSize.x, subSize.y,
			blendFunc
		);

		SelectObject(srcDC, oldBitmap);
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