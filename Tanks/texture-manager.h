#pragma once
#include "animation.h"
#include <map>
#include "SFML/Graphics.hpp"

class TextureManager
{
private:
	TextureManager();
	TextureManager(const TextureManager &) = delete;
	TextureManager(const TextureManager &&) = delete;
	TextureManager &operator= (const TextureManager &) = delete;

public:
	~TextureManager();

	static TextureManager *GetInstance();

public:
	const char *GetTextureDir();
	void SetTextureDir(const char *in_TextureDir);

	sf::Texture *GetTexture(const char *in_TextureName);

public:
	static TextureManager *m_Instance;

	std::string m_TextureDir;
	std::map<std::string, sf::Texture *> m_Textures;
};
