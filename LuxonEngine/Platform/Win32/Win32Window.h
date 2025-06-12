/**
 * @file	Win32Window.h
 * @brief	Win32ƽ̨���ڽӿ�
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
		HWND m_hWnd; // Win32 ���ھ��

		struct WindowData {
			std::string Title;
			unsigned int Width = 0;
			unsigned int Height = 0;
		};

		WindowData m_Data;
	};

} // namespace Luxon