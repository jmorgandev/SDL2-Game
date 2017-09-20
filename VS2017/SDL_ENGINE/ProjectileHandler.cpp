#include "ProjectileHandler.h"
#include "Game.h"
#include "CollisionManager.h"

ProjectileHandler* ProjectileHandler::instance() {
	static ProjectileHandler projectileHandler_instance;
	return &projectileHandler_instance;
}

//Update all projectiles and test for collisions
void ProjectileHandler::update() {
	for (std::vector<Projectile*>::iterator it = m_playerProjectiles.begin(); it != m_playerProjectiles.end();) {
		if (CollisionManager::instance()->checkTileCollision((*it)->getPosition(), (*it)->getScale(), (*it)->getCollisionLayer())) (*it)->collision("TILE");
		
		if ((*it)->toRemove()) {
			delete *it;
			it = m_playerProjectiles.erase(it);
		}
		else {
			(*it)->update();
			it++;
		}
	}
	for (std::vector<Projectile*>::iterator it = m_enemyProjectiles.begin(); it != m_enemyProjectiles.end();) {
		if (CollisionManager::instance()->checkTileCollision((*it)->getPosition(), (*it)->getScale(), (*it)->getCollisionLayer())) (*it)->collision("TILE");

		if ((*it)->toRemove()) {
			delete *it;
			it = m_enemyProjectiles.erase(it);
		}
		else {
			(*it)->update();
			it++;
		}
	}
}

//Draw all projectiles
void ProjectileHandler::draw() {
	for (std::vector<Projectile*>::iterator it = m_playerProjectiles.begin(); it != m_playerProjectiles.end(); it++) {
		(*it)->draw();
	}
	for (std::vector<Projectile*>::iterator it = m_enemyProjectiles.begin(); it != m_enemyProjectiles.end(); it++) {
		(*it)->draw();
	}
}

//Add a player projectile
void ProjectileHandler::addPlayerProjectile(int x, int y, int width, int height, std::string textureID, Vector2f direction, float speed, TileLayer* collisionLayer) {
	Projectile* pProjectile = new Projectile();
	pProjectile->load(LoadParameters(x, y, width, height, textureID, 0, 0), direction, speed, "PLAYER_PROJECTILE");
	pProjectile->setCollisionLayer(collisionLayer);
	m_playerProjectiles.push_back(pProjectile);
}

//Add an enemy projectile
void ProjectileHandler::addEnemyProjectile(int x, int y, int width, int height, std::string textureID, Vector2f direction, float speed, TileLayer* collisionLayer) {
	Projectile* pProjectile = new Projectile();
	pProjectile->load(LoadParameters(x, y, width, height, textureID, 0, 0), direction, speed, "ENEMY_PROJECTILE");
	pProjectile->setCollisionLayer(collisionLayer);
	m_enemyProjectiles.push_back(pProjectile);
}

//Clean up everything
void ProjectileHandler::clean() {
	for (std::vector<Projectile*>::iterator it = m_playerProjectiles.begin(); it != m_playerProjectiles.end(); it++) {
		delete *it;
	}
	m_playerProjectiles.clear();
	for (std::vector<Projectile*>::iterator it = m_enemyProjectiles.begin(); it != m_enemyProjectiles.end(); it++) {
		delete *it;
	}
	m_enemyProjectiles.clear();
}