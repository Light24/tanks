#include "texture-manager.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager *TextureManager::m_Instance;
TextureManager *TextureManager::GetInstance()
{
	if (!m_Instance)
		m_Instance = new TextureManager();

	return m_Instance;
}


void TextureManager::SetTextureDir(const char *in_TextureDir)
{
	m_TextureDir = in_TextureDir;
}

sf::Texture *TextureManager::GetTexture(const char *in_TextureName)
{
	if (m_Textures[std::string(in_TextureName ? in_TextureName : "")])
		return m_Textures[std::string(in_TextureName ? in_TextureName : "")];

	sf::Texture *texture = new sf::Texture();
	if (in_TextureName)
		texture->loadFromFile(std::string(m_TextureDir).append(in_TextureName));
	m_Textures[std::string(in_TextureName ? in_TextureName : "")] = texture;

	return m_Textures[std::string(in_TextureName ? in_TextureName : "")];
}
