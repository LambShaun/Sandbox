/**
 * @file	Collision.h
 * @brief	��Ϸ��ײ���
 * @author	LambShaun
 **/

#pragma once

#include "Core/Math/Vec2D.h"
#include "Platform/Window.h"

namespace Luxon {
namespace Function {
namespace Physics {
	class Collision {
	public:
		// ��̬���������һ�������ľ���λ���Ƿ��ڴ��ڱ߽��ڣ��������������λ��
				// rectPos: ���ε�ǰ��λ��
				// rectSize: ���εĴ�С
				// window: ��Ϸ���ڵ����ã����ڻ�ȡ�߽�
		static Core::Math::Vector2f CheckWindowCollision(
			const Core::Math::Vector2f& rectPos,
			const Core::Math::Vector2f& rectSize,
			const Platform::Window& window
		);	
	};
} // namespace Physics
} // namespace Function
} // namespace Luxon