#include "straightParallelepiped.h"

StraightParallelepiped::StraightParallelepiped(const gmt::vec3& size, const gmt::vec3& position,
											   const gmt::vec4& color)
	:_shader("shaders/straightParallelepipedShader.vs", "shaders/straightParallelepipedShader.fs"),
	 _position(position), _color(color), _size(size)
{
	GLfloat hx = 0.5f;
	GLfloat hy = 0.5f;
	GLfloat hz = 0.5f;

	std::vector<GLfloat> verticies = {
		//front

		-hx, -hy, hz,
		-hx,  hy, hz,
		 hx,  hy, hz,
		 hx, -hy, hz,

		 //right

		 hx, -hy,  hz,
		 hx,  hy,  hz,
		 hx,  hy, -hz,
		 hx, -hy, -hz,

		 //left

		 -hx, -hy,  hz,
		 -hx, -hy, -hz,
		 -hx,  hy, -hz,
		 -hx,  hy,  hz,

		 //bottom

		 -hx, -hy,  hz,
		 -hx, -hy, -hz,
		  hx, -hy, -hz,
		  hx, -hy,  hz,

		  //top

		   -hx, hy,  hz,
		   -hx, hy, -hz,
			hx, hy, -hz,
			hx, hy,  hz,

			//back

			-hx, -hy, -hz,
			 hx, -hy, -hz,
			 hx,  hy, -hz,
			-hx,  hy, -hz
	};

	std::vector<GLuint> indicies = { 0, 1, 2, 2, 3, 0 };

	for (size_t i = 0; i < 5; ++i)
		for (size_t j = 0; j < 6; ++j)
			indicies.push_back(indicies[j] + (i + 1) * 4);

	std::vector<GLuint> attributeCounts = { 3 };

	_vertexManager.init(verticies, indicies, attributeCounts);
}

void StraightParallelepiped::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	_shader.use();

	gmt::mat4 model = gmt::translate(_position) * gmt::scale(_size);

	_shader.setUniform("model", model);
	_shader.setUniform("view", view);
	_shader.setUniform("proj", projection);

	_shader.setUniform("color", _color);

	_vertexManager.draw();
}

void StraightParallelepiped::update(double_t deltaTime)
{

}

void StraightParallelepiped::setPosition(const gmt::vec3& position)
{
	_position = position;
}

void StraightParallelepiped::resize(const gmt::vec3& size)
{
	_size = size;
}