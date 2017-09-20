#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

//Singleton to handle all currently loaded textures, and loading of textures
class TextureManager {
public:
	static TextureManager* instance();

	bool loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int x, int y, int tileSize, int currentRow, int currentFrame, SDL_Renderer* pRenderer);
	void clearTexture(std::string id);
	void clean();

private:
	TextureManager(){}

	std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif