/**
 * @file	Scene.h
 * @brief	≥°æ∞º”‘ÿ
 * @author	LambShaun
 **/

#pragma once

#include "Core/GameObject.h"

#include <memory>
#include <string>
#include <vector>

namespace Luxon {
namespace Function {
namespace Scene {
	class Scene {
	public:
		static std::unique_ptr<Scene>Load(const std::string& filepath);
		std::vector<Core::GameObject>& GetGameObjects() {
			return m_GameObjects;
		}

	private:
		std::vector<Core::GameObject>m_GameObjects;
	};
} // namespace Scene
} // namespace Function
} // namespace Luxon
