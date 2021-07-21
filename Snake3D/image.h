#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include "skTypes.h"

class Image
{
public:
	Image(const Image& o) = default;
	Image& operator=(const Image& o) = default;
	Image(Image&& o);
	Image& operator=(Image&& o);

	Image(const std::vector<sk_byte> &data_, sk_uint width_, sk_uint height_, sk_uint channelsCount_ = 3);
	Image(const sk_uchar *data_, sk_uint width_, sk_uint height_, sk_uint channelsCount_ = 3);
	Image(std::vector<sk_byte> &&data_, sk_uint width_, sk_uint height_, sk_uint channelsCount_ = 3);

	void flip();

	const sk_byte* getDataPtr() const;
	sk_uint getWidth() const;
	sk_uint getHeight() const;
	sk_uint getChannelsCount() const;
private:
	std::vector<sk_byte> data;
	sk_uint width, height;
	sk_uint channelsCount;
};

#endif
