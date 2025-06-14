/**
 * @file	TransformComponent.h
 * @brief	�洢�����λ�á���ת�����ŵȿռ���Ϣ
 * @author	LambShaun
 **/

#pragma once

#include "core/Component.h"
#include "core/Math/Vec2D.h"

namespace Luxon {
namespace Function{
namespace Component {
	class TransformComponent :public Core::Component{
	public:
		Core::Math::Vector2f Position = { 0.0f,0.0f };

		virtual void Load(const nlohmann::json& data) override {
			if (data.contains("position")) {
				Position.x = data["position"].value("x", 0.0f);
				Position.y = data["position"].value("y", 0.0f);
			}
		}
	};

} // namespace Component
} // namespace Function
} // namespace Luxon