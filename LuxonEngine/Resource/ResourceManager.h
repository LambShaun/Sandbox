/**
 * @file	ResourceManager.h
 * @brief	模板化 可缓存和加载任何类型资源的管理器
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
		// 加载获取一个资源
		static std::shared_ptr<T>Load(const std::string& filepath) {
			// 检查是否加载过这个资源
			auto it = s_ResourceCache.find(filepath);
			if (it != s_ResourceCache.end()) {
				return it->second;
			}
			else {
				// 不存在 调用该资源类型自己的Load函数来从文件加载
				std::shared_ptr<T> resource = T::Load(filepath);
				if (resource) {
					// 将加载成功的资源存入缓存
					s_ResourceCache[filepath] = resource;
					return resource;
				}
			}
			// 失败抛出异常
			throw std::runtime_error("ResourceManager::Load Error: Failed to load resource: " + filepath);
		}
		// 释放不用的资源
		static void Unload(const std::string& filepath) {
			s_ResourceCache.erase(filepath);
		}

		// 清空缓存
		static void ClearCache() {
			s_ResourceCache.clear();
		}

	private:
		// 私有化构造函数
		ResourceManager() = default;
		// 静态map, shared_ptr 存储共享资源
		static std::map<std::string, std::shared_ptr<T>>s_ResourceCache;
	};

	// 模板类静态成员变量定义
	template<typename T>
	std::map<std::string, std::shared_ptr<T>>ResourceManager<T>::s_ResourceCache;

} // nmaspace Resource
} // namespace Luxon