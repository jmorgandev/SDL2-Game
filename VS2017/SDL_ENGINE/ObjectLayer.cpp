#include "ObjectLayer.h"
#include "Player.h"
#include "LevelManager.h"

//Update every gameobject in layer
void ObjectLayer::update() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();) {
		if ((*it)->toRemove()) {
			if ((*it)->getTag() == "PLAYER") LevelManager::instance()->getCurrentLevel()->setPlayer(NULL);
			(*it)->clean();
			delete *it;
			it = m_gameObjects.erase(it);
		}
		else {
			(*it)->update();
			it++;
		}
	}
}

//Render every gameobject in layer
void ObjectLayer::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

//Clean up gameobjects in layer
void ObjectLayer::clean() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		(*it)->clean();
		delete *it;
	}
	m_gameObjects.clear();
}
