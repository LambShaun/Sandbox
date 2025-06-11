/**
 * @file	RendererAPI.h
 * @brief	��ƽ̨�޹ص���Ⱦ���ӿ�
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
		virtual void Init(void* nativeWindowHandle) = 0;		// ��ʼ����Ⱦ��
		virtual void BeginScene() = 0;							// ��Ⱦ��ʼ
		virtual void EndScene() = 0;
		virtual void SetClearColor(const Color& color) = 0;		// ����������ɫ
		virtual void Clear() = 0;								// ����
		// ��ͼ(����)
		virtual void DrawRect(int x, int y, int width, int height, const Color& color) = 0;
	};
} // namespace Luxon