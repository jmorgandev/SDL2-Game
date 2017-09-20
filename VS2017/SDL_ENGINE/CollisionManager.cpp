#include "CollisionManager.h"

#include "Collision.h"
#include "ProjectileHandler.h"
#include "Game.h"

CollisionManager* CollisionManager::instance() {
	static CollisionManager collisionManager_instance;
	return &collisionManager_instance;
}

//Loop through all Enemy created projectiles and check if a collision with the player has happened
void CollisionManager::checkPlayerEnemyProjectile(Player* pPlayer) {
	if (pPlayer == NULL) return;
	std::vector<Projectile*>* enemyProjectiles = ProjectileHandler::instance()->getEnemyProjectiles();
	SDL_Rect projectileBox;
	for (std::vector<Projectile*>::iterator it = enemyProjectiles->begin(); it != enemyProjectiles->end(); it++) {
		projectileBox = { (int)(*it)->getPosition().getX(), (int)(*it)->getPosition().getY(), (int)(*it)->getScale().getX(), (int)(*it)->getScale().getY() };
		if (Collision::RectRect(&pPlayer->getCollisionBox(), &projectileBox)) {
			(*it)->collision("PLAYER");
			pPlayer->collision("ENEMY_PROJECTILE");
		}
	}
}

//Loop through all Enemy game objects and check if a collision with the player has happened
void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects) {
	if (pPlayer == NULL) return;
	SDL_Rect collisionBox;
	for (std::vector<GameObject*>::const_iterator it = objects.begin(); it != objects.end(); it++) {
		if ((*it)->getTag() != "ENEMY") continue;
		collisionBox = { (int)(*it)->getPosition().getX(), (int)(*it)->getPosition().getY(), (int)(*it)->getScale().getX(), (int)(*it)->getScale().getY() };
		if (Collision::RectRect(&pPlayer->getCollisionBox(), &collisionBox)) {
			pPlayer->collision("ENEMY");
		}
	}
}

//Loop through all gameobjects and check if the player has collided with a trigger object or a relic object
bool CollisionManager::checkPlayerTriggerCollision(Player* pPlayer, const std::vector<GameObject*> &objects) {
	if (pPlayer == NULL) return false;
	SDL_Rect collisionBox;
	for (std::vector<GameObject*>::const_iterator it = objects.begin(); it != objects.end(); it++) {
		if ((*it)->getTag() != "TRIGGER" && (*it)->getTag() != "RELIC") continue;
		collisionBox = { (int)(*it)->getPosition().getX(), (int)(*it)->getPosition().getY(), (int)(*it)->getScale().getX(), (int)(*it)->getScale().getY() };
		if (Collision::RectRect(&pPlayer->getCollisionBox(), &collisionBox)) {
			pPlayer->collision("TRIGGER");
			(*it)->collision("PLAYER");
			return true;
		}
	}
	return false;
}

//Loop through all enemy gameobjects and check for collisions with any player projectiles
void CollisionManager::checkEnemyPlayerProjectile(const std::vector<GameObject*> &objects) {
	std::vector<Projectile*>* playerProjectiles = ProjectileHandler::instance()->getPlayerProjectiles();
	SDL_Rect projectileBox, collisionBox;
	for (std::vector<Projectile*>::iterator it = playerProjectiles->begin(); it != playerProjectiles->end(); it++) {
		projectileBox = { (int)(*it)->getPosition().getX(), (int)(*it)->getPosition().getY(), (int)(*it)->getScale().getX(), (int)(*it)->getScale().getY() };
		for (std::vector<GameObject*>::const_iterator e_it = objects.begin(); e_it != objects.end(); e_it++) {
			if ((*e_it)->getTag() != "ENEMY") continue;
			collisionBox = { (int)(*e_it)->getPosition().getX(), (int)(*e_it)->getPosition().getY(), (int)(*e_it)->getScale().getX(), (int)(*e_it)->getScale().getY() };
			if (Collision::RectRect(&projectileBox, &collisionBox)) {
				(*e_it)->collision("PLAYER_PROJECTILE");
				(*it)->collision("ENEMY");
			}
		}
	}
}

//Check collision with a tile by taking in a collision layer
bool CollisionManager::checkTileCollision(Vector2f& pos, Vector2f& scale, TileLayer* collisionLayer) {
	std::vector<std::vector<int>> tiles = *collisionLayer->getTileIDs();

	Vector2f layerPos = collisionLayer->getPosition();

	int x = 0, y = 0, tileid = 0;

	x = layerPos.getX() / collisionLayer->getTileSize();
	y = layerPos.getY() / collisionLayer->getTileSize();
	
	Vector2f start(pos.getX() / collisionLayer->getTileSize(), pos.getY() / collisionLayer->getTileSize());
	Vector2f end((pos.getX() + scale.getX()) / collisionLayer->getTileSize(), (pos.getY() + scale.getY()) / collisionLayer->getTileSize());
	for (int i = start.getX(); i < end.getX(); i++) {
		for (int j = start.getY(); j < end.getY(); j++) {
			tileid = tiles[j + y][i + x];
			if (tileid != 0) return true;
		}
	}
	
	return false;
}