/**
 * @file	AnimationStateMachine.h
 * @brief	����״̬��
 * @author	LambShaun
 **/

#pragma once

#include "Animator.h"
#include <string>
#include <map>
#include <functional>

namespace Luxon {
namespace Function {
namespace Animation {
	class AnimationSet;
	class AnimationStateMachine {
	public:
		// �����л���������
		using TransitionCondition = std::function<bool(const std::map<std::string, bool>&)>;

		// ���һ��״̬������һ����������
		void AddState(const std::string& stateName, const std::string& animationName);
		
		// ��Ӵ�һ��״̬����һ��״̬���л�����
		void AddTransition(const std::string& fromState,const std::string & toState, TransitionCondition condition);

		// ÿһ֡����״̬��������Ƿ���Ҫ�л�״̬
		void Update(Animator& animator, AnimationSet& animationSet, const std::map<std::string, bool>& conditions);

		
		// ���ó�ʼ״̬
		void SetInitialState(const std::string& stateName);

	private:
		struct State {
			std::string AnimationName;
		};

		struct Transition {
			std::string ToState;
			TransitionCondition Condition;
		};

		std::string m_CurrentStateName;
		std::map<std::string, State> m_States;
		std::map<std::string, std::vector<Transition>> m_Transitions;
	};

} // namespace Animation
} // namespace Function
} // namespace Luxon