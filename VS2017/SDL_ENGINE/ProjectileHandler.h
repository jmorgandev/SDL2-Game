#ifndef PROJECTILE_HANDLER_H
#define PROJECTILE_HANDLER_H

#include "Projectile.h"
#include <vector>
#include "TileLayer.h"


//Handle every projectile in singleton class for easy collision testing
class ProjectileHandler {
public:
	static ProjectileHandler* instance();

	void update();
	void draw();
	void clean();

	void addPlayerProjectile(int x, int y, int width, int height, std::string textureID, Vector2f direction, float speed, TileLayer* collisionLayer);
	void addEnemyProjectile(int x, int y, int width, int height, std::string textureID, Vector2f direction, float speed, TileLayer* collisionLayer);

	std::vector<Projectile*>* getPlayerProjectiles() { return &m_playerProjectiles; }
	std::vector<Projectile*>* getEnemyProjectiles() { return &m_enemyProjectiles; }

private:
	ProjectileHandler(){}
	std::vector<Projectile*> m_playerProjectiles;
	std::vector<Projectile*> m_enemyProjectiles;
};

#endif