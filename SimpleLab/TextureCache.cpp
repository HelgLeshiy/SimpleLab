#include "TextureCache.h"

#include "SDL2/SDL_image.h"
#include <stdexcept>

TextureCache::TextureCache(void)
{
}


TextureCache::~TextureCache(void)
{
	for (auto it : m_textures)
		SDL_DestroyTexture(it.second);
}


SDL_Texture* TextureCache::getTexture(SDL_Renderer *renderer, const std::string& textureName)
{
	auto mit = m_textures.find(textureName);
	if (mit == m_textures.end())
	{
		SDL_Surface *temp = IMG_Load(textureName.c_str());
		if (!temp)
			throw std::runtime_error(std::string(SDL_GetError()));
		SDL_SetColorKey(temp, 1, 0xFFFFFF);
		SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, temp);
		m_textures.insert(std::make_pair(textureName, newTexture));
		SDL_FreeSurface(temp);
		return newTexture;
	}

	return mit->second;
}