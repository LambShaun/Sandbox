/**
 * @file	RendererAPI.h
 * @brief	��ƽ̨�޹ص���Ⱦ���ӿ�
 * @author	LambShaun
 **/

#pragma once

#include "Resource/Texture.h"
#include "core/Math/Vec2D.h"
#include <cstdint>
#include <memory>

namespace Luxon {
namespace Function {
namespace Rendering {
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
		virtual void DrawImage(int x, int y, const Resource::Texture& texture) = 0;
		// ��ͼ(����ͼ)
		virtual void DrawSubTexture(int x, int y, const Resource::Texture& texture,
			const Core::Math::Vector2i& subPos,			// �������ھ���ͼ������
			const Core::Math::Vector2i& subSize,		// �������С
			bool flipHorizontal = false) = 0;	
	};

} // namespace Rendering
} // namespace Function
} // namespace Luxon