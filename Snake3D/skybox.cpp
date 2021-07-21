#include "skybox.h"

Skybox::Skybox(const std::string& path)
	: _vertexManager(FLoader::loadFloats("resources/skybox_verticies.txt"), {3}),
	  _shader(FLoader::loadText("shaders/skybox.vs"), FLoader::loadText("shaders/skybox.fs"))
{
	glGenTextures(1, &_texID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);

	auto faces = cutSkyboxImage(FLoader::loadImage(path, false));

	for (sk_uint i = 0; i < faces.size(); ++i)
	{
		GLenum format = GL_RGB;

		if (faces[i].getChannelsCount() == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, faces[i].getWidth(), faces[i].getHeight(), 0,
					 format, GL_UNSIGNED_BYTE, faces[i].getDataPtr());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::draw(const gmt::mat4& projection, const gmt::mat4& view) const
{
	glDepthMask(GL_FALSE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);

	_shader.use();

	_shader.setUniform("tex", sk_int(0));
	_shader.setUniform("proj", projection);
	_shader.setUniform("view", view);

	_vertexManager.draw();

	glDepthMask(GL_TRUE);
}

std::vector<Image> Skybox::cutSkyboxImage(const Image& skybox)
{
	std::vector<Image> faces;

	sk_uint faceWidth = skybox.getWidth() / 4;
	sk_uint faceHeight = skybox.getHeight() / 3;
	sk_uint faceChannels = skybox.getChannelsCount();

	std::vector<sk_uint> segInds = { 1, 4, 5, 6, 7, 9 };

	for (sk_uint i : segInds)
	{
		sk_uchar* data = new sk_uchar[faceWidth * faceHeight * faceChannels];
		sk_uint offset = i * faceWidth * faceHeight * faceChannels;

		for (sk_uint row = 0; row < faceHeight; ++row)
			for (sk_uint col = 0; col < faceWidth * faceChannels; ++col)
			{
				sk_uint offset = (i / 4) * faceHeight * skybox.getWidth() * faceChannels +
								 row * skybox.getWidth() * faceChannels + 
								 (i % 4) * faceWidth * faceChannels + col;

				sk_uint ind = row * faceWidth * faceChannels + col;
				data[ind] = skybox.getDataPtr()[offset];
			}

		faces.push_back(Image(data, faceWidth, faceHeight, faceChannels));

		delete[] data;
	}

	std::swap(faces[0], faces[3]);
	std::swap(faces[2], faces[3]);
	std::swap(faces[3], faces[5]);
	std::swap(faces[4], faces[5]);

	return std::move(faces);
}