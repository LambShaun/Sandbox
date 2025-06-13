/**
 * @file	Animation.h
 * @brief	��������
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
		// ʹ�� std::vector ���洢һ���������а���������֡
		std::vector<AnimationFrame> Frames;
		bool IsLooping = true;
		// ��ȡ��ʱ��
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