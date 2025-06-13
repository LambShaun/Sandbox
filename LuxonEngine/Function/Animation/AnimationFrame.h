/**
 * @file	AnimationFarme.h
 * @brief	动画帧 切割图像 显示时间
 * @author	LambShaun
 **/

#pragma once

#include "core/Math/Vec2D.h"

namespace Luxon {
namespace Function {
namespace Animation {
	struct AnimationFrame{
		// 该帧在精灵图上的位置和大小
		Core::Math::Vector2i SourcePos;
		Core::Math::Vector2i SourceSize;
		// 该帧的持续时间 秒
		float Duration = 0.1f;
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon