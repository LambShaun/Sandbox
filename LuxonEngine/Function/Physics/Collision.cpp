#include "Collision.h"

namespace Luxon {
namespace Function {
namespace Physics {
	 Core::Math::Vector2f Collision::CheckWindowCollision(
		const Core::Math::Vector2f& rectPos,
		const Core::Math::Vector2f& rectSize,
		const Platform::Window& window) {
		// ����һ�ݸ�����������
		Core::Math::Vector2f correctedPos = rectPos;
		// ��ȡ���ڱ߽���Ϣ
		float windowWidth = static_cast<float>(window.GetWidth());
		float windowHeight = static_cast<float>(window.GetHeight());
		// �����ײ
		if (correctedPos.x < 0.0f) {
			correctedPos.x = 0.0f;
		}

		if (correctedPos.x + rectSize.x > windowWidth) {
			correctedPos.x = windowWidth - rectSize.x;
		}

		if (correctedPos.y < 0.0f) {
			correctedPos.y = 0.0f;
		}

		if (correctedPos.y + rectSize.y > windowHeight) {
			correctedPos.y = windowHeight - rectSize.y;
		}
		// ���������������λ��
		return correctedPos;
	}
} // namespace Physics
} // namespace Function
} // namespace Luxon