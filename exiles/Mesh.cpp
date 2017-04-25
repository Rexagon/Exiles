#include "Mesh.h"

Mesh::Mesh(const std::string & name) :
	m_name(name)
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_BBO);
	glGenBuffers(1, &m_EBO);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_BBO);
	glDeleteBuffers(1, &m_EBO);
}

void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_numIndices = indices.size();

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// Tangent attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Mesh::InitBoneData(const std::vector<VertexBoneData>& boneData)
{
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_BBO);
	glBufferData(GL_ARRAY_BUFFER, boneData.size() * sizeof(VertexBoneData), &boneData[0], GL_STATIC_DRAW);

	// Weights attribute
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)0);
	glEnableVertexAttribArray(4);
	// Indices attribute
	glVertexAttribIPointer(4, 4, GL_INT, sizeof(VertexBoneData), (GLvoid*)(4 * sizeof(float)));
	glEnableVertexAttribArray(5);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	m_material->Bind(0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
