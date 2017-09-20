#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "Layer.h"
#include "Tileset.h"
#include "Vector2.h"
#include <vector>


//Tile object layer
class TileLayer : public Layer {
public:
	TileLayer(int tileSize, int mapWidth, int mapHeight, const Tileset& tileSet);

	virtual void update();
	virtual void render();
	virtual void clean(){}
	
	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
	std::vector<std::vector<int>>* getTileIDs() { return &m_tileIDs; }
	void setTileSize(int tileSize) { m_tileSize = tileSize; }
	int getTileSize() { return m_tileSize; }

	void setMapWidth(int w) { m_mapWidth = w; }
	void setMapHeight(int h) { m_mapHeight = h; }
	int getMapWidth() { return m_mapWidth; }
	int getMapHeight() { return m_mapHeight; }

	Tileset* getTileset() { return &m_tileSet; }

private:

	int m_columns;
	int m_rows;
	int m_tileSize;

	Tileset m_tileSet;

	int m_mapWidth;
	int m_mapHeight;

	std::vector<std::vector<int>> m_tileIDs;
};

#endif