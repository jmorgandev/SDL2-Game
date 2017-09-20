#include "Camera.h"
#include "Game.h"
#include "Collision.h"

Camera* Camera::instance() {
	static Camera camera_instance;
	return &camera_instance;
}

Camera::Camera() : m_position(0,0) {
}

//Set the camera target to a Vector2 Position
void Camera::setTarget(Vector2f* target, Vector2f* targetScale) {
	m_target = target;
	m_targetScale = targetScale;
	m_position.setX((target->getX() + targetScale->getX() / 2) - Game::instance()->getScreenWidth() / 2);
	m_position.setY((target->getY() + targetScale->getY() / 2) - Game::instance()->getScreenHeight() / 2);
}

//Recenter the camera on it's current target
void Camera::centerView() {
	m_position.setX((m_target->getX() + m_targetScale->getX() / 2) - Game::instance()->getScreenWidth() / 2);
	m_position.setY((m_target->getY() + m_targetScale->getY() / 2) - Game::instance()->getScreenHeight() / 2);
}

//Check if an object is within the camera's viewport
bool Camera::inBounds(SDL_Rect* object) {
	SDL_Rect camera = { m_position.getX(), m_position.getY(), 
						Game::instance()->getScreenWidth() + Game::instance()->getScreenWidth() / 2, 
						Game::instance()->getScreenHeight() + Game::instance()->getScreenHeight() / 2 };

	return (Collision::RectRect(&camera, object));
}
