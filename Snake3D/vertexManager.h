#ifndef VERTEX_MANAGER
#define VERTEX_MANAGER
#include <glad/glad.h>
#include <cmath>
#include <vector>
#include "skTypes.h"

class VertexManager 
{
public:
	VertexManager();
	VertexManager(VertexManager&& o);
	VertexManager(const VertexManager& o) = delete;
	VertexManager& operator=(const VertexManager& o) = delete;

	void init(const std::vector<sk_float>& verticies, const std::vector<sk_uint>& indicies,
			  const std::vector<sk_uint>& attributeCounts);

	void draw();
private:
	sk_uint _vertexArrayID;
	sk_uint _indiciesCount;
};


#endif
