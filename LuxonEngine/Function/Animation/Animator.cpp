#include "Animator.h"

namespace Luxon {
namespace Function {
namespace Animation {
	Animator::Animator():m_CurrentAnimation(nullptr),
		m_CurrentTime(0.0f), m_CurrentFrameIndex(0){ }

	void Animator::Play(Animation* animation) {
		// �л����µĶ������У���������״̬
		m_CurrentAnimation = animation;
		m_CurrentTime = 0.0f;
        m_CurrentFrameIndex = 0;
	}

    void Animator::Update(Core::Time::Timestep ts) {
        if (!m_CurrentAnimation) {
            return; // ���û�ж����ڲ��ţ���ʲôҲ����
        }

        // �ۼ�ʱ��
        m_CurrentTime += ts.GetSeconds();
        
        // ����Ƿ���Ҫ�л�����һ֡
        if (m_CurrentTime >= m_CurrentAnimation->Frames[m_CurrentFrameIndex].Duration) {
            // �ӵ�ǰʱ���м�ȥ��ǰ֡�ĳ���ʱ��
            m_CurrentTime -= m_CurrentAnimation->Frames[m_CurrentFrameIndex].Duration;

            // �ƶ�����һ֡
            m_CurrentFrameIndex++;

            // ����Ƿ񵽴ﶯ�����е�ĩβ
            if (m_CurrentFrameIndex >= m_CurrentAnimation->Frames.size()) {
                // ���������ѭ���ģ��ͻص���һ֡
                if (m_CurrentAnimation->IsLooping) {
                    m_CurrentFrameIndex = 0;
                }
                else {
                    m_CurrentFrameIndex = m_CurrentAnimation->Frames.size() - 1;
                }
            }
        }
    }

    const AnimationFrame* Animator::GetCurrentFrame()const {
        if (!m_CurrentAnimation || m_CurrentAnimation->Frames.empty()) {
            return nullptr;
        }
        return &m_CurrentAnimation->Frames[m_CurrentFrameIndex];
    }

} // namespace Animation
} // namespace Function
} // namespace Luxon