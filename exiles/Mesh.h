#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

#include "Material.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh(const std::string& name = std::string());
	~Mesh();

	// Инициализирует буфферы вершин
	//@ необходимо вызвать до отрисовки геометрии
	void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	// Инициализирует буфферы костей
	//@ необходимо вызвать если модель анимированная
	void InitBoneData(const std::vector<VertexBoneData>& boneData);

	// Рисует геометрию
	//@ также перед отрисовкой биндит материал начиная с 1й позиции
	void Draw();

	// Устанавливает материал, который будет биндится перед отрисовкой
	void SetMaterial(material_ptr material) { m_material = material; }

	material_ptr GetMaterial() { return m_material; }

	std::string GetName() const { return m_name; }
private:
	std::string m_name;

	GLuint m_VAO;

	// Буфферы для вершин
	GLuint m_VBO;
	GLuint m_EBO;

	// Буфферы для костей
	GLuint m_BBO;

	unsigned int m_numIndices;

	material_ptr m_material;
};

typedef std::shared_ptr<Mesh> mesh_ptr;