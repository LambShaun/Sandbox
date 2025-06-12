/**
 * @file	Timestep.h
 * @brief	时间步长
 * @author	LambShaun
 **/

#pragma once

namespace Luxon {
namespace Core {
namespace Time {
	class Timestep {
	public:
		Timestep(float time = 0.0f) :m_Time(time) {}
		// 隐式转换成float
		operator float() const {
			return m_Time;
		}

		// 获取秒
		float GetSeconds() const {
			return m_Time;
		}
		
		// 获取毫秒
		float GetMilliseconds() const {
			return m_Time;
		}

	private:
		float m_Time; // 内部以秒为单位存储时间
	};

} // namespace Time
} // namespace Core
} // namespace Luxon