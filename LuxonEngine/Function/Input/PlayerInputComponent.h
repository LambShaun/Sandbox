/**
 * @file	PlayerInputComponent.h
 * @brief	玩家输入处理
 * @author	LambShaun
 **/

#pragma once

#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Function/Component/TransformComponent.h"
#include "Core/Time/Time.h"
#include "Function/Input/Input.h"

namespace Luxon {
namespace Function {
namespace Input {
	class PlayerInputComponent :public Core::Component {
	public:
		float Speed = 500.0f;

        void Update() {
            auto* transform = Owner->GetComponent<Function::Component::TransformComponent>();
            if (!transform) return;

            Core::Time::Timestep ts = Core::Time::Time::GetDeltaTime();
            Core::Math::Vector2f direction = { 0.0f, 0.0f };
            if (Input::IsKeyPressed('W')) direction.y = -1.0f;
            if (Input::IsKeyPressed('S')) direction.y = 1.0f;
            if (Input::IsKeyPressed('A')) direction.x = -1.0f;
            if (Input::IsKeyPressed('D')) direction.x = 1.0f;

            if (direction.LengthSquared() > 0.0f) {
                direction.Normalize();
            }
            transform->Position += direction * Speed * ts;
        }
	};
} // namespace Input
} // namespace Function
} // namespace Luxon