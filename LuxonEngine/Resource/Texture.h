/**
 * @file	Texture.h
 * @brief	ͼ����Դ������
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
		// Texture ���󱻴�����ͳ�����������
		Texture(uint32_t width, uint32_t height, uint32_t* data);
		~Texture();

		uint32_t GetWidth()const {
			return m_Width;
		}

		uint32_t GetHeight()const {
			return m_Height;
		}
		
		// ��ȡ�������ݵ�ָ��
		const uint32_t* GetData()const {
			return m_Data;
		}

		// ��·������λͼ ���ַ������洢
		static std::unique_ptr<Texture>	Load(const std::string& filepath);
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t* m_Data;
	};
} // namespace Resource
} // namespace Luxon
