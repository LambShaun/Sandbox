/**
 * @file	AnimationSet.h
 * @brief	�������ݼ�����
 * @author	LambShaun
 **/

#pragma once

#include "Animation.h"

#include <string>
#include <memory>
#include <map>

namespace Luxon {
namespace Function {
namespace Animation {
	class AnimationSet {
	public:
		// ͨ�����ֻ�ȡһ����������
		Function::Animation::Animation* GetAnimation(const std::string& name);
		// ��JSON�ļ��м�������������
		static std::shared_ptr<AnimationSet>Load(const std::string& filepath);
	
	private:
		// ʹ�� std::map ���洢�����ֵ��������е�ӳ��
		std::map<std::string ,Function::Animation::Animation> m_Animations;
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon