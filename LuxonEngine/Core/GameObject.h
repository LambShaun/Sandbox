/**
 * @file	GameObject.h
 * @brief	游戏世界中的"物体"表示 不含行为
 * @author	LambShaun
 **/

#pragma once

#include "Component.h"

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <typeindex>

namespace Luxon {
namespace Core {
	
	class GameObject {
	public:
		GameObject(std::string name = "GameObject");
		~GameObject();
		// 禁止复制
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		// 允许移动构造和移动赋值 vector扩容时需要 
		GameObject(GameObject&&) noexcept;
		GameObject& operator=(GameObject&&) noexcept;

		template<typename T, typename... TArgs>
		T* AddComponent(TArgs&&... args) {
			auto newComponent = std::make_unique<T>(std::forward<TArgs>(args)...);
			newComponent->Owner = this;
			T* componentPtr = newComponent.get();
			m_Components[typeid(T)] = std::move(newComponent);
			return componentPtr;
		}

		template<typename T>
		T* GetComponent() {
			auto it = m_Components.find(typeid(T));
			if (it != m_Components.end()) {
				return dynamic_cast<T*>(it->second.get());
			}
			return nullptr;
		}

		const std::string& GetName() const {
			return m_Name;
		}

		void StartAllComponents();
		void UpdateAllComponents();

	private:
		std::string m_Name; 
		std::map<std::type_index, std::unique_ptr<Component>>m_Components;
	};

} // namespace Core
} // namespace Luxon