/**
 * @file	Input.h
 * @brief	��ʱ��
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
		// ����ѭ����ÿһ֡��ʼʱ���� ���ڸ���ʱ����Ϣ
		static void Tick();
		// ��ȡ��һ֡��ʱ������ (Delta Time)
		static Timestep GetDeltaTime() {
			return s_DeltaTime;
		}
		// ��ȡFPS
		static float GetFPS() {
			return s_FPS;
		}

		// ����ʱ������ ʵ�������ٶȡ��������ͣ������
		 // scale = 1.0f (�����ٶ�), scale = 0.5f (��������), scale = 0.0f (��ͣ)
		static void GetTimeScale(float scale) {
			s_TimeScale = scale;
		}

		static float GetTimeScale() {
			return s_TimeScale;
		}	
			
	private: 
		// ��ֹ�ⲿ����ʵ��
		Time() {};

		// ����ʱ������
		static Timestep s_DeltaTime;
		static float s_TimeScale;

		// ���ڼ�����ڲ�����
		static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastFrameTime;

		// ���ڼ���fps����
		static int s_FrameCount; // ͳ�ƹ�ȥ 1 ���ڵ�֡��
		static float s_FPSTimer; // �ۼƹ�ȥ������		
		static float s_FPS;
	};

} // namespace Time
} // namespace Core
} // namespace Luxon