#include "Texture.h"

#include <fstream>
#include <vector>
#include <stdexcept>
#include <Windows.h>

namespace Luxon {
namespace Resource {
	Texture::Texture(uint32_t width, uint32_t height, uint32_t* data)
		:m_Width(width), m_Height(height), m_Data(data){ }
	
	Texture::~Texture() {
		delete[]m_Data;
	}

	std::unique_ptr<Texture> Texture::Load(const std::string& filepath) {
		std::ifstream file(filepath, std::ios::binary); // 以二进制模式读取 确保为原始数据
		if (!file) {
			throw std::runtime_error("Texture::Load Error: Failed to open file: " + filepath); // 错误信息包含具体的文件路径
		}

		// 读取文件头和信息头
		BITMAPFILEHEADER fileHeader;
		BITMAPINFOHEADER infoHeader;

		file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
		file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
		
		// 检查是否是位图文件
		if (fileHeader.bfType != 0x4D42) {
			throw std::runtime_error("Texture::Load Error : Not a valid BMP file : " + filepath);
		}

		// TODO: 24位或32位位图
		if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
			throw std::runtime_error("Texture::Load Error: Only 24-bit and 32-bit BMPs are supported.");
		}

		// 获取图片尺寸
		uint32_t width = infoHeader.biWidth;

		// 标准的BMP是自下而上 flase
		// 高度可能是负数 图片是自上而下存储的 true
		// 用取绝对值的方式读取
		uint32_t height = std::abs(infoHeader.biHeight);
		bool isTopDown = infoHeader.biHeight < 0;

		// 为像素数据分配内存 (RGBA 4字节/像素)
		uint32_t* pixels = new uint32_t[width * height];

		// 将文件指针移动到像素数据开始的位置
		file.seekg(fileHeader.bfOffBits, std::ios::beg);

		/* 计算每行像素数据占用的字节数(BMP要求每行是4字节的倍数)
		   (图像宽度* 字节) %4 
		   余数  0,  不用补 
			    1,	补1字节
				2,	补2字节
				3,	补3字节
			用 4 - 余数 = 补X字节
			** TODO:余数为零 会出现补4个字节
			** 修正: 对需要的补字节数进行再次取模
			*/

		// 未填充的行大小 + 填充字节数
		const int padding = (4 - (width * (infoHeader.biBitCount / 8)) % 4) % 4;
		const int rowSize = width * (infoHeader.biBitCount / 8) + padding;

		std::vector<char>rowBuffer(rowSize);
		for (uint32_t y = 0; y < height; ++y) {	
			file.read(rowBuffer.data(), rowSize);

			// 根据存储顺序决定当前处理的是哪一行
			int destY = isTopDown ? y : (height - 1 - y);
			
			for (uint32_t x = 0; x < width; ++x) {
				uint32_t pixel = 0;
				uint8_t r = 0, g = 0, b = 0, a = 255;

				if (infoHeader.biBitCount == 24) {
					b = rowBuffer[x * 3];
					g = rowBuffer[x * 3 + 1];
					r = rowBuffer[x * 3 + 2];	
				}else { // 32 - bit
					b = rowBuffer[x * 4];
					g = rowBuffer[x * 4 + 1];
					r = rowBuffer[x * 4 + 2];
					a = rowBuffer[x * 4 + 3];
				}
				// 组合成的 ARGB 格式 (0xAARRGGBB)
				pixel = (a << 24) | (r << 16) | (g << 8) | b;
				pixels[destY * width + x] = pixel;
			}
		}
		return std::make_unique<Texture>(width, height, pixels);
	}

} // namespace Resource
} // namespace Luxon