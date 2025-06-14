#include "AnimationSet.h"
#include "AnimationStateMachine.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
namespace Luxon {
namespace Function {
namespace Animation {
	Animation* AnimationSet::GetAnimation(const std::string& name) {
		auto it = m_Animations.find(name);
		// 判断
		if(it !=m_Animations.end()){
			return &it->second;
		}
		return nullptr;
	}
	
	void AnimationSet::ConfigureStateMachine(AnimationStateMachine& fsm) const {
		// 根据存储的状态数据 配置状态机
		if (m_StatesData.is_array()) {
			for (const auto& state : m_StatesData) {
				fsm.AddState(state.value("name", ""), state.value("animation", ""));
			}
		}

		// 根据存储的切换数据 配置状态机
		if (m_TransitionsData.is_array()) {
			for (const auto& transition : m_TransitionsData) {
				std::string conditionKey = transition.value("condition", "");
				if (conditionKey.empty()) continue;

				// 使用 Lambda 表达式创建一个通用的条件检查函数
				fsm.AddTransition(transition["from"], transition["to"],
					[conditionKey](const auto& conditions) {
						// 检查是否是 "!" 开头的反向条件
						if (conditionKey[0] == '!') {
							auto key = conditionKey.substr(1);
							return conditions.count(key) ? !conditions.at(key) : false;
						}
						return conditions.count(conditionKey) ? conditions.at(conditionKey) : false;
					}
				);
			}
		}

		// 设置初始状态
		fsm.SetInitialState(m_InitialState);
	}

    std::shared_ptr<AnimationSet> AnimationSet::Load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("AnimationSet::Load Error: Failed to open file: " + filepath);
        }

        nlohmann::json data = nlohmann::json::parse(file);
        std::shared_ptr<AnimationSet> animationSet(new AnimationSet());
        // 读取并存储精灵图的路径
        animationSet->m_SpriteSheetPath = data.value("texture", "");
        // 解析"animations"对象中的每一个动画序列
        if (data.contains("animations")) {
            for (auto& animNode : data["animations"].items()) {
                std::string animName = animNode.key();
                auto& animData = animNode.value();
                Animation newAnimation;
                newAnimation.Name = animName;
                newAnimation.IsLooping = animData.value("isLooping", true);

                // 遍历并解析该动画序列的所有帧
                if (animData.contains("frames")) {
                    for (const auto& frameData : animData["frames"]) {
                        AnimationFrame newFrame;
                        newFrame.SourcePos = { frameData.value("x", 0), frameData.value("y", 0) };
                        newFrame.SourceSize = { frameData.value("width", 0), frameData.value("height", 0) };
                        newFrame.Duration = frameData.value("duration", 0.1f);
                        newAnimation.Frames.push_back(newFrame);
                    }
                }
                // 将完整的动画序列存入 map 中
                animationSet->m_Animations[animName] = newAnimation;
            }
        }

        if (data.contains("states")) {
            animationSet->m_InitialState = data["states"].value("initialState", "");
            animationSet->m_StatesData = data["states"].value("list", nlohmann::json::array());
        }

        if (data.contains("transitions")) {
            animationSet->m_TransitionsData = data["transitions"];
        }
        return animationSet;
    }

} // namespace Animation
} // namespace Function
} // namespace Luxon