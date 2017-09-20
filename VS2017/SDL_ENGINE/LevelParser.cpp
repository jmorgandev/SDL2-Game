#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "base64.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "Camera.h"

#include "LevelTrigger.h"

#include <zlib.h>

//Parse in the XML file for Tile and Object handling
Level* LevelParser::parseLevel(const char *levelFile) {
	TiXmlDocument LEVEL_FILE;

	LEVEL_FILE.LoadFile(levelFile);

	Level* pLevel = new Level();
	m_pLevel = pLevel;

	TiXmlElement* pRoot = LEVEL_FILE.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("tileset")) parseTileset(e, pLevel->getTileset());
			if (e->Value() == std::string("layer")) parseTileLayer(e, pLevel->getLayers(), pLevel->getTileset());
			if (e->Value() == std::string("objectgroup")) parseObjectLayer(e, pLevel->getLayers());
	}
	return pLevel;
}

//Parse the tileset being used in the XML file
void LevelParser::parseTileset(TiXmlElement* pTilesetRoot, Tileset* pTileset) {
	TextureManager::instance()->loadTexture(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), Game::instance()->getRenderer());
		
	Tileset& tileset = *pTileset;

	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileW);
	pTilesetRoot->Attribute("tileheight", &tileset.tileH);
	tileset.name = pTilesetRoot->Attribute("name");

	tileset.columns = tileset.width / tileset.tileW;
}

//Parse any tileLayers inside the XML file
void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const Tileset* pTileset) {
	bool collidable = false;
	
	TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTileset);

	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	TiXmlElement* pDataNode = NULL;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("properties")) {
			for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
				if (property->Value() == std::string("property")) {
					if (property->Attribute("name") == std::string("collidable")) collidable = true;
				}
			}
		}
		if (e->Value() == std::string("data")) pDataNode = e;
	}

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
		std::string t = e->ToText()->Value();
		decodedIDs = base64_decode(t);
	}

	uLongf idSize = m_width* m_height* sizeof(int);

	std::vector<int> ids(m_width * m_height);
	uncompress((Bytef*)&ids[0], &idSize, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(m_width);

	for (int i = 0; i < m_height; i++) {
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++) {
		for (int cols = 0; cols < m_width; cols++) {
			data[rows][cols] = ids[rows * m_width + cols];
		}
	}
	pTileLayer->setTileIDs(data);
	if (collidable) {
		pTileLayer->setType(LAYER_COLLISION);
		m_pLevel->m_collisionLayer = pTileLayer;
	}
	else {
		pTileLayer->setType(LAYER_TILE);
		pLayers->push_back(pTileLayer);
	}
	
}

//Parse Object layer from XML file
void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers) {
	ObjectLayer* pObjectLayer = new ObjectLayer();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("object")) {
			int x = 0, y = 0, width = 0, height = 0, callbackID = 0;
			std::string textureID, levelID;

			e->Attribute("x", &x);
			e->Attribute("y", &y);
			e->Attribute("width", &width);
			e->Attribute("height", &height);
			GameObject* pGameObject = GameObjectFactory::instance()->create(e->Attribute("type"));

			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()) {
				if (properties->Value() == std::string("properties")) {
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
						if (property->Value() == std::string("property")) {
							if (property->Attribute("name") == std::string("textureID")) textureID = property->Attribute("value");
							else if (property->Attribute("name") == std::string("callbackID")) property->Attribute("value", &callbackID);
							else if (property->Attribute("name") == std::string("newX")) {
								int newX;
								property->Attribute("value", &newX);
								static_cast<LevelTrigger*>(pGameObject)->setNewX(newX);
							}
							else if (property->Attribute("name") == std::string("newY")) {
								int newY;
								property->Attribute("value", &newY);
								static_cast<LevelTrigger*>(pGameObject)->setNewY(newY);
							}
							else if (property->Attribute("name") == std::string("levelID")) {
								std::string levelID = property->Attribute("value");
								static_cast<LevelTrigger*>(pGameObject)->setLevelID(levelID);
							}
						}
					}
				}
			}

			pGameObject->load(LoadParameters(x, y, width, height, textureID, 0, 0, callbackID));
			pGameObject->setCollisionLayer(m_pLevel->getCollisionLayer());
			if (pGameObject->getTag() == "PLAYER") m_pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}
	pObjectLayer->setType(LAYER_OBJECT);
	pLayers->push_back(pObjectLayer);
}