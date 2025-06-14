/**
 * @file	Component.h
 * @brief	所有组件的基类
 * @author	LambShaun
 **/

#pragma once

#include <nlohmann/json.hpp>

namespace Luxon {
namespace Core {
	// 向前声明
	class GameObject;

	class Component {
	public:
		virtual ~Component() = default;
		// JSON加载接口
		virtual void Load(const nlohmann::json& data){} 
		virtual void Start() {}		// 生命周期：初始化
		virtual void Update() {}	// 生命周期：每帧更新
		// 关联 GameObject
		GameObject* Owner = nullptr;
	};

} // namespace Core
} // namespace Luxon