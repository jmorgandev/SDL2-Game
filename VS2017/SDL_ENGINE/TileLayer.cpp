#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"
#include "Camera.h"

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const Tileset& tileSet) {
	m_tileSize = tileSize;
	m_mapWidth = mapWidth;
	m_mapHeight = mapHeight;
	m_tileSet = tileSet;
	m_position.setZero();

	m_columns = mapWidth;
	m_rows = mapHeight;
}

void TileLayer::update() {
	
}

//Render tiles offset by the camera position
void TileLayer::render() {

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			SDL_Rect tile = { (j-2) * m_tileSize, (i-1) * m_tileSize, m_tileSize, m_tileSize };
			if (!Camera::instance()->inBounds(&tile)) continue;

			int id = m_tileIDs[i][j];

			id--;
			
			TextureManager::instance()->drawTile(m_tileSet.name,
												((j * m_tileSize) - (Camera::instance()->getPosition().getX())),
												((i * m_tileSize) - (Camera::instance()->getPosition().getY())),
												m_tileSize,
												(id - (m_tileSet.firstGridID - 1)) / m_tileSet.columns,
												(id - (m_tileSet.firstGridID - 1)) % m_tileSet.columns,
												Game::instance()->getRenderer());

			//((j * m_tileSize) - x2), ((i * m_tileSize - y2)
		}
	}
}