#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

//Menu state base class, handling callbacks for menu buttons

class MenuState : public GameState {
protected:
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	std::vector<Callback> m_callbacks;
};

#endif