#include "shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include "skTypes.h"

namespace bge
{
	Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept
	{
		_programId = glCreateProgram();
		sk_uint vertexShader = genVertexShader(vertexShaderSource);

		if (!_isValid) return;

		sk_uint fragmentShader = genFragmentShader(fragmentShaderSource);

		if (!_isValid) return;

		glAttachShader(_programId, vertexShader);
		glAttachShader(_programId, fragmentShader);
		glLinkProgram(_programId);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		sk_int success = 0;

		glGetProgramiv(_programId, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(_programId, _errorMessageSize, NULL, &_errorMessage[0]);
			_isValid = false;
		}
	}

	Shader::~Shader() noexcept
	{
		if(_isValid)
			glDeleteProgram(_programId);
	}

	void Shader::use() const
	{
		checkInvalidity();
		glUseProgram(_programId);
	}

	void Shader::setUniform(const std::string& name, const gmt::vec2& v) const
	{
		checkInvalidity();
		glUniform2f(glGetUniformLocation(_programId, &name[0]), v.x, v.y);
	}

	void Shader::setUniform(const std::string& name, const gmt::vec3& v) const
	{
		checkInvalidity();
		glUniform3f(glGetUniformLocation(_programId, &name[0]), v.x, v.y, v.z);
	}

	void Shader::setUniform(const std::string& name, const gmt::vec4& v) const
	{
		checkInvalidity();
		glUniform4f(glGetUniformLocation(_programId, &name[0]), v.x, v.y, v.z, v.w);
	}

	void Shader::setUniform(const std::string& name, sk_float x) const
	{
		checkInvalidity();
		glUniform1f(glGetUniformLocation(_programId, &name[0]), x);
	}

	void Shader::setUniform(const std::string& name, sk_uint x) const
	{
		checkInvalidity();
		glUniform1i(glGetUniformLocation(_programId, &name[0]), x);
	}

	void Shader::setUniform(const std::string& name, const gmt::mat2& m) const
	{
		checkInvalidity();
		glUniformMatrix2fv(glGetUniformLocation(_programId, &name[0]),
			1, GL_TRUE, gmt::valuePtr(m));
	}

	void Shader::setUniform(const std::string& name, const gmt::mat3& m) const
	{
		checkInvalidity();
		glUniformMatrix3fv(glGetUniformLocation(_programId, &name[0]),
			1, GL_TRUE, gmt::valuePtr(m));
	}

	void Shader::setUniform(const std::string& name, const gmt::mat4& m) const
	{
		checkInvalidity();
		glUniformMatrix4fv(glGetUniformLocation(_programId, &name[0]),
			1, GL_TRUE, gmt::valuePtr(m));
	}

	bool Shader::isValid() const
	{
		return _isValid;
	}

	bool Shader::genShader(sk_uint& id, GLenum type, const std::string& source)
	{
		id = glCreateShader(type);

		const sk_char *buf = &source[0];

		glShaderSource(id, 1, &buf, NULL);
		glCompileShader(id);

		sk_int success = 0;

		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(id, _errorMessageSize, NULL, &_errorMessage[0]);
			_isValid = false;
			return false;
		}

		return true;
	}

	sk_uint Shader::genVertexShader(const std::string& source)
	{
		sk_uint id = 0;

		genShader(id, GL_VERTEX_SHADER, source);

		return id;
	}

	sk_uint Shader::genFragmentShader(const std::string& source)
	{
		sk_uint id = 0;

		genShader(id, GL_FRAGMENT_SHADER, source);

		return id;
	}

	void Shader::checkInvalidity() const
	{
		if (!_isValid)
			throw std::invalid_argument(_errorMessage);
	}
}