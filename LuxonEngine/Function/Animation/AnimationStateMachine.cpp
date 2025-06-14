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
            return; // ���û�е�ǰ״̬�򲻸���
        }

        // ��鵱ǰ״̬�Ƿ����κο��Դ�����ת��
        auto it = m_Transitions.find(m_CurrentStateName);
        if (it == m_Transitions.end()) return; // û�дӵ�ǰ״̬������ת������

        auto& transitions = it->second;
        for (const auto& transition : transitions) {
            // �����ⲿ�����conditions map���ݸ��������������ж�
            if (transition.Condition(conditions)) {
                // �������� �л�״̬
                m_CurrentStateName = transition.ToState;
                // ����Animator������״̬��Ӧ�Ķ���
                animator.Play(animationSet.GetAnimation(m_States[m_CurrentStateName].AnimationName));
                return; // ÿֻ֡����һ��ת�� ��ֹһ֡�ڶ���л�
            }
        }
    }

    void AnimationStateMachine::SetInitialState(const std::string& stateName) {
        m_CurrentStateName = stateName;
    }

} // namespace Animation
} // namespace Function
} // namespace Luxon