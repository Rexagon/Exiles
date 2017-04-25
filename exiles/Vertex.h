#pragma once

#include "Math.h"

class Vertex
{
public:
	Vertex(const vec3& position, const vec2& texcoords, const vec3& normal, const vec3& tangent) :
		position(position), texcoords(texcoords), normal(normal), tangent(tangent) {}

	vec3 position;
	vec2 texcoords;
	vec3 normal;
	vec3 tangent;
};

class VertexBoneData
{
public:
	VertexBoneData(const vec4& weights, const ivec4& indices) :
		weights(weights), indices(indices) {}

	vec4 weights;
	ivec4 indices;
};