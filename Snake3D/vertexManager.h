#ifndef VERTEX_MANAGER
#define VERTEX_MANAGER
#include <glad/glad.h>
#include <cmath>
#include <vector>

class VertexManager 
{
public:
	VertexManager();
	VertexManager(VertexManager&& o);
	VertexManager(const VertexManager& o) = delete;
	VertexManager& operator=(const VertexManager& o) = delete;

	void init(const std::vector<GLfloat>& verticies, const std::vector<GLuint>& indicies,
			  const std::vector<GLuint>& attributeCounts);

	void draw();
private:
	size_t _vertexArrayID;
	size_t _indiciesCount;
};


#endif
