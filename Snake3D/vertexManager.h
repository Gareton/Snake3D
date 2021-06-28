#ifndef VERTEX_MANAGER
#define VERTEX_MANAGER
#include <glad/glad.h>
#include <cmath>
#include <vector>
#include "skTypes.h"

namespace bge
{
	// TODO: improve
	class VertexManager
	{
	public:
		VertexManager(const std::vector<sk_float>& verticies, const std::vector<sk_uint>& attributeCounts, 
					  const std::vector<sk_uint>& indicies = {});
		~VertexManager();
		VertexManager(VertexManager&& o);
		VertexManager(const VertexManager& o) = delete;
		VertexManager& operator=(const VertexManager& o) = delete;

		void draw();

		bool isValid() const;
	private:
		sk_uint _vertexArrayID;
		sk_uint _arrayBufferID;
		sk_uint _elementBufferID;
		sk_uint _indiciesCount;
		sk_uint _verticiesCount;
		bool _isValid = true;

		static const std::string _errorMessage;  
	};

}

#endif
