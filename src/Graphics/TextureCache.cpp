#include "TextureCache.h"

Texture* TextureCache::getTexture(std::string textureLocation)
{
    if (m_cachedTextures.find(textureLocation) == m_cachedTextures.end())
        m_cachedTextures[textureLocation] = Texture(textureLocation.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    return &m_cachedTextures[textureLocation];
}

void TextureCache::clearTextureCache()
{
    for (auto i = m_cachedTextures.begin(); i != m_cachedTextures.end(); i++)
        i->second.Delete();

    m_cachedTextures.clear();
}
