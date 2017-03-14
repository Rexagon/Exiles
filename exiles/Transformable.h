#pragma once

#include "Math.h"

class Transformable
{
public:
	Transformable();

	// Восстанавливает позицию, поворот, растяжение из матрицы
	virtual void SetTransformation(const mat4& transformation);

	virtual mat4 GetTransformation();

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(const vec3& position);
	virtual void Move(float x, float y, float z);
	virtual void Move(const vec3& vector);
	vec3 GetPosition() const;

	virtual void SetRotation(float x, float y, float z);
	virtual void SetRotation(const vec3& eulerAngles);
	virtual void SetRotation(const quat& rotation);
	virtual void Rotate(float x, float y, float z);
	virtual void Rotate(const vec3& eulerAngles);
	virtual void Rotate(const quat& rotation);
	quat GetRotation() const { return m_rotation; }
	vec3 GetRotationEuler() const;

	virtual void Scale(float s);
	virtual void Scale(float x, float y, float z);
	virtual void Scale(const vec3& s);
	virtual void SetScaling(float s);
	virtual void SetScaling(float x, float y, float z);
	virtual void SetScaling(const vec3& s);
	vec3 GetScaling() const;
protected:
	bool m_hasChanged;

	vec3 m_position;
	quat m_rotation;
	vec3 m_scaling;

	mat4 m_transformation;
};