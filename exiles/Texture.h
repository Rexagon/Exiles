#pragma once

#include <GL\glew.h>

#include "AssetManager.h"

class Texture : public Asset
{
public:
	Texture();
	virtual ~Texture();

	void LoadFromFile(const std::string& path);
	void LoadFromMemory(const void* data, unsigned int size);

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