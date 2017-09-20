#ifndef BUTTON_H
#define BUTTON_H

#include "SDLGameObject.h"
#include "EventHandler.h"
#include "BaseCreator.h"

//Menu Button Class
class Button : public SDLGameObject, public EventHandler {
public:
	Button(){}
	virtual ~Button(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID() { return m_callbackID; }

private:
	virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
	virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent& e);

	enum ButtonState { MOUSE_OUT, MOUSE_OVER, MOUSE_DOWN };
	ButtonState m_buttonState;

	int m_callbackID;
	void(*m_callback)();
};

class ButtonCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new Button(); }
};

#endif