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

	std::shared_ptr<Texture> Texture::Load(const std::string& filepath) {
		int width, height, channels;
		// stbi_load 是 stb_image 的核心函数
		// 参数：文件路径、宽度(输出)、高度(输出)、通道数(输出)、期望的通道数
		// 我们期望4个通道(RGBA)所以最后一个参数是 4
		// 它返回一个指向 uint8_t* 的像素数据指针
		stbi_uc* loaded_pixels = stbi_load(filepath.c_str(), &width, &height, &channels, 4);
        if (loaded_pixels == nullptr) {
            // 如果加载失败stbi_failure_reason() 会提供失败的原因
            throw std::runtime_error("Texture::Load Error [stb_image]: " + std::string(stbi_failure_reason()) + " - " + filepath);
        }
        // stb_image 加载的像素数据是 uint8_t 类型的 需要把它转换成 uint32_t
        // ARGB 格式 (0xAARRGGBB)
        uint32_t* pixels = new uint32_t[width * height];
        uint8_t* p = loaded_pixels;
        for (int i = 0; i < width * height; ++i) {
            uint8_t r = p[0];
            uint8_t g = p[1];
            uint8_t b = p[2];
            uint8_t a = p[3];
            pixels[i] = (a << 24) | (r << 16) | (g << 8) | b;
            p += 4; // 移动到下一个像素 (RGBA)
        }
        // stbi_load 分配的内存 必须用 stbi_image_free 来释放！
        stbi_image_free(loaded_pixels);

        // 创建的 Texture 对象并返回
        return std::make_shared<Texture>(width, height, loaded_pixels);
	}

} // namespace Resource
} // namespace Luxon