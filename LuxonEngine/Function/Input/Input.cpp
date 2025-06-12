#include "Input.h"
#include <cstring>

namespace Luxon {
namespace Function {
namespace Input {
	bool Input::s_Keys[256] = { false }; // ��ʼ�����м�ֵΪδ����״̬

	// ��鰴���Ƿ�����Ч��Χ��
	bool Input::IsKeyPressed(int keycode) {
		if (keycode >= 0 && keycode < 256) {
			return s_Keys[keycode];
		}
		return false;
	}

	void Input::SetKeyPressed(int keycode, bool isPressed) {
		// �����ض�����״̬
		if (keycode >= 0 && keycode < 256) {
			 s_Keys[keycode] = isPressed;
		}
	}

} // namespace Input
} // namespace Function
} // namespace Luxon