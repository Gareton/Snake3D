#ifndef STRAIGHT_PARALLELEPIPED_H
#define STRAIGHT_PARALLELEPIPED_H
#include "drawable.h"
#include "shader.h"
#include "vertexManager.h"
#include "skTypes.h"
#include <memory>

namespace bge
{
	class StraightParallelepiped : public Drawable
	{
	public:
		explicit StraightParallelepiped(const gmt::vec3& size, const gmt::vec3& pos = {}, const gmt::vec3& color = {});

		void draw(const gmt::mat4& projection, const gmt::mat4& view) const override;

		void setSize(const gmt::vec3& size);
		void setPos(const gmt::vec3& pos);
		void setColor(const gmt::vec3& color);

		void applyTransform(const gmt::mat4& tform);

		gmt::vec3 getSize() const;
	private:
		std::unique_ptr<bge::VertexManager> _vertexManager;
		bge::Shader _shader;
		gmt::vec3 _pos;
		gmt::vec3 _color;
		gmt::vec3 _size;
		gmt::mat4 _tform;
	};
}

#endif
