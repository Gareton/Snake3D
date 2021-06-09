#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>
#include "gmath.h"


class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	Shader(const Shader& o) = delete;
	Shader& operator=(const Shader& o) = delete;
	void use() const;
	void setUniform(const std::string& name, const gmt::vec2& v) const;
	void setUniform(const std::string& name, const gmt::vec3& v) const;
	void setUniform(const std::string& name, const gmt::vec4& v) const;
	void setUniform(const std::string& name, GLfloat x) const;
	void setUniform(const std::string& name, GLuint x) const;
	void setUniform(const std::string& name, const gmt::mat2& m) const;
	void setUniform(const std::string& name, const gmt::mat3& m) const;
	void setUniform(const std::string& name, const gmt::mat4& m) const;
private:
	bool genShader(GLuint& id, GLenum type, const std::string& source);
	GLuint genVertexShader(const std::string& source);
	GLuint genFragmentShader(const std::string& source);

	static const GLuint _infoLogSize = 512;

	GLuint _programId;
	GLchar _infoLog[_infoLogSize];
};

#endif
