#include "shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "file_loader.h"
#include "skTypes.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	_programId = glCreateProgram();
	sk_uint vertexShader = genVertexShader(loadFromFile(vertexShaderPath));
	sk_uint fragmentShader = genFragmentShader(loadFromFile(fragmentShaderPath));

	glAttachShader(_programId, vertexShader);
	glAttachShader(_programId, fragmentShader);
	glLinkProgram(_programId);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	sk_int success = 0;

	glGetProgramiv(_programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(_programId, _infoLogSize, NULL, _infoLog);
		std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED" << std::endl;
		std::cerr << _infoLog << std::endl;
		glfwTerminate();
		exit(-1);
	}
}

void Shader::use() const
{
	glUseProgram(_programId);
}

void Shader::setUniform(const std::string& name, const gmt::vec2& v) const
{
	glUniform2f(glGetUniformLocation(_programId, &name[0]), v.x, v.y);
}

void Shader::setUniform(const std::string& name, const gmt::vec3& v) const
{
	glUniform3f(glGetUniformLocation(_programId, &name[0]), v.x, v.y, v.z);
}

void Shader::setUniform(const std::string& name, const gmt::vec4& v) const
{
	glUniform4f(glGetUniformLocation(_programId, &name[0]), v.x, v.y, v.z, v.w);
}

void Shader::setUniform(const std::string& name, sk_float x) const
{
	glUniform1f(glGetUniformLocation(_programId, &name[0]), x);
}

void Shader::setUniform(const std::string& name, sk_uint x) const
{
	glUniform1i(glGetUniformLocation(_programId, &name[0]), x);
}

void Shader::setUniform(const std::string& name, const gmt::mat2& m) const
{
	glUniformMatrix2fv(glGetUniformLocation(_programId, &name[0]), 
					   1, GL_TRUE, &(m[0][0]));
}

void Shader::setUniform(const std::string& name, const gmt::mat3& m) const
{
	glUniformMatrix3fv(glGetUniformLocation(_programId, &name[0]),
		1, GL_TRUE, &(m[0][0]));
}

void Shader::setUniform(const std::string& name, const gmt::mat4& m) const
{
	glUniformMatrix4fv(glGetUniformLocation(_programId, &name[0]),
		1, GL_TRUE, &(m[0][0]));
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
		glGetShaderInfoLog(id, _infoLogSize, NULL, _infoLog);
		return false;
	}

	return true;
}

sk_uint Shader::genVertexShader(const std::string& source)
{
	sk_uint id = 0;
	
	if (!genShader(id, GL_VERTEX_SHADER, source))
	{
		std::cerr << "ERROR::SHADER::VERTEX" << std::endl;
		std::cerr << _infoLog << std::endl;
		glfwTerminate();
		exit(-1);
	}

	return id;
}

sk_uint Shader::genFragmentShader(const std::string& source)
{
	sk_uint id = 0;

	if (!genShader(id, GL_FRAGMENT_SHADER, source))
	{
		std::cerr << "ERROR::FRAGMENT::VERTEX" << std::endl;
		std::cerr << _infoLog << std::endl;
		glfwTerminate();
		exit(-1);
	}

	return id;
}