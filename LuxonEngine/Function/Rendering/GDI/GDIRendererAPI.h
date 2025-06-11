/**
 * @file	GDIRendererAPI.h
 * @brief	GDI��Ⱦ���ӿ�
 * @author	LambShaun
 **/

#pragma once

#include "Function/Rendering/RendererAPI.h"

#include <Windows.h>

namespace Luxon {
	class GDIRendererAPI :public RendererAPI {
	public:
		virtual void Init(void* nativeWindowHandle) override;
		virtual void BeginScene() override;
		virtual void EndScene() override;
		virtual void SetClearColor(const Color& color) override;
		virtual void Clear() override;
		virtual void DrawRect(int x, int y, int width, int height, const Color& color) override;


	private:
		static HWND s_hWnd;				// ��¼��ȾĿ�괰�ھ�� ȫ��Ψһ����
		static HDC s_hWindowDC;			// �豸������(DC)
		static HDC s_hMemoryDC;			// �ڴ���(DC) Ϊ��˫����
		static HBITMAP s_hBitmap;		// λͼ �ڴ滭ͼ��Ҫһ��λͼ
		static HBITMAP s_hOldBitmap;	// �ɵ�λͼ ����ɵ�λͼ�Ա㻹ԭ
		static int s_Width, s_Height;	
		static COLORREF m_ClearColor;   // ������ɫ
	};

} // namespace Luxon
