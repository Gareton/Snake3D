#include "vertexManager.h"
#include <numeric>

VertexManager::VertexManager()
{

}

void VertexManager::init(const std::vector<GLfloat>& verticies, const std::vector<GLuint>& indicies,
						 const std::vector<GLuint>& attributeCounts)
{
	if (verticies.empty() || indicies.empty() || attributeCounts.empty())
		throw std::runtime_error("ERROR::GAME::VERTEX_MANAGER::INIT_FAILED");

	GLuint vertexArrayID = 0;

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	GLuint vertexBufferID = 0;

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(verticies[0]), &verticies[0], GL_STATIC_DRAW);

	GLuint offset = 0;
	GLuint stride = std::accumulate(attributeCounts.begin(), attributeCounts.end(), static_cast<size_t>(0));

	for (size_t i = 0; i < attributeCounts.size(); ++i)
	{
		GLuint size = attributeCounts[i];

		glVertexAttribPointer(static_cast<GLuint>(i),
			size,
			GL_FLOAT,
			GL_FALSE,
			stride * static_cast<GLuint>(sizeof(GLfloat)),
			reinterpret_cast<void *>(sizeof(GLfloat) * static_cast<size_t>(offset)));
		glEnableVertexAttribArray(static_cast<GLuint>(i));

		offset += size;
	}

	GLuint elementBufferID = 0;

	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(indicies[0]), &indicies[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	_vertexArrayID = vertexArrayID;
	_indiciesCount = indicies.size();
}

VertexManager::VertexManager(VertexManager&& o)
{
	_vertexArrayID = o._vertexArrayID;
	_indiciesCount = o._indiciesCount;
	o._vertexArrayID = 0;
	o._indiciesCount = 0;
}

void VertexManager::draw()
{
	glBindVertexArray(_vertexArrayID);
	glDrawElements(GL_TRIANGLES, _indiciesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}