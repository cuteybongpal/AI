#include "ImageLoader.h"
#include <vector>
#include <string>
#include "stb_image.h"
#include <iostream>


std::vector<float> ImageLoader::LoadPNG(const char* path)
{
	float* nomalizedImage = stbi_loadf(path, new int(28), new int(28), new int(1), 1);
	std::vector<float> imageVec = std::vector<float>();

	
	for (int y = 0; y < 28; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			imageVec.push_back(nomalizedImage[y * 28 + x]);
		}
	}
	stbi_image_free(nomalizedImage);

	return imageVec;
}