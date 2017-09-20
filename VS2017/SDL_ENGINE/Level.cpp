#include "Level.h"
#include "CollisionManager.h"
#include "ObjectLayer.h"
#include "ProjectileHandler.h"

Level::Level() {
	m_PlayerRef = NULL;
}

//Render all layers in the level
void Level::render() {
	for (int i = 0; i < m_layers.size(); i++) {
		m_layers[i]->render();
		if (m_layers[i]->getType() == LAYER_OBJECT) ProjectileHandler::instance()->draw();
	}
}

//Update all layers in the level, including collision checking
//Break the loop if a player has collided with a load level trigger
void Level::update() {
	for (int i = 0; i < m_layers.size(); i++) {
		m_layers[i]->update();
		if (m_layers[i]->getType() == LAYER_OBJECT) { 
			ObjectLayer* pLayer = dynamic_cast<ObjectLayer*>(m_layers[i]);
			ProjectileHandler::instance()->update();
			CollisionManager::instance()->checkPlayerEnemyCollision(m_PlayerRef, *pLayer->getGameObjects());
			if (CollisionManager::instance()->checkPlayerTriggerCollision(m_PlayerRef, *pLayer->getGameObjects())) break;
			CollisionManager::instance()->checkPlayerEnemyProjectile(m_PlayerRef);
			CollisionManager::instance()->checkEnemyPlayerProjectile(*pLayer->getGameObjects());
		}
		m_collisionLayer->update();
	}
}

//Clean everything
void Level::clean() {
	ProjectileHandler::instance()->clean();
	for (std::vector<Layer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++) {
		(*it)->clean();
		delete *it;
	}
	m_layers.clear();
	
	m_collisionLayer->clean();
	delete m_collisionLayer;
}