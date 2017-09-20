#include "TextureManager.h"

TextureManager* TextureManager::instance() {
	static TextureManager textureManager_instance;
	return &textureManager_instance;
}


//Load a texture into the map
bool TextureManager::loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == NULL) {
		printf("\nError: %s", SDL_GetError());
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	pTempSurface = NULL;

	if (pTexture == NULL) {
		printf("\nCould not create texture from surface. Error: %s", SDL_GetError());
		return false;
	}

	m_textureMap[id] = pTexture;
	return true;
}

//Draw texture to renderer
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect sourceRect, destinationRect;

	sourceRect.x = sourceRect.y = 0;
	sourceRect.w = destinationRect.w = width;
	sourceRect.h = destinationRect.h = height;
	destinationRect.x = x;
	destinationRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &sourceRect, &destinationRect, 0, 0, flip);
}

//Draw a frame of an object to renderer
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect sourceRect, destinationRect;

	sourceRect.x = width * currentFrame;
	sourceRect.y = height * currentRow;
	sourceRect.w = destinationRect.w = width;
	sourceRect.h = destinationRect.h = height;
	destinationRect.x = x;
	destinationRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &sourceRect, &destinationRect, 0, 0, flip);
}

//Draw a tile to the renderer
void TextureManager::drawTile(std::string id, int x, int y, int tileSize, int currentRow, int currentFrame, SDL_Renderer* pRenderer) {
	SDL_Rect sourceRect, destinationRect;
	
	sourceRect.x = tileSize * currentFrame;
	sourceRect.y = tileSize * currentRow;
	sourceRect.w = sourceRect.h = destinationRect.w = destinationRect.h = tileSize;
	destinationRect.x = x;
	destinationRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &sourceRect, &destinationRect, 0, 0, SDL_FLIP_NONE);
}

//remove texture from map
void TextureManager::clearTexture(std::string id) {
	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
}


//clean everything
void TextureManager::clean() {
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_textureMap.begin(); it != m_textureMap.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	m_textureMap.clear();
}