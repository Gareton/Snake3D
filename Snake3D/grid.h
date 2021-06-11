#ifndef GRID_H
#define GRID_H
#include "drawable.h"
#include "gmath.h"
#include "vertexManager.h"
#include "Shader.h"
#include "texture.h"
#include "skTypes.h"

class Grid : public Drawable
{
public:
	Grid(const gmt::vec3& position, sk_float cubeSize, 
		 sk_uint width, sk_uint height, sk_uint length, 
		 sk_float thickness, const gmt::vec4& color);

	void draw(const gmt::mat4& projection, const gmt::mat4& view) final;
	void update(sk_double deltaTime) final;

	sk_float getCubeSize() const;
	gmt::vec3i worldToGridCoordinateBruh(gmt::vec3 coord) const;
	gmt::vec3 gridToWorldCoordinateBruh(const gmt::vec3i& coord) const;
	gmt::vec3i worldToGridCoordinate(gmt::vec3 coord) const;
	gmt::vec3 gridToWorldCoordinate(const gmt::vec3i& coord) const;
	gmt::vec3 getOrigin() const;
	sk_uint getWidth() const;
	sk_uint getHeight() const;
	sk_uint getLength() const;
	bool isInside(const gmt::vec3i& coord) const;
private:
	void addLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addXLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addYLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addZLine(const gmt::vec3& p1, const gmt::vec3& p2);
	void addVertex(const gmt::vec3& p, const gmt::vec2& borderCoord);
	void addRectangle(const gmt::vec3& p1, const gmt::vec3& p2); // adds rectangle in a plane with diagonal points p1 and p2

	const gmt::vec3 _position;
	gmt::vec3 _centerPosition;
	const sk_float _cubeSize;
	const sk_uint _width;
	const sk_uint _height;
	const sk_uint _length;
	const sk_float _thickness;
	const sk_float _borderRatio = 0.4f;
	const gmt::vec4 _color;
	VertexManager _vertexManager;
	Shader _shader;
	std::vector<sk_float> _verticies;
	std::vector<sk_uint> _indicies;
};

#endif
