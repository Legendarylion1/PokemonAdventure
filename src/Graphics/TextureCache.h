#pragma once

#include <unordered_map>
#include <string>
#include "Texture/Texture.h"

class TextureCache
{
public:
	TextureCache() {};
	~TextureCache() { clearTextureCache(); };

	Texture* getTexture(std::string textureLocation);
	void clearTextureCache();

private:
	std::unordered_map<std::string, Texture> m_cachedTextures;
};