/**
 * @file	ResourceManager.h
 * @brief	ģ�廯 �ɻ���ͼ����κ�������Դ�Ĺ�����
 * @author	LambShaun
 **/

#pragma once

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

namespace Luxon {
namespace Resource {
	template <typename T>
	class ResourceManager {
	public:
		// ���ػ�ȡһ����Դ
		static std::shared_ptr<T>Load(const std::string& filepath) {
			// ����Ƿ���ع������Դ
			auto it = s_ResourceCache.find(filepath);
			if (it != s_ResourceCache.end()) {
				return it->second;
			}
			else {
				// ������ ���ø���Դ�����Լ���Load���������ļ�����
				std::shared_ptr<T> resource = T::Load(filepath);
				if (resource) {
					// �����سɹ�����Դ���뻺��
					s_ResourceCache[filepath] = resource;
					return resource;
				}
			}
			// ʧ���׳��쳣
			throw std::runtime_error("ResourceManager::Load Error: Failed to load resource: " + filepath);
		}
		// �ͷŲ��õ���Դ
		static void Unload(const std::string& filepath) {
			s_ResourceCache.erase(filepath);
		}

		// ��ջ���
		static void ClearCache() {
			s_ResourceCache.clear();
		}

	private:
		// ˽�л����캯��
		ResourceManager() = default;
		// ��̬map, shared_ptr �洢������Դ
		static std::map<std::string, std::shared_ptr<T>>s_ResourceCache;
	};

	// ģ���ྲ̬��Ա��������
	template<typename T>
	std::map<std::string, std::shared_ptr<T>>ResourceManager<T>::s_ResourceCache;

} // nmaspace Resource
} // namespace Luxon