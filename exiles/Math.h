#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

using vec2 = glm::vec2;
using ivec2 = glm::ivec2;
using uvec2 = glm::uvec2;

using vec3 = glm::vec3;
using ivec3 = glm::ivec3;
using uvec3 = glm::uvec3;

using vec4 = glm::vec4;
using ivec4 = glm::ivec4;
using uvec4 = glm::uvec4;

using mat4 = glm::mat4;

using quat = glm::quat;

template<class T>
struct _rect
{
	typedef glm::tvec2<T, glm::packed_highp> vec_type;

	_rect() :
		x(0), y(0), width(0), height(0) {}

	_rect(T x, T y, T width, T height) :
		x(x), y(y), width(width), height(height) {}

	_rect(const vec_type& position, const vec_type& size) :
		x(position.x), y(position.y), width(size.x), height(size.y) {}

	bool Contains(T px, T py)
	{
		T minX = std::min(x, static_cast<T>(x + width));
		T maxX = std::max(x, static_cast<T>(x + width));
		T minY = std::min(y, static_cast<T>(y + height));
		T maxY = std::max(y, static_cast<T>(y + height));

		return (px >= minX) && (px < maxX) && (py >= minY) && (py < maxY);
	}

	bool Contains(const vec_type& point)
	{
		return Contains(point.x, point.y);
	}

	bool Intersects(const _rect& rectangle, _rect& intersection) const
	{
		T r1MinX = std::min(x, static_cast<T>(x + width));
		T r1MaxX = std::max(x, static_cast<T>(x + width));
		T r1MinY = std::min(y, static_cast<T>(y + height));
		T r1MaxY = std::max(y, static_cast<T>(y + height));

		T r2MinX = std::min(rectangle.x, static_cast<T>(rectangle.x + rectangle.width));
		T r2MaxX = std::max(rectangle.x, static_cast<T>(rectangle.x + rectangle.width));
		T r2MinY = std::min(rectangle.y, static_cast<T>(rectangle.y + rectangle.height));
		T r2MaxY = std::max(rectangle.y, static_cast<T>(rectangle.y + rectangle.height));

		T interLeft = std::max(r1MinX, r2MinX);
		T interTop = std::max(r1MinY, r2MinY);
		T interRight = std::min(r1MaxX, r2MaxX);
		T interBottom = std::min(r1MaxY, r2MaxY);

		if ((interLeft < interRight) && (interTop < interBottom)) {
			intersection = _rect(interLeft, interTop, interRight - interLeft, interBottom - interTop);
			return true;
		}
		else {
			intersection = _rect();
			return false;
		}
	}

	bool Intersects(const _rect& rectangle) const
	{
		_rect intersection;
		return intersects(rectangle, intersection);
	}

	void SetPosition(const vec_type& position)
	{
		x = position.x;
		y = position.y;
	}

	vec_type GetPosition() const
	{
		return vec_type(x, y);
	}

	void SetSize(const vec_type& size)
	{
		width = size.x;
		height = size.y;
	}

	vec_type GetSize() const
	{
		return vec_type(width, height);
	}

	bool operator==(const _rect& right)
	{
		return x == right.x && y == right.y && width == right.width && height == right.height;
	}

	bool operator!=(const _rect& right)
	{
		return !((*this) == right);
	}

	T x;
	T y;
	T width;
	T height;
};

typedef _rect<float> rect;
typedef _rect<int> irect;
typedef _rect<unsigned int> urect;