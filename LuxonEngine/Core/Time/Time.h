/**
 * @file	Input.h
 * @brief	计时器
 * @author	LambShaun
 **/

#pragma once

#include "Timestep.h"

#include <chrono>

namespace Luxon {
namespace Core {
namespace Time {
	class Time {
	public:
		// 在主循环的每一帧开始时调用 用于更新时间信息
		static void Tick();
		// 获取上一帧的时间增量 (Delta Time)
		static Timestep GetDeltaTime() {
			return s_DeltaTime;
		}
		// 获取FPS
		static float GetFPS() {
			return s_FPS;
		}

		// 设置时间缩放 实现正常速度、快进、暂停、慢放
		 // scale = 1.0f (正常速度), scale = 0.5f (半速慢放), scale = 0.0f (暂停)
		static void GetTimeScale(float scale) {
			s_TimeScale = scale;
		}

		static float GetTimeScale() {
			return s_TimeScale;
		}	
			
	private: 
		// 防止外部创建实例
		Time() {};

		// 核心时间数据
		static Timestep s_DeltaTime;
		static float s_TimeScale;

		// 用于计算的内部变量
		static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastFrameTime;

		// 用于计算fps变量
		static int s_FrameCount; // 统计过去 1 秒内的帧数
		static float s_FPSTimer; // 累计过去多少秒		
		static float s_FPS;
	};

} // namespace Time
} // namespace Core
} // namespace Luxon