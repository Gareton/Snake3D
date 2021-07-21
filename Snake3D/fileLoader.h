#ifndef FILE_LOADER_H
#define FILE_LOADER_H
#include <vector>
#include <string>
#include "skTypes.h"
#include "image.h"

namespace FLoader
{
	std::vector<sk_byte> loadRaw(const std::string& path);
	std::string loadText(const std::string& path);
	Image loadImage(const std::string& path, bool flip = true);
	std::vector<sk_float> loadFloats(const std::string& path);
}

#endif