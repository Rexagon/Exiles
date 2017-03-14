#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Transformable.h"

#include "Shader.h"
//#include "Mesh.h"

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

	void SetActive(bool active) { m_isActive = active; }
	bool IsActive() const { return m_isActive; }

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() const { return m_name; }
private:
	friend class Model;

	GameObject* m_parent;
	std::vector<std::shared_ptr<GameObject>> m_children;

	bool m_isActive; // ����� false � ������� �� ���������� ������� Update � Draw
	std::string m_name;

	mat4 m_globalTransformation;
};