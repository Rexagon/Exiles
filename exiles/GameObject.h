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

	void SetActive(bool active) { m_isActive = active; }
	bool IsActive() const { return m_isActive; }

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() const { return m_name; }
private:
	friend class Model;

	GameObject* m_parent;
	std::vector<std::shared_ptr<GameObject>> m_children;

	bool m_isActive; // когда false у объекта не вызываются функции Update и Draw
	std::string m_name;

	mat4 m_globalTransformation;
};