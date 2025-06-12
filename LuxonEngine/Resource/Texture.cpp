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
		std::ifstream file(filepath, std::ios::binary); // �Զ�����ģʽ��ȡ ȷ��Ϊԭʼ����
		if (!file) {
			throw std::runtime_error("Texture::Load Error: Failed to open file: " + filepath); // ������Ϣ����������ļ�·��
		}

		// ��ȡ�ļ�ͷ����Ϣͷ
		BITMAPFILEHEADER fileHeader;
		BITMAPINFOHEADER infoHeader;

		file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
		file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
		
		// ����Ƿ���λͼ�ļ�
		if (fileHeader.bfType != 0x4D42) {
			throw std::runtime_error("Texture::Load Error : Not a valid BMP file : " + filepath);
		}

		// TODO: 24λ��32λλͼ
		if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
			throw std::runtime_error("Texture::Load Error: Only 24-bit and 32-bit BMPs are supported.");
		}

		// ��ȡͼƬ�ߴ�
		uint32_t width = infoHeader.biWidth;

		// ��׼��BMP�����¶��� flase
		// �߶ȿ����Ǹ��� ͼƬ�����϶��´洢�� true
		// ��ȡ����ֵ�ķ�ʽ��ȡ
		uint32_t height = std::abs(infoHeader.biHeight);
		bool isTopDown = infoHeader.biHeight < 0;

		// Ϊ�������ݷ����ڴ� (RGBA 4�ֽ�/����)
		uint32_t* pixels = new uint32_t[width * height];

		// ���ļ�ָ���ƶ����������ݿ�ʼ��λ��
		file.seekg(fileHeader.bfOffBits, std::ios::beg);

		/* ����ÿ����������ռ�õ��ֽ���(BMPҪ��ÿ����4�ֽڵı���)
		   (ͼ����* �ֽ�) %4 
		   ����  0,  ���ò� 
			    1,	��1�ֽ�
				2,	��2�ֽ�
				3,	��3�ֽ�
			�� 4 - ���� = ��X�ֽ�
			** TODO:����Ϊ�� ����ֲ�4���ֽ�
			** ����: ����Ҫ�Ĳ��ֽ��������ٴ�ȡģ
			*/

		// δ�����д�С + ����ֽ���
		const int padding = (4 - (width * (infoHeader.biBitCount / 8)) % 4) % 4;
		const int rowSize = width * (infoHeader.biBitCount / 8) + padding;

		std::vector<char>rowBuffer(rowSize);
		for (uint32_t y = 0; y < height; ++y) {	
			file.read(rowBuffer.data(), rowSize);

			// ���ݴ洢˳�������ǰ���������һ��
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
				// ��ϳɵ� ARGB ��ʽ (0xAARRGGBB)
				pixel = (a << 24) | (r << 16) | (g << 8) | b;
				pixels[destY * width + x] = pixel;
			}
		}
		return std::make_unique<Texture>(width, height, pixels);
	}

} // namespace Resource
} // namespace Luxon