#include "fileLoader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "stb_image.h"
#include <stdexcept>
#include <GLFW/glfw3.h>

namespace FLoader
{
	// TODO: process errors
	// TODO: optimize
	std::vector<sk_byte> loadRaw(const std::string& path) 
	{
		std::ifstream in(path);
		std::string res, s;

		while (std::getline(in, s)) res += s + "\n";

		std::vector<sk_byte> rval;
		rval.reserve(res.size());

		for (char c : res)
			rval.push_back(static_cast<sk_byte>(c));
			
		return std::move(rval);
	}

	std::string loadText(const std::string& path)
	{
		std::ifstream in(path);
		std::string res, s;

		while (std::getline(in, s)) res += s + "\n";

		return std::move(res);
	}

	Image loadImage(const std::string& path, bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);

		int width = 0, height = 0, nrChannels = 0;
		sk_uchar *data = stbi_load(&path[0], &width, &height, &nrChannels, 0);

		if(data == nullptr)
			throw std::runtime_error("ERROR::FLOADER::LOAD_IMAGE::LOAD_FAILED");

		std::vector<sk_uchar> vector_data(width * height * nrChannels);

		std::copy(data, data + width * height * nrChannels, vector_data.begin());
		stbi_image_free(data);

		return Image(vector_data, width, height, nrChannels);
	}

	std::vector<sk_float> loadFloats(const std::string& path)
	{
		std::vector<sk_float> rval;
		std::ifstream in(path);
		sk_float curFloat = 0.0f;

		while (in >> curFloat) rval.push_back(curFloat);

		return std::move(rval);
	}
}