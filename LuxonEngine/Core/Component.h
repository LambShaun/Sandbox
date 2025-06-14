/**
 * @file	Component.h
 * @brief	��������Ļ���
 * @author	LambShaun
 **/

#pragma once

#include <nlohmann/json.hpp>

namespace Luxon {
namespace Core {
	// ��ǰ����
	class GameObject;

	class Component {
	public:
		virtual ~Component() = default;
		// JSON���ؽӿ�
		virtual void Load(const nlohmann::json& data){} 
		virtual void Start() {}		// �������ڣ���ʼ��
		virtual void Update() {}	// �������ڣ�ÿ֡����
		// ���� GameObject
		GameObject* Owner = nullptr;
	};

} // namespace Core
} // namespace Luxon