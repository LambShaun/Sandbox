/**
 * @file	AnimationSet.h
 * @brief	�������ݼ�����
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
        // ͨ�����ֻ�ȡһ����������
        Function::Animation::Animation* GetAnimation(const std::string& name);
        // ��ȡ�˶����������ľ���ͼ�ļ�·��
        const std::string& GetSpriteSheetPath() const {
            return m_SpriteSheetPath;
        }
        // ��ȡ���ж��������ã������ⲿʹ��
        const std::map<std::string, Animation>& GetAnimations() const {
            return m_Animations;
        }

        // ��ȡ��ʼ״̬��
        const std::string& GetInitialState() const { return m_InitialState; }
        // ���Լ��洢��JSON����������һ���ⲿ��״̬��
        void ConfigureStateMachine(AnimationStateMachine& fsm) const;

        // ��̬���������� JSON �ļ���������������
        static std::shared_ptr<AnimationSet> Load(const std::string& filepath);

	private:
		// Ϊ���� ResourceManager ���Է���˽�й��캯��
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