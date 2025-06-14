/**
 * @file	AnimatedSpriteComponent.h
 * @brief	存储一个物体的动画所需的所有资源和状态
 * @author	LambShaun
 **/

#pragma once

#include "Core/Component.h"
#include "Resource/Texture.h"
#include "Function/Animation/AnimationSet.h"
#include "Function/Animation/Animator.h"
#include "Resource/ResourceManager.h"
#include "Function/Animation/AnimationStateMachine.h"

#include <memory>
#include <string>

namespace Luxon {
namespace Function {
namespace Rendering {
    class AnimatedSpriteComponent : public Core::Component {
    public:
        std::shared_ptr<Resource::Texture> SpriteSheet = nullptr;
        std::shared_ptr<Animation::AnimationSet> AnimationData = nullptr;
        Animation::Animator Animator;
        Animation::AnimationStateMachine FSM;

        void Load(const nlohmann::json& data) override {
            if (data.contains("animationData")) {
                std::string animPath = data["animationData"];
                AnimationData = Resource::ResourceManager<Animation::AnimationSet>::Load(animPath);

                if (AnimationData && !AnimationData->GetSpriteSheetPath().empty()) {
                    SpriteSheet = Resource::ResourceManager<Resource::Texture>::Load(AnimationData->GetSpriteSheetPath());
                }
            }
        }

        void Start() override {
            if (AnimationData) {
                // 从数据配置状态机
                AnimationData->ConfigureStateMachine(FSM);
                // 播放初始动画
                std::string initialState = AnimationData->GetInitialState();
                if (!initialState.empty()) {
                    Animator.Play(AnimationData->GetAnimation(initialState));
                }
            }
        }

        void Update() override {
            // 在这里不直接更新 Animator，而是由状态机驱动
        }
    };

} // namespace Rendering
} // namespace Function
} // namespace Luxon