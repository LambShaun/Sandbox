/**
 * @file	AnimationStateMachine.h
 * @brief	动画状态机
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
		// 条件切换函数类型
		using TransitionCondition = std::function<bool(const std::map<std::string, bool>&)>;

		// 添加一个状态并关联一个动画名称
		void AddState(const std::string& stateName, const std::string& animationName);
		
		// 添加从一个状态到另一个状态的切换规则
		void AddTransition(const std::string& fromState,const std::string & toState, TransitionCondition condition);

		// 每一帧更新状态集，检查是否需要切换状态
		void Update(Animator& animator, AnimationSet& animationSet, const std::map<std::string, bool>& conditions);

		
		// 设置初始状态
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