#pragma once

#include <string>
#include <map>

#include <GL\glew.h>

#include "AssetManager.h"
#include "Math.h"

class ShaderPart;

class Shader : public Asset
{
public:
	Shader();
	~Shader();

	// ”станавливает этот шейдер как текущий дл€ отрисовки
	void Bind();

	// ”станавливает никакой шейдер дл€ отрисовки
	void Unbind();

	// ”станавливает входной атрибут дл€ вершинного шейдера на нужную позицию
	void SetAttribute(const std::string& name, unsigned int index);

	// ќбъ€вл€ет входное значение дл€ шейдера
	void AddUniform(const std::string& name);

	// ќбъ€вл€ет входное значение дл€ шейдера если такого нет и возвращает его id
	GLuint GetUniformLocation(const std::string& name);


	// SetUniform - объ€вл€ют переменную в шейдере типа с именем name если такой нет 
	//				и устанавливают еЄ значение в соответствующее

	void SetUniform(const std::string& name, int u);
	void SetUniform(const std::string& name, float u);
	void SetUniform(const std::string& name, const vec2& u);
	void SetUniform(const std::string& name, const ivec2& u);
	void SetUniform(const std::string& name, const vec3& u);
	void SetUniform(const std::string& name, const ivec3& u);


	// SetUniformArray - объ€вл€ют массив в шейдере с именем name если такого нет 
	//					 и устанавливают его длину и значение в соответствующие

	void SetUniformArray(const std::string& name, int* arr, int size);
	void SetUniformArray(const std::string& name, float* arr, int size);
	void SetUniformArray(const std::string& name, vec2* arr, int size);
	void SetUniformArray(const std::string& name, ivec2* arr, int size);
	void SetUniformArray(const std::string& name, vec3* arr, int size);
	void SetUniformArray(const std::string& name, ivec3* arr, int size);
private:
	friend class ShaderAsset;

	void AttachPart(ShaderPart* part);
	bool LinkProgram();

	GLuint m_id;
	unsigned int m_shaderCount;

	std::map<std::string, GLint> m_uniformLocations;
};

typedef std::shared_ptr<Shader> shader_ptr;


class ShaderAsset : public AssetFactory
{
public:
	ShaderAsset(const std::string& vertexPart, const std::string& fragmentPart);
	ShaderAsset(const std::string& vertexPart, const std::string& geometryPart, const std::string& fragmentPart);

	asset_ptr Load() override;
private:
	shader_ptr m_shader;

	std::string m_vertexPart;
	std::string m_fragmentPart;
	std::string m_geometryPart;

	ShaderPart* GetShaderPart(const std::string& name, GLenum type);
	static std::map<std::string, std::unique_ptr<ShaderPart>> m_shaderParts;
};