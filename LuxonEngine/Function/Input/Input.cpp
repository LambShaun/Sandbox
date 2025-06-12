#include "Input.h"
#include <cstring>

namespace Luxon {
	bool Input::s_Keys[256] = { false }; // 初始化所有键值为未按下状态

	// 检查按键是否在有效范围内
	bool Input::isKeyPressed(int keycode) {
		if (keycode >= 0 && keycode < 256) {
			return s_Keys[keycode];
		}
		return false;
	}

	void Input::SetKeyPressed(int keycode, bool isPressed) {
		// 设置特定按键状态
		if (keycode >= 0 && keycode < 256) {
			 s_Keys[keycode] = isPressed;
		}
	}
} // namespace Luxon