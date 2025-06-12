/**
 * @file	Input.h
 * @brief	按键输入处理
 * @author	LambShaun
 **/

#pragma once

namespace Luxon {
namespace Function {
namespace Input {
	class Input {
	public:
		static bool IsKeyPressed(int keycode); // 检查是否按下按键
		static void SetKeyPressed(int keycode, bool isPressed); // 设置按下的按键

	private: 
		static bool s_Keys[256]; // 储存按键的键值
	};

} // namespace Input
} // namespace Function
} // namespace Luxon