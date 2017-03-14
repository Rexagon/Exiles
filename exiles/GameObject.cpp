#include "GameObject.h"

#include <stack>

GameObject::GameObject(const std::string & name) :
	m_name(name), m_isActive(true), m_globalTransformation(GetTransformation()), m_parent(nullptr)
{
}

GameObject::~GameObject()
{
	m_children.clear();
}

std::shared_ptr<GameObject> GameObject::MakeCopy(GameObject * object)
{
	auto result = std::make_shared<GameObject>(object->m_name);

	result->m_parent = nullptr;
	//result->m_meshes = object->m_meshes;
	result->m_transformation = object->m_transformation;

	for (auto& child : object->m_children) {
		result->AddChild(MakeCopy(child.get()));
	}

	return std::move(result);
}

void GameObject::Update(const float dt)
{
}

void GameObject::CascadeUpdate(const float dt)
{
	std::stack<GameObject*> objects;
	objects.push(this);

	while (!objects.empty()) {
		auto object = objects.top();
		objects.pop();

		if (m_isActive) {
			object->Update(dt);
		}

		object->m_globalTransformation = object->GetTransformation();
		if (object->m_parent) {
			object->m_globalTransformation = object->m_parent->m_globalTransformation * object->m_globalTransformation;
		}

		for (auto& child : object->m_children) {
			objects.push(child.get());
		}
	}
}

void GameObject::AddChild(std::shared_ptr<GameObject> object)
{
	if (object->m_parent) {
		object = object->m_parent->DetachChild(object->m_name);
	}

	object->m_parent = this;
	m_children.push_back(std::move(object));
}

GameObject * GameObject::GetChild(const std::string & name)
{
	for (auto& child : m_children) {
		if (child->m_name == name) {
			return child.get();
		}
	}

	return nullptr;
}

GameObject * GameObject::FindChild(const std::string & name)
{
	std::stack<GameObject*> objects;
	objects.push(this);

	while (!objects.empty()) {
		GameObject* object = objects.top();
		objects.pop();

		for (unsigned int i = 0; i < object->m_children.size(); ++i) {
			if (object->m_children[i]->m_name == name) {
				return object->m_children[i].get();
			}
			else {
				objects.push(object->m_children[i].get());
			}
		}
	}

	return nullptr;
}

std::shared_ptr<GameObject> GameObject::DetachChild(const std::string & name)
{
	for (unsigned int i = 0; i < m_children.size(); ++i) {
		if (m_children[i]->m_name == name) {
			m_children[i]->m_parent = nullptr;

			auto tmp = std::move(m_children[i]);
			m_children.erase(m_children.begin() + i);
			return tmp;
		}
	}

	return std::shared_ptr<GameObject>();
}