#include "Texture.h"
#include "stb_image.h"

#include <stdexcept>


namespace Luxon {
namespace Resource {
	Texture::Texture(uint32_t width, uint32_t height, uint32_t* data)
		:m_Width(width), m_Height(height), m_Data(data){ }
	
	Texture::~Texture() {
		delete[]m_Data;
	}

	std::unique_ptr<Texture> Texture::Load(const std::string& filepath) {
		int width, height, channels;
		// stbi_load �� stb_image �ĺ��ĺ���
		// �������ļ�·�������(���)���߶�(���)��ͨ����(���)��������ͨ����
		// ��������4��ͨ��(RGBA)�������һ�������� 4
		// ������һ��ָ�� uint8_t* ����������ָ��
		stbi_uc* loaded_pixels = stbi_load(filepath.c_str(), &width, &height, &channels, 4);
        if (loaded_pixels == nullptr) {
            // �������ʧ��stbi_failure_reason() ���ṩʧ�ܵ�ԭ��
            throw std::runtime_error("stb_image Error: Failed to load image: " + filepath + " - " + stbi_failure_reason());
        }
        // stb_image ���ص����������� uint8_t ���͵� ��Ҫ����ת���� uint32_t
        // ARGB ��ʽ (0xAARRGGBB)
        uint32_t* pixels = new uint32_t[width * height];
        uint8_t* p = loaded_pixels;
        for (int i = 0; i < width * height; ++i) {
            uint8_t r = p[0];
            uint8_t g = p[1];
            uint8_t b = p[2];
            uint8_t a = p[3];
            pixels[i] = (a << 24) | (r << 16) | (g << 8) | b;
            p += 4; // �ƶ�����һ������ (RGBA)
        }
        // stbi_load ������ڴ� ������ stbi_image_free ���ͷţ�
        stbi_image_free(loaded_pixels);

        // ������ Texture ���󲢷���
        return std::make_unique<Texture>(width, height, pixels);
	}

} // namespace Resource
} // namespace Luxon