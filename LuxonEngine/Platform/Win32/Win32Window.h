/**
 * @file	Win32Window.h
 * @brief	Win32平台窗口接口
 * @author	LambShaun
 **/

#pragma once

#include "Platform/Window.h"
#include <Windows.h>

namespace Luxon {
	class Win32Window :public Window {
	public:
		Win32Window(const WindowProps& props);
		virtual ~Win32Window();

		void OnUpdate() override;
		unsigned int GetWidth() const override {
			return m_Data.Width;
		}

		unsigned int GetHeight() const override {
			return m_Data.Height;
		}
		void* GetNativeWindow()const override {
			return m_hWnd;
		}
	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		HWND m_hWnd; // Win32 窗口句柄

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
		};

		WindowData m_Data;
	};

} // namespace Luxon