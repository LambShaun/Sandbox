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
		bmi.bmiHeader.biHeight = -static_cast<LONG>(texture.GetHeight()); // ���ű�ʾ���϶���
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32; // ������32λARGB
		bmi.bmiHeader.biCompression = BI_RGB;

		BLENDFUNCTION blendFunc = {};
		blendFunc.BlendOp = AC_SRC_OVER; // ��׼��Alpha��Ϲ�ʽ
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 255; // ʹ��ͼƬÿ�������Լ���Alphaֵ
		blendFunc.AlphaFormat = AC_SRC_ALPHA; // �ؼ���ָ��ԴͼƬ����Alphaͨ��

		// ���� AlphaBlend ����
		AlphaBlend(
			s_hMemoryDC,        // Ŀ��DC����̨�ڴ滭��
			x, y,               // Ŀ��λ��
			subSize.x,          // Ŀ���߾���������Ĵ�С
			subSize.y,

			s_hMemoryDC,        // ע�⣺GDI��һ����񱣬ԴDC��Ŀ��DC������ͬһ��
			// ����Ҫһ��DC������λͼ �ú�̨DC����
			subPos.x, subPos.y, // Դλ�� ��ͼƬ���ĸ����꿪ʼ��
			subSize.x,          // Դ��С
			subSize.y,
			blendFunc           // �������úõĻ�Ϻ���
		);

		// AlphaBlend �ڴ���ʱ���ƺ���Ҫһ��λͼ��ѡ��ԴDC�С�
		// s_hMemoryDC �Ѿ�ѡ���� s_hBitmap�����������������һ֡�ġ�
		// һ����������ʵ�֣���Ϊÿ��Texture����һ��HBITMAP�������ܸ��ӡ�
		// ��һ����������ʱ����һ��DC��λͼ����texture���ݷŽ�ȥ��
		// �������ͨ���ܹ����ļ��ɣ�����ƭһ��AlphaBlend��
		// �����ڲ�ʵ�ֻ�ͨ��GetDataָ�����¶�ȡ���ݡ�
		// ��Ҫ��texture��������ʱ"blt"����̨������ĳ���ط���AlphaBlend����
		// ���߸��򵥣�ֱ����StretchDIBits����Ϊ������Ҳ�ܴ���͸���ȣ���AlphaBlend��רҵ��
		// Ϊ�˱��ּ򵥺͹�����ȷ��������Ҫһ����ʱ��DC�����е�Դ���ݡ�

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
		BitBlt(s_hWindowDC, 0, 0, s_Width, s_Height, s_hMemoryDC, 0, 0, SRCCOPY); // ���ƻ��浽��Ļ
	}


} // namespace GDI
} // namespace Rendering
} // namespace Function
} // namespace Luxon