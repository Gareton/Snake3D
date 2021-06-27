#include "vertexManager.h"
#include <numeric>

namespace bge
{
	const std::string VertexManager::_errorMessage = "ERROR::INVALID_VERTEX_MANAGER";

	VertexManager::VertexManager(const std::vector<sk_float>& verticies, const std::vector<sk_uint>& attributeCounts,
								 const std::vector<sk_uint>& indicies)
		: _indiciesCount(indicies.size()), _verticiesCount(verticies.size())
	{
		if (verticies.empty() || attributeCounts.empty())
		{
			_isValid = false;
			return;
		}

		glGenVertexArrays(1, &_vertexArrayID);
		glBindVertexArray(_vertexArrayID);

		glGenBuffers(1, &_arrayBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _arrayBufferID);
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
				reinterpret_cast<void *>(sizeof(sk_float) * offset));

			glEnableVertexAttribArray(i);

			offset += size;
		}


		if (!indicies.empty())
		{
			glGenBuffers(1, &_elementBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(indicies[0]), &indicies[0], GL_STATIC_DRAW);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	VertexManager::~VertexManager()
	{
		if (!_vertexArrayID)
			return;

		GLint currentVertexArrayID = 0;
		GLint currentArrayBufferID = 0;
		GLint currentElementBufferID = 0;

		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVertexArrayID);
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentArrayBufferID);
		glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentElementBufferID);

		if (currentVertexArrayID == _vertexArrayID)
			glBindVertexArray(0);

		if (currentArrayBufferID == _arrayBufferID)
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (currentElementBufferID == _elementBufferID)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDeleteVertexArrays(1, &_vertexArrayID);
		glDeleteBuffers(1, &_arrayBufferID);

		if(_elementBufferID)
			glDeleteBuffers(1, &_elementBufferID);
	}

	VertexManager::VertexManager(VertexManager&& o)
	{
		_vertexArrayID = o._vertexArrayID;
		_arrayBufferID = o._arrayBufferID;
		_elementBufferID = o._elementBufferID;
		_indiciesCount = o._indiciesCount;
		_verticiesCount = o._verticiesCount;
		_isValid = o._isValid;

		o._vertexArrayID = 0;
	}

	void VertexManager::draw()
	{
		if (!_isValid) throw std::invalid_argument(_errorMessage);

		glBindVertexArray(_vertexArrayID);

		if (_indiciesCount)
			glDrawElements(GL_TRIANGLES, _indiciesCount, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, _verticiesCount);
		glBindVertexArray(0);
	}

	bool VertexManager::isValid() const
	{
		return _isValid;
	}
}