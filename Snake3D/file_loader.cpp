#include "file_loader.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <algorithm>
#include <iostream>
#include <GLFW/glfw3.h>

Image::Image(const std::vector<unsigned char> &data_, size_t width_, size_t height_, 
	         size_t channelsCount_)
	: data(data_), width(width_), height(height_), channelsCount(channelsCount_)
{}

Image::Image(const unsigned char *data_, size_t width_, size_t height_, 
			 size_t channelsCount_)
	: width(width_), height(height_), channelsCount(channelsCount_)
{
	if(width * height * channelsCount != 0)
		data.resize(width * height * channelsCount);

	for (size_t i = 0; i < data.size(); ++i)
		data[i] = data_[i];
}

Image::Image(std::vector<unsigned char> &&data_, size_t width_, size_t height_, 
			 size_t channelsCount_)
	: data(data_), width(width_), height(height_), channelsCount(channelsCount_)
{}

std::string loadFromFile(const std::string& path)
{
	std::ifstream in(path);
	std::string res, s;

	while (std::getline(in, s)) res += s + "\n";

	return move(res);
}

Image loadImage(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);

	int width = 0, height = 0, nrChannels = 0;
	unsigned char *data = stbi_load(&path[0], &width, &height, &nrChannels, 0);

	if (data == nullptr)
	{
		std::cerr << "ERROR::LOAD_IMAGE::LOAD_FAILED" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	std::vector<unsigned char> vector_data(width * height * nrChannels);

	std::copy(data, data + width * height * nrChannels, vector_data.begin());
	stbi_image_free(data);
	
	return Image(vector_data, width, height);
}