#pragma once

class GameObject;

class Component
{
public:
	Component() : m_owner(nullptr) {}
	virtual ~Component() {}

	void SetOwner(GameObject* object) { m_owner = object; }
	GameObject* GetOwner() { return m_owner; }
private:
	GameObject* m_owner;
};