#pragma once

#include <GL\glew.h>

#include "AssetManager.h"

class Texture : public Asset
{
public:
	Texture();
	virtual ~Texture();
	
	// Загружает изображение с помощью FileSystem
	void LoadFromFile(const std::string& path);

	// Загружает изображение из памяти
	void LoadFromMemory(const void* data, unsigned int size);

	// Привязывает текстуру к GL_TEXTUREunit
	void Bind(unsigned int unit);

	GLuint GetId();
private:
	GLuint m_id;
};

typedef std::shared_ptr<Texture> texture_ptr;


class TextureAsset : public AssetFactory
{
public:
	TextureAsset(const std::string& path);

	asset_ptr Load() override;
private:
	texture_ptr m_texture;
};