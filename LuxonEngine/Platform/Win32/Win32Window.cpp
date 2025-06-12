#include "Platform/Window.h"
#include "Win32Window.h"
#include "Function/Input/Input.h"

// ������Ϣ������
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE: {
		PostQuitMessage(0);
		return 0;
	}break;

	case WM_KEYDOWN: { // ����������Ϣ����
		// wParam ����������������µļ���������
		Luxon::Input::SetKeyPressed(wParam, true);
		return 0;
	}break;
 
	case WM_KEYUP: {
		Luxon::Input::SetKeyPressed(wParam, false);
		return 0;
	}break;
					
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

namespace Luxon {
	// ʵ�ֹ�������
	Window* Window::Create(const WindowProps& props) {
		return new Win32Window(props);
	}

	Win32Window::Win32Window(const WindowProps& props) {
		Init(props);
	}

	Win32Window::~Win32Window() {
		Shutdown();
	}

	void Win32Window::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		const wchar_t CLASS_NAME[] = L"Luxon Window Class";

		WNDCLASSEXW wc = {};
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = CLASS_NAME;

		RegisterClassExW(&wc);
		std::wstring wTitle(m_Data.Title.begin(), m_Data.Title.end());

		m_hWnd = CreateWindowExW(
			0, CLASS_NAME, wTitle.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, m_Data.Width, m_Data.Height,
			NULL, NULL, GetModuleHandle(NULL), NULL
		);

		ShowWindow(m_hWnd, SW_SHOW);
	}

	void Win32Window::Shutdown() {
		DestroyWindow(m_hWnd);
	}

	void Win32Window::OnUpdate() {

	}
	
} // namespace Luxon