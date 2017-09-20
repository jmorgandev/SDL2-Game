#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

//Load gameobject
void SDLGameObject::load(const LoadParameters parameters) {
	m_position = Vector2f(parameters.getX(), parameters.getY());
	m_scale = Vector2f(parameters.getWidth(), parameters.getHeight());
	m_velocity.setZero();
	m_textureID = parameters.getTextureID();
	m_currentRow = parameters.getCurrentRow();
	m_currentFrame = parameters.getCurrentFrame();
	m_flip = SDL_FLIP_NONE;
}


//Draw gameobject if drawable
void SDLGameObject::draw() {
	if(m_drawable) TextureManager::instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_scale.getX(), m_scale.getY(), m_currentRow, m_currentFrame, Game::instance()->getRenderer(), m_flip);
}

//Default gameobject update
void SDLGameObject::update() {
	m_position += m_velocity;
}