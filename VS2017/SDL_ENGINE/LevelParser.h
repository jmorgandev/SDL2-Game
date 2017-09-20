#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "Level.h"
#include "tinyxml.h"
#include "TileLayer.h"


//Class to parse level XML file
class LevelParser {
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTileset(TiXmlElement* pTilesetRoot, Tileset* pTileset);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const Tileset* pTileset);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers);

	int m_tileSize;
	int m_width;
	int m_height;

	Level* m_pLevel;
};

#endif