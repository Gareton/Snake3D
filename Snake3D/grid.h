#ifndef GRID_H
#define GRID_H
#include "drawable.h"
#include "gmath.h"
#include "vertexManager.h"
#include "Shader.h"
#include "texture.h"

class Grid : public Drawable
{
public:
	Grid(const gmt::vec3& position, float_t cubeSize, 
		 size_t width, size_t height, size_t length, 
		 float_t thickness, const gmt::vec4& color);

	void draw(const gmt::mat4& projection, const gmt::mat4& view) final;
	void update(double_t deltaTime) final;

	float_t getCubeSize() const;
	gmt::vec3i worldToGridCoordinate(gmt::vec3 coord) const;
	gmt::vec3 gridToWorldCoordinate(const gmt::vec3i& coord) const;
	gmt::vec3 getOrigin() const;
	float_t getWidth() const;
	float_t getHeight() const;
	float_t getLength() const;
	bool isInside(const gmt::vec3i& coord) const;
private:
	void addLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addXLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addYLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addZLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addVertex(const gmt::vec3& p, const gmt::vec2& borderCoord, float_t ratio);
	void addRectangle(const gmt::vec3& p1, const gmt::vec3& p2); // adds rectangle in a plane with opposing points p1 and p2

	const gmt::vec3 _position;
	gmt::vec3 _centerPosition;
	const float_t _cubeSize;
	const size_t _width;
	const size_t _height;
	const size_t _length;
	const float_t _thickness;
	const gmt::vec4 _color;
	VertexManager _vertexManager;
	Shader _shader;
	std::vector<GLfloat> _verticies;
	std::vector<GLuint> _indicies;
};

#endif
