#include "ResourceManager.h"
#include <string>

TextureCache ResourceManager::m_textureCache;

SDL_Texture* ResourceManager::getTexture(SDL_Renderer *renderer, const std::string& texturePath)
{
	if (texturePath == "NONE")
		return nullptr;

	return m_textureCache.getTexture(renderer, texturePath);
}