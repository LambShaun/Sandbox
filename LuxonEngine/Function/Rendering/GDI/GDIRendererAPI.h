/**
 * @file	GDIRendererAPI.h
 * @brief	GDI��Ⱦ���ӿ�
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
		static HWND s_hWnd;				// ��¼��ȾĿ�괰�ھ�� ȫ��Ψһ����
		static HDC s_hWindowDC;			// �豸������(DC)
		static HDC s_hMemoryDC;			// �ڴ���(DC) Ϊ��˫����
		static HBITMAP s_hBitmap;		// λͼ �ڴ滭ͼ��Ҫһ��λͼ
		static HBITMAP s_hOldBitmap;	// �ɵ�λͼ ����ɵ�λͼ�Ա㻹ԭ
		static int s_Width, s_Height;	
		static COLORREF m_ClearColor;   // ������ɫ
	};

} // namespace GDI
} // namespace Rendering
} // namespace Function
} // namespace Luxon
