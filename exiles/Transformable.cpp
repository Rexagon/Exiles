#include "Transformable.h"

#include <glm/gtx/matrix_decompose.hpp>

Transformable::Transformable() :
	m_hasChanged(true), m_transformation(1.0f), m_scaling(1.0f)
{
}

void Transformable::SetTransformation(const mat4 & transformation)
{
	m_transformation = transformation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformation, m_scaling, m_rotation, m_position, skew, perspective);
	m_rotation = glm::conjugate(m_rotation);
}

mat4 Transformable::GetTransformation()
{
	if (m_hasChanged) {
		mat4 translation = glm::translate(m_position);
		mat4 rotation = glm::toMat4(m_rotation);
		mat4 scaling = glm::scale(m_scaling);

		m_transformation = translation * rotation * scaling;
		m_hasChanged = false;
	}

	return m_transformation;
}



void Transformable::SetPosition(float x, float y, float z)
{
	m_hasChanged = true;
	m_position = vec3(x, y, z);
}

void Transformable::SetPosition(const vec3 & position)
{
	m_hasChanged = true;
	m_position = position;
}

void Transformable::Move(float x, float y, float z)
{
	m_hasChanged = true;
	m_position += vec3(x, y, z);
}

void Transformable::Move(const vec3 & vector)
{
	m_hasChanged = true;
	m_position += vector;
}

vec3 Transformable::GetPosition() const
{
	return m_position;
}



void Transformable::SetRotation(float x, float y, float z)
{
	m_hasChanged = true;
	m_rotation = quat(vec3(x, y, z));
}

void Transformable::SetRotation(const vec3 & eulerAngles)
{
	m_hasChanged = true;
	m_rotation = eulerAngles;
}

void Transformable::SetRotation(const quat & rotation)
{
	m_hasChanged = true;
	m_rotation = rotation;
}

void Transformable::Rotate(float x, float y, float z)
{
	m_hasChanged = true;
	m_rotation = quat(vec3(x, y, z)) * m_rotation;
}

void Transformable::Rotate(const vec3 & eulerAngles)
{
	m_hasChanged = true;
	m_rotation = quat(eulerAngles) * m_rotation;
}

void Transformable::Rotate(const quat & rotation)
{
	m_hasChanged = true;
	m_rotation = rotation * m_rotation;
}

quat Transformable::GetRotation() const
{
	return m_rotation;
}

vec3 Transformable::GetRotationEuler() const
{
	return glm::eulerAngles(m_rotation);
}



void Transformable::Scale(float s)
{
	m_hasChanged = true;
	m_scaling *= s;
}

void Transformable::Scale(float x, float y, float z)
{
	m_hasChanged = true;
	m_scaling *= vec3(x, y, z);
}

void Transformable::Scale(const vec3 & s)
{
	m_hasChanged = true;
	m_scaling *= s;
}

void Transformable::SetScaling(float s)
{
	m_hasChanged = true;
	m_scaling = vec3(s);
}

void Transformable::SetScaling(float x, float y, float z)
{
	m_hasChanged = true;
	m_scaling = vec3(x, y, z);
}

void Transformable::SetScaling(const vec3 & s)
{
	m_hasChanged = true;
	m_scaling = s;
}

vec3 Transformable::GetScaling() const
{
	return m_scaling;
}
