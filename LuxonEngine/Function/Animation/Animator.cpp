#include "Animator.h"

namespace Luxon {
namespace Function {
namespace Animation {
	Animator::Animator():m_CurrentAnimation(nullptr),
		m_CurrentTime(0.0f), m_CurrentFrameIndex(0){ }

	void Animator::Play(Animation* animation) {
		// 切换到新的动画序列，重置所有状态
		m_CurrentAnimation = animation;
		m_CurrentTime = 0.0f;
        m_CurrentFrameIndex = 0;
	}

    void Animator::Update(Core::Time::Timestep ts) {
        if (!m_CurrentAnimation) {
            return; // 如果没有动画在播放，就什么也不做
        }

        // 累加时间
        m_CurrentTime += ts.GetSeconds();
        
        // 检查是否需要切换到下一帧
        if (m_CurrentTime >= m_CurrentAnimation->Frames[m_CurrentFrameIndex].Duration) {
            // 从当前时间中减去当前帧的持续时间
            m_CurrentTime -= m_CurrentAnimation->Frames[m_CurrentFrameIndex].Duration;

            // 移动到下一帧
            m_CurrentFrameIndex++;

            // 检查是否到达动画序列的末尾
            if (m_CurrentFrameIndex >= m_CurrentAnimation->Frames.size()) {
                // 如果动画是循环的，就回到第一帧
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