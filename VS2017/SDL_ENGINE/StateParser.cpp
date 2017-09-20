#include "StateParser.h"
#include <stdio.h>
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "LoadParameters.h"

//Parse the state from the given XML file
bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<std::string> *pTextureIDs, std::vector<GameObject*> *pObjects) {
	TiXmlDocument XML_FILE;

	if (!XML_FILE.LoadFile(stateFile)) {
		printf("ERROR: Could not load %s\n", stateFile);
		printf("XML ERROR: %s\n", XML_FILE.ErrorDesc());
		return false;
	}

	TiXmlElement* pRoot = XML_FILE.RootElement();
	TiXmlElement* pStateRoot = NULL;
	TiXmlElement* pTextureRoot = NULL;
	TiXmlElement* pObjectRoot = NULL;

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == stateID) pStateRoot = e;
	}

	if (pStateRoot == NULL) {
		printf("XML ERROR: Could not find State Root in %s\n", stateFile);
		return false;
	}

	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("TEXTURES")) pTextureRoot = e;
		if (e->Value() == std::string("OBJECTS")) pObjectRoot = e;
	}

	if (pTextureRoot == NULL) {
		printf("XML ERROR: Could not find Texture Root in %s\n", stateFile);
		return false;
	}
	if (pObjectRoot == NULL) {
		printf("XML ERROR: Could not find Object Root in %s\n", stateFile);
		return false;
	}

	parseTextures(pTextureRoot, pTextureIDs);
	parseObjects(pObjectRoot, pObjects);

	return true;
}

//Parse textures from the texture section of the XML file
void StateParser::parseTextures(TiXmlElement* pRoot, std::vector<std::string> *pTextureIDs) {
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		std::string fileName = e->Attribute("filename");
		std::string ID = e->Attribute("ID");
		pTextureIDs->push_back(ID);
		TextureManager::instance()->loadTexture(fileName, ID, Game::instance()->getRenderer());
	}
}

//Parse objects from the object section of the XML file
void StateParser::parseObjects(TiXmlElement* pRoot, std::vector<GameObject*> *pObjects) {
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		int x = 0, y = 0, width = 0, height = 0, row = 0, frame = 0, callbackID = 0;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("row", &row);
		e->Attribute("frame", &frame);
		e->Attribute("callbackID", &callbackID);
		textureID = e->Attribute("textureID");

		GameObject* pGameObject = GameObjectFactory::instance()->create(e->Attribute("type"));
		pGameObject->load(LoadParameters(x, y, width, height, textureID, row, frame, callbackID));
		pObjects->push_back(pGameObject);
	}
}