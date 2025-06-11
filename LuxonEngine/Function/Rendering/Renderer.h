/**
 * @file	Renderer.h
 * @brief	ȫ����Ⱦ���ӿ� ���ײ��RendererAPI���� Ϊδ������Vulkan ���̵�
 * @author	LambShaun
 **/

#pragma once

#include "RendererAPI.h"

#include <memory>

namespace Luxon {
	class Renderer {
	public:
		static void Init(void* nativeWindowHandle);
		static void Shutdown();

		static void BeginScene();
		static void EndScene();
		static void SetClearColor(const Color& color);
		static void Clear();
		static void DrawRect(int x, int y, int width, int height, const Color& color);

	private:
		static std::unique_ptr<RendererAPI>s_RendererAPI;
	};
}