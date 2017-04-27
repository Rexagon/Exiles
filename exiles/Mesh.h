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

	// �������������� ������� ������
	//@ ���������� ������� �� ��������� ���������
	void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	// �������������� ������� ������
	//@ ���������� ������� ���� ������ �������������
	void InitBoneData(const std::vector<VertexBoneData>& boneData);

	// ������ ���������
	//@ ����� ����� ���������� ������ �������� ������� � 1� �������
	void Draw();

	// ������������� ��������, ������� ����� �������� ����� ����������
	void SetMaterial(material_ptr material) { m_material = material; }

	material_ptr GetMaterial() { return m_material; }

	std::string GetName() const { return m_name; }
private:
	std::string m_name;

	GLuint m_VAO;

	// ������� ��� ������
	GLuint m_VBO;
	GLuint m_EBO;

	// ������� ��� ������
	GLuint m_BBO;

	unsigned int m_numIndices;

	material_ptr m_material;
};

typedef std::shared_ptr<Mesh> mesh_ptr;