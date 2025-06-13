#include "AnimationSet.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
namespace Luxon {
namespace Function {
namespace Animation {
	Animation* AnimationSet::GetAnimation(const std::string& name) {
		auto it = m_Animations.find(name);
		// �ж�
		if(it !=m_Animations.end()){
			return &it->second;
		}
		return nullptr;
	}
	
	std::unique_ptr<AnimationSet> AnimationSet::Load(const std::string& filepath) {
		std::ifstream file(filepath);
		if (!file.is_open()) {
			throw std::runtime_error("AnimationSet::Load Error: Failed to open file: " + filepath);
		}
		// ����JSON�ļ�
		nlohmann::json data = nlohmann::json::parse(file);
		
		// ���� AnimationSet ʵ��
		auto animationSet = std::make_unique<AnimationSet>();
		
		// ��Ϊ��ǰ JSON ��ʽû�е����Ķ������ƣ����Խ�����֡����һ��Ĭ�϶���
		Animation defaultAnimation;
		defaultAnimation.Name = "default"; // ����������Ϊ "default"
		defaultAnimation.IsLooping = true; // ��Ϊѭ������

		// ��������������֡
		// ���JSON�Ƿ����"sprites"����
		if (data.contains("sprites") && data["sprites"].is_array()) {
			// ����������ÿ������(����֡)
			for (const auto& frameData : data["sprites"]) {
				AnimationFrame newFrame; // ����һ���µĶ�������

				// ��ȡJSON��֡���꼰��Ϣ
				newFrame.SourcePos.x = frameData["x"];
				newFrame.SourcePos.y = frameData["y"];
				newFrame.SourceSize.x = frameData["width"];
				newFrame.SourceSize.y = frameData["height"];

				// TODO����ʱ����Ĭ��֡��������ʱ��
				newFrame.Duration = 0.1f;

				// ���½��Ķ���֡��ӵ�Ĭ�ϵĶ����б���
				defaultAnimation.Frames.push_back(newFrame);
			}
		}
		// Ĭ�϶����洢��AnimationSet��
		animationSet->m_Animations["default"] = defaultAnimation;

		return animationSet;
	} 
} // namespace Animation
} // namespace Function
} // namespace Luxon