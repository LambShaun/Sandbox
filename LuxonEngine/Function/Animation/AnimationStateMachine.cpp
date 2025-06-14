#include "AnimationStateMachine.h"
#include "AnimationSet.h"

namespace Luxon {
namespace Function {
namespace Animation {

	void AnimationStateMachine::AddState(const std::string& stateName, const std::string& animationName) {
		m_States[stateName] = { animationName };
	}

	void AnimationStateMachine::AddTransition(const std::string& fromState, const std::string& toState, TransitionCondition condition) {
		m_Transitions[fromState].push_back({ toState,condition });
	}

    void AnimationStateMachine::Update(Animator& animator, AnimationSet& animationSet, const std::map<std::string, bool>& conditions) {
        if (m_CurrentStateName.empty() || m_States.find(m_CurrentStateName) == m_States.end()) {
            return; // 如果没有当前状态则不更新
        }

        // 检查当前状态是否有任何可以触发的转换
        auto it = m_Transitions.find(m_CurrentStateName);
        if (it == m_Transitions.end()) return; // 没有从当前状态出发的转换规则

        auto& transitions = it->second;
        for (const auto& transition : transitions) {
            // 将从外部传入的conditions map传递给条件函数进行判断
            if (transition.Condition(conditions)) {
                // 条件满足 切换状态
                m_CurrentStateName = transition.ToState;
                // 命令Animator播放新状态对应的动画
                animator.Play(animationSet.GetAnimation(m_States[m_CurrentStateName].AnimationName));
                return; // 每帧只处理一次转换 防止一帧内多次切换
            }
        }
    }

    void AnimationStateMachine::SetInitialState(const std::string& stateName) {
        m_CurrentStateName = stateName;
    }

} // namespace Animation
} // namespace Function
} // namespace Luxon