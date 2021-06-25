#include "image.h"

Image::Image(Image&& o)
{
	if (&o == this)
		return;

	data = std::move(o.data);
	width = o.width;
	height = o.height;
	channelsCount = o.channelsCount;
}

Image& Image::operator=(Image&& o)
{
	if (&o == this)
		return *this;

	data = std::move(o.data);
	width = o.width;
	height = o.height;
	channelsCount = o.channelsCount;

	return *this;
}

Image::Image(const std::vector<sk_uchar> &data_, sk_uint width_, sk_uint height_, sk_uint channelsCount_)
	: data(data_), width(width_), height(height_), channelsCount(channelsCount_)
{}

Image::Image(const sk_uchar *data_, sk_uint width_, sk_uint height_, sk_uint channelsCount_)
	: width(width_), height(height_), channelsCount(channelsCount_)
{
	if (width * height * channelsCount != 0)
		data.resize(width * height * channelsCount);

	for (sk_uint i = 0; i < data.size(); ++i)
		data[i] = data_[i];
}

Image::Image(std::vector<sk_uchar> &&data_, sk_uint width_, sk_uint height_, sk_uint channelsCount_)
	: data(data_), width(width_), height(height_), channelsCount(channelsCount_)
{}

const sk_byte* Image::getDataPtr() const
{
	if (data.empty()) return nullptr;

	return &data[0];
}

sk_uint Image::getWidth() const
{
	return width;
}

sk_uint Image::getHeight() const
{
	return height;
}

sk_uint Image::getChannelsCount() const
{
	return channelsCount;
}