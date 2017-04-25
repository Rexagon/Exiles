#pragma once

#include "Texture.h"

class Material
{
public:
	Material();
	Material(texture_ptr diffuseTexture, texture_ptr normalsTexture, texture_ptr specularTexture);
	~Material();

	void Bind(unsigned int unit);


	void SetDuffuseTexture(texture_ptr texture) { m_diffuseTexture = texture; }
	texture_ptr GetDiffuseTexture() { return m_diffuseTexture; }

	void SetNormalsTexture(texture_ptr texture) { m_normalsTexture = texture; }
	texture_ptr GetNormalsTexture() { return m_normalsTexture; }

	void SetSpecularTexture(texture_ptr texture) { m_specularTexture = texture; }
	texture_ptr GetSpecularTexture() { return m_specularTexture; }
private:
	texture_ptr m_diffuseTexture;
	texture_ptr m_normalsTexture;
	texture_ptr m_specularTexture;
};

typedef std::shared_ptr<Material> material_ptr;