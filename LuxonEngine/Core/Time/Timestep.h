/**
 * @file	Timestep.h
 * @brief	ʱ�䲽��
 * @author	LambShaun
 **/

#pragma once

namespace Luxon {
namespace Core {
namespace Time {
	class Timestep {
	public:
		Timestep(float time = 0.0f) :m_Time(time) {}
		// ��ʽת����float
		operator float() const {
			return m_Time;
		}

		// ��ȡ��
		float GetSeconds() const {
			return m_Time;
		}
		
		// ��ȡ����
		float GetMilliseconds() const {
			return m_Time;
		}

	private:
		float m_Time; // �ڲ�����Ϊ��λ�洢ʱ��
	};

} // namespace Time
} // namespace Core
} // namespace Luxon