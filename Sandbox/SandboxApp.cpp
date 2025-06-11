#include <Windows.h>
#include <string>
static HWND m_hWnd;
const wchar_t CLASS_NAME[] = L"TestWindow";
LRESULT CALLBACK Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);  
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);  
		return 0;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	WNDCLASSEXW wc = {};
		wc.cbSize= sizeof(WNDCLASSEXW);
		wc.lpfnWndProc = Wndproc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = CLASS_NAME;

		RegisterClassExW(&wc);

		m_hWnd = CreateWindowExW(
			0,
			CLASS_NAME,
			L"My Test Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL);
	
		ShowWindow(m_hWnd, SW_SHOW);

		bool running = true;
		MSG Msg;
		while (running) {
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
				if (Msg.message == WM_QUIT) {
					running = false;
				}
				else {
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
				
			}	
		}
	return 0;
}