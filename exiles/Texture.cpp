#include "Texture.h"

#include <SFML/Graphics.hpp>

#include "FileSystem.h"
#include "Log.h"

// Texture //
/////////////

Texture::Texture()
{
	glGenTextures(1, &m_id);
#ifdef DEBUG
	Log::Write("[DEBUG] texture created");
#endif // DEBUG
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
#ifdef DEBUG
	Log::Write("[DEBUG] texture deleted");
#endif // DEBUG
}

void Texture::LoadFromFile(const std::string & path)
{
	std::string data = FileSystem::GetFileData(path);
	LoadFromMemory(data.c_str(), data.size());
}

void Texture::LoadFromMemory(const void * data, unsigned int size)
{
	sf::Image image;

	if (!image.loadFromMemory(data, size)) {
		throw std::runtime_error("Unable to load texture");
	}

	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

GLuint Texture::GetId()
{
	return m_id;
}


// TextureAsset //
//////////////////

TextureAsset::TextureAsset(const std::string & path)
{
	SetFilePath(path);
}

asset_ptr TextureAsset::Load()
{
	if (!m_texture) {
		m_texture = std::make_shared<Texture>();
		m_texture->LoadFromFile(GetFilePath());
	}

	return m_texture;
}
