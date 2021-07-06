#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>
#include "gmath.h"
#include "skTypes.h"

namespace bge
{
	// TODO: add to some of setUnifrom proper suffixies  

	class Shader {
	public:
		Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept;
		~Shader() noexcept;
		Shader(const Shader& o) = delete;
		Shader& operator=(const Shader& o) = delete;
		void use() const;
		void setUniform(const std::string& name, const gmt::vec2& v) const;
		void setUniform(const std::string& name, const gmt::vec3& v) const;
		void setUniform(const std::string& name, const gmt::vec4& v) const;
		void setUniform(const std::string& name, const gmt::mat2& m) const;
		void setUniform(const std::string& name, const gmt::mat3& m) const;
		void setUniform(const std::string& name, const gmt::mat4& m) const;
		void setUniform(const std::string& name, sk_float x) const;
		void setUniform(const std::string& name, sk_uint x) const;
		bool isValid() const;
	private:
		bool genShader(sk_uint& id, GLenum type, const std::string& source);
		sk_uint genVertexShader(const std::string& source);
		sk_uint genFragmentShader(const std::string& source);
		void checkInvalidity() const;

		static const sk_uint _errorMessageSize = 512;

		sk_uint _programId;

		bool _isValid = true;
		std::string _errorMessage = std::string(_errorMessageSize, '#');
	};
}

#endif
