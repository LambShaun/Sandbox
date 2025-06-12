#include "Time.h"

namespace Luxon {
namespace Core {
namespace Time {
	Timestep Time::s_DeltaTime = Timestep(0.0f);
	float Time::s_TimeScale = 1.0f; // 速度正常速度
	std::chrono::time_point<std::chrono::high_resolution_clock> Time::s_LastFrameTime = std::chrono::high_resolution_clock::now();
	int Time::s_FrameCount = 0;
	float Time::s_FPSTimer = 0.0f;
	float Time::s_FPS = 0.0f;

	void Time::Tick() {
		// 当前时间
		auto currentTime = std::chrono::high_resolution_clock::now();
		// 原始增量时间
		float rawDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - s_LastFrameTime).count();
		// 最后一帧时间
		s_LastFrameTime = currentTime;

		// DeltaTime 应用时间缩放
		s_DeltaTime = Timestep(rawDeltaTime * s_TimeScale);
		// 计算 FPS
		s_FrameCount++;
		s_FPSTimer += rawDeltaTime; // 用未缩放的时间来累计FPS计时器
		if (s_FPSTimer >= 1.0f) // 每秒更新一次FPS
		{
			s_FPS = static_cast<float>(s_FrameCount) / s_FPSTimer;
			s_FrameCount = 0;
			s_FPSTimer = 0.0f;
		}
	}
	
} // namespace Time
} // namespace Core
} // namespace Luxon