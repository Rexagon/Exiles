#pragma once

#include "Math.h"

class Vertex
{
public:
	Vertex(const vec3& position, const vec2& texcoords = vec2(), 
		   const vec3& normal = vec3(), const vec3& tangent = vec3()) :
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