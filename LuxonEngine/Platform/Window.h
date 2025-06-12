/**
 * @file	Window.h
 * @brief	��ƽ̨���ڽӿ�
 * @author	LambShaun
 **/

#pragma once

#include<string>

namespace Luxon { 
namespace Platform{
	// ������������
	struct WindowProps { 
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Luxon Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
		: Title(title),Width(width),Height(height){}
	};
	// ���ڽӿ���
	class Window {
	public:
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;
		virtual unsigned GetWidth() const = 0;
		virtual unsigned GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;
		// �������ڹ�������
		static Window* Create(const WindowProps& props = WindowProps());
	};

} // namespace Platform
} // namespace Luxon