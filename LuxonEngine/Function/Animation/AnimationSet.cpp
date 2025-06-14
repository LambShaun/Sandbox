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
		// �ж�
		if(it !=m_Animations.end()){
			return &it->second;
		}
		return nullptr;
	}
	
	void AnimationSet::ConfigureStateMachine(AnimationStateMachine& fsm) const {
		// ���ݴ洢��״̬���� ����״̬��
		if (m_StatesData.is_array()) {
			for (const auto& state : m_StatesData) {
				fsm.AddState(state.value("name", ""), state.value("animation", ""));
			}
		}

		// ���ݴ洢���л����� ����״̬��
		if (m_TransitionsData.is_array()) {
			for (const auto& transition : m_TransitionsData) {
				std::string conditionKey = transition.value("condition", "");
				if (conditionKey.empty()) continue;

				// ʹ�� Lambda ���ʽ����һ��ͨ�õ�������麯��
				fsm.AddTransition(transition["from"], transition["to"],
					[conditionKey](const auto& conditions) {
						// ����Ƿ��� "!" ��ͷ�ķ�������
						if (conditionKey[0] == '!') {
							auto key = conditionKey.substr(1);
							return conditions.count(key) ? !conditions.at(key) : false;
						}
						return conditions.count(conditionKey) ? conditions.at(conditionKey) : false;
					}
				);
			}
		}

		// ���ó�ʼ״̬
		fsm.SetInitialState(m_InitialState);
	}

    std::shared_ptr<AnimationSet> AnimationSet::Load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("AnimationSet::Load Error: Failed to open file: " + filepath);
        }

        nlohmann::json data = nlohmann::json::parse(file);
        std::shared_ptr<AnimationSet> animationSet(new AnimationSet());
        // ��ȡ���洢����ͼ��·��
        animationSet->m_SpriteSheetPath = data.value("texture", "");
        // ����"animations"�����е�ÿһ����������
        if (data.contains("animations")) {
            for (auto& animNode : data["animations"].items()) {
                std::string animName = animNode.key();
                auto& animData = animNode.value();
                Animation newAnimation;
                newAnimation.Name = animName;
                newAnimation.IsLooping = animData.value("isLooping", true);

                // �����������ö������е�����֡
                if (animData.contains("frames")) {
                    for (const auto& frameData : animData["frames"]) {
                        AnimationFrame newFrame;
                        newFrame.SourcePos = { frameData.value("x", 0), frameData.value("y", 0) };
                        newFrame.SourceSize = { frameData.value("width", 0), frameData.value("height", 0) };
                        newFrame.Duration = frameData.value("duration", 0.1f);
                        newAnimation.Frames.push_back(newFrame);
                    }
                }
                // �������Ķ������д��� map ��
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