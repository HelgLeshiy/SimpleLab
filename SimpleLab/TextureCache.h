#pragma once
#include <map>
#include <SDL2/SDL.h>

class TextureCache
{
public:
	TextureCache(void);
	~TextureCache(void);

	SDL_Texture* getTexture(SDL_Renderer *renderer, const std::string& textureName);

private:
	std::map<std::string, SDL_Texture*> m_textures;
};
