#include "EventHandler.h"

//Send the correct event to the receiving functions
void EventHandler::handleEvent(const SDL_Event &e) {
	switch (e.type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		OnKeyboardEvent(e.key);
		break;
	case SDL_JOYAXISMOTION:
		OnJoystickAxisEvent(e.jaxis);
		break;
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		OnJoystickButtonEvent(e.jbutton);
		break;
	case SDL_MOUSEMOTION:
		OnMouseMotionEvent(e.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		OnMouseButtonEvent(e.button);
		break;
	}
}