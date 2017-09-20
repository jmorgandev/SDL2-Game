#include "Button.h"
#include "Game.h"

//Load GameObject
void Button::load(const LoadParameters parameters) {
	Game::instance()->addEventHandler(this);
	SDLGameObject::load(parameters);
	m_callbackID = parameters.getCallbackID();
	m_buttonState = MOUSE_OUT;
}

void Button::draw() {
	SDLGameObject::draw();
}

//Set the current frame depending on the state of the button
void Button::update() {
	m_currentFrame = m_buttonState;
}

void Button::clean() {
	Game::instance()->removeEventHandler(this);
}

//Change the button state if the mouse is held over the button
void Button::OnMouseMotionEvent(const SDL_MouseMotionEvent& e) {
	if (e.x < m_position.getX() + m_scale.getX() && e.x > m_position.getX() &&
		e.y < m_position.getY() + m_scale.getY() && e.y > m_position.getY()) {
		m_buttonState = MOUSE_OVER;
	}
	else {
		m_buttonState = MOUSE_OUT;
	}
}

//Execute the callback function if the mouse is over and clicked
void Button::OnMouseButtonEvent(const SDL_MouseButtonEvent& e) {
	if (e.button == SDL_BUTTON_LEFT) {
		switch (e.state) {
		case SDL_PRESSED:
			if (m_buttonState == MOUSE_OVER) m_buttonState = MOUSE_DOWN;
			break;
		case SDL_RELEASED:
			if (m_buttonState == MOUSE_DOWN) {
				m_buttonState = MOUSE_OVER;
				m_callback();
			}
			break;
		}
	}
}