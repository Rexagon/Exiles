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

	// Репликация дерева
	//@ возвращаемый объект станет корнем, т.е. у него m_object=nullptr
	static std::shared_ptr<GameObject> MakeCopy(GameObject* object);

	// Обновляет текуий объект
	virtual void Update(const float dt);

	// Обновляет этот объект и всё что ниже по дереву
	void CascadeUpdate(const float dt);

	// Добавляет прямого потомка к текущему объекту
	//@ владение переданным объеком передаётся текущему
	void AddChild(std::shared_ptr<GameObject> node);

	// Ищет объект с именем name среди прямых потомков текущего объекта
	//@ если не найден объект с менем name, вернёт nullptr
	GameObject* GetChild(const std::string& name);

	// Ищет объект с именем name сдели всех потомков текущего объекта
	//@ если не найден объект с менем name, вернёт nullptr
	GameObject* FindChild(const std::string& name);

	// Отсоединяет прямого потомка с именем name
	//@ возвращаемый объект станет корнем, т.е. у него m_object=nullptr
	//@ если не найден объект с менем name, вернёт std::unique_ptr<GameObject>()
	std::shared_ptr<GameObject> DetachChild(const std::string& name);

	// Создаёт компонент компонент указанного типа и добавляет его к объекту
	//@ в качестве параметров передаются параметры компонента
	//@ если компонент такого типа уже есть у объекта, то новый его перезапишет
	template<class T, class ...Args>
	void AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "GameObject::AddComponent template argument must be the child of \"Component\" class");

		std::unique_ptr<T> component(new T(std::forward<Args>(args)...));
		dynamic_cast<Component*>(component.get())->SetOwner(this);
		m_components[std::type_index(typeid(T))] = std::move(component);
	}

	// Возвращает указатель на компонент указанного типа
	//@ если у объекта нет такого компонента, вернёт nullptr
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

	// Проверяет на наличие компонента указанного типа у объекта
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
	bool m_isActive; // когда false у объекта не вызывается функция Update
	
	std::string m_name;
	std::string m_type;
	std::map<std::type_index, std::unique_ptr<Component>> m_components;

	GameObject* m_parent;
	std::vector<std::shared_ptr<GameObject>> m_children;

	mat4 m_globalTransformation;
};