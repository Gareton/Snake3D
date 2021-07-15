#include "straightParallelepiped.h"
#include "fileLoader.h"

namespace bge
{

	StraightParallelepiped::StraightParallelepiped(const gmt::vec3& size, const gmt::vec3& pos, const gmt::vec3& color)
		:_shader(FLoader::loadText("shaders/straightParallelepipedShader.vs"),
			FLoader::loadText("shaders/straightParallelepipedShader.fs")),
		_pos(pos), _color(color), _size(size)
	{

		std::vector<sk_float> verticies = {
			//front
				-0.5f, -0.5f, 0.5f,
				-0.5f,  0.5f, 0.5f,
				 0.5f,  0.5f, 0.5f,
				 0.5f, -0.5f, 0.5f,

				 //right
					  0.5f, -0.5f,  0.5f,
					  0.5f,  0.5f,  0.5f,
					  0.5f,  0.5f, -0.5f,
					  0.5f, -0.5f, -0.5f,

					  //left
						  -0.5f, -0.5f,  0.5f,
						  -0.5f, -0.5f, -0.5f,
						  -0.5f,  0.5f, -0.5f,
						  -0.5f,  0.5f,  0.5f,

						  //bottom
							  -0.5f, -0.5f,  0.5f,
							  -0.5f, -0.5f, -0.5f,
							   0.5f, -0.5f, -0.5f,
							   0.5f, -0.5f,  0.5f,

							   //top
								   -0.5f, 0.5f,  0.5f,
								   -0.5f, 0.5f, -0.5f,
									0.5f, 0.5f, -0.5f,
									0.5f, 0.5f,  0.5f,

									//back
										-0.5f, -0.5f, -0.5f,
										 0.5f, -0.5f, -0.5f,
										 0.5f,  0.5f, -0.5f,
										-0.5f,  0.5f, -0.5f
		};

		std::vector<sk_uint> indicies = { 0, 1, 2, 2, 3, 0 };

		for (sk_uint i = 0; i < 5; ++i)
			for (sk_uint j = 0; j < 6; ++j)
				indicies.push_back(indicies[j] + (i + 1) * 4);

		_vertexManager.reset(new bge::VertexManager(verticies, { 3 }, indicies));
	}

	void StraightParallelepiped::draw(const gmt::mat4& projection, const gmt::mat4& view) const
	{
		gmt::mat4 model = gmt::translate(_pos) * gmt::scale(_size);

		_shader.use();

		_shader.setUniform("model", model);
		_shader.setUniform("view", view);
		_shader.setUniform("proj", projection);

		_shader.setUniform("color", _color);

		_vertexManager->draw();
	}

	void StraightParallelepiped::setPos(const gmt::vec3& pos)
	{
		_pos = pos;
	}

	void StraightParallelepiped::setColor(const gmt::vec3& color)
	{
		_color = color;
	}

	void StraightParallelepiped::setSize(const gmt::vec3& size)
	{
		_size = size;
	}

	gmt::vec3 StraightParallelepiped::getSize() const
	{
		return _size;
	}
}