#include "Collision.h"

namespace Luxon {
namespace Function {
namespace Physics {
	 Core::Math::Vector2f Collision::CheckWindowCollision(
		const Core::Math::Vector2f& rectPos,
		const Core::Math::Vector2f& rectSize,
		const Platform::Window& window) {
		// 复制一份副本进行修正
		Core::Math::Vector2f correctedPos = rectPos;
		// 获取窗口边界信息
		float windowWidth = static_cast<float>(window.GetWidth());
		float windowHeight = static_cast<float>(window.GetHeight());
		// 检查碰撞
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
		// 返回修正后的最终位置
		return correctedPos;
	}
} // namespace Physics
} // namespace Function
} // namespace Luxon