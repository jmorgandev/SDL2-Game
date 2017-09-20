#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>

//Eventhandler interface for sending SDL events
class EventHandler {
public:

	virtual ~EventHandler() {}

	void handleEvent(const SDL_Event& e);

	virtual void OnKeyboardEvent(const SDL_KeyboardEvent& e) {}

	virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent& e) {}
	virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent& e) {}

	virtual void OnJoystickAxisEvent(const SDL_JoyAxisEvent& e){}
	virtual void OnJoystickButtonEvent(const SDL_JoyButtonEvent& e){}
	
};

#endif