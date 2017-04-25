#pragma once

#include <typeindex>
#include <vector>
#include <memory>
#include <string>
#include <map>

#include "Transformable.h"
#include "Component.h"

class GameObject : public Transformable
{
public:
	GameObject(const std::string& name);
	~GameObject();

	// ���������� ������
	//@ ������������ ������ ������ ������, �.�. � ���� m_object=nullptr
	static std::shared_ptr<GameObject> MakeCopy(GameObject* object);

	// ��������� ������ ������
	virtual void Update(const float dt);

	// ��������� ���� ������ � �� ��� ���� �� ������
	void CascadeUpdate(const float dt);

	// ��������� ������� ������� � �������� �������
	//@ �������� ���������� ������� ��������� ��������
	void AddChild(std::shared_ptr<GameObject> node);

	// ���� ������ � ������ name ����� ������ �������� �������� �������
	//@ ���� �� ������ ������ � ����� name, ����� nullptr
	GameObject* GetChild(const std::string& name);

	// ���� ������ � ������ name ����� ���� �������� �������� �������
	//@ ���� �� ������ ������ � ����� name, ����� nullptr
	GameObject* FindChild(const std::string& name);

	// ����������� ������� ������� � ������ name
	//@ ������������ ������ ������ ������, �.�. � ���� m_object=nullptr
	//@ ���� �� ������ ������ � ����� name, ����� std::unique_ptr<GameObject>()
	std::shared_ptr<GameObject> DetachChild(const std::string& name);

	// ������ ��������� ��������� ���������� ���� � ��������� ��� � �������
	//@ � �������� ���������� ���������� ��������� ����������
	//@ ���� ��������� ������ ���� ��� ���� � �������, �� ����� ��� �����������
	template<class T, class ...Args>
	void AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "GameObject::AddComponent template argument must be the child of \"Component\" class");

		std::unique_ptr<T> component(new T(std::forward<Args>(args)...));
		dynamic_cast<Component*>(component.get())->SetOwner(this);
		m_components[std::type_index(typeid(T))] = std::move(component);
	}

	// ���������� ��������� �� ��������� ���������� ����
	//@ ���� � ������� ��� ������ ����������, ����� nullptr
	template<class T>
	T* GetComponent()
	{
		auto it = m_components.find(std::type_index(typeid(T)));
		if (it == m_components.end()) {
			return nullptr;
		}
		else {
			return dynamic_cast<T*>(it->second.get());
		}
	}

	// ��������� �� ������� ���������� ���������� ���� � �������
	template<class T>
	bool HasComponent()
	{
		return m_components.find(std::type_index(typeid(T))) != m_components.end();
	}

	void SetActive(bool active) { m_isActive = active; }
	bool IsActive() const { return m_isActive; }

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() const { return m_name; }

	void SetType(const std::string& type) { m_type = type; }
	std::string GetType() const { return m_type; }
protected:
	bool m_isActive; // ����� false � ������� �� ���������� ������� Update
	
	std::string m_name;
	std::string m_type;
	std::map<std::type_index, std::unique_ptr<Component>> m_components;

	GameObject* m_parent;
	std::vector<std::shared_ptr<GameObject>> m_children;

	mat4 m_globalTransformation;
};