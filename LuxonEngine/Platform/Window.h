/**
 * @file	Window.h
 * @brief	跨平台窗口接口
 * @author	LambShaun
 **/

#pragma once

#include<string>

namespace Luxon { 
	// 窗口配置属性
	struct WindowProps { 
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Luxon Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
		: Title(title),Width(width),Height(height){}
	};
	// 窗口接口类
	class Window {
	public:
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;
		virtual unsigned GetWidth() const = 0;
		virtual unsigned GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;
		// 创建窗口工厂函数
		static Window* Create(const WindowProps& props = WindowProps());
	};

} // namespace Luxon