#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Tileset.h"
#include "TileLayer.h"
#include "Player.h"



//Level class to display the current game level
class Level {
public:

	~Level(){}

	void update();
	void render();
	void clean();

	std::vector<Layer*>* getLayers() { return &m_layers; }
	TileLayer* getCollisionLayer() { return m_collisionLayer; }
	Tileset* getTileset() { return &m_tileSet; }

	Player* getPlayer() { return m_PlayerRef; }
	void setPlayer(Player* pPlayer) { m_PlayerRef = pPlayer; }

private:
	Level();

	Tileset m_tileSet;
	std::vector<Layer*> m_layers;
	TileLayer* m_collisionLayer;

	Player* m_PlayerRef;

	friend class LevelParser;
};

#endif