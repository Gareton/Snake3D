#include "vertexManager.h"
#include <numeric>

VertexManager::VertexManager()
{

}

void VertexManager::init(const std::vector<sk_float>& verticies, const std::vector<sk_uint>& indicies,
						 const std::vector<sk_uint>& attributeCounts)
{
	if (verticies.empty() || indicies.empty() || attributeCounts.empty())
		throw std::runtime_error("ERROR::GAME::VERTEX_MANAGER::INIT_FAILED");

	sk_uint vertexArrayID = 0;

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	sk_uint vertexBufferID = 0;

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(verticies[0]), &verticies[0], GL_STATIC_DRAW);

	sk_uint offset = 0;
	sk_uint stride = std::accumulate(attributeCounts.begin(), attributeCounts.end(), static_cast<sk_uint>(0));

	for (sk_uint i = 0; i < attributeCounts.size(); ++i)
	{
		sk_uint size = attributeCounts[i];

		glVertexAttribPointer(static_cast<sk_uint>(i),
			size,
			GL_FLOAT,
			GL_FALSE,
			stride * static_cast<sk_uint>(sizeof(sk_float)),
			reinterpret_cast<void *>(sizeof(sk_float) * static_cast<sk_uint>(offset)));
		glEnableVertexAttribArray(static_cast<sk_uint>(i));

		offset += size;
	}

	sk_uint elementBufferID = 0;

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