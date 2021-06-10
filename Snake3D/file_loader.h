#ifndef FILE_LOADER_H
#define FILE_LOADER_H
#include <string>
#include <vector>
#include "skTypes.h"

struct Image
{
	Image(const std::vector<sk_uchar> &data_, sk_uint width_, sk_uint height_, 
		  sk_uint _channelsCount = 3);
	Image(const sk_uchar *data_, sk_uint width_, sk_uint height_, 
		  sk_uint _channelsCount = 3);
	Image(std::vector<sk_uchar> &&data_, sk_uint width_, sk_uint height_, 
		  sk_uint _channelsCount = 3);

	std::vector<sk_uchar> data;
	sk_uint width, height;
	sk_uint channelsCount;
};

std::string loadFromFile(const std::string& path);
Image loadImage(const std::string& path);

#endif
