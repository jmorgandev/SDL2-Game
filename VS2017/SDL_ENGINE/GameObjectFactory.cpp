#include "GameObjectFactory.h"
#include <stdio.h>

GameObjectFactory* GameObjectFactory::instance() {
	static GameObjectFactory gameObjectFactory_instance;
	return &gameObjectFactory_instance;
}

//Register a BaseCreator type
bool GameObjectFactory::registerType(std::string ID, BaseCreator* pCreator) {
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(ID);
	if (it != m_creators.end()) {
		delete pCreator;
		return false;
	}
	m_creators[ID] = pCreator;
	return true;
}


//Create a gameobject using the appropriate Gameobject creator
GameObject* GameObjectFactory::create(std::string ID) {
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(ID);

	if (it == m_creators.end()) {
		printf("ERROR: Could not find Factory Type \"%s\"\n", ID.c_str());
		return NULL;
	}

	return (*it).second->createGameObject();
}


//Cleanup
void GameObjectFactory::clean() {
	if (!m_creators.empty()) {
		std::map<std::string, BaseCreator*>::iterator it;
		for (it = m_creators.begin(); it != m_creators.end(); it++) {
			delete it->second;
		}
		m_creators.clear();
	}
}