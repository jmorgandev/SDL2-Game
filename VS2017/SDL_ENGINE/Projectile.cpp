#include "Projectile.h"
#include "Camera.h"

//Load gameobject and set frame depending on velocity
void Projectile::load(const LoadParameters parameters, Vector2f direction, float speed, std::string tag) {
	SDLGameObject::load(parameters);
	m_speed = speed;
	m_velocity = Vector2f(direction.getX() * m_speed, direction.getY() * m_speed);
	if (m_velocity.getY() < 0) m_currentFrame = 0;
	if (m_velocity.getY() > 0) m_currentFrame = 1;
	if (m_velocity.getX() < 0) m_currentFrame = 2;
	if (m_velocity.getX() > 0) m_currentFrame = 3;
	m_tag = tag;
}

//Offset drawing from camera position
void Projectile::draw() {
	m_position.modX(-Camera::instance()->getPosition().getX());
	m_position.modY(-Camera::instance()->getPosition().getY());
	SDLGameObject::draw();
	m_position.modX(Camera::instance()->getPosition().getX());
	m_position.modY(Camera::instance()->getPosition().getY());
}

//Prevent the player and enemy's own projectiles from colliding with themselves
void Projectile::collision(std::string tag) {
	if (tag == "PLAYER" && m_tag != "PLAYER_PROJECTILE") m_destroyed = true;
	if (tag == "ENEMY" && m_tag != "ENEMY_PROJECTILE") m_destroyed = true;
	if (tag == "TILE") m_destroyed = true;
}