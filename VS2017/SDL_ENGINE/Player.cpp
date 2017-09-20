#include "Player.h"
#include "Game.h"
#include <algorithm>
#include "CollisionManager.h"
#include "Camera.h"
#include "Level.h"
#include "ProjectileHandler.h"

Player::Player() {
	m_maxTimer = m_invulnerableTimer = 60;
	m_invulnerable = false;
}

//Load gameobject
void Player::load(const LoadParameters parameters) {
	Game::instance()->addEventHandler(this);
	SDLGameObject::load(parameters);
	m_health = 4;
	m_collider = { (int)m_position.getX(), (int)m_position.getY() - 4, 10, 8 };
	m_speed = 1;
	m_direction = Vector2f(0, 1);
	Camera::instance()->setTarget(&m_position, &m_scale);
	m_victory = false;
}

//Offset drawing by camera position
void Player::draw() {
	m_position.modX(-Camera::instance()->getPosition().getX());
	m_position.modY(-Camera::instance()->getPosition().getY());
	SDLGameObject::draw();
	m_position.modX(Camera::instance()->getPosition().getX());
	m_position.modY(Camera::instance()->getPosition().getY());
}

//Handle animation and movement
void Player::update() {
	m_collider.x = m_position.getX() + 3;
	m_collider.y = m_position.getY() + 10;

	if (m_invulnerable) {
		m_invulnerableTimer--;
		if (m_invulnerableTimer <= 0) {
			m_invulnerableTimer = m_maxTimer;
			m_invulnerable = false;
		}
	}

	doMovement();

	m_moving = (m_velocity.length() > 0) ? true : false;
	if (m_moving) m_currentFrame = int((SDL_GetTicks() / 175) % 4);
	else m_currentFrame = 0;

	m_velocity.setZero();
}


void Player::clean() {
	Game::instance()->removeEventHandler(this);
}

//Take the most recent key on the key stack and move based on it
//Check collisions with the collision layer
void Player::doMovement() {
	if (!m_keyList.empty()) {
		switch (m_keyList.back()) {
		case SDL_SCANCODE_W: m_direction = Vector2f(0, -1); m_currentRow = 1; m_flip = SDL_FLIP_NONE; m_velocity.setY(-m_speed); break;
		case SDL_SCANCODE_S: m_direction = Vector2f(0, 1); m_currentRow = 0; m_flip = SDL_FLIP_NONE; m_velocity.setY(m_speed); break;
		case SDL_SCANCODE_A: m_direction = Vector2f(-1, 0); m_currentRow = 2; m_flip = SDL_FLIP_NONE; m_velocity.setX(-m_speed); break;
		case SDL_SCANCODE_D: m_direction = Vector2f(1, 0); m_currentRow = 2; m_flip = SDL_FLIP_HORIZONTAL; m_velocity.setX(m_speed); break;
		}
	}
	Vector2f newPos(m_collider.x, m_collider.y);
	Vector2f scale(m_collider.w, m_collider.h);
	newPos += m_velocity;

	if (CollisionManager::instance()->checkTileCollision(newPos, scale, m_collisionLayer)) {
		m_velocity.setZero();
	}
	m_position += m_velocity;
	Camera::instance()->scrollCamera(m_velocity);
}

//Handle keyboard events sent by the Event Poller
void Player::OnKeyboardEvent(const SDL_KeyboardEvent& e) {
	if (e.repeat == 0) {
		switch (e.keysym.scancode) {
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_D:
			if (e.state == SDL_PRESSED) m_keyList.push_back(e.keysym.scancode);
			else m_keyList.erase(std::remove(m_keyList.begin(), m_keyList.end(), e.keysym.scancode), m_keyList.end()); break;

		case SDL_SCANCODE_K:
			if(e.state == SDL_PRESSED)
				ProjectileHandler::instance()->addPlayerProjectile(m_position.getX()+4.5, m_position.getY()+7, 9, 9, "playerProjectile", m_direction, 2, m_collisionLayer);
			break;
		}
	}
}

//Remove health if colliding with an enemy projectile or an enemy
//Load the victory state if colliding with a relic
void Player::collision(std::string tag) {
	if (tag == "ENEMY_PROJECTILE" || tag == "ENEMY") {
		if (!m_invulnerable) {
			m_health -= 1;
			if (m_health == 0) {
				m_dead = true;
			}
			else {
				m_invulnerable = true;
			}
		}
	}
	if (tag == "RELIC") {
		m_victory = true;
	}
}