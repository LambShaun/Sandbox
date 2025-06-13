/**
 * @file	AnimationSet.h
 * @brief	动画数据加载器
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
		// 通过名字获取一个动画序列
		Function::Animation::Animation* GetAnimation(const std::string& name);
		// 从JSON文件中加载整个动画集
		static std::unique_ptr<AnimationSet>Load(const std::string& filepath);
	
	private:
		// 使用 std::map 来存储从名字到动画序列的映射
		std::map<std::string ,Function::Animation::Animation> m_Animations;
	};
} // namespace Animation
} // namespace Function
} // namespace Luxon