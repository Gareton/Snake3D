#ifndef FILE_LOADER_H
#define FILE_LOADER_H
#include <string>
#include <vector>

struct Image
{
	Image(const std::vector<unsigned char> &data_, size_t width_, size_t height_, 
		  size_t _channelsCount = 3);
	Image(const unsigned char *data_, size_t width_, size_t height_, 
		  size_t _channelsCount = 3);
	Image(std::vector<unsigned char> &&data_, size_t width_, size_t height_, 
		  size_t _channelsCount = 3);

	std::vector<unsigned char> data;
	size_t width, height;
	size_t channelsCount;
};

std::string loadFromFile(const std::string& path);
Image loadImage(const std::string& path);

#endif
