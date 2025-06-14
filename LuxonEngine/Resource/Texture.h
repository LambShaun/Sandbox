/**
 * @file	Texture.h
 * @brief	图像资源管理器
 * @author	LambShaun
 **/

#pragma once

#include <string>
#include <cstdint>
#include <memory>

namespace Luxon {
namespace Resource {
	class Texture {
	public:
		// Texture 对象被创建后就持有像素数据
		Texture(uint32_t width, uint32_t height, uint32_t* data);
		~Texture();

		uint32_t GetWidth()const {
			return m_Width;
		}

		uint32_t GetHeight()const {
			return m_Height;
		}
		
		// 获取像素数据的指针
		const uint32_t* GetData()const {
			return m_Data;
		}

		// 从路径加载位图 用字符串来存储
		static std::shared_ptr<Texture>	Load(const std::string& filepath);
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t* m_Data;
	};
} // namespace Resource
} // namespace Luxon
