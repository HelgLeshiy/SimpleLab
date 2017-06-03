#pragma once
#include "TextureCache.h"

class ResourceManager
{
public:
	static SDL_Texture* getTexture(SDL_Renderer *renderer, const std::string& texturePath);

private:
	static TextureCache m_textureCache;
};