/**
 * @file	AnimationSet.h
 * @brief	动画数据加载器
 * @author	LambShaun
 **/

#pragma once

#include "Animation.h"
#include "AnimationStateMachine.h"

#include <string>
#include <memory>
#include <map>
#include <nlohmann/json.hpp>
namespace Luxon {
namespace Resource {
    template<typename T>
    class ResourceManager;
}
}


namespace Luxon {
namespace Function {
namespace Animation {
	class AnimationSet {
	public:
        // 通过名字获取一个动画序列
        Function::Animation::Animation* GetAnimation(const std::string& name);
        // 获取此动画集关联的精灵图文件路径
        const std::string& GetSpriteSheetPath() const {
            return m_SpriteSheetPath;
        }
        // 获取所有动画的引用，方便外部使用
        const std::map<std::string, Animation>& GetAnimations() const {
            return m_Animations;
        }

        // 获取初始状态名
        const std::string& GetInitialState() const { return m_InitialState; }
        // 用自己存储的JSON数据来配置一个外部的状态机
        void ConfigureStateMachine(AnimationStateMachine& fsm) const;

        // 静态工厂函数从 JSON 文件加载整个动画集
        static std::shared_ptr<AnimationSet> Load(const std::string& filepath);

	private:
		// 为了让 ResourceManager 可以访问私有构造函数
		friend class Resource::ResourceManager<AnimationSet>;
		AnimationSet() = default;

		std::string m_SpriteSheetPath;
		std::map<std::string, Animation> m_Animations;

		std::string m_InitialState;
		nlohmann::json m_StatesData;
		nlohmann::json m_TransitionsData;
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon