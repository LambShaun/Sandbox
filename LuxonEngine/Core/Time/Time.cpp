#include "Time.h"

namespace Luxon {
namespace Core {
namespace Time {
	Timestep Time::s_DeltaTime = Timestep(0.0f);
	float Time::s_TimeScale = 1.0f; // �ٶ������ٶ�
	std::chrono::time_point<std::chrono::high_resolution_clock> Time::s_LastFrameTime = std::chrono::high_resolution_clock::now();
	int Time::s_FrameCount = 0;
	float Time::s_FPSTimer = 0.0f;
	float Time::s_FPS = 0.0f;

	void Time::Tick() {
		// ��ǰʱ��
		auto currentTime = std::chrono::high_resolution_clock::now();
		// ԭʼ����ʱ��
		float rawDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - s_LastFrameTime).count();
		// ���һ֡ʱ��
		s_LastFrameTime = currentTime;

		// DeltaTime Ӧ��ʱ������
		s_DeltaTime = Timestep(rawDeltaTime * s_TimeScale);
		// ���� FPS
		s_FrameCount++;
		s_FPSTimer += rawDeltaTime; // ��δ���ŵ�ʱ�����ۼ�FPS��ʱ��
		if (s_FPSTimer >= 1.0f) // ÿ�����һ��FPS
		{
			s_FPS = static_cast<float>(s_FrameCount) / s_FPSTimer;
			s_FrameCount = 0;
			s_FPSTimer = 0.0f;
		}
	}
	
} // namespace Time
} // namespace Core
} // namespace Luxon