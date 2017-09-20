#include "ScrollingImage.h"

//Draw once, offset by height, and draw again
//Giving the appearence of a repeating image
void ScrollingImage::draw() {
	SDLGameObject::draw();
	m_position.modY(m_scale.getY());
	SDLGameObject::draw();
	m_position.modY(-m_scale.getY());
}

void ScrollingImage::update() {
	m_position.setY(-int(SDL_GetTicks() / 100) % 144);
}