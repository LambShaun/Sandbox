/**
 * @file	Animator.h
 * @brief	动画系统核心
 * @author	LambShaun
 **/

#pragma once

#include "Animation.h"
#include "core/Time/Timestep.h"

namespace Luxon {
namespace Function {
namespace Animation {
	class Animator {
	public:
		Animator();

		// 开始播放一个新的动画序列
		void Play(Animation* animation);

		// 根据时间增量来更新动画状态
		void Update(Core::Time::Timestep ts);

		// 获取当前要绘制的动画帧
		const AnimationFrame* GetCurrentFrame()const;

	private:
		Animation* m_CurrentAnimation; // 当前播放的动画
		float m_CurrentTime;		   // 当前动画累计播放时间 秒
		int m_CurrentFrameIndex;	   // 当前播放帧的索引
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon