#include "AnimationSet.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
namespace Luxon {
namespace Function {
namespace Animation {
	Animation* AnimationSet::GetAnimation(const std::string& name) {
		auto it = m_Animations.find(name);
		// 判断
		if(it !=m_Animations.end()){
			return &it->second;
		}
		return nullptr;
	}
	
	std::shared_ptr<AnimationSet> AnimationSet::Load(const std::string& filepath) {
		std::ifstream file(filepath);
		if (!file.is_open()) {
			throw std::runtime_error("AnimationSet::Load Error: Failed to open file: " + filepath);
		}
		// 解析JSON文件
		nlohmann::json data = nlohmann::json::parse(file);
		
		// 创建 AnimationSet 实例
		auto animationSet = std::make_unique<AnimationSet>();
		
		// 因为当前 JSON 格式没有单独的动画名称，所以将所有帧归入一个默认动画
		Animation defaultAnimation;
		defaultAnimation.Name = "default"; // 动画名称设为 "default"
		defaultAnimation.IsLooping = true; // 设为循环播放

		// 遍历并解析动画帧
		// 检查JSON是否存在"sprites"数组
		if (data.contains("sprites") && data["sprites"].is_array()) {
			// 遍历数组中每个数据(动画帧)
			for (const auto& frameData : data["sprites"]) {
				AnimationFrame newFrame; // 创建一个新的动画对象

				// 提取JSON中帧坐标及信息
				newFrame.SourcePos.x = frameData["x"];
				newFrame.SourcePos.y = frameData["y"];
				newFrame.SourceSize.x = frameData["width"];
				newFrame.SourceSize.y = frameData["height"];

				// TODO：暂时设置默认帧动画持续时间
				newFrame.Duration = 0.1f;

				// 将新建的动画帧添加到默认的动画列表中
				defaultAnimation.Frames.push_back(newFrame);
			}
		}
		// 默认动画存储到AnimationSet中
		animationSet->m_Animations["default"] = defaultAnimation;

		return animationSet;
	} 
} // namespace Animation
} // namespace Function
} // namespace Luxon