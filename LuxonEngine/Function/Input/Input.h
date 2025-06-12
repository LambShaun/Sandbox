/**
 * @file	Input.h
 * @brief	�������봦��
 * @author	LambShaun
 **/

#pragma once

namespace Luxon {
	class Input {
	public:
		static bool isKeyPressed(int keycode); // ����Ƿ��°���
		static void SetKeyPressed(int keycode, bool isPressed); // ���ð��µİ���

	private: 
		static bool s_Keys[256]; // ���水���ļ�ֵ
	};
} // namespace Luxon