/**
 * @file	AnimationFarme.h
 * @brief	����֡ �и�ͼ�� ��ʾʱ��
 * @author	LambShaun
 **/

#pragma once

#include "core/Math/Vec2D.h"

namespace Luxon {
namespace Function {
namespace Animation {
	struct AnimationFrame{
		// ��֡�ھ���ͼ�ϵ�λ�úʹ�С
		Core::Math::Vector2i SourcePos;
		Core::Math::Vector2i SourceSize;
		// ��֡�ĳ���ʱ�� ��
		float Duration = 0.1f;
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon