#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Player.h"
#include "TileLayer.h"

//Sends collision events to relevent game objects
class CollisionManager {
public:
	static CollisionManager* instance();

	void checkPlayerEnemyProjectile(Player* pPlayer);
	void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
	void checkEnemyPlayerProjectile(const std::vector<GameObject*> &objects);
	bool checkTileCollision(Vector2f& pos, Vector2f& scale, TileLayer* collisionLayer);
	bool checkPlayerTriggerCollision(Player* pPlayer, const std::vector<GameObject*> &objects);

private:
	CollisionManager(){}
};

#endif