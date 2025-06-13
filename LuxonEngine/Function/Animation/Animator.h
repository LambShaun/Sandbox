/**
 * @file	Animator.h
 * @brief	����ϵͳ����
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

		// ��ʼ����һ���µĶ�������
		void Play(Animation* animation);

		// ����ʱ�����������¶���״̬
		void Update(Core::Time::Timestep ts);

		// ��ȡ��ǰҪ���ƵĶ���֡
		const AnimationFrame* GetCurrentFrame()const;

	private:
		Animation* m_CurrentAnimation; // ��ǰ���ŵĶ���
		float m_CurrentTime;		   // ��ǰ�����ۼƲ���ʱ�� ��
		int m_CurrentFrameIndex;	   // ��ǰ����֡������
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon