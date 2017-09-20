#include "Enemy.h"
#include "Game.h"
#include <algorithm>
#include "CollisionManager.h"
#include "Camera.h"
#include "Level.h"
#include "ProjectileHandler.h"
#include "LevelManager.h"

Enemy::Enemy() {
}

//Load gameobject
void Enemy::load(const LoadParameters parameters) {
	SDLGameObject::load(parameters);
	m_health = 2;
	m_collider = { (int)m_position.getX(), (int)m_position.getY(), 16, 16 };
	m_speed = 0.25;
	m_target = Vector2f(m_position.getX(), m_position.getY());

	m_attackTimer = m_maxTimer = 120;
}

//Offset the drawing by the Camera position
void Enemy::draw() {
	m_position.modX(-Camera::instance()->getPosition().getX());
	m_position.modY(-Camera::instance()->getPosition().getY());
	SDLGameObject::draw();
	m_position.modX(Camera::instance()->getPosition().getX());
	m_position.modY(Camera::instance()->getPosition().getY());
}

//Search for the player, then move toward the player
//Also check for tile collisions
void Enemy::update() {
	m_collider.x = m_position.getX();
	m_collider.y = m_position.getY();

	if (LevelManager::instance()->getCurrentLevel()->getPlayer() != NULL) {
		if (m_found) {
			m_target = LevelManager::instance()->getCurrentLevel()->getPlayer()->getPosition();
		}
		else {
			if (m_position.distance(LevelManager::instance()->getCurrentLevel()->getPlayer()->getPosition()) < 64) {
				m_target = LevelManager::instance()->getCurrentLevel()->getPlayer()->getPosition();
				if (!m_found) m_found = true;
			}
			else m_found = false;
		}
	}
	else m_found = false;

	if (m_found) {
		attack();
		if (m_position.distance(m_target) <= 10) {
			m_velocity.setZero();
		}
		else {
			m_velocity = m_target - m_position;
			m_velocity.normalize();
			m_velocity /= 4;
		}
	}

	Vector2f newPos(m_position.getX(), m_position.getY());

	newPos.modX(m_velocity.getX());
	if (CollisionManager::instance()->checkTileCollision(newPos, m_scale, m_collisionLayer)) {
		m_velocity.setX(0);
		newPos.setX(m_position.getX());
	}
	else m_position.setX(newPos.getX());

	newPos.modY(m_velocity.getY());
	if (CollisionManager::instance()->checkTileCollision(newPos, m_scale, m_collisionLayer)) {
		m_velocity.setY(0);
		newPos.setY(m_position.getY());
	}
	else m_position.setY(newPos.getY());

	m_velocity.setZero();
}

void Enemy::clean() {
}

//Remove health if a collision with a player projectile has occurred
void Enemy::collision(std::string tag) {
	if (tag == "PLAYER_PROJECTILE") {
		m_health -= 1;
		if (m_health == 0) {
			m_dead = true;
		}
		else {
			
		}
	}
}

//Add enemy projectiles in an expanding ring around the enemy
void Enemy::attack() {
	m_attackTimer--;
	if (m_attackTimer <= 0) {

		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(0,-1), 1, m_collisionLayer);
		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(0, 1), 1, m_collisionLayer);
		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(-1, 0), 1, m_collisionLayer);
		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(1, 0), 1, m_collisionLayer);

		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(-0.5, -0.5), 1, m_collisionLayer);
		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(0.5, -0.5), 1, m_collisionLayer);
		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(-0.5, 0.5), 1, m_collisionLayer);
		ProjectileHandler::instance()->addEnemyProjectile(m_position.getX() + 6, m_position.getY() + 6, 8, 8, "enemyProjectile", Vector2f(0.5, 0.5), 1, m_collisionLayer);

		m_attackTimer = m_maxTimer;
	}
}