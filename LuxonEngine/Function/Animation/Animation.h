/**
 * @file	Animation.h
 * @brief	动画序列
 * @author	LambShaun
 **/

#pragma once

#include "AnimationFrame.h"

#include <vector>
#include <string>

namespace Luxon {
namespace Function {
namespace Animation {
	class Animation {
	public:
		std::string Name;
		// 使用 std::vector 来存储一个动画序列包含的所有帧
		std::vector<AnimationFrame> Frames;
		bool IsLooping = true;
		// 获取总时长
		float GetTotalDuration()const {
			float duration = 0.0f;
			for (const auto& frame : Frames) {
				duration += frame.Duration;
			}
			return duration;
		}
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon