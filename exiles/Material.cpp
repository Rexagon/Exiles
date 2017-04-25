#include "Material.h"

Material::Material() :
	m_diffuseTexture(nullptr), m_normalsTexture(nullptr), m_specularTexture(nullptr)
{
}

Material::Material(texture_ptr diffuseTexture, texture_ptr normalsTexture, texture_ptr specularTexture) :
	m_diffuseTexture(diffuseTexture),
	m_normalsTexture(normalsTexture),
	m_specularTexture(specularTexture) 
{
}

Material::~Material()
{
	m_diffuseTexture.reset();
	m_normalsTexture.reset();
	m_specularTexture.reset();
}

void Material::Bind(unsigned int unit)
{
	if (m_diffuseTexture) {
		m_diffuseTexture->Bind(unit);
	}
	if (m_normalsTexture) {
		m_normalsTexture->Bind(unit + 1);
	}
	if (m_specularTexture) {
		m_specularTexture->Bind(unit + 2);
	}
}
