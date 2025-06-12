/**
 * @file	Input.h
 * @brief	�������봦��
 * @author	LambShaun
 **/

#pragma once

namespace Luxon {
namespace Function {
namespace Input {
	class Input {
	public:
		static bool IsKeyPressed(int keycode); // ����Ƿ��°���
		static void SetKeyPressed(int keycode, bool isPressed); // ���ð��µİ���

	private: 
		static bool s_Keys[256]; // ���水���ļ�ֵ
	};

} // namespace Input
} // namespace Function
} // namespace Luxon